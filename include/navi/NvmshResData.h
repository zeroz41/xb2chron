#ifndef NAVI_NVMSHRESDATA_H
#define NAVI_NVMSHRESDATA_H

#include "mm/Vec3.h"
#include "mtl/MemManager.h"

namespace navi {

// one block of NvmshResMan's resource memory (no table; NvmshResMemMan's constructor makes 38 in a 0x5F0
// allocation, the first one covering the whole buffer). The field names are not the original's.
class NvmshResMemObj {
public:
    NvmshResMemObj() : m_prev(nullptr), m_next(nullptr), m_flags(0), m_data(nullptr), m_size(0) {}

    NvmshResMemObj* m_prev;
    NvmshResMemObj* m_next;
    // bit 0: in use (NvmshResMan::update skips it), bit 1: set by NvmshResMan::update on the first free block
    // that has a next one, bit 2: NvmshResData::update resets its navi data and clears it
    unsigned int m_flags;
    unsigned char* m_data;
    unsigned int m_size;
};

// NvmshResMan's resource memory blocks (no table; NvmshResMan holds one at 0x48 and deletes it). The names are
// not the original's.
class NvmshResMemMan {
public:
    // a list of blocks linked through their m_prev/m_next (the names are not the original's)
    struct ObjList {
        NvmshResMemObj* m_head;
        NvmshResMemObj* m_tail;

        void pushBack(NvmshResMemObj* obj) {
            if (m_tail != nullptr) {
                m_tail->m_next = obj;
                obj->m_prev = m_tail;
                m_tail = obj;
            } else {
                m_head = obj;
                m_tail = obj;
                obj->m_prev = nullptr;
            }
            obj->m_next = nullptr;
        }
        void erase(NvmshResMemObj* obj) {
            NvmshResMemObj* prev = obj->m_prev;
            NvmshResMemObj* next = obj->m_next;
            if (prev == nullptr) {
                if (next != nullptr) {
                    m_head = next;
                    next->m_prev = nullptr;
                } else {
                    m_tail = nullptr;
                    m_head = nullptr;
                }
            } else if (next == nullptr) {
                m_tail = prev;
                prev->m_next = nullptr;
            } else {
                prev->m_next = next;
                obj->m_next->m_prev = obj->m_prev;
            }
        }
    };

    ~NvmshResMemMan() {
        if (m_objs != nullptr) {
            mtl::MemManager::deallocate(m_objs, 0, false);
        }
    }
    // frees obj and merges it with a free neighbour (the merged one goes back to the free list)
    void clearMemObj(NvmshResMemObj* obj);

    NvmshResMemObj* m_objs;  // the 38 blocks' allocation
    ObjList m_freeList;  // blocks holding no memory
    ObjList m_usedList;  // the buffer's blocks in address order, free (m_flags bit 0 clear) or in use
};

// a navigation resource's blocks, located from its head (no table; NvmshResData holds two at 0x10).
// NvmshUtil::getPoliCenter's NvmshResObj: its +0x8/0x10/0x18/0x20 are m_res, m_head and the first two blocks.
// The member names are not the original's.
class NvmshResObj {
public:
    // a vertex (block 1, 6 bytes each): grid coordinates scaled by Head::m_scale from Head's origin
    // (bit-fields: getPoliCenter reads x and y as one 32-bit word)
    struct Vertex {
        unsigned short x : 16;
        unsigned short y : 16;
        unsigned short z : 16;
    };
    // the offsets of a resource's blocks (the name is not the original's)
    struct Head {
        unsigned char pad_0[0x28];
        unsigned int m_blockOfs0;
        unsigned char pad_2C[0x4];
        unsigned int m_blockOfs1;
        unsigned char pad_34[0xC];
        unsigned int m_blockOfs6;
        unsigned char pad_44[0x4];
        unsigned int m_blockOfs3;
        unsigned char pad_4C[0x4];
        unsigned int m_blockOfs7;
        unsigned int m_blockOfs2;
        unsigned char pad_58[0x4];
        float m_originX;  // the vertices' origin and grid scale (getPoliCenter; the names are not the original's)
        float m_originY;
        float m_originZ;
        float m_scale;
        unsigned int m_blockOfs4;
        unsigned char pad_70[0x4];
        unsigned int m_blockOfs5;

        // a vertex's position (the name is not the original's)
        void calcPos(mm::Vec3& pos, const Vertex& v) const {
            pos = mm::Vec3((unsigned int)v.x, (unsigned int)v.y, (unsigned int)v.z) * m_scale +
                  mm::Vec3(m_originX, m_originY, m_originZ);
        }
    };
    // a polygon (block 0, 8 bytes each): its vertex count and the offset of its vertex indices from m_res
    struct Poly {
        unsigned char m_num;
        unsigned char pad_1[0x3];
        unsigned int m_idxOfs;
    };

    NvmshResObj() : m_valid(0), m_res(nullptr), m_head(nullptr) {
        for (int i = 0; i < 8; i++) {
            m_blocks[i] = nullptr;
        }
    }
    void clear() {
        m_valid = 0;
        m_res = nullptr;
    }
    void set(unsigned char* res) {
        setBlocks(res);
        m_valid = 1;
    }
    // as set, but ORs the valid bit in (createNavi)
    void create(unsigned char* res) {
        setBlocks(res);
        m_valid |= 1;
    }
    void setBlocks(unsigned char* res) {
        m_res = res;
        m_head = reinterpret_cast<const Head*>(res);
        m_blocks[0] = res + m_head->m_blockOfs0;
        m_blocks[1] = res + m_head->m_blockOfs1;
        m_blocks[2] = res + m_head->m_blockOfs2;
        m_blocks[6] = res + m_head->m_blockOfs6;
        m_blocks[3] = res + m_head->m_blockOfs3;
        m_blocks[7] = res + m_head->m_blockOfs7;
        m_blocks[4] = res + m_head->m_blockOfs4;
        m_blocks[5] = res + m_head->m_blockOfs5;
    }

    int m_valid;
    unsigned char* m_res;
    const Head* m_head;
    unsigned char* m_blocks[8];
};

// one navigation resource NvmshResMan holds (no table; NvmshResMan holds 26 from 0xB0). The names are not the
// original's.
class NvmshResData {
public:
    // the read's description (the name is not the original's): bit 0 of m_flags a first navi, bit 1 a second one
    // at m_secondOfs (or first when bit 0 is clear)
    struct ReadInfo {
        unsigned int m_flags;
        unsigned char pad_4[0x8];
        unsigned int m_secondOfs;
    };

    NvmshResData() : m_flags(0), m_counter(0), m_info(nullptr), pad_C0(0), m_memObj(nullptr) {}
    void update(NvmshResMemMan* memMan);
    void resetNavi();
    void createNavi();

    // bit 0: set up, bit 2: released (update frees it after 4 frames), bit 4: used this frame
    unsigned int m_flags;
    short m_counter;  // frames since it was last used (or released)
    const ReadInfo* m_info;
    NvmshResObj m_navi[2];
    int pad_C0;  // zeroed by the constructor, nothing here reads it
    NvmshResMemObj* m_memObj;  // the block holding the resource
};

}  // namespace navi

#endif
