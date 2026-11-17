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

// the party's drivers alone (GfGameParty::getCurrentPartyInfo fills the ten members' drivers, then the game data's
// leader). The field names are not the original's.
class RQ_SETUP_PARTY_DRIVER {
public:
    unsigned short m_drivers[10];
    unsigned int m_leader;
};

// what GfGameParty::getPartyPosition fills: one record per party slot (0x20 bytes each; the member names are
// not the original's: the constructor sets the position to mm::Vec3::zero and the rest to zero)
struct GfPartyPosInfo {
    struct Pos {
        Pos() : m_pos(mm::Vec3::zero), m_rotY(0), m_isValid(false) {}
        mm::Vec3 m_pos;
        // the y rotation setupPartyPositionByPartyPosition gives the slot's object setup (GfObjSetup::pad_30.y)
        float m_rotY;
        bool m_isValid;
    };
    Pos m_pos[9];
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
    // the constructor zeroes 0xC8 to 0x115 (one memset). For an Ira game GfGameParty::getCurrentPartyInfo fills these
    // in place of m_drivers: each member's driver in the parties 0-2 (by PTPOS); the name is not the original's
    unsigned short m_iraDrivers[10][3];
    Extra m_extras[2];
    // copied with the members above (SCOM_DESTROY_PARTY_OBJ::create's copy: one memcpy of 0x115 bytes)
    unsigned char pad_114;
    // the party's positions (0x120: the constructor sets them up as GfPartyPosInfo's; the copy copies each one's
    // Vec3, float and bool). 0x240 bytes in all: GfSelectIra's copy (GfGameParty's at 0x130) ends where its
    // m_currentPartyValid (0x240) starts. The name is not the original's
    GfPartyPosInfo m_posInfo;
};

// where a map jump goes. The names are not the original's.
class GfMapjumpInfo {
public:
    // inline (no symbol; SeqManager::start_areajump/end_areajump build one on the stack). The original's stores fix
    // the body's order: the positions, m_kind, then m_flags reset as one (a 7-byte memset) and m_startChapter
    // and pad_162 set true afterwards
    explicit GfMapjumpInfo(unsigned int map) : m_map(map), pad_4(0), pad_8(-1), pad_C(1.0f) {
        m_kind = 0;
        m_flags = Flags();
        m_flags.m_startChapter = true;
        m_flags.pad_162 = true;
    }
    // inline (SCOM_CREATE_PARTY_OBJ's creators build one in place): as above with no map and no flag set. The
    // positions are reset from a temporary: the original loads Vec3::zero's three floats before the first store
    GfMapjumpInfo() : m_map(0), pad_4(0), pad_8(-1), pad_C(1.0f) {
        m_posInfo = GfPartyPosInfo();
        m_kind = 0;
        m_flags = Flags();
    }

    // for a game loaded from save data (GfManager::startGame: the saved map, position and rotation in radians,
    // and GfDataUtil::isStartChapterSave)
    void setupForSaveData(unsigned int map, const mm::Vec3& pos, const mm::Vec3& rot, bool startChapter);

    unsigned int m_map;
    unsigned int pad_4;
    int pad_8;
    float pad_C;
    // a text of up to 31 characters (the copy runs FixStr's strlen, assert and strcpy on it)
    mm::mtl::FixStr<32> pad_10;
    // where the party stands after the jump (0x40: SCOM_CREATE_PARTY_OBJ::exec passes its copy's to
    // GfGameParty::setupPartyPositionByPartyPosition and createPos assigns one; GfMapjumpInfo's copy copies each
    // position's Vec3, then the float and the bool). The name is not the original's
    GfPartyPosInfo m_posInfo;
    // seven bytes the constructor value-initializes as one (a 7-byte memset); the names are not the original's
    struct Flags {
        bool m_fromSaveData;
        bool m_startChapter;
        bool pad_162;
        bool pad_163;
        // the jump stops the player (GfPlayFactory::createMapjump wraps it in addEventPlayerStop and state 9 instead
        // of 8); the name is not the original's
        bool m_stopPlayer;
        unsigned char pad_165;
        unsigned char pad_166;
    };
    Flags m_flags;  // 0x160
    unsigned char pad_167;
    unsigned int m_kind;  // setupForSaveData's 1
};

}  // namespace gf

#endif
