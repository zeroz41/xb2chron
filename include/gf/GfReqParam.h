#ifndef GF_GFREQPARAM_H
#define GF_GFREQPARAM_H

#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace gf {

// what a request is given (GfReqManager::addCommand takes it and deletes it once the request ran, with no
// virtual destructor)
class GfReqParam {};

// a driver's blades to set up (0xE bytes: 1.0.0's GfMenuObjBladeSet2::makeSetupBlade_Remove fills the driver,
// then the blades at 4 to 0xC). The names are not the original's.
class RQ_SETUP_BLADE {
public:
    RQ_SETUP_BLADE();
    unsigned short m_driver;
    unsigned short m_activeBlade;  // makeSetupBlade_Remove's m_blades[the driver's blade set]
    unsigned short m_blades[5];
};

// the party to set up: ten drivers, each with the blades it engages. The names are not the original's.
class RQ_SETUP_PARTY {
public:
    RQ_SETUP_PARTY();  // GfAppendWire's unit holds its C2 (0x710028D7E8)
    struct Driver {
        unsigned int m_driver;  // getAllBlade asks GfDataDriver::getMaxSetBladeNum with it
        unsigned int m_activeIndex;  // the engaged blade's index (replaceActBlade engages the first with the default)
        unsigned short m_blades[5];  // 0: none
        unsigned short pad_12;
    };
    // every blade the drivers engage (3.0.1's vector holds 32: its push_back asserts the size below 32)
    void getAllBlade(mm::mtl::FixedVector<unsigned int, 32>& blades) const;
    // every act blade to the common blade it stands for, and the DLC drivers to their default blades
    void replaceActBlade();

    // two more members past the drivers: replaceActBlade turns the id of one whose type is 4 into its common blade.
    // The names are not the original's.
    struct Extra {
        unsigned int m_type;
        unsigned int m_id;
    };

    Driver m_drivers[10];
    unsigned char pad_C8[0x3C];  // the constructor zeroes 0xC8 to 0x115 (one memset)
    Extra m_extras[2];
    // 0x240 bytes in all: GfGameParty's copy at 0x130 ends where its m_currentPartyValid (0x370) starts
    unsigned char pad_114[0x12C];
};

// where a map jump goes. The names are not the original's.
class GfMapjumpInfo {
public:
    // for a game loaded from save data (GfManager::startGame: the saved map, position and rotation in radians,
    // and GfDataUtil::isStartChapterSave)
    void setupForSaveData(unsigned int map, const mm::Vec3& pos, const mm::Vec3& rot, bool startChapter);

    // a position and turn after the jump; GfMapjumpInfo holds nine (its copy, out of line in gf_play_command, copies
    // each one's Vec3, then the float and the bool only). The name is not the original's
    class Point {
    public:
        mm::Vec3 m_pos;
        float m_rotY;
        bool m_setRotY;
    };

    unsigned int m_map;
    unsigned char pad_4[0xC];
    // a text of up to 31 characters (the copy runs FixStr's strlen, assert and strcpy on it)
    mm::mtl::FixStr<32> pad_10;
    mm::Vec3 m_pos;
    float m_rotY;
    bool m_setRotY;
    // eight more positions after m_pos's; the name is not the original's
    Point m_points[8];
    bool m_fromSaveData;
    bool m_startChapter;
    unsigned char pad_162[0x2];
    // the jump stops the player (GfPlayFactory::createMapjump wraps it in addEventPlayerStop and state 9 instead of
    // 8); the name is not the original's
    bool m_stopPlayer;
    unsigned char pad_165[0x3];
    unsigned int m_kind;  // setupForSaveData's 1
};

}  // namespace gf

#endif
