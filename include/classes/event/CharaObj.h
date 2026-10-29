#ifndef CLASSES_EVENT_CHARAOBJ_H
#define CLASSES_EVENT_CHARAOBJ_H

#include "classes/event/CharaEffectPlayer.h"
#include "classes/event/CmdQueue.h"
#include "classes/event/CharaPlayAction.h"
#include "classes/event/CharaPlayActionAuto.h"
#include "classes/event/CharaSetIdle.h"
#include "classes/event/CharaSetPos.h"
#include "classes/event/CharaSetRot.h"
#include "mm/Vec3.h"

namespace event { class AttachActorBase; }

namespace event {
// which weapon a hide request is for (the evt_chara script commands pass 3); no enumerator is named
enum WPNHIDEID : int {};
// table 0x7100B3CAF8
class CharaObj {
public:
    virtual ~CharaObj();  // slot 0
    void playMotion(const char* name, float a, float b, float c);
    void playFade(bool fade, float time);
    void playWink(int a, float b, bool c, float d, float e, int f, bool g, bool h);
    void playTalk(bool a, float b, bool c, bool d, float e, float f, float g, float h);
    void setPos(const mm::Vec3& pos);
    void setRot(const mm::Vec3& rot);
    // queues m_setIdle with this object and id, after erasing the idle and action commands
    void setIdle(int id);
    void playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, float time, float delay);
    void playVolumeFade(CharaEffectPlayer::VF_TYPE type, int a, const mm::Vec3& b, const mm::Vec3& c, float d, float e,
                        int f, float g);
    void stopVolumeFade(CharaEffectPlayer::VF_TYPE type);
    void resetDynamics(int type);
    void playRimBloom(int type);
    void stopRimBloom();
    void setExtDisp(const char* name, bool disp);
    void setExtParam(const char* name, float value);
    void setHideWeapon(WPNHIDEID id, bool hide, bool flag);
    // empties the command queues (1.0.0 has it out of line; ObjectChara::clear inlines it)
    void clear() {
        m_cmdQueue0.eraseAll();
        m_cmdQueue1.eraseAll();
        m_cmdQueue2.eraseAll();
    }
    void start();
    void end();

    // the command setPos queues (CharaObj's constructor builds it); the name is not the original's
    CharaSetPos m_setPos;  // 0x8
    // the command setRot queues (CharaObj's constructor builds it); the name is not the original's
    CharaSetRot m_setRot;  // 0x18
    unsigned char pad_28[0x5b8];
    // the commands setIdle erases from m_cmdQueue0 (CharaObj's constructor builds them); the names are not the original's
    CharaSetIdle m_setIdle;  // 0x5e0
    CharaPlayActionAuto m_playActionAuto;  // 0x608
    CharaPlayAction m_playAction;  // 0x630
    unsigned char pad_670[0x630];
    // bit 5: playFade's flag (it sets or clears it); the name is not the original's
    unsigned int m_flags;  // 0xca0
    unsigned char pad_ca4[0xb4];
    // initModel stores a new AttachActorGf here (the destructor deletes it); the name is not the original's
    AttachActorBase* m_attach;  // 0xd58
    unsigned char pad_d60[0x630];
    // playVolumeFade/playRimBloom and their stops forward to it; the name is not the original's
    CharaEffectPlayer m_effectPlayer;  // 0x1390
    unsigned char pad_1398[0x3a0];
    // three command queues ObjectChara::clear empties (1.0.0's CharaObj::clear); the names are not the original's
    CmdQueue<8, 0> m_cmdQueue0;  // 0x1738
    CmdQueue<8, 0> m_cmdQueue1;  // 0x2088
    CmdQueue<5, 0> m_cmdQueue2;  // 0x29d8
    // the position setPos stores before queueing its command; the name is not the original's
    mm::Vec3 m_pos;  // 0x2fb0
    unsigned char pad_2fc0[0x10];
    // the rotation setRot stores before queueing its command; the name is not the original's
    mm::Vec3 m_rot;  // 0x2fd0
};
}  // namespace event

#endif
