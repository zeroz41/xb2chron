#include "classes/gf/GfMenuObjBtlMdlView.h"

namespace gf {

GfMenuObjBtlMdlView::GfMenuObjBtlMdlView(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjBtlMdlView::~GfMenuObjBtlMdlView() {
    ;  // stores the class's table: clang skips the store for an empty body
}

void GfMenuObjBtlMdlView::initialize() {
    GfMenuObject::initialize();
}

void GfMenuObjBtlMdlView::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBtlMdlView::update() {
    GfMenuObject::update();
}

}  // namespace gf
