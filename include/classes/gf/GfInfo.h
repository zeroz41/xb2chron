#ifndef CLASSES_GF_GFINFO_H
#define CLASSES_GF_GFINFO_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B59228; its destructor is its singleton's
class GfInfo : public ::mm::mtl::PtrSingleton<GfInfo> {
public:
    virtual ~GfInfo();  // slot 0
    static void destroy();
    void finalize();
    static bool isInitialized();
    bool m_initialized;  // cleared by the constructor and finalize
    static int m_nScreenW;
};

int GfScreenW();  // GfInfo::m_nScreenW
}  // namespace gf

#endif
