#include "classes/gf/GfMenuObjMovieLayer.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIScreenObject.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjNameSelect.h"
#include "classes/gf/GfMenuObjNameSelect/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

void GfMenuObjNameSelect::update() {
    GfMenuObject::update();
}

void GfMenuObjNameSelect::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjNameSelect::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
// the second piece of gf_menu_obj_name_select.cpp: its citations name that file
#line 52 "D:/Monolithsoft/BF2/prog/application/BF2/gf/menu/object/gf_menu_obj_name_select.cpp"
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::initialize();
}

GfMenuObjNameSelect::~GfMenuObjNameSelect() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

GfMenuObjNameSelect::GfMenuObjNameSelect(unsigned int handle) : GfMenuObject(handle), m_context(nullptr) {
    m_context = GfMenuCallContext::create();
}

}  // namespace gf
