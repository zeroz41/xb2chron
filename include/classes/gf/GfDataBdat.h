#ifndef CLASSES_GF_GFDATABDAT_H
#define CLASSES_GF_GFDATABDAT_H

#include "classes/gf/IDataBdat.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfDataBdat; }
namespace gf { class GfSetupParam; }
namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
namespace _gfbdat {
// the BDAT tables' names, by the id getFP takes
extern const char* s_aszGfBdatName[481];
}  // namespace _gfbdat

// table 0x7100B4D7B8 (1.0.0's _ZTVN2gf10GfDataBdatE): the BDAT tables, each loaded table by its id, and the table
// classes built on them
class GfDataBdat : public ::mm::mtl::PtrSingleton< ::gf::GfDataBdat>, public ::gf::IGfEvent {
public:
    GfDataBdat(const GfSetupParam& param);
    virtual ~GfDataBdat();  // slot 0
    virtual void gevReloadBdat(gf::RELOAD_BDAT type, unsigned int id);  // slot 2
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static bool isInitialized();
    bool loadBdat(const char* name, unsigned int slot);
    bool isBdatLoading(unsigned int slot) const;
    static void setupBdatInfo();
    static void releaseBdatInfo();
    void destroyBdat(unsigned int slot);
    static unsigned char* getFP(unsigned int id);  // the loaded BDAT file of that id
    static unsigned int getReloadCount();

    // the loaded tables by id (setupBdatInfo looks each name up), how many times they were looked up, whether
    // initialize ran, and the table classes it built (the names are not the original's)
    unsigned char* m_fp[481];
    unsigned int m_reloadCount;
    bool m_initialized;
    mm::mtl::FixedVector<IDataBdat*, 128> m_bdats;
};
}  // namespace gf

#endif
