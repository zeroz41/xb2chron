#ifndef CLASSES_IDCOLI_IDCOLIOBJGRDCHAR_H
#define CLASSES_IDCOLI_IDCOLIOBJGRDCHAR_H

#include "classes/idcoli/IDColiObj.h"
#include "idcoli/IDColiGrandMesh.h"
#include "mm/Vec3.h"

namespace idcoli { class IDColiObjGrand; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }

namespace idcoli {
// table 0x7100B7F5E8
class IDColiObjGrdChar : public ::idcoli::IDColiObj {
public:
    IDColiObjGrdChar();
    virtual ~IDColiObjGrdChar();  // slot 0
    // m_max/m_min become the bounds of all parts
    virtual void update();  // slot 4
    // each part whose grand is enabled is tested with the input taken into the part's space (IDColiInputUtil)
    bool testLine(IDColiResult& result, const IDColiInput& input);
    bool testRay(IDColiResult& result, const IDColiInput& input);
    bool testSphere(IDColiResult& result, const IDColiInput& input);
    bool testCapsule(IDColiResult& result, const IDColiInput& input);
    bool testWallSphere(IDColiResult& result, const IDColiInput& input);
    bool testWallCapsule(IDColiResult& result, const IDColiInput& input);
    // one grand of the character (0xC0 bytes: the destructor and update index them so; createWorkBuffer fills
    // them, IDColiPrimitive::createBasePoli/createBaPosPoli read one through a shape's pointer). The names are
    // not the original's.
    class Part {
    public:
        IDCmfPosData m_posData;  // 0x0
        IDColiObjGrand* m_grand;  // 0xA0, built in m_memBlock (the destructor destroys it)
        const mm::Vec3* m_corners;  // 0xA8, two corners of the data's record (createBasePoli's setup)
        const void* pad_b0;  // createWorkBuffer points it into the data; no reader seen yet
        const void* pad_b8;  // createWorkBuffer points it into the data; no reader seen yet
    };

    // the bounds of all parts (update; the constructor makes them 1 and -1); the names are not the original's
    mm::Vec3 m_max;  // 0x50
    mm::Vec3 m_min;  // 0x60
    void* m_memBlock;  // 0x70, the parts' grands (createWorkBuffer allocates it)
    IDColiObj* m_owner;  // 0x78, createWorkBuffer's object (the name is not the original's)
    Part* m_parts;  // 0x80
    int m_partNum;  // 0x88
    // 0x90 bytes: IDColiManager::createColiGrdChar allocates it so
};
}  // namespace idcoli

#endif
