#include "classes/gf/GfMenuObjMainRoot.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjMainRoot/MainListener.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuTypes.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjMainRoot::GfMenuObjMainRoot(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjMainRoot::~GfMenuObjMainRoot() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjMainRoot::registOpenParam(const OpenParam& param) {
    GfMenuTypes::Param layerParam;
    layerParam.m_menuId = param.m_menuId;
    GfMenuFullScreen::registLayerParam(GfMenuFullScreen::getScreenLayerID(2), layerParam);
}

void GfMenuObjMainRoot::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object == nullptr) {
        return;
    }
#line 54
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuTypes::Param param;
    unsigned int menuId = GfMenuObject::getFSLayerParam(m_fsLayer, param) ? param.m_menuId : 1;
    unsigned short layer = GfMenuObject::getMenuLayerID(menuId);
    GfMenuObject::changeFSSubLayer(acc.m_handle, 1, layer, true);
    acc.setDispChild(true, "IMG_bg_black");
    GfMenuObject::setFSShadowLayer(m_fsLayer, true);
    GfMenuObject::disableInput(acc.m_handle);
    GfMenuObject::initialize();
}

void GfMenuObjMainRoot::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMainRoot::update() {
    GfMenuObject::update();
}

void GfMenuObjMainRoot::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 8:
        if (event.m_param1 == 3) {
            GfMenuObject::closeFSLayer(acc.m_handle, true, true);
        }
        break;
    case 0x43:
        GfMenuObject::closeFSLayer(acc.m_handle, true, true);
        UIObjectListener::reciveEvent(event, handle);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

GfMenuObjMainRoot::MainListener::~MainListener() {}

}  // namespace gf
