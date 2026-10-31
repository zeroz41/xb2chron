#ifndef NAVI_NVMSHRESDATA_H
#define NAVI_NVMSHRESDATA_H

#include "mm/Vec3.h"
#include <new>
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
        ObjList() : m_head(nullptr), m_tail(nullptr) {}

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

    // the 38 blocks from handle, the first one holding all of data and in use order, the rest free (NvmshResMan's
    // constructor inlines it; the parameter names are not the original's)
    NvmshResMemMan(unsigned char* data, unsigned int size, mtl::ALLOC_HANDLE handle) : m_freeList(), m_usedList() {
        NvmshResMemObj* objs = static_cast<NvmshResMemObj*>(
            mtl::MemManager::allocate(handle, sizeof(NvmshResMemObj) * 38, 0x40, false, "no name", 0));
        m_objs = objs;
        for (int i = 0; i < 38; i++) {
            new (&objs[i]) NvmshResMemObj();
        }
        objs[0].m_data = data;
        objs[0].m_size = size;
        m_usedList.pushBack(&objs[0]);
        for (int i = 1; i < 38; i++) {
            m_freeList.pushBack(&objs[i]);
        }
    }
    ~NvmshResMemMan() {
        if (m_objs != nullptr) {
            mtl::MemManager::deallocate(m_objs, 0, false);
        }
    }
    // frees obj and merges it with a free neighbour (the merged one goes back to the free list)
    void clearMemObj(NvmshResMemObj* obj);
    // the first free block of at least size bytes, cut to size (the rest goes to a block from the free list
    // after it), marked in use; null when there is none (NvmshResMan::createNaviDataRead; the name is not the
    // original's)
    NvmshResMemObj* allocMemObj(unsigned int size) {
        for (NvmshResMemObj* obj = m_usedList.m_head; obj != nullptr; obj = obj->m_next) {
            if (!(obj->m_flags & 1) && obj->m_size >= size) {
                unsigned int rest = obj->m_size - size;
                if (rest != 0) {
                    NvmshResMemObj* split = m_freeList.m_head;
                    if (split == nullptr) {
                        return nullptr;
                    }
                    obj->m_size = size;
                    split->m_size = rest;
                    split->m_data = obj->m_data + size;
                    m_freeList.erase(split);
                    split->m_flags = 0;
                    split->m_prev = nullptr;
                    split->m_next = nullptr;
                    NvmshResMemObj* next = obj->m_next;
                    obj->m_next = split;
                    split->m_prev = obj;
                    if (next != nullptr) {
                        split->m_next = next;
                        next->m_prev = split;
                    } else {
                        split->m_next = nullptr;
                        m_usedList.m_tail = split;
                    }
                }
                obj->m_flags |= 1;
                return obj;
            }
        }
        return nullptr;
    }

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
        unsigned char pad_0[0x8];
        // the resource's grid cell (read as one word by NvmshResMan::calcNaviObjUpdate)
        unsigned int m_cellX : 16;
        unsigned int m_cellY : 16;
        unsigned char pad_C[0x1C];
        unsigned int m_blockOfs0;
        int m_workSize;  // what NvmshResMan::calcNaviObjUpdate sums into _NaviCalcResTbl::m_total
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

// a navi resource's read (the type name is NvmshResMan::createNaviDataRead's mangled signature's, the member
// names are not the original's): bit 0 of m_flags a first navi, bit 1 a second one at m_secondOfs (or first
// when bit 0 is clear)
struct _NvMhAllReadObj {
    unsigned int m_flags;
    unsigned int m_fileOfs;  // where the resource starts in the file
    unsigned int m_size;
    unsigned int m_secondOfs;
};

// one navigation resource NvmshResMan holds (no table; NvmshResMan holds 26 from 0xB0). The names are not the
// original's.
class NvmshResData {
public:
    NvmshResData() : m_flags(0), m_counter(0), m_info(nullptr), m_readArg(0), m_memObj(nullptr) {}
    void update(NvmshResMemMan* memMan);
    void resetNavi();
    void createNavi();

    // bit 0: set up, bit 2: released (update frees it after 4 frames), bit 4: used this frame
    unsigned int m_flags;
    short m_counter;  // frames since it was last used (or released)
    const _NvMhAllReadObj* m_info;
    NvmshResObj m_navi[2];
    int m_readArg;  // createNaviDataRead's last argument (the name is not the original's)
    NvmshResMemObj* m_memObj;  // the block holding the resource
};

// a world of the navigation data (0x40 bytes, from _NvMhAllHead's m_worldOfs; the type name is the mangled
// signatures', the member names are not the original's)
struct _NvMhAllWorldHead {
    int m_gridW;  // the grid's size in cells
    int m_gridH;
    float m_gridSize;  // a cell's size
    unsigned char pad_C[0xC];
    float m_originX;  // the grid's origin
    unsigned char pad_1C[0x4];
    float m_originZ;
    // the grid's cells' reads (one unsigned short per cell: 1 + its _NvMhAllReadObj's index, 0: none), from the
    // root (the name is not the original's)
    unsigned int m_cellOfs;
    unsigned char pad_28[0x4];
    int m_id;  // what resInfoUpdate's world id selects
    unsigned int m_treeOfs;  // the world's tree data, from the root (0: none)
    unsigned char pad_34[0xC];
};

// a world's connection data offsets (0x18 bytes each, from _NvMhAllHead's m_conectOfs; the type name is the
// mangled signatures', the member names are not the original's)
struct _NvMhAllWrdConectHead {
    unsigned int m_layerOfs[2];  // each navi layer's connection data, from the root (0: none)
    unsigned char pad_8[0x10];
};

// the navigation data's root (NvmshResMan's m_allHead; the names are not the original's)
struct _NvMhAllHead {
    unsigned char pad_0[0x4];
    int m_version;  // setupResource takes only 0x1013 (the name is not the original's)
    unsigned int m_readOfs;  // the _NvMhAllReadObj array (the name is not the original's)
    unsigned char pad_C[0x4];
    unsigned int m_worldOfs;  // the _NvMhAllWorldHead array
    int m_worldNum;
    unsigned int m_conectOfs;  // the _NvMhAllWrdConectHead array (0: none)
};

// a navi layer's connection data (from _NvMhAllWrdConectHead; the names are not the original's): block
// offsets from its start, and the count calcConectInfoUpdate sizes its bit table by
struct _NvMhConectData {
    unsigned char pad_0[0x8];
    unsigned int m_blockOfs0;
    unsigned char pad_C[0x4];
    unsigned int m_blockOfs1;
    unsigned char pad_14[0x4];
    unsigned int m_blockOfs2;
    int m_num;
    unsigned int m_blockOfs3;
    unsigned char pad_24[0x4];
    unsigned int m_blockOfs4;
    unsigned char pad_2C[0x4];
    unsigned int m_blockOfs5;
    int m_blockNum5;
    unsigned int m_blockOfs6;
    int m_blockNum6;
    unsigned char pad_40[0x8];
    unsigned int m_blockOfs7;
};

// a world's tree data (from _NvMhAllWorldHead's m_treeOfs; the names are not the original's): block offsets
// from its start, one per navi layer at 0x1C/0x20
struct _NvMhTreeData {
    unsigned char pad_0[0x4];
    unsigned int m_blockOfs0;
    unsigned int m_blockOfs2;
    unsigned char pad_C[0x4];
    unsigned int m_blockOfs3;
    unsigned char pad_14[0x8];
    unsigned int m_layerOfs[2];
};

// the grid around the current position NvmshResMan::calcNaviInfoUpdate sets up (0x60 bytes; the type name is
// NvmshAcObjBase::calcMoveVecRay's mangled signature's, the member names are not the original's)
struct _NaviCalcResInfo {
    // a grid cell
    struct Cell {
        short x;
        short y;
    };

    // the cells by value (the callers read each as one word; the names are not the original's)
    Cell getBase() const { return m_base; }
    Cell getTarget() const { return m_target; }

    const _NvMhAllWorldHead* m_worldHead;
    unsigned char pad_8[0x8];
    mm::Vec3 m_pos;
    mm::Vec3 m_max;  // the 5x5 cells' far corner
    mm::Vec3 m_min;  // the 5x5 cells' near corner
    float m_gridSize;
    float m_invGridSize;
    Cell m_base;  // the 5x5 cells' first one (two before the position's)
    Cell m_target;  // the target's cell
    Cell m_end;  // m_base + 5, clamped to the grid
    Cell m_start;  // m_base, clamped to 0
    unsigned char pad_58[0x8];
};

// a navi layer's resources in the 5x5 cells around the position (0x1C0 bytes, two in NvmshResMan's work
// allocation; the type name is the mangled signatures', the member names are not the original's)
struct _NaviCalcResTbl {
    unsigned int m_mask;  // bit (y * 5 + x): m_objs[] holds the cell's navi
    NvmshResObj* m_objs[25];
    int m_ofs[25];  // each navi's start in the layer's sum of m_objs[]'s 0x2C sizes
    int m_total;
    int m_alignTotal;  // m_total rounded up to 32
    int m_conectSize;  // the connection bit table's size (one bit per connection, rounded up to 32 bytes)
    NvmshResObj* m_targetObj;  // the target cell's navi
    const _NvMhConectData* m_conect;
    const unsigned char* m_conectBlocks[8];
    const _NvMhTreeData* m_tree;
    const unsigned char* m_treeBlocks[4];
    _NaviCalcResInfo* m_info;
};

}  // namespace navi

#endif
