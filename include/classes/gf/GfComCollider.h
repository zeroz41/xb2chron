#ifndef CLASSES_GF_GFCOMCOLLIDER_H
#define CLASSES_GF_GFCOMCOLLIDER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/IColiEventListener.h"
#include "classes/fw/AnimColPoseModifier.h"
#include "classes/fw/ColiUserData.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComponent.h"
#include "mm/mtl/Vector.h"

namespace fw { class ColiObject; }
namespace fw { class ColiCharacterInfo; }

namespace gf {
// table 0x7100B66220; its fw::IColiEventListener at 0x10 (that table: enter, leave, contact); an object's
// collision objects, by index, whose events it hands its object as messages
class GfComCollider : public ::gf::GfComponent, public ::fw::IColiEventListener {
public:
    // table 0x7100B66298; what its collision objects carry for it (m_rtti's base is fw::ColiUserData's)
    class UserData : public ::fw::ColiUserData {
    public:
        UserData(GfComCollider* owner) : m_owner(owner) {}
        virtual const mm::mtl::RTTI* getRTTI() const;  // slot 0
        static mm::mtl::RTTI m_rtti;

        GfComCollider* m_owner;  // the collider holding it (the name is not the original's)
    };
    // what setup takes (setup reads nothing of it)
    struct SetupInfo {};

    GfComCollider();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComCollider();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void enter(fw::IColiEventListener::EnterInfo const&);  // slot 5
    virtual void leave(fw::IColiEventListener::LeaveInfo const&);  // slot 6
    virtual void contact(fw::IColiEventListener::EnterInfo const&);  // slot 7
    void setup(const SetupInfo& info);
    void cleanup();
    void createColiCharacter(unsigned int index, const fw::ColiCharacterInfo& info,
                             mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
    void createColiMoveCharacter(unsigned int index, const fw::ColiCharacterInfo& info,
                                 mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
    // the collision object at index made by create from info, following frame (the transform's frame when none)
    template <typename Info, typename Create>
    void createColi(const Create& create, unsigned int index, const Info& info,
                    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);
    static mm::mtl::RTTI m_rtti;

    mm::mtl::Vector<fw::ColiObject*> m_coliObjects;  // its collision objects
    UserData m_userData;                             // the user data its collision objects carry
    fw::AnimColPoseModifier m_poseModifier;          // poses a kind 5 collision from the model (the name is not the original's)
};
}  // namespace gf

#endif
