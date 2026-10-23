#include "classes/gf/TUnk_B63860.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {

TUnk_B63860::TUnk_B63860(unsigned int handle) : GfMenuObject(handle), m_list(nullptr) {
    m_list = GfMenuIDList::create();
}

TUnk_B63860::~TUnk_B63860() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

// fn_71004451D0 and fn_7100445258 (the open and close calls) and initialize (0x71004452C4) are not here yet: see the
// report

void TUnk_B63860::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B63860::update() {
    GfMenuObject::update();
}

// TUnk_B638A8::reciveEvent (0x7100445478) is not here yet: see the report

}  // namespace gf
