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

namespace gf {
// table 0x7100B4DA08
class GfDataManager : public ::mm::mtl::PtrSingleton< ::gf::GfDataManager>, public ::gf::IGfEvent {
public:
    static void build(const GfSetupParam& param);
    static void destroy();
    virtual ~GfDataManager();  // slot 0
    virtual void vf2();  // slot 2
    static void clear();
    static void setupGame(const SDataSystem* system, const SDataGame* game, const SDataOption* option);
    static void setupOptionData(const SDataOption& option);
    static SDataGame* getDataGame();  // GfDataStore's
    static SDataOption* getDataOption();  // GfDataStore's
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address follows
    // getDataGame's in this unit and, like it, it only forwards to a GfDataStore function (fn_710022D440). What it
    // does: returns the DLC drivers' data, 0xDAC-byte records for driver rows 0x11-0x19 (GfDataDriver::getSDataDriver
    // indexes it with row - 0x11).
    static SDataDriverDlc* fn_7100224A10();
};
}  // namespace gf

#endif
