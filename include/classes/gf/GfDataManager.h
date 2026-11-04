#ifndef CLASSES_GF_GFDATAMANAGER_H
#define CLASSES_GF_GFDATAMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/SDataGame.h"

namespace gf { class GfSetupParam; }
namespace gf { class GfDataManager; }
namespace gf { class SDataGame; }
namespace gf { class SDataSystem; }
namespace gf { class SDataGameIra; }
namespace gf { class SDataOption; }
namespace gf { struct SDataDlc; }
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
    // 2.0.0's symbols spell the fourth parameter, which goes on to GfDataStore::setGameData
    static void setupGame(const SDataSystem* system, const SDataGame* game, const SDataOption* option,
                          const SDataGameIra* ira);
    static void setupOptionData(const SDataOption& option);
    static SDataSystem* getDataSystem();  // GfDataStore's
    static SDataGame* getDataGame();  // GfDataStore's
    static SDataOption* getDataOption();  // GfDataStore's
    // 2.0.0's symbols name it. What it does: returns the DLC drivers' data (GfDataDriver::getSDataDriver indexes its
    // 0xDAC-byte driver records with row - 0x11).
    static SDataDlc* getDataGameIra();

private:
    // 1.0.0's initialize and finalize (the constructor and destroy hold their bodies in 3.0.1)
    void initialize(const GfSetupParam& param);
    void finalize();

    bool m_initialized;  // 0x10 (1.0.0's isInitialized reads it; the name is not the original's)
};
}  // namespace gf

#endif
