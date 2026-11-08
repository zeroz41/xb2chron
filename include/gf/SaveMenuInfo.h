#ifndef GF_SAVEMENUINFO_H
#define GF_SAVEMENUINFO_H

#include "classes/gf/GfFieldTime.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// the save menu's summary of a save (0x518 bytes): GfGameUtilSaveData::getSaveDataMenuInfo fills it and
// GfMenuObjSaveLoad2::refreshSave shows it. The symbols name the type only; the member names are not the original's.
class SaveMenuInfo {
public:
    // one party driver (16 bytes): GfGameUtilSaveData::fn_71002EAF78 fills one per driver id of the save
    class Driver {
    public:
        unsigned short m_driver;  // the driver's id, 0 for none
        short m_bladeTop;  // the first of m_blades refreshSave shows (wrapped at GfMenuObjUtil::getBladeSlotMax)
        unsigned short m_level;
        unsigned short m_blades[3];  // the driver's engaged blades
        unsigned char pad_c[0x4];
    };
    // one party driver of the add-on story (8 bytes), what refreshSave shows with GfMenuObjUtil::isValidExpansion(3)
    class IraDriver {
    public:
        unsigned short m_driver;  // the driver's id, 0 for none
        unsigned short m_blade1;  // the first blade (IMG_blade1 and IMG_blade3), 0 for none
        unsigned short m_blade2;  // the second blade (IMG_blade2), 0 for none
        unsigned short m_level;  // 1 without a driver
    };

    SaveMenuInfo() : m_saveTime(), m_playTime() {}

    Driver m_drivers[10];
    IraDriver m_iraDrivers[10];  // 0xA0
    RealTime m_saveTime;  // 0xF0
    ElapseTime m_playTime;  // 0xF8
    unsigned int m_scenario;  // 0xFC: the save's scenario flag
    unsigned short m_progress;  // 0x100: m_scenario / 1000, 1 for none
    unsigned short m_mapJump;  // 0x102: GfDataMap::getMapID's argument
    bool m_newGame;  // 0x104: true when GfManager::isExistSaveData does not hold
    mm::mtl::FixedVector<unsigned short, 512> m_events;  // 0x108: the event theater's watched events
    unsigned char pad_510[0x8];  // 0x510: a bool fn_71002EAF78 copies from the save (0x1AE91), then padding
};
}  // namespace gf

#endif
