#ifndef IDCOLI_IDCOLITREETOP_H
#define IDCOLI_IDCOLITREETOP_H

#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/ColiLinkList.h"

namespace mm { class Vec3; }


namespace idcoli {

// only the members other files call are declared so far (its owners' destructors call the destructor; its body is
// empty). Fields are not declared yet.
class IDColiTreeTop {
public:
    IDColiTreeTop();
    ~IDColiTreeTop();
    // links obj into the cell the box max/min falls in; returns the cell's index
    int setupTreeList(IDColiTreeObj* obj, const mm::Vec3& max, const mm::Vec3& min);
    void updateTree();
    ColiLinkList<IDColiTreeObj>* getObjList(int x, int z, int level);
    void begin();
    void end();

    // per level: the first cell's index in m_objList, and the cells per side (this unit's .rodata)
    static const unsigned char COLI_TBL_INDEX[5];
    static const unsigned char COLI_TBL_GRID[5];
    // the box of the objects linked this frame (begin resets it to an empty box) and the previous frame's
    // (begin keeps it); the names are not the original's
    mm::Vec3 m_max;  // 0x0
    mm::Vec3 m_min;  // 0x10
    mm::Vec3 m_prevMax;  // 0x20
    mm::Vec3 m_prevMin;  // 0x30
    unsigned char pad_40[0xF0];
    unsigned long m_cellUsed[6];  // 0x130, a bit per cell of m_objList (releaseDefTree)
    unsigned int m_flags;  // 0x160, begin clears bit 0 (the name is not the original's)
    unsigned char pad_164[4];
    ColiLinkList<IDColiTreeObj> m_objList[341];  // 0x168, the cells of the five levels (1 + 4 + 16 + 64 + 256)
    unsigned char pad_16b8[0x1558];  // IDColiManager's constructor allocates 0x2C10
};

}  // namespace idcoli

#endif
