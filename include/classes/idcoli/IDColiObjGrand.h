#ifndef CLASSES_IDCOLI_IDCOLIOBJGRAND_H
#define CLASSES_IDCOLI_IDCOLIOBJGRAND_H

#include "classes/idcoli/IDColiObj.h"
#include "mtl/AllocHandle.h"

namespace mm { class Vec3; }
namespace idcoli { class IDColiTreeTop; }
namespace idcoli { class IDColiGrdMoveObj; }

namespace idcoli {
// table 0x7100B7F5A0
class IDColiObjGrand : public ::idcoli::IDColiObj {
public:
    IDColiObjGrand();
    virtual ~IDColiObjGrand();  // slot 0
    // updates the moving parts and rebuilds the other tree with them
    virtual void update();  // slot 4
    // widens max/min by its bounds (IDColiAccMan::getGrandAABB; the parameter names are not the original's)
    void getGrandAABB(mm::Vec3& max, mm::Vec3& min) const;
    // builds the grand collision from its data (IDColiManager::createColiGrand; the parameter names are not the
    // original's)
    void createGrand(mtl::ALLOC_HANDLE handle, const void* data);
    unsigned char pad_50[0x70];
    // the moving parts (0x200 bytes each); update updates them and enters them into a tree
    IDColiGrdMoveObj* m_moveObjs;  // 0xC0
    int m_moveObjNum;  // 0xC8
    unsigned char pad_cc[0x14];
    // the destructor destroys both (without freeing them) while m_memBlock is set, then frees m_memBlock; the
    // names are not the original's
    IDColiTreeTop* m_treeTops[2];  // 0xE0
    // the tree update builds is m_treeTops[m_bank == 0]; update then makes it m_bank
    int m_bank;  // 0xF0
    unsigned char pad_f4[4];
    void* m_memBlock;  // 0xF8, the constructor clears it
    // 0x100 bytes: IDColiManager::createColiGrand allocates it so
};
}  // namespace idcoli

#endif
