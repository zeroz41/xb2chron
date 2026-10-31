#ifndef CLASSES_IDCOLI_IDCOLIOBJGRAND_H
#define CLASSES_IDCOLI_IDCOLIOBJGRAND_H

#include "classes/idcoli/IDColiObj.h"
#include "idcoli/IDColiGrandMesh.h"
#include "mtl/AllocHandle.h"

namespace mm { class Vec3; }

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
    // its grand mesh work (IDColiParmsGrand and IDColiGrandObj reach the object through it)
    wrkIDCmfWork m_work;  // 0x50
    // 0x100 bytes: IDColiManager::createColiGrand allocates it so
};
}  // namespace idcoli

#endif
