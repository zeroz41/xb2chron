#ifndef CLASSES_GF_GFMENUOBJMERCENARYTOP_H
#define CLASSES_GF_GFMENUOBJMERCENARYTOP_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace ui { class UICtrlRevolveSelect; class UISelectObjList; }

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuIDList;
class GfMenuReferenceNumber;
class GfMenuReferenceQuest;

// table 0x7100B63608. Field names are not the original's.
class GfMenuObjMercenaryTop : public ::gf::GfMenuObject {
public:
    class MainListener;
    class MissionListener;
    class ZoneListener;
    // what registOpenParam passes on as the layer param's menu word (the name is not the original's)
    struct OpenParam {
        unsigned int m_value;
    };
    GfMenuObjMercenaryTop(unsigned int handle);
    virtual ~GfMenuObjMercenaryTop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // registers the param of full-screen layer 0x34 (this menu's)
    static void registOpenParam(OpenParam const& param);
    // shows unit slot index of the zone layout handle as ready / on a mission / returning (static: no object)
    void updateMissionList();  // lists the zone's missions and shows the zone notice icons
    void refreshMissionList();  // restyles the mission rows shown (and the selected one's conditions)
    static void setDispUnitReady(unsigned int handle, unsigned int index);
    static void setDispUnitProgress(unsigned int handle, unsigned int index);
    static void setDispUnitReturn(unsigned int handle, unsigned int index);
    bool seqUnitBreak();
    bool seqCanNotOrder();
    bool seqExit();

    unsigned char pad_24[4];
    // 0x28-0x98: created by the constructor or initialize, released by the destructor (the names are not the
    // original's)
    GfMenuIDList* m_zoneList;                  // 0x28: initialize fills it (GfMenuIDList::create)
    GfMenuIDList* m_missionList;               // 0x30: GfMenuMissionAdapter::createFromList's list
    GfMenuBladeList* m_bladeList;              // 0x38: set up from the team (GfMenuBladeList::setupFromTeam)
    GfMenuBladeList* m_bladeList2;             // 0x40
    ui::UISelectObjList* m_zoneSelect;         // 0x48: what m_zoneRevolve turns
    ui::UICtrlRevolveSelect* m_zoneRevolve;    // 0x50
    float m_revolveStep;                       // 0x58: the constructor sets 1.0, initialize a layout ratio
    unsigned char pad_5C[4];
    ui::UISelectObjList* m_flagIcons;           // 0x60: created after "mnu090_icon_flag_select"
    ui::UISelectObjList* m_noticeIcons;           // 0x68: updateMissionList adds the zone notice icons
    ui::UISelectObjList* m_missionSelect;      // 0x70: "LAY_mis_sel_item@%02d"
    unsigned char pad_78[8];
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_zoneNumber;  // 0x80: its value is the zone updateMissionList lists
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_rewardNumber;  // 0x88: read before GfMenuObjQuestReward::create
    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> m_quest;      // 0x90
    GfMenuCallContext* m_callContext;          // 0x98: GfMenuObjQuestReward::create's context
    GfMenuSequence<GfMenuObjMercenaryTop, 8> m_seq;  // 0xA0
    bool m_jobStarted;  // 0x330: the running job has started (opened its window); seqUnitBreak/seqCanNotOrder
    unsigned int m_exitHandle;  // 0x334: seqExit sends it event 0x100 and clears it
    GfMenuCallContext* m_callContext2;  // 0x338: the constructor creates it, the destructor releases it first
    bool m_canClose;            // 0x340: the constructor sets it; MainListener fades out on 2/0x22 only while set
};
}  // namespace gf

#endif
