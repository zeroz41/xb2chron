#ifndef CLASSES_EVENT_ATTACHACTORBASE_H
#define CLASSES_EVENT_ATTACHACTORBASE_H

enum EVT_attachtype : int;
#include "mm/Mat44.h"
#include "classes/event/IAttachActor.h"
namespace mm { class Vec3; }

namespace event {
// table 0x7100B3C220
class AttachActorBase : public ::event::IAttachActor {
public:
    virtual ~AttachActorBase() {}  // slot 0
    virtual const char* getName() const;  // slot 2: returns m_name
    virtual void setEffectCaster(bool, unsigned int) = 0;  // slot 3
    virtual void setEffectMount(bool, unsigned int, char const*, mm::Vec3 const&, bool, EVT_attachtype) = 0;  // slot 4
    virtual bool getMat(mm::Mat44&) const;  // slot 5: copies m_mat, returns true
    virtual bool getMtpMatGlobal(mm::Mat44&, char const*) const;  // slot 6
    virtual bool getMtpMat(mm::Mat44&, char const*) const = 0;  // slot 7
    virtual bool hasMtp(char const*) const;  // slot 8
    virtual bool getEfpMatGlobal(mm::Mat44&, char const*) const;  // slot 9
    virtual bool getEfpMat(mm::Mat44&, char const*) const = 0;  // slot 10
    virtual bool hasEfp(char const*) const;  // slot 11
    virtual bool getBoneMatGlobal(mm::Mat44&, char const*) const;  // slot 12
    virtual bool getBoneMat(mm::Mat44&, char const*) const = 0;  // slot 13
    virtual bool hasBone(char const*) const;  // slot 14 (evt_eff.play stores its result with setBool)
    // slots 15-17 are inline (this unit keeps their copies after the destructor's): each tries the motion
    // point, then the effect point, then the bone of that name
    virtual bool getMultipleMatGlobal(mm::Mat44& mat, char const* name) const {
        return getMtpMatGlobal(mat, name) || getEfpMatGlobal(mat, name) || getBoneMatGlobal(mat, name);
    }  // slot 15
    virtual bool getMultipleMat(mm::Mat44& mat, char const* name) const {
        return getMtpMat(mat, name) || getEfpMat(mat, name) || getBoneMat(mat, name);
    }  // slot 16
    virtual bool hasMultiple(char const* name) const {
        return hasMtp(name) || hasEfp(name) || hasBone(name);
    }  // slot 17

    // the actor's name (getName returns it); the name is not the original's
    char m_name[0x50 - 0x8];  // 0x8
    unsigned char pad_50[0x60 - 0x50];
    // the actor's matrix getMat copies; the name is not the original's
    mm::Mat44 m_mat;  // 0x60
};
}  // namespace event

#endif
