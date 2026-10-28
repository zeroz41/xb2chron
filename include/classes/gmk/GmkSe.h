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
        BootedGmkCond m_bootedGmk;          // the row's OP_gimmickType/ID (must be booted)
        BootedGmkCond m_bootedGmkNot;       // a second <prefix>gimmickType/ID pair (must NOT be booted)
    };
    GmkSe() {}  // inline: construct_n<GmkSe> constructs in place with these stores
    virtual ~GmkSe();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(15);
    unsigned char pad_58[0x8];
    GmkPhantom m_phantom;  // 0x60 (the name is not the original's)
    unsigned char pad_e8[0x8];
    // fields the constructor clears (meaning unknown)
    unsigned short pad_f0 = 0;
    unsigned char pad_f2[0x2];
    int pad_f4 = 0;
    int pad_f8 = 0;
    int pad_fc = 0;
    bool pad_100 = false;
    unsigned char pad_101[0xf];  // size from TGmkList::getInst's stride (0x110)
};
}  // namespace gmk

#endif
