#ifndef CLASSES_GF_GFMENUPRECIOUS_H
#define CLASSES_GF_GFMENUPRECIOUS_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5EEC8; its destructor is its singleton's
class GfMenuPrecious : public ::mm::mtl::PtrSingleton<GfMenuPrecious> {
public:
    GfMenuPrecious(const GfSetupParam& param);
    virtual ~GfMenuPrecious();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static bool isInitialized();
    void postUpdate(const fw::UpdateInfo& info);
    bool m_initialized;  // set by initialize, cleared by finalize
};
}  // namespace gf

#endif
