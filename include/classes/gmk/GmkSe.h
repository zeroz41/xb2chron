#ifndef CLASSES_GMK_GMKSE_H
#define CLASSES_GMK_GMKSE_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/BootedGmkCond.h"
class CBdatWrapper;
namespace gmk { class GmkSeGob; }

namespace gmk {
// table 0x7100B6C5B8
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
// its node (a second, non-polymorphic base at 0x48) links it into TGmkActiveList<GmkSe>
class alignas(16) GmkSe : public ::gmk::AGmkBase, public mm::mtl::IntrusiveListNodeBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x71005EC9F4 (whose constructor sets its fields; their defaults are not written yet)
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatched() const;
        bool m_seType;                      // flag "se_type" (no default: resize leaves it)
        bool m_playOnce = false;            // flag "play_once"
        unsigned short m_seName = 0;        // the row's "seName"
        unsigned char m_volumeMax = 100;    // the row's "volumeMAX"
        unsigned char m_volumeMin = 0;      // the row's "volumeMIN"
        unsigned short m_condition = 0;     // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned char m_inRoomVolume = 100; // the row's "InRoom_volume"
        unsigned char pad_9;
        ScenarioFlagCond m_scenarioFlag;    // the row's ScenarioFlagMin/Max
        QuestFlagCond m_questFlag;          // the row's QuestFlag/Min/Max
        TimeCond m_popTime;                 // the row's "SEpopTime"
        WeatherCond m_weather;              // the row's "wtrSEType"
        BootedGmkCond m_bootedGmk;          // 0x38: the row's gimmickType/ID, no prefix (must be booted)
        BootedGmkCond m_bootedGmkNot;       // 0x3C: the row's OP_gimmickType/ID (must NOT be booted)
    };
    // its data in the gimmick section (m_createInfo.m_data): debugDraw draws circles of radius pad_4 (blue) and
    // pad_0 (red) around the gimmick (meanings not known)
    struct Data {
        float pad_0;
        float pad_4;
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    GmkSe() {}  // inline: construct_n<GmkSe> constructs in place with these stores
    virtual ~GmkSe();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    // its step while in TGmkActiveList<GmkSe> (GmkManager::seqUpdate calls it for each)
    void updateInActiveList(float);
    // its sound started at the row's volumeMIN (stopped first when one plays); TGmkActiveList<GmkSe> takes it then
    void createInst();
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(15);
    // 0x58..0x60: padding (the copies of Vector<T>::expand copy nothing there)
    GmkPhantom m_phantom;  // 0x60 (the name is not the original's)
    // fields the constructor clears (meaning unknown)
    // 0xf0: update stores BdatInfo::isPopCondMatched's answer here and acts when it changes; debugDraw draws only
    // while it is set (the name is not the original's)
    bool m_popCondMatched = false;
    unsigned char pad_f1 = 0;
    unsigned char pad_f2[0x2];
    unsigned m_seHandle = 0;  // 0xf4: the playing sound (dispose stops it; the name is not the original's)
    float pad_f8 = 0.0f;  // createInst clears it; updateInActiveList adds dt and sets the volume from 1.0 on
    float pad_fc = 0.0f;  // updateInActiveList stores the player's distance here
    bool pad_100 = false;
    // 0x101..0x110: tail padding (not copied); size from TGmkList::getInst's stride (0x110)
};
}  // namespace gmk

#endif
