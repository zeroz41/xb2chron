#ifndef CLASSES_GF_GFDATASTORE_H
#define CLASSES_GF_GFDATASTORE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/SDataOption.h"
#include "gf/SDataSaveIra.h"
#include "gf/SDataDlc.h"

namespace gf { class GfDataStore; class GfSetupParam; }

namespace gf {
// table 0x7100B50B18: the game's data (the system, the game, the options, the DLC drivers and the block after them,
// laid out as a save keeps them): 0x137BB0 bytes (build allocates them)
class GfDataStore : public ::mm::mtl::PtrSingleton< ::gf::GfDataStore> {
public:
    GfDataStore(const GfSetupParam& param);
    virtual ~GfDataStore();  // slot 0
    void initialize(const GfSetupParam& param);  // 1.0.0's, inline in 3.0.1's constructor
    static void build(const GfSetupParam& param);
    static void destroy();  // destroy
    static void clear();
    static void initGameData();
    static void initOptionData();  // 1.0.0's, inline in 3.0.1's clear and constructor
    static SDataSystem& getDataSystem();
    static SDataGame& getDataGame();
    static SDataOption& getDataOption();
    // 2.0.0's symbols name it. What it does: returns the DLC drivers (GfDataDriver::getSDataDriver's rows 0x11-0x19).
    static SDataDlc& getDataGameIra();
    // 1.0.0's GfDataManager::setupGame calls setGameData; 3.0.1's calls fn_710022D7DC (the symbols spell it so), which
    // copies the three blocks and calls checkAndReplaceGameData: this is setGameData
    static void setGameData(const SDataSystem* system, const SDataGame* game, const SDataOption* option);
    // 2.0.0's symbols name it. What it does: takes no arguments; fixes up the game data after a load (Hikari current,
    // clamps game+0x1176A8 to 100, version stamp at 0x117388 with a 0x306 memset, GfDataUtil::setupUi1868ForSDataGame) and tail-calls
    // fn_710022D55C.
    static void checkAndReplaceGameData();
    static void setupOptionData(const SDataOption& option);

    SDataSystem m_system;  // 0x8 (the member names are not the original's)
    SDataGame m_game;  // 0x20
    SDataOption m_option;  // 0x126DA0
    // 0x126E28: the DLC drivers and the block a save keeps after them (SDataSaveIra's m_dlcDrivers and pad_134850)
    SDataDlc m_dlc;
    bool m_initialized;  // 0x137BA8: destroy clears it, initialize sets it
};
}  // namespace gf

#endif
