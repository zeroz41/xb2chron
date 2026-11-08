#ifndef CLASSES_EVENT_CHARAEVAPLAYER_H
#define CLASSES_EVENT_CHARAEVAPLAYER_H

#include "classes/event/CharaWpnAsm.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/CRchaEx.h"
#include "fw/Message.h"
#include "mm/Vec3.h"

namespace event { class CharaObj; class CharaDysUpdater; }

namespace event {
// table 0x7100B3CBF0
class CharaEvaPlayer {
public:
    virtual ~CharaEvaPlayer();  // slot 0
    // 1.0.0's names (setMountWeapon 0x71000CAF48, setBattleWeapon 0x71000CAFE4); the field names are not the original's
    void setMountWeapon(int weapon);
    void setBattleWeapon(int weapon);
    // 3.0.1 symbols (0x71000E26F0, 0x71000E2310, 0x71000E2964, 0x71000E25F8)
    void play(CharaObj* chara, gf::GfEvtModel* model, CharaDysUpdater* dys, void* eva, void* anm, bool action,
              bool weapon, const char* name, const mm::Vec3& pos);
    void playAction(int action);
    void stopAction();
    void playFoot(bool foot);
    // 1.0.0's CharaEvaPlayer::stop (0x71000C97E0, out of line there; 3.0.1 inlines it into ~CharaEvaPlayer and play)
    void stop() {
        if (m_rcha) {
            if ((m_flags & 6) == 6) {
                if (m_model->m_modelType == 2) {
                    m_wpnRight.m_mots.clear();
                    m_wpnRight.m_mots.push_back(1);
                    m_wpnRight.pad_50 = m_wpnRight.m_mots[m_wpnRight.m_mots.size() - 1];
                    unsigned int flags = m_wpnRight.pad_8 & ~1u;
                    flags &= ~4u;
                    m_wpnRight.m_model = m_model;
                    m_wpnRight.m_param = nullptr;
                    m_wpnRight.m_speed = 0;
                    m_wpnRight.pad_8 = flags;
                    m_battleWeapon = 1;
                }
                m_flags &= ~4u;
            }
            delete m_rcha;
            m_rcha = nullptr;
        }
        m_wpnRight.update(1.0f);
        m_wpnLeft.update(1.0f);
        m_dys = nullptr;
        m_anm = nullptr;
        m_chara = nullptr;
        m_model = nullptr;
    }
    // the message playFoot sends to the object's GfComEffectCaster (id 0x100005b; the name is not the original's)
    struct FootMessage : fw::Message {
        FootMessage(int side) : fw::Message(0x100005b, 0x80), m_side(side), pad_c(0) {}
        int m_side;  // 0 when playFoot's foot is set, else 1
        int pad_c;  // 0xc: 0
    };
    // play: bit 0 = play's action flag, bit 1 = its weapon flag, bit 2 = weapon state set (stop resets it), bit 3 =
    // the name holds wp050101_l/_r (or wp730011 in Ira) (the field names here are not the original's)
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    CharaObj* m_chara;  // 0x10
    // the model whose weapons the players drive (its m_modelType picks them)
    gf::GfEvtModel* m_model;  // 0x18
    CharaDysUpdater* m_dys;  // 0x20
    void* m_anm;  // 0x28
    CRchaEx* m_rcha;  // 0x30: play's new CRchaEx set up from the eva data
    float m_time;  // 0x38: play clears it
    unsigned char pad_3c[0x4];
    mm::Vec3 m_pos;  // 0x40: play's pos
    unsigned char pad_50[0x20];
    int m_action;  // 0x70: playAction's action, stopAction clears it
    unsigned char pad_74[0xc];
    int m_mountWeapon;  // 0x80: setMountWeapon's weapon
    int m_battleWeapon;  // 0x84: setBattleWeapon's weapon
    CharaWpnAsm m_wpnRight;  // 0x88 (execCmd/mount's left = false)
    CharaWpnAsm m_wpnLeft;  // 0xe0 (left = true)
};
}  // namespace event

#endif
