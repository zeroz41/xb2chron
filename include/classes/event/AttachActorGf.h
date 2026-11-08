#ifndef CLASSES_EVENT_ATTACHACTORGF_H
#define CLASSES_EVENT_ATTACHACTORGF_H

#include "classes/event/AttachActorBase.h"

enum EVT_attachtype : int;
namespace mm { class Mat44; }
namespace mm { class Vec3; }
namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3C360
class AttachActorGf : public ::event::AttachActorBase {
public:
    virtual ~AttachActorGf();  // slot 0
    virtual void setEffectCaster(bool, unsigned int);  // slot 3
    virtual void setEffectMount(bool, unsigned int, char const*, mm::Vec3 const&, bool, EVT_attachtype);  // slot 4
    virtual bool getMtpMat(mm::Mat44&, char const*) const;  // slot 7
    virtual bool getEfpMat(mm::Mat44&, char const*) const;  // slot 10
    virtual bool getBoneMat(mm::Mat44&, char const*) const;  // slot 13

    // the object whose effect caster setEffectCaster and setEffectMount use (-1: none); the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0xa0
};
}  // namespace event

#endif
