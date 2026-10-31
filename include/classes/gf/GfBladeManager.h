#ifndef CLASSES_GF_GFBLADEMANAGER_H
#define CLASSES_GF_GFBLADEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBladeManager; class GfSetupParam; }

namespace gf {
namespace _gfdbm {
// .data 0x7100B53A88, initially 1: GfBladeManager's constructor sets it to 1, fn_7100297864 reads and updates it
extern int s_outofname;
}  // namespace _gfdbm

// table 0x7100B53A90; 0x10 bytes (build allocates so many)
class GfBladeManager : public ::mm::mtl::PtrSingleton< ::gf::GfBladeManager> {
public:
    GfBladeManager() {
        _gfdbm::s_outofname = 1;
        m_initialized = true;
    }
    virtual ~GfBladeManager();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static void setupGame();
    static bool isBindRareBladeCrystal(unsigned int item);

    bool m_initialized;  // build sets it, destroy clears it
};
}  // namespace gf

#endif
