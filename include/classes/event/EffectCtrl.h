#ifndef CLASSES_EVENT_EFFECTCTRL_H
#define CLASSES_EVENT_EFFECTCTRL_H

#include "classes/event/IAttachActor.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

enum EVT_attachtype : int;

namespace event {
// table 0x7100B3CE50
class EffectCtrl {
public:
    virtual ~EffectCtrl();  // slot 0
    void create(const char* name, unsigned int param);
    void genelate();
    void kill();
    void update();
    void setCaster(IAttachActor* caster);
    void setMount(IAttachActor* actor, const char* name, const mm::Vec3& pos, bool flag, EVT_attachtype type);

    // the effect genelate creates (kill removes it); the name is not the original's
    unsigned int m_effect;  // 0x8
    // the effect handles kill removes and setCaster/setMount hand to the actors; not empty while the effect is
    // alive (1.0.0's ObjectList::isUsingEffect tests it, EffectCtrl::dead reads it); the name is not the original's
    mm::mtl::FixedVector<unsigned int, 64> m_handles;  // 0x10 (count at 0x110)
    // create's arguments: the effect name genelate creates and the second argument; the names are not the original's
    mm::mtl::FixStr<64> m_name;  // 0x118
    unsigned int m_param;  // 0x15c
    // the transform and colour EffectObj's linear commands write (EffectObj::play hands them &EffectObj::m_ctrl);
    // ScriptEffectScale and ScriptEffectColor save and restore m_scale and m_color; the names are not the original's
    mm::Vec3 m_pos;  // 0x160
    mm::Vec3 m_rot;  // 0x170
    mm::Vec3 m_scale;  // 0x180
    mm::Col4 m_color;  // 0x190
    // zeroed by create; update hands pad_1a0 to the handles' SendParam::m_rangeA, pad_1a4 to the live effect's
    // m_valueA and pad_1a8 to both m_flagA; what they hold is not known yet
    float pad_1a0;
    float pad_1a4;
    int pad_1a8;
    unsigned char pad_1ac[0x4];
    // the actor setCaster stores and the one setMount stores, with setMount's other arguments (the names are not
    // the original's)
    IAttachActor* m_caster;  // 0x1b0
    unsigned char pad_1b8[0x8];
    IAttachActor* m_mount;  // 0x1c0
    mm::mtl::FixStr<32> m_mountName;  // 0x1c8
    mm::Vec3 m_mountPos;  // 0x1f0
    bool m_mountFlag;  // 0x200
    EVT_attachtype m_mountType;  // 0x204
    unsigned char pad_208[0x8];
};
}  // namespace event

#endif
