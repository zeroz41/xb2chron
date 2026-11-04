#include "classes/gf/GfMenuObjNamedDialog.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {

GfMenuObjNamedDialog::GfMenuObjNamedDialog(unsigned int handle) : GfMenuObject(handle), m_list(nullptr) {
    m_list = GfMenuIDList::create();
}

GfMenuObjNamedDialog::~GfMenuObjNamedDialog() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

// fn_71004451D0 and close (the open and close calls) and initialize (0x71004452C4) are not here yet: see the
// report

void GfMenuObjNamedDialog::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjNamedDialog::update() {
    GfMenuObject::update();
}

// TUnk_B638A8::reciveEvent (0x7100445478) is not here yet: see the report

}  // namespace gf
