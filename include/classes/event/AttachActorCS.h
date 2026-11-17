#ifndef CLASSES_EVENT_ATTACHACTORCS_H
#define CLASSES_EVENT_ATTACHACTORCS_H

#include "classes/event/AttachActorBase.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"
#include "mm/Vec3.h"

enum EVT_attachtype : int;
namespace mm { class Mat44; }
namespace gf { class GF_OBJ_HANDLE; }

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

    // moves the casters and mounts from the current object to handle (CharaObj's model stream)
    void setActor(gf::GF_OBJ_HANDLE* handle);

    // an effect mount setEffectMount allocates (0x50 bytes): what it passed to AttachUtil::setMount, so setActor
    // can mount it again on another object (the type and field names are not the original's; the position is
    // taken by value: its copy is read right after the allocation)
    struct Mount {
        Mount(unsigned int id, const char* name, mm::Vec3 pos, bool flag, EVT_attachtype type)
            : m_handle(id), m_name(name), m_pos(pos), m_flag(flag), m_type(type) {}
        unsigned int m_handle;
        mm::mtl::FixStr<32> m_name;  // 0x4
        mm::Vec3 m_pos;              // 0x30
        bool m_flag;                 // 0x40
        EVT_attachtype m_type;       // 0x44
    };
    // the object whose effect caster the casters and mounts use (-1: none; setActor sets it); the name is not the
    // original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0xa0
    // the effect handles setEffectCaster allocates (4 bytes each) and the mounts; the destructor releases each
    // through the slot (first entry until none is left); the names are not the original's
    mm::mtl::FixedVector<unsigned int*, 128> m_casters;  // 0xa8, count 0x4a8
    mm::mtl::FixedVector<Mount*, 128> m_mounts;          // 0x4b0, count 0x8b0
};
}  // namespace event

#endif
