#ifndef CLASSES_GMK_GMKSE_H
#define CLASSES_GMK_GMKSE_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/BootedGmkCond.h"
class CBdatWrapper;
namespace gmk { class GmkSeGob; }

namespace gmk {
// table 0x7100B6C5B8
class GmkSe : public ::gmk::AGmkBase {
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
        unsigned char pad_12[0x6];
        TimeCond m_popTime;                 // the row's "SEpopTime"
        WeatherCond m_weather;              // the row's "wtrSEType"
        BootedGmkCond m_bootedGmk;          // the row's OP_gimmickType/ID (must be booted)
        BootedGmkCond m_bootedGmkNot;       // a second <prefix>gimmickType/ID pair (must NOT be booted)
    };
    virtual ~GmkSe();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(15);
    unsigned char pad_48[0xc8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
