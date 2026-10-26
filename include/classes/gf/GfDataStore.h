#ifndef CLASSES_GF_GFDATASTORE_H
#define CLASSES_GF_GFDATASTORE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/SDataOption.h"
#include "gf/SDataSave.h"

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
    static SDataSystem* getDataSystem();
    static SDataGame* getDataGame();
    static SDataOption* getDataOption();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the singleton's
    // object like getDataGame. What it does: returns the DLC drivers (GfDataDriver::getSDataDriver's rows 0x11-0x19).
    static SDataDriverDlc* fn_710022D440();
    static void setGameData(const SDataSystem* system, const SDataGame* game, const SDataOption* option);
    static void setupOptionData(const SDataOption& option);

    SDataSystem m_system;  // 0x8 (the member names are not the original's)
    SDataGame m_game;  // 0x20
    SDataOption m_option;  // 0x126DA0
    SDataDriverDlc m_dlcDrivers[16];  // 0x126E28
    // 0x1348E8: the block a save keeps after its DLC drivers (SDataSave's pad_134850)
    unsigned char m_dlcBlock[0x32C0];
    bool m_initialized;  // 0x137BA8: destroy clears it, initialize sets it
};
}  // namespace gf

#endif
