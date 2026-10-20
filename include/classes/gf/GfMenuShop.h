#ifndef CLASSES_GF_GFMENUSHOP_H
#define CLASSES_GF_GFMENUSHOP_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5F030; its destructor is its singleton's
class GfMenuShop : public ::mm::mtl::PtrSingleton<GfMenuShop> {
public:
    GfMenuShop(const GfSetupParam& param);
    virtual ~GfMenuShop();  // slot 0
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
