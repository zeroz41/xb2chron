#ifndef CLASSES_GF_GFDATASTORE_H
#define CLASSES_GF_GFDATASTORE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/SDataOption.h"
#include "gf/SDataSave.h"
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
    static void destroy();  // fn_710022D040
    static void clear();
    static void initGameData();
    static void initOptionData();  // 1.0.0's, inline in 3.0.1's clear and constructor
    static SDataSystem& getDataSystem();
    static SDataGame& getDataGame();
    static SDataOption& getDataOption();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the singleton's
    // object like getDataGame. What it does: returns the DLC drivers (GfDataDriver::getSDataDriver's rows 0x11-0x19).
    static SDataDlc& fn_710022D440();
    // 1.0.0's GfDataManager::setupGame calls setGameData; 3.0.1's calls fn_710022D7DC (the symbols spell it so), which
    // copies the three blocks and calls fn_710022D478: this is setGameData
    static void setGameData(const SDataSystem* system, const SDataGame* game, const SDataOption* option);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (the symbols spelled it setGameData, which
    // setupGame's call proves is fn_710022D7DC). A member because setGameData calls it after copying the data. What it
    // does: takes no arguments; fixes up the game data after a load (Hikari current, clamps game+0x1176A8 to 100,
    // version stamp at 0x117388 with a 0x306 memset, fn_71002322E0) and tail-calls fn_710022D55C.
    static void fn_710022D478();
    static void setupOptionData(const SDataOption& option);

    SDataSystem m_system;  // 0x8 (the member names are not the original's)
    SDataGame m_game;  // 0x20
    SDataOption m_option;  // 0x126DA0
    // 0x126E28: the DLC drivers and the block a save keeps after them (SDataSave's m_dlcDrivers and pad_134850)
    SDataDlc m_dlc;
    bool m_initialized;  // 0x137BA8: destroy clears it, initialize sets it
};
}  // namespace gf

#endif
