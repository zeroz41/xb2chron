#ifndef CLASSES_GF_GFGAMETALK_H
#define CLASSES_GF_GFGAMETALK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B591A8; its destructor is its singleton's
class GfGameTalk : public ::mm::mtl::PtrSingleton<GfGameTalk> {
public:
    GfGameTalk(const GfSetupParam& param);
    virtual ~GfGameTalk();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static bool isInitialized();
    void update(const fw::UpdateInfo& info);
    bool m_initialized;  // set by initialize, cleared by finalize
};
}  // namespace gf

#endif
