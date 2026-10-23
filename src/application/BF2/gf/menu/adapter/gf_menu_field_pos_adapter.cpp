#include "classes/gf/GfMenuFieldPosAdapter.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "mm/Vec3.h"

namespace gf {

GfMenuFieldPosAdapter::~GfMenuFieldPosAdapter() {
    ;  // the original's body compiled away; clang skips the table store for an empty one
}

GfMenuFieldPosAdapter* GfMenuFieldPosAdapter::create(unsigned int handle, const mm::Vec3& pos, bool keepAdjusted) {
    ui::UIObjectPlugin* plugin = ui::UIObjectPosPlugin::create(handle, 0, 0);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 55
    GfMenuFieldPosAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuFieldPosAdapter(plugin);
    if (adapter != nullptr) {
        adapter->setup(handle, pos, keepAdjusted);
    }
    plugin->release();
    return adapter;
}

GfMenuFieldPosAdapter* GfMenuFieldPosAdapter::create(unsigned int handle, const mm::Vec3& pos) {
    return create(handle, pos, false);
}

// update: not written yet (2 words apart: the registers of the 10000, 10000 position); see wip
// fn_710033D6E4: not written yet (55 words apart: the order the projection's rows are computed in)

}  // namespace gf
