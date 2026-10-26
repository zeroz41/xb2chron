#include "mm/mtl/FixStr.h"
#include "mm/mtl/Map.h"
#include "fw/PadRelay.h"
#include "gf/CameraPadData.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

CameraPadData::CameraPadData() {
    reset();
    bind();
}

void CameraPadData::bind() {
    PadRelay::bind(0, 2, getAllocator(ALLOCATOR(0)));
    bindAction("reset", this, &CameraPadData::resetAction);
    bindAction("zoom", this, &CameraPadData::zoomCamera);
    bindAction("height", this, &CameraPadData::heightCamera);
    bindAction("side_left", this, &CameraPadData::sideLeftCamera);
    bindAction("side_right", this, &CameraPadData::sideRightCamera);
    bindAction("side_reset", this, &CameraPadData::sideResetCamera);
    bindAction("all_reset", this, &CameraPadData::allResetAction);
    bindAxis("arx", this, &CameraPadData::setARX);
    bindAxis("ary", this, &CameraPadData::setARY);
}

CameraPadData::~CameraPadData() {
    unbind();
}

void CameraPadData::update() {
    reset();
    PadRelay::update();
}

void CameraPadData::resetAction() {
    m_reset = true;
}

void CameraPadData::zoomCamera() {
    m_zoom = true;
}

void CameraPadData::heightCamera() {
    m_height = true;
}

void CameraPadData::sideLeftCamera() {
    m_sideLeft = true;
}

void CameraPadData::sideRightCamera() {
    m_sideRight = true;
}

void CameraPadData::sideResetCamera() {
    m_sideReset = true;
}

void CameraPadData::allResetAction() {
    m_allReset = true;
}

void CameraPadData::setARX(float value) {
    m_arx = value;
}

void CameraPadData::setARY(float value) {
    m_ary = value;
}

}  // namespace gf
