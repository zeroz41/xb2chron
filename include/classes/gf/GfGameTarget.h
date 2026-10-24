#ifndef CLASSES_GF_GFGAMETARGET_H
#define CLASSES_GF_GFGAMETARGET_H

#include "ai/Fsm.h"
#include "classes/fw/MessageObject.h"
#include "classes/fw/ParamList.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/PadRelay.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_SEARCH_OBJ; }
namespace gf { class GfGameTarget; }
namespace gf { class GfSearchInfo; }
namespace gf { class GfSetupParam; }
namespace gf { class MsgGameDebugTarget; }

namespace gf {
// table 0x7100B56700: the player's field target (an Fsm of four states picks it from two searches around the
// player; the pad actions change mode, select left/right and hold for the nearest)
class GfGameTarget : public ::mm::mtl::PtrSingleton< ::gf::GfGameTarget>, public ::fw::MessageObject, public ::gf::IGfEvent {
public:
    class StateAutoTarget;
    class StateBattleTarget;
    class StateDriverNotActive;
    class StateEnemyTarget;
    // its parameter list's first entry (1.0.0's GfGameTarget::Param::createReflection names the type; the field
    // names are not the original's)
    struct Param {
        float m_searchRadius;  // createSearchObj: the target search's radius
        float m_heightRange;   // setTargetNearest: the greatest height difference of an auto target
        float m_fadeTime;      // updateImpl: how long a fading target stays
        float m_nearTime;      // updateImpl/judgeNearTarget: the near-target hold's time
    };

    GfGameTarget();
    virtual ~GfGameTarget();  // slot 0
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevChangeLeader(gf::GF_OBJ_HANDLE*);  // slot 3
    virtual void gevSwapFormation(unsigned int, unsigned int);  // slot 4
    void procMsgGameDebugTarget(fw::MessageObject* sender, MsgGameDebugTarget& msg);
    static void build(const GfSetupParam& param);
    void setup(const GfSetupParam& param);
    static void destroy();
    void cleanup();
    static void update(const fw::UpdateInfo& info);
    void updateImpl(const fw::UpdateInfo& info);
    static bool testActive();
    void changeMode();
    void selectRight();
    void selectLeft();
    // 1.0.0's name: its setup binds "close_target_on" to startNearTarget at the same place, and its body (no mode
    // change asked for: timer 0, hold on) is this one's tail
    void startNearTarget();
    void judgeNearTarget();
    void notifyTarget();
    void createSearchObj();
    void selectTarget(const mm::mtl::FixedList<GfSearchInfo*, 256>& list);
    bool setTargetNearest(const mm::mtl::FixedList<GfSearchInfo*, 256>& list);
    bool setTargetNearestEnemy(const mm::mtl::FixedList<GfSearchInfo*, 256>& list);
    bool setTargetNearestEnemyBattle(const mm::mtl::FixedList<GfSearchInfo*, 256>& list);
    void changeBattleTarget(bool battle);
    static void lockTarget(bool lock);
    static void disableTargetWithoutEnemy();

    // 1.0.0's (names from its symbols), inline in 3.0.1
    const Param* getParam() const { return m_paramList->getAdapter(0).get<Param>(); }
    void resetTarget() {
        if (m_target != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            m_target = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
            m_changed = true;
            m_fading = false;
        }
    }
    void setTarget(GF_OBJ_HANDLE* target) {
        if (m_target != target) {
            m_target = target;
            m_changed = true;
            m_fading = false;
        }
    }
    static bool testLockTarget() { return get() != nullptr && get()->m_lock; }
    void destroySearchObj();

    // (the names below are not the original's)
    ai::Fsm m_fsm;  // the states: 0 StateDriverNotActive, 1 StateAutoTarget, 2 StateEnemyTarget, 3 StateBattleTarget
    GF_SEARCH_OBJ* m_enemySearch;  // createSearchObj's first search (the enemy states'), -1 for none
    GF_SEARCH_OBJ* m_autoSearch;   // its second, around the player (StateAutoTarget's), -1 for none
    GF_OBJ_HANDLE* m_player;       // the controlled object the searches follow
    GF_OBJ_HANDLE* m_target;       // the target, -1 for none
    bool m_changed;                // notifyTarget tells the target's watchers while it is set
    bool m_lock;                   // lockTarget's
    bool m_fading;                 // a target losing its validity stays m_fadeTime (fadeOutTarget in 1.0.0)
    float m_fadeTimer;
    bool m_reqChangeMode;          // the pad's requests, cleared each update
    bool m_reqSelectRight;
    bool m_reqSelectLeft;
    bool m_reqNearTarget;
    bool m_nearHold;               // "close_target_on" to "close_target_off"
    float m_nearTimer;
    fw::PadRelay m_padRelay;
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // the parameter manager's list 0
};
}  // namespace gf

#endif
