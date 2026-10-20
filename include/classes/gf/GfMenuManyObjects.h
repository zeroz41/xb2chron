#ifndef CLASSES_GF_GFMENUMANYOBJECTS_H
#define CLASSES_GF_GFMENUMANYOBJECTS_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5ED80; its destructor is its singleton's
class GfMenuManyObjects : public ::mm::mtl::PtrSingleton<GfMenuManyObjects> {
public:
    GfMenuManyObjects(const GfSetupParam& param);
    virtual ~GfMenuManyObjects();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static bool isInitialized();
    void postUpdate(const fw::UpdateInfo& info);
    bool m_initialized;  // set by initialize, cleared by finalize
    // remove and closeAll (templates on the kind of object) index the first eight: each a queue of that kind's
    // open objects, or none
    void* m_queues[9];
};
}  // namespace gf

#endif
