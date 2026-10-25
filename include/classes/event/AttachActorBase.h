#ifndef CLASSES_EVENT_ATTACHACTORBASE_H
#define CLASSES_EVENT_ATTACHACTORBASE_H

namespace event { enum ATTACH_TYPE : int; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace event {
// table 0x7100B3C220
class AttachActorBase {
public:
    virtual ~AttachActorBase();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void setEffectCaster(bool, unsigned int) = 0;  // slot 3
    virtual void setEffectMount(bool, unsigned int, char const*, mm::Vec3 const&, bool, event::ATTACH_TYPE) = 0;  // slot 4
    virtual void getMat(mm::Mat44&) const;  // slot 5
    virtual void getMtpMatGlobal(mm::Mat44&, char const*) const;  // slot 6
    virtual void getMtpMat(mm::Mat44&, char const*) const = 0;  // slot 7
    virtual void hasMtp(char const*) const;  // slot 8
    virtual void getEfpMatGlobal(mm::Mat44&, char const*) const;  // slot 9
    virtual void getEfpMat(mm::Mat44&, char const*) const = 0;  // slot 10
    virtual void hasEfp(char const*) const;  // slot 11
    virtual void getBoneMatGlobal(mm::Mat44&, char const*) const;  // slot 12
    virtual void getBoneMat(mm::Mat44&, char const*) const = 0;  // slot 13
    virtual bool hasBone(char const*) const;  // slot 14 (evt_eff.play stores its result with setBool)
    virtual void getMultipleMatGlobal(mm::Mat44&, char const*) const;  // slot 15
    virtual void getMultipleMat(mm::Mat44&, char const*) const;  // slot 16
    virtual bool hasMultiple(char const*) const;  // slot 17
};
}  // namespace event

#endif
