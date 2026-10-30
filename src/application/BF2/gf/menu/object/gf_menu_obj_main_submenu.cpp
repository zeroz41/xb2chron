#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjMainSubmenu.h"
#include "classes/gf/GfMenuObjMainSubmenu/ListListener.h"
#include "classes/gf/GfMenuObjMainSubmenu/MainListener.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UISelectObjList.h"

namespace gf {

GfMenuObjMainSubmenu::GfMenuObjMainSubmenu(unsigned int handle)
    : GfMenuObject(handle), m_kind(0), m_guideText(0), m_subIndexText(0), m_list(nullptr), m_items(),
      m_fadeOnClose(true), m_context(nullptr) {
    for (int i = 0; i < 5; i++) {
        m_growCtrl[i] = -1;
    }
}

GfMenuObjMainSubmenu::~GfMenuObjMainSubmenu() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void GfMenuObjMainSubmenu::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMainSubmenu::update() {
    GfMenuObject::update();
}

}  // namespace gf
