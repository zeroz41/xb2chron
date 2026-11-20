#ifndef CLASSES_EVENT_CHARAIKUPDATER_H
#define CLASSES_EVENT_CHARAIKUPDATER_H

#include "mm/Vec2.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3C9F0
class CharaIKUpdater {
public:
    CharaIKUpdater()
        : m_flags(0), m_changed(0), m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), pad_18(0),
          pad_20(mm::Vec3::zero), pad_30(mm::Vec2::zero), pad_40(mm::Vec2::zero), pad_50(mm::Vec2::zero),
          pad_60(mm::Vec2::zero), pad_70(mm::Vec2::zero) {}
    virtual ~CharaIKUpdater() {}  // slot 0
    void update(float);
    // the foot setFootIK switches (1.0.0's symbols name the type; the values follow its flag bits)
    enum FOOT_TYPE : int {};
    // 1.0.0's CharaIKUpdater::setFootIK (0x71000B9570): sets or clears the foot's bit in m_flags (type 0: bit 1,
    // 1: bit 2, 2: bit 3) and marks bit 1 of m_changed; inline in 3.0.1 (CharaLinerPos::update)
    void setFootIK(bool on, FOOT_TYPE type) {
        switch (type) {
        case 0:
            if (on) {
                m_flags |= 2;
            } else {
                m_flags &= ~2;
            }
            break;
        case 1:
            if (on) {
                m_flags |= 4;
            } else {
                m_flags &= ~4;
            }
            break;
        case 2:
            if (on) {
                m_flags |= 8;
            } else {
                m_flags &= ~8;
            }
            break;
        }
        m_changed |= 2;
    }
    // the IK switches (1.0.0's setAllIK sets or clears bit 0, setFootIK bits 1-3); the name is not the original's
    unsigned int m_flags;  // 0x8
    // the switches changed since the last update (setAllIK ORs 0x1F, setFootIK bit 1); the name is not the
    // original's
    unsigned int m_changed;  // 0xc
    // the handle 1.0.0's create(GF_OBJ_HANDLE*) stores; the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10
    int pad_18;
    unsigned char pad_1c[0x4];
    mm::Vec3 pad_20;
    mm::Vec2 pad_30;
    mm::Vec2 pad_40;
    mm::Vec2 pad_50;
    mm::Vec2 pad_60;
    mm::Vec2 pad_70;
};
}  // namespace event

#endif
