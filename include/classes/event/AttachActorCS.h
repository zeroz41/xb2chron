#ifndef CLASSES_EVENT_ATTACHACTORCS_H
#define CLASSES_EVENT_ATTACHACTORCS_H

#include "classes/event/AttachActorBase.h"
#include "mm/mtl/FixedVector.h"

enum EVT_attachtype : int;
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace event {
// table 0x7100B3C2C0
class AttachActorCS : public ::event::AttachActorBase {
public:
    virtual ~AttachActorCS();  // slot 0
    virtual void setEffectCaster(bool, unsigned int);  // slot 3
    virtual void setEffectMount(bool, unsigned int, char const*, mm::Vec3 const&, bool, EVT_attachtype);  // slot 4
    virtual bool getMtpMat(mm::Mat44&, char const*) const;  // slot 7
    virtual bool getEfpMat(mm::Mat44&, char const*) const;  // slot 10
    virtual bool getBoneMat(mm::Mat44&, char const*) const;  // slot 13

    // an effect mount setEffectMount allocates (0x50 bytes, the handle first); the name is not the original's
    struct Mount {
        unsigned int m_handle;
        unsigned char pad_4[0x4c];
    };
    long pad_a0;  // setEffectCaster passes the casters to fw::EffectManager::setParam while it is not -1
    // the effect handles setEffectCaster allocates (4 bytes each) and the mounts; the destructor releases each
    // through the slot (first entry until none is left); the names are not the original's
    mm::mtl::FixedVector<unsigned int*, 128> m_casters;  // 0xa8, count 0x4a8
    mm::mtl::FixedVector<Mount*, 128> m_mounts;          // 0x4b0, count 0x8b0
};
}  // namespace event

#endif
