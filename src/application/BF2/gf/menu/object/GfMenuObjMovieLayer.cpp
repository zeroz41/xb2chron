#include "classes/gf/GfMenuObjMovieLayer.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIScreenObject.h"
#include "ui/UIUtil.h"

namespace gf {

GfMenuObjMovieLayer::GfMenuObjMovieLayer(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjMovieLayer::~GfMenuObjMovieLayer() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjMovieLayer::initialize() {
    GfMenuObject::attachExternalCall(0x7E, m_handle);
    GfMenuObject::initialize();
}

void GfMenuObjMovieLayer::finalize() {
    GfMovieManager::get()->close();
    GfMenuObject::finalize();
}

void GfMenuObjMovieLayer::update() {
    GfMenuObject::update();
}

unsigned int GfMenuObjMovieLayer::m_CreatedCount;

unsigned int GfMenuObjMovieLayer::createMovieLayer(unsigned int width, unsigned int height,
                                                   const ui::UIScreenObject::OnMemoryInfo& info) {
    if (GfMenuObject::getAttachedObject(0x7E) == 0) {
        return 0;
    }
    ui::UIObject* object = ui::UIUtil::getObject(GfMenuObject::getAttachedObject(0x7E));
    ui::UILayoutObject* layout = object != nullptr && object->getRTTI()->isKindOf(&ui::UILayoutObject::m_rtti)
                                     ? static_cast<ui::UILayoutObject*>(object)
                                     : nullptr;
    mm::mtl::FixStr<32> name;
    name.format("SCR_movie%02d", m_CreatedCount % 100);
    m_CreatedCount++;
    ui::UIScreenObject* screen =
        ui::UIScreenObject::createOnMemory(layout, width, height, name, ui::UIUtil::getProgAllocator(), info);
    unsigned int handle = 0;
    if (screen != nullptr) {
        ui::UIObject::importDisplayInfo(screen->m_displayInfo, screen->m_layer);
        handle = ui::UIUtil::registObject(screen);
        if (handle != 0) {
            layout->addChild(handle, screen);
            screen->m_flags.set(4, true);
        }
    }
    return handle;
}

}  // namespace gf
