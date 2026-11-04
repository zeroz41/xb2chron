#ifndef CLASSES_GF_GFPLAYCOMTALK_H
#define CLASSES_GF_GFPLAYCOMTALK_H
#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfSetupPfTalk.h"
#include "gf/QuestID.h"
namespace fw { class UpdateInfo; }
namespace gf {
// table 0x7100B57FC0 (the PtrSingleton's at +0x58): a talk with an object (GfSequentialPlay::addTalk). The destructor
// and getFuncName are inline (their bodies sit in the unit's tail with the table's thunks); start is the key function
class GfPlayComTalk : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComTalk> {
public:
    explicit GfPlayComTalk(const GfSetupPfTalk& talk)
        : GfPlayCom(0x21, false), m_setup(talk), m_npc(talk.pad_10), m_quest(), m_lastOrder(), m_newMeet(false) {}
    static GfPlayComTalk* create(const GfSetupPfTalk& talk);
    // the NPC the running talk's quest task targets, when the task's condition is condId (else 0)
    static unsigned int getQuestTargetNpc(unsigned int condId);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComTalk() {}  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComTalk";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static unsigned int s_questTargetNpc;
    static unsigned int s_questTargetCondID;

    // the names below are not the original's
    GfSetupPfTalk m_setup;  // GfGameTalk::play's
    unsigned int m_pause;   // from GfGameScene::createPlayerPause
    unsigned int m_npc;     // the setup's word at 0x10; start replaces it with the NPC setup's BDAT id
    unsigned int m_map;     // GfGameManager::getMapID when created
    QuestID m_quest;        // GfQuestManager::getProgressCurrentQuest(0) at the start
    QuestID m_lastOrder;    // GfQuestManager::getLastOrder at the start
    bool m_newMeet;         // the talk set the NPC's met flag (GfDataNpc::isHitonowaMeetsFlag changed)
};
}  // namespace gf
#endif
