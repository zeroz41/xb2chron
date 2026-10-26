#define MM_LIB_FROM_LAYER
#include "classes/layer/LayerTag.h"
#include "classes/layer/LayerMemHandleAllocator.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerManager.h"
#include "layer/LayerAccManager.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "classes/layer/LayerObjLayout.h"
#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccFontStyle.h"
#include "layer/LayerAccPolyObj.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccAction.h"
#include "layer/LayerAccDefTexture.h"
#include "layer/LayerAccDefObj.h"
#include "layer/LayerAccLayoutObj.h"
#include "classes/layer/LayerObjWork.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjFont.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/layer/LayerSortObj.h"
#include "classes/layer/LayerObjTopFont.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjSortDef.h"
#include "classes/layer/LayerObjSortFont.h"
#include "classes/layer/LayerObjSortTexObj.h"
#include "classes/layer/LayerObjSortPolyObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerTagStr.h"
#include "classes/ml/IDrDrawWorkInfo.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "layer/LayerRceManager.h"
#include "layer/LayerStrInfo.h"
#include "mtl/MemManager.h"

namespace layer {

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

float LayerAccManager::getScreenWidth() const {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_shdManager->m_screenWidth;
}

float LayerAccManager::getScreenHeight() const {
    return mm::mtl::PtrSingleton<LayerManager>::get()->m_shdManager->m_screenHeight;
}

LayerCoordinate LayerAccManager::getCoordinate() const { return mm::mtl::PtrSingleton<LayerManager>::get()->m_coordinate; }

void LayerAccManager::setCoordinate(LayerCoordinate coordinate) {
    mm::mtl::PtrSingleton<LayerManager>::get()->m_coordinate = coordinate;
}

void LayerAccManager::setGamma(float gamma) { mm::mtl::PtrSingleton<LayerManager>::get()->m_shdManager->m_gamma = gamma; }

LayerAccAction::LayerAccAction(LayerBase* layer) : m_layer(layer) {}

bool LayerAccAction::isActionData() const { return static_cast<LayerActBase*>(m_layer)->m_actionData != nullptr; }

bool LayerAccAction::isRunning() const {
    const LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    if (act->m_stateFlags & LayerObj::STATE_PARTS_ACTION) {
        return true;
    }
    return act->isFlag(LayerManager::s_nDebIdx, LayerObj::FLAG_ACTION_RUNNING);
}

unsigned int LayerAccAction::getRunningActIdx() const {
    const LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    if (act->m_stateFlags & LayerObj::STATE_PARTS_ACTION) {
        return act->m_actionData->m_runningIdx;
    }
    int index = LayerManager::s_nDebIdx;
    if (!act->isFlag(index, LayerObj::FLAG_ACTION_RUNNING)) {
        return -1;
    }
    return act->m_runningActIdx[index];
}

void LayerAccAction::setRunningActSec(float sec) {
    LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    if ((act->m_stateFlags & LayerObj::STATE_PARTS_ACTION) ||
        act->isFlag(LayerManager::s_nDebIdx, LayerObj::FLAG_ACTION_RUNNING)) {
        act->m_actionData->m_runningSec = sec;
    }
}

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

void LayerAccDefObj::setParm(float param) {
    if (m_layer->m_objType == 1) {
        static_cast<LayerObjTopDef*>(m_layer)->m_param = param;
    }
}

void LayerAccDefObj::setIconNum(unsigned short num) {
    switch (m_layer->m_objType) {
    case 1:
        static_cast<LayerObjTopDef*>(m_layer)->m_iconNum = num;
        break;
    case 7:
        static_cast<LayerObjTopMaskObj*>(m_layer)->m_iconNum = num;
        break;
    }
}

unsigned short LayerAccDefObj::getIconNum() const {
    switch (m_layer->m_objType) {
    case 1:
        return static_cast<LayerObjTopDef*>(m_layer)->m_iconNum;
    case 7:
        return static_cast<LayerObjTopMaskObj*>(m_layer)->m_iconNum;
    }
    return 0;
}

unsigned short LayerAccDefObj::getIconMax() const {
    switch (m_layer->m_objType) {
    case 1:
        return static_cast<LayerObjTopDef*>(m_layer)->m_iconMax;
    case 7:
        return static_cast<LayerObjTopMaskObj*>(m_layer)->m_iconMax;
    }
    return 0;
}

void LayerAccDefObj::setGauge(LAYER_GAUGE gauge) {
    if (m_layer->m_objType == 1) {
        static_cast<LayerObjTopDef*>(m_layer)->m_gauge = gauge;
    }
}

LAYER_GAUGE LayerAccDefObj::getGauge() const {
    if (m_layer->m_objType == 1) {
        return static_cast<LAYER_GAUGE>(static_cast<LayerObjTopDef*>(m_layer)->m_gauge);
    }
    return static_cast<LAYER_GAUGE>(0);
}

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

LayerAccLayoutObj::LayerAccLayoutObj(LayerBase* layer) : m_layer(layer) {}

void LayerAccLayoutObj::setViewPortMode(bool enable) {
    LayerObjLayout* obj = static_cast<LayerObjLayout*>(m_layer);
    if (enable) {
        obj->m_stateFlags |= LayerObj::STATE_VIEWPORT;
    } else {
        obj->m_stateFlags &= ~LayerObj::STATE_VIEWPORT;
    }
}

void LayerAccLayoutObj::setViewPort(float x, float y, float width, float height) {
    LayerObjLayout* obj = static_cast<LayerObjLayout*>(m_layer);
    obj->m_viewPortX = x;
    obj->m_viewPortY = y;
    obj->m_viewPortWidth = width;
    obj->m_viewPortHeight = height;
}

void LayerAccLayoutObj::createPriorityTbl(unsigned int count) {
    static_cast<LayerObjLayout*>(m_layer)->m_priorityTblCount[LayerManager::s_nStkIdx] = count;
    static_cast<LayerObjLayout*>(m_layer)->offFlag(LayerManager::s_nStkIdx, LayerObj::FLAG_PRIORITY_TBL);
}

void LayerAccLayoutObj::setAutoAnchorMode(LAYER_ANCHOR anchor) { static_cast<LayerObjLayout*>(m_layer)->m_anchorMode = anchor; }

int LayerManager::s_nStkIdx = 1;

int LayerManager::s_nDebIdx;

int LayerManager::s_nTriIdx;

void* LayerMemHandleAllocator::allocate(unsigned long size, unsigned long alignment) {
    return mtl::MemManager::allocate(m_memHandle, size, alignment, false, "no name", 0);
}

void LayerMemHandleAllocator::deallocate(void* memory) {
    if (memory != nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
    }
}

void LayerManager::beginFastSetup() {
    m_flags |= FLAG_LOADING;
    m_shdManager->readShader();
    m_setupFunc = &LayerManager::loadWait;
}

LayerManager::~LayerManager() {
    ml::ScnRenderDrSys* renderDrSys = m_scn->m_renderDrSys;
    if (renderDrSys != nullptr) {
        renderDrSys->releaseCallBack(this);
    }
    if (m_objManager != nullptr) {
        delete m_objManager;
        m_objManager = nullptr;
    }
    if (m_fontManager != nullptr) {
        delete m_fontManager;
        m_fontManager = nullptr;
    }
    if (m_rceManager != nullptr) {
        delete m_rceManager;
        m_rceManager = nullptr;
    }
    if (m_shdManager != nullptr) {
        delete m_shdManager;
        m_shdManager = nullptr;
    }
    if (m_gxHandle.m_handle != 0) {
        mtl::MemManager::erase(m_gxHandle);
        m_gxHandle = mtl::ALLOC_HANDLE();
    }
    if (m_workHandle.m_handle != 0) {
        mtl::MemManager::erase(m_workHandle);
        m_workHandle = mtl::ALLOC_HANDLE();
    }
    if (m_dataHandle.m_handle != 0) {
        mtl::MemManager::erase(m_dataHandle);
        m_dataHandle = mtl::ALLOC_HANDLE();
    }
    if (m_topHandle.m_handle != 0) {
        mtl::MemManager::erase(m_topHandle);
        m_topHandle = mtl::ALLOC_HANDLE();
    }
}

void LayerManager::tail() {
    s_nDebIdx = s_nDebIdx == 0 ? 1 : 0;
    s_nStkIdx = s_nDebIdx == 0 ? 1 : 0;
    s_nTriIdx = s_nTriIdx > 1 ? 0 : s_nTriIdx + 1;
}

float LayerManager::getScreenDivWidth() const { return m_shdManager->m_screenDivWidth; }

float LayerManager::getScreenCalcSclWidth() const { return m_shdManager->m_screenCalcSclWidth; }

float LayerManager::getScreenCalcSclHeight() const { return m_shdManager->m_screenCalcSclHeight; }

float LayerManager::getScreenCalcPosWidth() const { return m_shdManager->m_screenCalcPosWidth; }

float LayerManager::getScreenCalcPosHeight() const { return m_shdManager->m_screenCalcPosHeight; }

void LayerManager::begin() { (this->*m_setupFunc)(); }

void LayerManager::end() {
    if (!(m_flags & FLAG_LOADING)) {
        m_objManager->end();
    }
}

void LayerManager::apply(const ml::IDrDrawWorkInfo* info) {
    if (!(m_flags & FLAG_LOADING) && info->m_subPass == 0) {
        m_objManager->apply(info);
    }
}

void LayerManager::finalRender(const ml::IDrDrawWorkInfo* info) {
    if (!(m_flags & FLAG_LOADING) && info->m_subPass == 0) {
        m_shdManager->beginShader(info);
        m_objManager->finalRender(info);
        m_shdManager->endShader(info);
    }
}

void LayerManager::loadWait() {
    m_flags |= FLAG_LOADING;
    if (m_shdManager->setupUpdate()) {
        defSetup();
        m_setupFunc = &LayerManager::defSetup;
    }
}

void LayerManager::defSetup() {
    m_flags &= ~FLAG_LOADING;
    m_fontManager->update();
    m_rceManager->update();
    m_objManager->begin();
}

LayerStrInfo::LayerStrInfo() {}

LayerTagStr::LayerTagStr() : m_stockTbl(nullptr), m_stockSize(0), m_stockCount(0) {}

LayerTagStr::~LayerTagStr() {}

void LayerTagStr::setStockTbl(char* tbl, int size) {
    m_stockTbl = tbl;
    m_stockSize = size;
}

void LayerTagStr::stockString(const char* str) {
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        m_stockTbl[m_stockCount++] = str[i];
    }
}

void LayerTagStr::beginParseString() { m_stockCount = 0; }

void LayerTagStr::endParseString() { m_stockTbl[m_stockCount] = '\0'; }

void LayerTagStr::parseNotTag(const unsigned char* str, unsigned int& pos) {
    m_stockTbl[m_stockCount++] = str[pos];
    pos++;
}

void LayerTagStr::callTagNoUse(const unsigned char* str) { stockString(reinterpret_cast<const char*>(str)); }

}  // namespace layer
