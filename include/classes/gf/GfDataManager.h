#ifndef CLASSES_GF_GFDATAMANAGER_H
#define CLASSES_GF_GFDATAMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace gf { class GfDataManager; }
namespace gf { class SDataGame; }
namespace gf { class SDataSystem; }
namespace gf { class SDataOption; }
namespace gf { struct SDataDriverDlc; }
namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
// table 0x7100B4DA08 (its primary part: the destructors and gevReloadBdat, the overrider of IGfEvent's slot 52; the
// IGfEvent part at 8 holds the thunks)
class GfDataManager : public ::mm::mtl::PtrSingleton< ::gf::GfDataManager>, public ::gf::IGfEvent {
public:
    GfDataManager(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    virtual ~GfDataManager();  // slot 0
    // 1.0.0's GfDataBdat::gevReloadBdat refreshed the tables here; 3.0.1's GfDataManager overrides it (its thunk in the
    // IGfEvent part has the same body)
    virtual void gevReloadBdat(RELOAD_BDAT type, unsigned int id);  // slot 2
    static void clear();
    static void setupGame(const SDataSystem* system, const SDataGame* game, const SDataOption* option);
    static void setupOptionData(const SDataOption& option);
    static SDataSystem* getDataSystem();  // GfDataStore's
    static SDataGame* getDataGame();  // GfDataStore's
    static SDataOption* getDataOption();  // GfDataStore's
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address follows
    // getDataGame's in this unit and, like it, it only forwards to a GfDataStore function (fn_710022D440). What it
    // does: returns the DLC drivers' data, 0xDAC-byte records for driver rows 0x11-0x19 (GfDataDriver::getSDataDriver
    // indexes it with row - 0x11).
    static SDataDriverDlc* fn_7100224A10();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in this
    // unit and it takes no object (GfDataManager's statics fill the unit). What it does: GfDataItem::getItemType of
    // item, then by the type (1..0x14, jump table 0x71009B9BCC) a per-type function on the matching parts of the
    // favorite item area (SDataGame::m_favoriteItemType) and the item box (SDataGame::m_itemBox); 0 for an unknown
    // item. GfGameUtilSaveData::fn_71002EDC78 / fn_71002EDCEC pass items 25495 / 25496 and test it against 0.
    static unsigned int fn_7100223650(unsigned char* favorite, unsigned char* box, unsigned int item);

private:
    // 1.0.0's initialize and finalize (the constructor and destroy hold their bodies in 3.0.1)
    void initialize(const GfSetupParam& param);
    void finalize();

    bool m_initialized;  // 0x10 (1.0.0's isInitialized reads it; the name is not the original's)
};
}  // namespace gf

#endif
