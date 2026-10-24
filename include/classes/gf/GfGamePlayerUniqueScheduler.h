#ifndef CLASSES_GF_GFGAMEPLAYERUNIQUESCHEDULER_H
#define CLASSES_GF_GFGAMEPLAYERUNIQUESCHEDULER_H

#include "classes/fw/MessageObject.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"
#include "classes/gf/GfBdatUniqueMotion.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGamePlayerUniqueScheduler; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B55930: now and then has the party's characters play their unique motions together, by the presets
// GfBdatUniqueMotion gives for the party (1.0.0's symbols name the class and its functions)
class GfGamePlayerUniqueScheduler : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerUniqueScheduler>, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    // the scheduler's parameters: fw::ParamManager's list 12, entry 0 (the type and field names are not the original's)
    struct Param {
        float m_interval;     // seconds between judgements
        float m_probability;  // percent: the chance a judgement draws a preset
    };
    // a party member (the type and field names are not the original's)
    struct Member {
        Member() : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_charaId(0), m_state(0), m_motion(0), m_wait(0.0f) {}
        GF_OBJ_HANDLE* m_handle;
        unsigned short m_charaId;  // its GfObjSetup's m_bdatId (its bdat row), 0 for none
        unsigned char pad_a[0x2];
        int m_state;  // 0 none, 1 waiting, 2 ready (answered MsgPcFieldTestEnableUniqueMotion), 3 motion scheduled
        unsigned short m_motion;  // which of its three motions (0 to 2)
        unsigned char pad_12[0x2];
        float m_wait;  // seconds until the scheduled motion plays
    };

    GfGamePlayerUniqueScheduler();
    virtual ~GfGamePlayerUniqueScheduler();  // slot 0
    virtual void gevPartyMemberOK(bool);  // slot 2
    virtual void gevBattleStart();  // slot 3
    // overrides IGfEvent's slot 35 (new in 3.0.1: 1.0.0's class has no override)
    virtual void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int);  // slot 4

    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    static void onReload();
    // 1.0.0's (3.0.1 has no copies: build, destroy, update, onReload and gevPartyMemberOK inline them)
    void setup() {
        GfEvent::addEventCallback(this);
        m_paramList = fw::ParamManager::get()->m_paramLists[12];
    }
    void cleanup() { GfEvent::removeEventCallback(this); }
    void executeRequest(const fw::UpdateInfo& info);
    void judge(const fw::UpdateInfo& info);
    void rebuildPreset();
    const Param* getParam() const { return m_paramList->getAdapter(0).get<Param>(); }
    // a member from the party's handle (inline: the name is not the original's)
    void setMember(Member& member, GF_OBJ_HANDLE* handle);
    // the member playing a character, none if no member does (inline: the name is not the original's)
    Member* findMember(unsigned short charaId);

    float m_timer;  // seconds since the last judgement (the name is not the original's)
    unsigned char pad_2c[0x4];
    Member m_members[9];  // the names are not the original's
    mm::mtl::FixedQueue<const GfBdatUniqueMotion::PresetInfo*, 32> m_presets;  // queryPreset's for the party
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;
};
}  // namespace gf

#endif
