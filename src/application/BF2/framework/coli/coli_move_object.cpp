#include "mm/Mat44.h"
#include "classes/fw/ReferenceFrame.h"
#include "idcoli/IDColiAccMan.h"
#include "idcoli/IDColiMove.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiMoveObject.h"
#include "classes/fw/ColiManager.h"
#include "classes/fw/ColiManager.h"
#include "classes/fw/ColiMoveObject.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw {

ColiMoveObject* ColiMoveObject::createColiCharacter(ColiCharacterInfo const& info,
                                                    mm::mtl::IntrusivePtr<ReferenceFrame> const& frame) {
    idcoli::IDColiAccMan accMan;
    idcoli::IDColiObj* coliObj = accMan.createColiCharacter();
#line 29
    ColiMoveObject* object = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) ColiMoveObject();
    object->addRef();
    object->setColiObject(coliObj);
    object->setHitMaterialFlag(~5u);
    mm::mtl::PtrSingleton<ColiManager>::get()->registObject(object);
    if (object != nullptr) {
        setupColiCharacter(object, info, frame);
    }
    return object;
}

void ColiMoveObject::setDir(mm::Vec3 const& dir) { m_dir = dir; }

void ColiMoveObject::postUpdate() {
    ColiObject::postUpdate();
    if (m_followType == 0) {
        return;
    }
    if (m_coliObj != nullptr) {
        idcoli::IDColiMove move;
        if (m_moveFlags & 2) {
            move.setAccuracy(true);
            m_moveFlags &= ~2u;
        }
        move.moveColi(m_coliObj, m_dir);
        mm::Mat44 matrix = getMatrix();
        const mm::Vec3 moved = move.m_result;
        matrix.m[3][0] = moved.x + matrix.m[3][0];
        matrix.m[3][1] = moved.y + matrix.m[3][1];
        matrix.m[3][2] = moved.z + matrix.m[3][2];
        setMatrix(matrix);
        if (m_frame.get() != nullptr) {
            ReferenceFrame* frame = m_frame.get();
            frame->m_syncFlags = (frame->m_syncFlags & ~7u) | 2;
            Transform& world = frame->m_worldTransform;
            world.position.x = world.position.x + move.m_result.x;
            world.position.y = world.position.y + move.m_result.y;
            world.position.z = world.position.z + move.m_result.z;
        }
    }
    m_dir = mm::Vec3::zero;
}

}  // namespace fw
