#ifndef CLASSES_FW_COLIOBJECT_H
#define CLASSES_FW_COLIOBJECT_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Mat44.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/UniquePtr.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/IColiEventListener.h"
#include "classes/fw/ColiObjUserData.h"
namespace mm { class Vec3; }
namespace idcoli { class IDColiObj; }
namespace fw { class ColiCharacterInfo; }
namespace fw { class ColiUserData; }

namespace fw {
// a collision attribute (idcoli::IDColiParmsBase::isAttr tests it); no value has a name yet
enum ColiAtrr {};
// a collision state bit (idcoli::IDColiParmsBase::isState/setState/clearState take it)
enum ColiState {
    // setActivate(false) sets it, isActivate tests it is clear (the name is not the original's)
    COLI_STATE_INACTIVE = 2,
};
// a collision shape's parameters, its kind first (setupColiCharacter copies ColiCharacterInfo's into a block of the
// kind's size: 0 8 bytes, 1 0x10, 2 0x30, 3 0xC, 5 0x10). The names are not the original's.
class ColiShape {
public:
    int m_kind;
};
// kind 3's: resetCharacter sets both and rebuilds the collision with them
class ColiShapeCharacter : public ColiShape {
public:
    float m_height;
    float m_radius;
};
// how a collision object follows its frame (setColiType); no value has a name yet
enum ColiType {};
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
    bool testState(fw::ColiState state) const;
    void setColiObject(idcoli::IDColiObj* coliObj);
    void setHitMaterialFlag(unsigned int flag);
    unsigned int getHitMaterialFlag() const;
    const mm::Mat44& getMatrix() const;
    void setMatrix(mm::Mat44 const& matrix);
    void setInstantlyMatrix(mm::Mat44 const& matrix);
    void setColiType(fw::ColiType type);
    void setPriority(int priority);
    int getPriority() const;
    void setState(fw::ColiState state);
    void clearState(fw::ColiState state);
    void resetCharacter(float height, float radius);
    void setHandle(unsigned int handle);
    bool isChar() const;
    bool isGrand() const;
    void setActivate(bool activate);
    bool isActivate() const;
    void setAdsorption(float adsorption);
    float getAdsorption() const;
    bool isLanding() const;
    bool isContactWall() const;
    bool getAABB(mm::Vec3& min, mm::Vec3& max) const;
    void enter(fw::IColiEventListener::EnterInfo const& info);
    void leave(fw::IColiEventListener::LeaveInfo const& info);
    void contact(fw::IColiEventListener::EnterInfo const& info);
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

    // its links (the constructor points both at itself; the name is not the original's)
    mm::mtl::IntrusiveListNodeBase m_node;
    idcoli::IDColiObj* m_coliObj;                       // setColiObject's
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;  // setupColiCharacter's; postUpdate follows it
    // setupColiCharacter's, from ColiCharacterInfo (at 4); at 0 it flags one sync (bit 0 of m_flags);
    // ColiMoveObject::postUpdate moves only while it is not 0
    // setColiType's (the field name is not the original's)
    fw::ColiType m_followType;
    unsigned short m_flags;
    unsigned char pad_36[0x2];
    unsigned int pad_38;  // the constructor zeroes it; no reader seen yet
    unsigned char pad_3c[0x4];
    void* pad_40;  // the constructor zeroes it; no reader seen yet
    // setupColiCharacter's, from ColiCharacterInfo: which events reach m_listener (enter needs bit 0; the names
    // of these three are not the original's)
    unsigned int m_eventMask;
    unsigned char pad_4c[0x4];
    fw::IColiEventListener* m_listener;  // enter, leave and contact hand their events to it
    fw::ColiUserData* m_userData;        // its owner's: GfComCollider::enter tests the other object's
    mm::Mat44 pad_60;  // the constructor sets it to Mat44::identity; setMatrix reads it
    mm::Mat44 m_matrix;  // getMatrix's
    // the constructor's is 1; setMatrix scales the matrix it is given by it (the name is not the original's)
    float m_scale;
    unsigned char pad_e4[0x4];
    // setupColiCharacter's copy of its info's shape (the name is not the original's)
    mm::mtl::UniquePtr<ColiShape> m_shape;
    // its user data: setHandle hands it to the collision object with the handle (the name is not the original's)
    fw::ColiObjUserData m_objUserData;
};
}  // namespace fw

#endif
