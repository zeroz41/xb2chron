#ifndef CLASSES_EVENT_ATTACHACTORGF_H
#define CLASSES_EVENT_ATTACHACTORGF_H

#include "classes/event/AttachActorBase.h"

namespace event { enum ATTACH_TYPE : int; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace event {
// table 0x7100B3C360
class AttachActorGf : public ::event::AttachActorBase {
public:
    virtual ~AttachActorGf();  // slot 0
    virtual void setEffectCaster(bool, unsigned int);  // slot 3
    virtual void setEffectMount(bool, unsigned int, char const*, mm::Vec3 const&, bool, event::ATTACH_TYPE);  // slot 4
    virtual void getMtpMat(mm::Mat44&, char const*) const;  // slot 7
    virtual void getEfpMat(mm::Mat44&, char const*) const;  // slot 10
    virtual void getBoneMat(mm::Mat44&, char const*) const;  // slot 13
};
}  // namespace event

#endif
