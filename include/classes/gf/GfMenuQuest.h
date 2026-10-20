#ifndef CLASSES_GF_GFMENUQUEST_H
#define CLASSES_GF_GFMENUQUEST_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5EF08; its destructor is its singleton's
class GfMenuQuest : public ::mm::mtl::PtrSingleton<GfMenuQuest> {
public:
    GfMenuQuest(const GfSetupParam& param);
    virtual ~GfMenuQuest();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static bool isInitialized();
    void postUpdate(const fw::UpdateInfo& info);
    bool m_initialized;  // set by initialize, cleared by finalize
    // what openMenu (1.0.0 has it) last asked for: its second argument, its first, and its flag
    unsigned int m_openValue;
    unsigned int m_openId;  // none: -1
    bool m_openFlag;
};
}  // namespace gf

#endif
