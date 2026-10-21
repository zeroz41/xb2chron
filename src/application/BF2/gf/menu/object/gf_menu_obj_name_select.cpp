#include "classes/gf/GfMenuObjMovieLayer.h"
#include "classes/gf/GfMovieManager.h"

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

}  // namespace gf
