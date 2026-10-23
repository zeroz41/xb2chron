#ifndef CLASSES_FW_COLIOBJECT_H
#define CLASSES_FW_COLIOBJECT_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Mat44.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/fw/ReferenceFrame.h"
namespace mm { class Vec3; }
namespace idcoli { class IDColiObj; }
namespace fw { class ColiCharacterInfo; }
namespace fw { class ColiUserData; }
namespace fw { class IColiEventListener; }

namespace fw {
// a collision attribute (idcoli::IDColiParmsBase::isAttr tests it); no value has a name yet
enum ColiAtrr {};
}  // namespace fw

namespace fw {
// table 0x7100B41180; counted (ColiMoveObject::createColiCharacter adds the first reference)
class ColiObject : public mm::mtl::ReferenceObject {
public:
    ColiObject();
    virtual ~ColiObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void update();  // slot 3
    virtual void postUpdate();  // slot 4
    virtual void setDir(mm::Vec3 const&) {}  // slot 5
    bool testAttribute(fw::ColiAtrr attribute) const;
    void setColiObject(idcoli::IDColiObj* coliObj);
    void setHitMaterialFlag(unsigned int flag);
    const mm::Mat44& getMatrix() const;
    void setMatrix(mm::Mat44 const& matrix);
    // gives `object` the character's shape and attributes and the frame it follows (a null object is skipped)
    static void setupColiCharacter(ColiObject* object, ColiCharacterInfo const& info,
                                   mm::mtl::IntrusivePtr<fw::ReferenceFrame> const& frame);
    // the collision of a map's ground from its resource (gf::MapColi::create keeps it, counted)
    static ColiObject* createColiGrand(const void* resource);
    // a character's collision object, registered with the ColiManager, that follows `frame`
    static ColiObject* createColiCharacter(ColiCharacterInfo const& info,
                                           mm::mtl::IntrusivePtr<fw::ReferenceFrame> const& frame);
    // (inline: the name is not the original's; GfComCollider::createColi sets its own)
    void setUserData(fw::ColiUserData* userData) { m_userData = userData; }
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_10[0x10];
    idcoli::IDColiObj* m_coliObj;                       // setColiObject's
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;  // setupColiCharacter's; postUpdate follows it
    // setupColiCharacter's, from ColiCharacterInfo (at 4); at 0 it flags one sync (bit 0 of m_flags);
    // ColiMoveObject::postUpdate moves only while it is not 0
    int m_followType;
    unsigned short m_flags;
    unsigned char pad_36[0x12];
    // setupColiCharacter's, from ColiCharacterInfo: which events reach m_listener (enter needs bit 0; the names
    // of these three are not the original's)
    unsigned int m_eventMask;
    unsigned char pad_4c[0x4];
    fw::IColiEventListener* m_listener;  // enter, leave and contact hand their events to it
    fw::ColiUserData* m_userData;        // its owner's: GfComCollider::enter tests the other object's
    unsigned char pad_60[0x40];
    mm::Mat44 m_matrix;  // getMatrix's
    unsigned char pad_e0[0x20];
};
}  // namespace fw

#endif
