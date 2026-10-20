#ifndef CLASSES_GF_GFGAMEFLAG_H
#define CLASSES_GF_GFGAMEFLAG_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B50FA0; its destructor is its singleton's
class GfGameFlag : public ::mm::mtl::PtrSingleton<GfGameFlag> {
public:
    GfGameFlag(const GfSetupParam& param);
    virtual ~GfGameFlag();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static bool isInitialized();
    bool m_initialized;  // set by initialize, cleared by finalize
};
}  // namespace gf

#endif
