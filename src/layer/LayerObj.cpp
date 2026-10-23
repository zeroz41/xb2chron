#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccFontStyle.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccPolyObj.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccAction.h"
#include "layer/LayerAccDefTexture.h"
#include "layer/LayerAccDefObj.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjWork.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjFont.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/layer/LayerSortObj.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopFont.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjSortDef.h"
#include "classes/layer/LayerObjSortFont.h"
#include "classes/layer/LayerObjSortTexObj.h"
#include "classes/layer/LayerObjSortPolyObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerTagStr.h"

namespace navi {

void NvmshAcObjBase::setMeshNum(int num) { m_isMeshNum = num > 0; }
const mm::Vec3& NvmshAcObjBase::getMoveVec() const { return m_moveVec; }
void NvmshAcObjBase::setBeginPos(const mm::Vec3& pos) { m_beginPos = pos; }
void NvmshAcObjBase::setEndPos(const mm::Vec3& pos) { m_endPos = pos; }
void NvmshAcObjBase::setBeginRadius(float radius) { m_beginRadius = radius; }
void NvmshAcObjBase::setEndRadius(float radius) { m_endRadius = radius; }
void NvmshAcObjBase::setBeginSeachRadius(float radius) { m_beginSeachRadius = radius; }
void NvmshAcObjBase::setEndSeachRadius(float radius) { m_endSeachRadius = radius; }
void NvmshAcObjBase::setBeginHeight(float a, float b) {
    m_beginHeight[0] = a;
    m_beginHeight[1] = b;
}
void NvmshAcObjBase::setEndHeight(float a, float b) {
    m_endHeight[0] = a;
    m_endHeight[1] = b;
}
int NvmshAcObjBase::getMeshNum() const { return m_meshNum; }
void NvmshAcObjBase::setMoveSpd(float spd) { m_moveSpd = spd; }

}  // namespace navi

namespace layer {

LayerTagStr::~LayerTagStr() {}

LayerAccManager::LayerAccManager() {}
LayerBase* LayerAccManager::createObj(const void* resource) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_objManager->createObj(resource);
}
LayerBase* LayerAccManager::createMaskObj(const void* resource) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_objManager->createMaskObj(resource);
}
LayerBase* LayerAccManager::createLayoutObj() {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_objManager->createLayoutObj();
}
LayerBase* LayerAccManager::createTexObj(const grlib::CGLibTextureBuffer& texture) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_objManager->createTexObj(texture);
}
LayerBase* LayerAccManager::createMemObj(unsigned int width, unsigned int height, LayerMemType type) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_objManager->createMemObj(width, height, type);
}
LayerBase* LayerAccManager::createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                                          unsigned short indexCount, LayerPrimitiveType type) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_objManager->createPolyObj(width, height, vertexCount,
                                                                                    indexCount, type);
}
LayerBase* LayerAccManager::createFontResObj(const void* data) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager->createFontResObj(data);
}
LayerBase* LayerAccManager::createFontIconObj(const void* data) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager->createFontIconObj(data);
}
LayerBase* LayerAccManager::createFontStyleObj(const void* data) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager->createStyleObj(data);
}
LayerBase* LayerAccManager::createFontColorMapObj(const void* data) {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager->createFontColMapObj(data);
}
LayerCoordinate LayerAccManager::getCoordinate() const { return mm::mtl::PtrSingleton<LayerManager>::get()->m_coordinate; }
void LayerAccManager::setCoordinate(LayerCoordinate coordinate) {
    mm::mtl::PtrSingleton<LayerManager>::get()->m_coordinate = coordinate;
}

LayerAccAction::LayerAccAction(LayerBase* layer) : m_layer(layer) {}
bool LayerAccAction::isActionData() const { return static_cast<LayerActBase*>(m_layer)->m_actionData != nullptr; }
unsigned int LayerAccAction::getActionMax() const {
    LyrActionData* data = static_cast<LayerActBase*>(m_layer)->m_actionData;
    if (data == nullptr) {
        return 0;
    }
    return data->m_actionMax;
}
float LayerAccAction::getActionSec(unsigned int index) const {
    LyrActionData* data = static_cast<LayerActBase*>(m_layer)->m_actionData;
    if (data != nullptr && index < data->m_actionMax) {
        return data->m_actions[index].m_sec;
    }
    return 0.0f;
}
bool LayerAccAction::actionIdx(unsigned int index) {
    LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    LyrActionData* data = act->m_actionData;
    if (data == nullptr) {
        return false;
    }
    if (index >= data->m_actionMax) {
        return false;
    }
    act->actionIdx(index);
    return true;
}
bool LayerAccAction::actionID(unsigned int id) {
    LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    LyrActionData* data = act->m_actionData;
    if (data == nullptr) {
        return false;
    }
    for (int i = 0; i < data->m_actionMax; i++) {
        if (data->m_actions[i].m_id == id) {
            act->actionIdx(i);
            return true;
        }
    }
    return false;
}
void LayerAccAction::actionEnd() {
    LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    if (act->m_actionData != nullptr) {
        act->actionEnd();
    }
}

LayerAccObjBase::LayerAccObjBase(LayerBase* layer) : m_layer(layer) {}
void LayerAccObjBase::setSpace(LAYER_SPACE_TYPE space) { static_cast<LayerObj*>(m_layer)->m_space = space; }
void LayerAccObjBase::setPos(float x, float y) { static_cast<LayerObj*>(m_layer)->setPos(x, y); }
void LayerAccObjBase::setRot(float rot) { static_cast<LayerObj*>(m_layer)->setRot(rot); }
void LayerAccObjBase::setScale(float x, float y) { static_cast<LayerObj*>(m_layer)->setScale(x, y); }
void LayerAccObjBase::setMulCol(const mm::Col4& col) { static_cast<LayerObj*>(m_layer)->setMulCol(col); }
void LayerAccObjBase::setAddCol(const mm::Col3& col) { static_cast<LayerObj*>(m_layer)->setAddCol(col); }
void LayerAccObjBase::setMatrix(const mm::Mat44& mtx) { static_cast<LayerObj*>(m_layer)->setMatrix(mtx); }
void LayerAccObjBase::getPos(float& x, float& y) const { static_cast<LayerObj*>(m_layer)->getPos(x, y); }
void LayerAccObjBase::getRot(float& rot) const { static_cast<LayerObj*>(m_layer)->getRot(rot); }
void LayerAccObjBase::getScale(float& x, float& y) const { static_cast<LayerObj*>(m_layer)->getScale(x, y); }
const mm::Col4& LayerAccObjBase::getMulCol() const { return static_cast<LayerObj*>(m_layer)->getMulCol(); }
const mm::Mat44& LayerAccObjBase::getMatrix() const { return static_cast<LayerObj*>(m_layer)->getMatrix(); }
void LayerAccObjBase::setBlendType(LayerBlendType type) { static_cast<LayerObj*>(m_layer)->m_blendType = type; }
void LayerAccObjBase::setTexFilterType(LayerTexFilterType type) { static_cast<LayerObj*>(m_layer)->m_texFilterType = type; }
void LayerAccObjBase::setPriority(unsigned short priority) { static_cast<LayerObj*>(m_layer)->m_priority = priority; }
void LayerAccObjBase::setDisp(bool disp) { static_cast<LayerObj*>(m_layer)->setDisp(disp); }
void LayerAccObjBase::setFlip(LayerFlipType type, bool flip) { static_cast<LayerObj*>(m_layer)->setFlip(type, flip); }
unsigned short LayerAccObjBase::getPixelWidth() const { return static_cast<LayerObj*>(m_layer)->m_pixelWidth; }
unsigned short LayerAccObjBase::getPixelHeight() const { return static_cast<LayerObj*>(m_layer)->m_pixelHeight; }
void LayerAccObjBase::setCenterType(LayerCenterType type) { static_cast<LayerObj*>(m_layer)->m_centerType = type; }
LayerCenterType LayerAccObjBase::getCenterType() const {
    return static_cast<LayerCenterType>(static_cast<LayerObj*>(m_layer)->m_centerType);
}
void LayerAccObjBase::setMaskObj(const LayerBase* mask) { static_cast<LayerObj*>(m_layer)->m_maskObj = mask; }
const void* LayerAccObjBase::getResData() const { return static_cast<LayerObj*>(m_layer)->m_resData; }

LayerAccDefObj::LayerAccDefObj(LayerBase* layer) : LayerAccObjBase(layer) {}

LayerAccDefTexture::LayerAccDefTexture(LayerBase* layer) : m_layer(layer) {}
void LayerAccDefTexture::setTexutre(const void* texture) { static_cast<LayerObjWork*>(m_layer)->setAddTexture(texture, 0); }

LayerAccMemObj::LayerAccMemObj(LayerBase* layer) : m_layer(layer), m_memObj(static_cast<LayerObjTopMemObj*>(layer)) {}
void* LayerAccMemObj::getMemBufer() { return m_memObj->getBuffer(); }
void LayerAccMemObj::updateMemBufer() { m_memObj->updateBufer(); }
unsigned int LayerAccMemObj::getMemWidth() const { return m_memObj->m_memWidth; }
unsigned int LayerAccMemObj::getMemHeight() const { return m_memObj->m_memHeight; }
void LayerAccMemObj::setRender(bool render) { m_memObj->setRender(render); }
grlib::CGLibTextureBuffer* LayerAccMemObj::getTexture() { return m_memObj->m_texture; }

LayerAccPolyObj::LayerAccPolyObj(LayerBase* layer) : m_layer(layer), m_polyObj(static_cast<LayerObjTopPolyObj*>(layer)) {}
void LayerAccPolyObj::LockVertex() { m_polyObj->LockVertex(); }
void LayerAccPolyObj::setVertex(unsigned int index, const LayerPolyVertex& vertex) { m_polyObj->setVertex(index, vertex); }
void LayerAccPolyObj::UnlockVertex() { m_polyObj->UnlockVertex(); }
void LayerAccPolyObj::LockIndex() { m_polyObj->LockIndex(); }
void LayerAccPolyObj::setIndex(unsigned int index, unsigned short value) { m_polyObj->setIndex(index, value); }
void LayerAccPolyObj::UnlockIndex() { m_polyObj->UnlockIndex(); }
void LayerAccPolyObj::setIndexInfo(unsigned short start, unsigned short count) { m_polyObj->setIndexInfo(start, count); }
void LayerAccPolyObj::setTexutre(const void* texture) { m_polyObj->setTexutre(texture); }
void LayerAccPolyObj::setTexutre(grlib::CGLibTextureBuffer& texture) { m_polyObj->setTexutre(texture); }

LayerAccFontStyle::LayerAccFontStyle(LayerBase* layer) : m_layer(layer) {}
unsigned int LayerAccFontStyle::getStyleDataMax() const { return static_cast<LayerFontStyleObj*>(m_layer)->m_styleDataMax; }
LayerFontStyleInfo LayerAccFontStyle::getStyleInfo(unsigned int style) const {
    LayerFontStyleObj* obj = static_cast<LayerFontStyleObj*>(m_layer);
    unsigned int max = obj->m_styleDataMax;
    LayerFontStyleInfo info;
    info.m_strings = obj->m_strings;
    info.m_data = style < max ? &obj->m_styleData[style] : obj->m_styleData;
    return info;
}
const char* LayerAccFontStyle::getFontName(unsigned int style) const {
    return static_cast<LayerFontStyleObj*>(m_layer)->getFontName(style);
}
mm::mtl::Vector<LayerStrInfo>* LayerAccFontStyle::createColorInfo(unsigned int count) {
    return static_cast<LayerFontStyleObj*>(m_layer)->createColorInfo(count);
}
mm::mtl::Vector<LayerStrInfo>* LayerAccFontStyle::createIconInfo(unsigned int count) {
    return static_cast<LayerFontStyleObj*>(m_layer)->createIconInfo(count);
}

LayerAccFontObj::LayerAccFontObj(LayerBase* layer) : m_layer(layer) {}
void LayerAccFontObj::setHorizontal(LayerFontHorizontal horizontal) { static_cast<LayerObjFont*>(m_layer)->m_horizontal = horizontal; }
void LayerAccFontObj::setVertical(LayerFontVertical vertical) { static_cast<LayerObjFont*>(m_layer)->m_vertical = vertical; }
void LayerAccFontObj::setDisplayArea(LayerFontDisplayArea area) { static_cast<LayerObjFont*>(m_layer)->m_displayArea = area; }
void LayerAccFontObj::setDispSetting(LayerFontSetting setting) { static_cast<LayerObjFont*>(m_layer)->m_dispSetting = setting; }
void LayerAccFontObj::setBorderWeight(float weight) { static_cast<LayerObjFont*>(m_layer)->setBorderWeight(weight); }
void LayerAccFontObj::setSlopeRot(float rot) { static_cast<LayerObjFont*>(m_layer)->setSlopeRot(rot); }
LayerFontHorizontal LayerAccFontObj::getHorizontal() const { return static_cast<LayerObjFont*>(m_layer)->m_horizontal; }
LayerFontVertical LayerAccFontObj::getVertical() const { return static_cast<LayerObjFont*>(m_layer)->m_vertical; }
LayerFontDisplayArea LayerAccFontObj::getDisplayArea() const { return static_cast<LayerObjFont*>(m_layer)->m_displayArea; }
float LayerAccFontObj::getBorderWeight() const { return static_cast<LayerObjFont*>(m_layer)->getBorderWeight(); }
float LayerAccFontObj::getSlopeRot() const { return static_cast<LayerObjFont*>(m_layer)->getSlopeRot(); }
short LayerAccFontObj::getFontPixelX() const { return static_cast<LayerObjFont*>(m_layer)->m_fontPixelX; }
short LayerAccFontObj::getFontPixelY() const { return static_cast<LayerObjFont*>(m_layer)->m_fontPixelY; }
unsigned short LayerAccFontObj::getFontPixelWidth() const { return static_cast<LayerObjFont*>(m_layer)->m_fontPixelWidth; }
unsigned short LayerAccFontObj::getFontPixelHeight() const { return static_cast<LayerObjFont*>(m_layer)->m_fontPixelHeight; }
void LayerAccFontObj::setMsg(const char* text, const LayerBase* font, unsigned int style) {
    LayerFontManager* manager = mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager;
    static_cast<LayerObjFont*>(m_layer)->setMsg(reinterpret_cast<const unsigned char*>(text),
                                                static_cast<const LayerFontResObj*>(font), manager->m_defaultStyle,
                                                static_cast<const LayerFontIconObj*>(manager->m_defaultObj), style);
}
void LayerAccFontObj::setMsg(const char* text) {
    LayerObjFont* obj = static_cast<LayerObjFont*>(m_layer);
    const LayerFontResObj* font = obj->m_font;
    const LayerFontStyleObj* style = obj->m_style;
    const LayerFontIconObj* icon = obj->m_icon;
    unsigned int styleIndex = obj->m_styleIndex;
    if (style == nullptr) {
        style = mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager->m_defaultStyle;
    }
    if (font == nullptr) {
        font = static_cast<const LayerFontResObj*>(mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager->m_defaultObj);
    }
    if (icon == nullptr) {
        icon = static_cast<const LayerFontIconObj*>(mm::mtl::PtrSingleton<LayerManager>::get()->m_fontManager->m_defaultObj);
    }
    obj->setMsg(reinterpret_cast<const unsigned char*>(text), font, style, icon, styleIndex);
}
void LayerAccFontObj::setColorMap(const LayerBase* colorMap, unsigned int pattern) {
    static_cast<LayerObjFont*>(m_layer)->setColorMap(static_cast<const LayerFontIconObj*>(colorMap), pattern);
}

void LayerObjSortDef::finalRender() { static_cast<LayerObjTopDef*>(m_obj)->finalRender(); }
void LayerObjSortFont::finalRender() { static_cast<LayerObjTopFont*>(m_obj)->finalRender(); }
void LayerObjSortTexObj::finalRender() { static_cast<LayerObjTopTexObj*>(m_obj)->finalRender(); }
void LayerObjSortPolyObj::finalRender() { static_cast<LayerObjTopPolyObj*>(m_obj)->finalRender(); }

}  // namespace layer
