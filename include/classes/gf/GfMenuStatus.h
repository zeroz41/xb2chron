#ifndef CLASSES_GF_GFMENUSTATUS_H
#define CLASSES_GF_GFMENUSTATUS_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5F0B0; its destructor is its singleton's
class GfMenuStatus : public ::mm::mtl::PtrSingleton<GfMenuStatus> {
public:
    GfMenuStatus(const GfSetupParam& param);
    virtual ~GfMenuStatus();  // slot 0
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
