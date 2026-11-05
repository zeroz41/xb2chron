#ifndef CLASSES_EVENT_CHARAOBJ_H
#define CLASSES_EVENT_CHARAOBJ_H

#include "classes/event/CharaEffectPlayer.h"
#include "classes/event/CmdQueue.h"
#include "classes/event/FrameInfo.h"
#include "classes/event/CharaFade.h"
#include "classes/event/CharaHideWpn.h"
#include "classes/event/CharaPlayEva.h"
#include "classes/event/CharaPlayEvaEff.h"
#include "classes/event/CharaPlayFacial.h"
#include "classes/event/CharaPlayHead.h"
#include "classes/event/CharaStopHead.h"
#include "classes/event/CharaPlayMotion.h"
#include "classes/event/CharaPlayMotionABC.h"
#include "classes/event/CharaPlayTalk.h"
#include "classes/event/CharaPlayTalkAuto.h"
#include "classes/event/CharaPlayWink.h"
#include "classes/event/CharaPlayAction.h"
#include "classes/event/CharaPlayActionAuto.h"
#include "classes/event/CharaStopAction.h"
#include "classes/event/CharaSetIdle.h"
#include "classes/event/CharaSetPos.h"
#include "classes/event/CharaSetRot.h"
#include "classes/event/CharaSetTar.h"
#include "classes/event/CharaTurnRot.h"
#include "classes/event/CharaLinerPos.h"
#include "classes/event/CharaLinerRot.h"
#include "classes/event/CharaIKUpdater.h"
#include "classes/event/CharaDysUpdater.h"
#include "classes/event/CharaPartUpdater.h"
#include "classes/event/CharaWalkPos.h"
#include "classes/event/CharaMount.h"
#include "event/CvType.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; class GfEvtModel; }

namespace event { class AttachActorBase; class TarAxis; class ModelObj; enum CHARA_TYPE : int; }

// the kinds CharaObj::setTar takes (the mangled names spell global enums); their values are not known
enum EVT_tarcvtype : int;
enum EVT_aimtype : int;
// the curve kind ObjectChara::walkPosAxis and CharaObj::walkPos take (the mangled names spell a global enum); 0 sets
// the position at once, 1-8 also face the walk's direction; no enumerator is named
enum EVT_poscvtype {};
// how turnRotAxis and CharaObj::turnRot turn (ScriptCharaTurnRot::doit passes val 4); no enumerator is named
enum EVT_rotcvtype : int {};

namespace event {
// which weapon a hide request is for (the evt_chara script commands pass 3); no enumerator is named
enum WPNHIDEID : int {};
// table 0x7100B3CAF8
class CharaObj {
public:
    CharaObj(const char* name);
    virtual ~CharaObj();  // slot 0
    void playMotion(const char* name, float a, float b, float c);
    // out of line (0x71000DDE48, not written yet); playMotion calls it in state 4 or 5
    void initModelStream();
    void playFade(bool fade, float time);
    void playWink(int a, float b, bool c, float d, float e, int f, bool g, bool h);
    void playTalk(bool a, float b, bool c, bool d, float e, float f, float g, float h);
    void setPos(const mm::Vec3& pos);
    void setRot(const mm::Vec3& rot);
    void walkPos(const mm::Vec3& pos, EVT_poscvtype type, bool flag);
    // adjust: the position's height is first fitted by CharaUtil::adjestPosY
    void linerPos(const mm::Vec3& pos, bool adjust, float time, CV_TYPE cvType);
    void turnRot(const mm::Vec3& rot, EVT_rotcvtype type, float time);
    void linerRot(const mm::Vec3& rot, float time, CV_TYPE cvType);
    void setTar(const TarAxis& tar, float time, EVT_tarcvtype cvType, EVT_aimtype aimType, float a, float b);
    // queues m_setIdle with this object and id, after erasing the idle and action commands
    void setIdle(int id);
    // the id of the queued m_setIdle, 0 when none is queued (inlined by ScriptCharaSetIdle::doit); the name is not
    // the original's
    int getIdle() const { return m_cmdQueue0.contains(&m_setIdle) ? m_setIdle.m_id : 0; }
    void playAutoAction(float time);
    void playMotionABC(const char* a, const char* b, const char* c, float d, float e, float f, float g, float h, float i);
    void playFacial(int a, float b, int c, float d, int e, float f, int g, float h, float i, float j);
    // queues m_playHead (1.0.0 has playHead(int, float, bool, bool); 3.0.1 adds the two floats, -1 when unused)
    void playHead(int id, float time, bool a, bool b, float c, float d);
    // replaces a queued m_playHead with m_stopHead
    void stopHead();
    void playAction(int id, float time, bool a, bool b);
    // replaces a queued m_playAction with m_stopAction (as stopHead does for m_playHead)
    void stopAction();
    void mount(CharaObj* parent, const char* name, const mm::Vec3& pos, const mm::Vec3& rot);
    void playAutoTalk(float time);
    void playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, float time, float delay);
    void playVolumeFade(CharaEffectPlayer::VF_TYPE type, int a, const mm::Vec3& b, const mm::Vec3& c, float d, float e,
                        int f, float g);
    void stopVolumeFade(CharaEffectPlayer::VF_TYPE type);
    void resetDynamics(int type);
    void createGfObj(gf::GF_OBJ_HANDLE* handle);
    void createGfObj(CHARA_TYPE type, unsigned int id, unsigned int, unsigned int);
    void createModel(const char* name, unsigned int, unsigned int);
    void createGhost();
    void setScaleWeapon(float scale);
    void setDispJiji(bool disp);
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
    void update(const FrameInfo& info);
    void tail(const FrameInfo& info);

    // the command setPos queues (CharaObj's constructor builds it); the name is not the original's
    CharaSetPos m_setPos;  // 0x8
    // the command setRot queues (CharaObj's constructor builds it); the name is not the original's
    CharaSetRot m_setRot;  // 0x18
    unsigned char pad_28[0x8];
    // the command walkPos queues; the name is not the original's
    CharaWalkPos m_walkPos;  // 0x30
    unsigned char pad_38[0xc8];
    // the liner position command linerPos queues (CharaObj's constructor builds it); the name is not the original's
    CharaLinerPos m_linerPos;  // 0x100
    // the turn and liner rotation commands (RandPlayer::Reply::update tests whether either is queued); the names are
    // not the original's
    CharaTurnRot m_turnRot;  // 0x310
    CharaLinerRot m_linerRot;  // 0x330
    // the command setTar queues in m_cmdQueue2 (ScriptCharaTgt::doit tests whether it is queued); the name is not
    // the original's
    CharaSetTar m_setTar;  // 0x530
    unsigned char pad_540[0xa0];
    // the commands setIdle erases from m_cmdQueue0 (CharaObj's constructor builds them); the names are not the original's
    CharaSetIdle m_setIdle;  // 0x5e0
    CharaPlayActionAuto m_playActionAuto;  // 0x608
    CharaPlayAction m_playAction;  // 0x630
    CharaStopAction m_stopAction;  // 0x670 (the constructor installs its table); the name is not the original's
    // the commands the play*/set* functions queue (CharaObj's constructor builds them); the names are not the original's
    CharaPlayMotion m_playMotion;  // 0x680
    CharaPlayMotionABC m_playMotionABC;  // 0x6d0
    CharaPlayEva m_playEva;  // 0x750
    unsigned char pad_790[0x140];
    // where the last walkPos or linerPos heads (the position as passed); the name is not the original's
    mm::Vec3 m_moveGoal;  // 0x8d0
    CharaPlayEvaEff m_playEvaEff;  // 0x8e0
    CharaHideWpn m_hideWpn;  // 0x938
    CharaPlayHead m_playHead;  // 0x950
    CharaStopHead m_stopHead;  // 0x988
    unsigned char pad_998[0x8];
    CharaPlayFacial m_playFacial;  // 0x9a0
    CharaPlayTalkAuto m_playTalkAuto;  // 0xa10
    CharaPlayTalk m_playTalk;  // 0xa38
    CharaPlayWink m_playWink;  // 0xab0
    // the command mount queues; the name is not the original's
    CharaMount m_mount;  // 0xb40
    CharaFade m_fade;  // 0xb80
    // bit 5: playFade's flag (it sets or clears it); the name is not the original's
    // bit 4: set while mounted (mount sets or clears it), bit 7: setDispJiji's flag (it sets or clears it); the name is not the original's
    unsigned int m_flags;  // 0xca0
    // createGhost sets 6 (what the values mean is not known); the name is not the original's
    int m_state;  // 0xca4
    unsigned char pad_ca8[0x98];
    // the character's gf object (RandPlayer::Wait::update hands it to GfObjUtil::isStanbyTalkingPlayer); the name is
    // not the original's
    gf::GF_OBJ_HANDLE* m_gfHandle;  // 0xd40
    // the character's game model (setScaleWeapon, setHideWeapon and setDispJiji pick the call by its m_modelType);
    // the name is not the original's
    gf::GfEvtModel* m_model;  // 0xd48
    // the model createGhost makes; the name is not the original's
    ModelObj* m_ghost;  // 0xd50
    // initModel stores a new AttachActorGf here (the destructor deletes it); the name is not the original's
    AttachActorBase* m_attach;  // 0xd58
    // tail updates it; the name is not the original's
    CharaIKUpdater m_ikUpdater;  // 0xd60
    unsigned char pad_d70[0x70];
    // tail updates it last; resetDynamics forwards to it; the name is not the original's
    CharaDysUpdater m_dysUpdater;  // 0xde0
    unsigned char pad_e00[0x590];
    // playVolumeFade/playRimBloom and their stops forward to it; the name is not the original's
    CharaEffectPlayer m_effectPlayer;  // 0x1390
    unsigned char pad_1630[0x20];
    // setExtDisp/setExtParam forward to it and tail runs its updateRequest; the name is not the original's
    CharaPartUpdater m_partUpdater;  // 0x1650
    unsigned char pad_1658[0xd8];
    float pad_1730;  // 0x1730: DofManager::calcDistSub adds it to m_pos's y (a height above the position)
    unsigned char pad_1734[0x4];
    // three command queues ObjectChara::clear empties (1.0.0's CharaObj::clear); the names are not the original's
    CmdQueue<8, 0> m_cmdQueue0;  // 0x1738
    CmdQueue<8, 0> m_cmdQueue1;  // 0x2088
    CmdQueue<5, 0> m_cmdQueue2;  // 0x29d8
    // the position setPos stores before queueing its command; the name is not the original's
    mm::Vec3 m_pos;  // 0x2fb0
    // the position a queued walk or liner move heads for; the name is not the original's
    mm::Vec3 m_posGoal;  // 0x2fc0
    // the rotation setRot stores before queueing its command; the name is not the original's
    mm::Vec3 m_rot;  // 0x2fd0
    // the rotation a queued turn or liner rotation heads for (RandPlayer::Reply::update reads it instead of m_rot while
    // one is queued); the name is not the original's
    mm::Vec3 m_rotGoal;  // 0x2fe0
    unsigned char pad_2ff0[0x40];
    // update stores its FrameInfo here; the commands read it through val(0)'s CharaObj (the name is not the
    // original's)
    FrameInfo m_frameInfo;  // 0x3030
    // playMotion's first float, kept when it starts the model stream (state 4 or 5); the name is not the original's
    float m_motionParam;  // 0x3044
    // setScaleWeapon's scale; the name is not the original's
    float m_weaponScale;  // 0x3048
    // setHideWeapon's hide bits (one per WPNHIDEID), right [0] and left [1]; the name is not the original's
    unsigned int m_hideWpnMask[2];  // 0x304c
    // the id createGhost hands ModelManager::createModel; the name is not the original's
    int m_modelId;  // 0x3054
    // ObjectChara::createGfObj allocates 0x3060 bytes
    unsigned char pad_3058[0x8];
};
}  // namespace event

#endif
