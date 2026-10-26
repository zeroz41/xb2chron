#ifndef CLASSES_GF_GFQUESTTARGET_H
#define CLASSES_GF_GFQUESTTARGET_H

#include "classes/gf/IQuestEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"
#include "gf/QuestID.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfQuestTarget; }
namespace fw { class UpdateInfo; }
namespace gf { class QuestChangeParam; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestOrderParam; }
namespace gf { class QuestStateParam; }
namespace gf { class QuestTaskParam; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// table 0x7100B56DF8
class GfQuestTarget : public ::mm::mtl::PtrSingleton< ::gf::GfQuestTarget>, public ::gf::IQuestEvent {
public:
    // an object a quest marks as a target, cached for a while (1.0.0's FixedList<GfQuestTarget::TargetCache, 512>
    // and GfQuestTarget::getTargetCache(GF_OBJ_HANDLE*); the field names are not the original's)
    struct TargetCache {
        // the quest is assigned (QuestID's operator= stores its halves one by one)
        TargetCache(GF_OBJ_HANDLE* handle, QuestID questId) : m_handle(handle), m_value(0) {
            m_questId = questId;
            m_frames = 0;
            m_destroy = false;
            m_flag = false;
        }
        GF_OBJ_HANDLE* m_handle;     // 0x0
        unsigned long m_value;       // 0x8: entryTargetCache zeroes it
        QuestID m_questId;           // 0x10: destroyTargetQuest drops the entries of its quest
        unsigned short m_frames;     // 0x14: update counts it up while the entry lives
        bool m_destroy;              // 0x16: set after 300 frames or when its quest changes; update erases one a frame
        bool m_flag;                 // 0x17: entryTargetCache clears it
    };

    GfQuestTarget();
    virtual ~GfQuestTarget();  // slot 0
    void update(const fw::UpdateInfo& info);
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    // 1.0.0 has it out of line; 3.0.1 inlines every call
    void destroyTargetQuest(QuestID questId);
    void entryTargetCache(GF_OBJ_HANDLE* handle, QuestID questId);
    virtual void qevChangeTaskState(gf::QuestTaskParam const&);  // slot 2
    virtual void qevChangeQuestState(gf::QuestStateParam const&);  // slot 3
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 4
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 5
    virtual void qevChangeCurrentQuest(gf::QuestChangeParam const&);  // slot 6
    virtual void qevChangeTaskCondition(gf::QuestTaskParam const&);  // slot 7
    // the field locators pass its result to gmk::getBdatIdOfQuestTargetIcon (LocatorTbox: 1 and the box's id,
    // LocatorPrecious: 2 and the item's id, then the quest, the map's FLD_maplist id, true)
    static unsigned int getIconTypeCollect(unsigned int kind, unsigned int id, QuestID questId, unsigned int mapId,
                                           bool flag);
    // LocatorTalk_NpcID passes the NPC's id, the quest, the map's FLD_maplist id, true
    // LocatorBat_EnemySpeciesID passes 3, the species id, the quest, no object ((GF_OBJ_HANDLE*)-1), true
    static unsigned int getIconTypeBattle(unsigned int kind, unsigned int id, QuestID questId, GF_OBJ_HANDLE* handle,
                                          bool flag);
    // LocatorReach passes its "Category" and "PlaceID", the quest, its map's FLD_maplist id, true
    static unsigned int getIconTypeReachPlace(unsigned int category, unsigned int placeId, QuestID questId,
                                              unsigned int mapId, bool flag);
    static unsigned int getIconTypeTalk(unsigned int npcId, QuestID questId, unsigned int mapId, bool flag);
    static unsigned int getIconTypeTalk(GF_OBJ_HANDLE* handle, QuestID questId, unsigned int mapId, bool flag);

    ::mm::mtl::FixedList<TargetCache, 512> m_targetCache;  // 0x10
};
}  // namespace gf

#endif
