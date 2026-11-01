#ifndef CLASSES_EVENT_CHARAIKUPDATER_H
#define CLASSES_EVENT_CHARAIKUPDATER_H

namespace event {
// table 0x7100B3C9F0
class CharaIKUpdater {
public:
    virtual ~CharaIKUpdater() {}  // slot 0
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
};
}  // namespace event

#endif
