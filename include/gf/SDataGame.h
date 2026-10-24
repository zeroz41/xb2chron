#ifndef GF_SDATAGAME_H
#define GF_SDATAGAME_H

#include "gf/GameFlag.h"
#include "gf/SDataBlade.h"
#include "gf/SDataDriver.h"
#include "gf/GfDataMercenaries.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Vec3.h"

namespace gf {
// the game's data, as GfDataManager::getDataGame hands it out (1.0.0's GfGameUtil::setupNewGameParam takes one;
// that getDataGame's is one is inferred)
class SDataGame {
public:
    unsigned int m_money;  // 0x0 (named after its accessors; the name is not the original's)
    // 0x4-0x24: the landmark point, its position and Y rotation (1.0.0's GfFieldManager::setLandmarkPoint stores them,
    // getLandmarkPoint/Pos/RotY read them; the names are not the original's)
    unsigned int m_landmarkPoint;
    unsigned char pad_8[0x8];
    mm::Vec3 m_landmarkPos;
    float m_landmarkRotY;
    unsigned char pad_24[0x4];
    unsigned short m_eventChapterSave;  // 0x28 (named after its accessors; the name is not the original's)
    unsigned char pad_2A[0x2];
    // by GfDataDriver::getSDataDriver (rows 1-16; the name is not the original's)
    SDataDriver m_drivers[16];
    // by GfDataBlade::getBladeIndex (the name is not the original's; the count is the indexes it hands out)
    SDataBlade m_blades[422];
    unsigned char pad_E9884[0x12340];  // GfDataParty::getSDataParty points at its start
    GameFlag m_gameFlag;  // GfGameFlag's (the name is not the original's)
    unsigned int m_scenario;  // 0x1097E4 (named after its accessors; the name is not the original's)
    unsigned int m_select;  // 0x1097E8 (named after its accessors; the name is not the original's)
    unsigned char pad_1097EC[0xC4];
    unsigned int m_skipTravelID;  // 0x1098B0 (named after its accessors; the name is not the original's)
    unsigned char pad_1098B4[0x14];
    // 0x1098C8: the mercenary teams (GfDataMercenaries' team functions search them; getTeamByIndex asserts in
    // fixed_vector.h's operator[]; the capacity is the room before the count at 0x109940; the name is not the original's)
    mm::mtl::FixedVector<GfDataMercenaries::Team, 3> m_teams;
    unsigned char pad_109948[0x1E0];
    float m_playerCameraDistance;  // 0x109B28 (named after its accessors; the name is not the original's)
    unsigned char pad_109B2C[0x1210];
    unsigned int m_ether;  // 0x10AD3C (named after its accessors; the name is not the original's)
    unsigned char pad_10AD40[0x8];
    unsigned int m_assurePoint;  // 0x10AD48 (named after its accessors; the name is not the original's)
    unsigned int m_assureCount;  // 0x10AD4C (named after its accessors; the name is not the original's)
    unsigned short m_rareBladeAppearType;  // 0x10AD50 (named after its accessors; the name is not the original's)
    unsigned char pad_10AD52[0x2];
    unsigned int m_coin;  // 0x10AD54 (named after its accessors; the name is not the original's)
    unsigned char pad_10AD58[0x18];
    float m_cameraHeight;  // 0x10AD70 (named after its accessors; the name is not the original's)
    unsigned char pad_10AD74[0x100];
    float m_cameraYaw;  // 0x10AE74 (named after its accessors; the name is not the original's)
    float m_cameraPitch;  // 0x10AE78 (named after its accessors; the name is not the original's)
    unsigned char m_cameraFreeMode;  // 0x10AE7C (named after its accessors; the name is not the original's)
    unsigned char m_hikariCurrent;  // 0x10AE7D (named after its accessors; the name is not the original's)
    unsigned short m_autoEventAfterLoad;  // 0x10AE7E (named after its accessors; the name is not the original's)
    unsigned char m_collectFlagNewVersion;  // 0x10AE80 (named after its accessors; the name is not the original's)
    unsigned char pad_10AE81[0x1];
    unsigned char m_cameraSide;  // 0x10AE82 (named after its accessors; the name is not the original's)
};
}  // namespace gf

#endif
