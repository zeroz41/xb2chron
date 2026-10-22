#ifndef CLASSES_FW_COLIMOVEOBJECT_H
#define CLASSES_FW_COLIMOVEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "classes/fw/ColiObject.h"

namespace fw { class ColiCharacterInfo; }
namespace fw { class ReferenceFrame; }

namespace fw {
// table 0x7100B41140
class ColiMoveObject : public ::fw::ColiObject {
public:
    ColiMoveObject() : m_dir(mm::Vec3::zero), m_moveFlags(0) {}
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void postUpdate();  // slot 4
    virtual void setDir(mm::Vec3 const&);  // slot 5
    // a character's collision object, registered with the ColiManager, that follows `frame`
    static ColiMoveObject* createColiCharacter(ColiCharacterInfo const& info,
                                               mm::mtl::IntrusivePtr<fw::ReferenceFrame> const& frame);
    static mm::mtl::RTTI m_rtti;

    mm::Vec3 m_dir;  // setDir's: the next postUpdate moves the object by it, then clears it
    // bit 1: the next postUpdate's move is accurate (idcoli::IDColiMove::setAccuracy); the move clears it
    unsigned int m_moveFlags;
};
}  // namespace fw

#endif
