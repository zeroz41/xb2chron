#ifndef CLASSES_EVENT_CHARAEVAPLAYER_H
#define CLASSES_EVENT_CHARAEVAPLAYER_H

#include "classes/event/CharaWpnAsm.h"

namespace gf { class GfEvtModel; }

namespace event {
// table 0x7100B3CBF0
class CharaEvaPlayer {
public:
    virtual ~CharaEvaPlayer();  // slot 0
    // 1.0.0's names (setMountWeapon 0x71000CAF48, setBattleWeapon 0x71000CAFE4); the field names are not the original's
    void setMountWeapon(int weapon);
    void setBattleWeapon(int weapon);
    unsigned char pad_8[0x10];
    // the model whose weapons the players drive (its m_modelType picks them)
    gf::GfEvtModel* m_model;  // 0x18
    unsigned char pad_20[0x60];
    int m_mountWeapon;  // 0x80: setMountWeapon's weapon
    int m_battleWeapon;  // 0x84: setBattleWeapon's weapon
    CharaWpnAsm m_wpnRight;  // 0x88 (execCmd/mount's left = false)
    CharaWpnAsm m_wpnLeft;  // 0xe0 (left = true)
};
}  // namespace event

#endif
