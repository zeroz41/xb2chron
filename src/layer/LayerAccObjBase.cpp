#define MM_LIB_FROM_LAYER
#include "layer/LayerRenderView.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerManager.h"
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
#include "ml/CriticalSection.h"
#include "layer/LayerAccLayoutBinary.h"
#include "layer/LayerAccFormat.h"
#include "layer/LayerObjUtil.h"
#include <string.h>

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
    LayerActBase::ActionWork* data = static_cast<LayerActBase*>(m_layer)->m_actionData;
    if (data == nullptr) {
        return 0;
    }
    return data->m_actionMax;
}

float LayerAccAction::getActionSec(unsigned int index) const {
    LayerActBase::ActionWork* data = static_cast<LayerActBase*>(m_layer)->m_actionData;
    if (data != nullptr && index < data->m_actionMax) {
        return data->m_actions[index].m_sec;
    }
    return 0.0f;
}

bool LayerAccAction::actionIdx(unsigned int index) {
    LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    LayerActBase::ActionWork* data = act->m_actionData;
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
    LayerActBase::ActionWork* data = act->m_actionData;
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

bool LayerAccAction::actionName(const char* name) {
    LayerActBase* act = static_cast<LayerActBase*>(m_layer);
    LayerActBase::ActionWork* data = act->m_actionData;
    if (data != nullptr) {
        for (int i = 0; i < data->m_actionMax; i++) {
            const LyrActionData& action = data->m_actions[i];
            if (strcmp(name, reinterpret_cast<const char*>(data->m_data) + (action.m_cmdOfs + action.m_nameOfs)) == 0) {
                act->actionIdx(i);
                return true;
            }
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

unsigned short LayerAccObjBase::getPixelWidth() const { return static_cast<LayerObj*>(m_layer)->m_renderInfo.m_pixelWidth; }

unsigned short LayerAccObjBase::getPixelHeight() const { return static_cast<LayerObj*>(m_layer)->m_renderInfo.m_pixelHeight; }

void LayerAccObjBase::setCenterType(LayerCenterType type) { static_cast<LayerObj*>(m_layer)->m_renderInfo.m_centerType = type; }

LayerCenterType LayerAccObjBase::getCenterType() const {
    return static_cast<LayerCenterType>(static_cast<LayerObj*>(m_layer)->m_renderInfo.m_centerType);
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

unsigned int LayerAccMemObj::getMemWidth() const { return m_memObj->m_memSize.m_width; }

unsigned int LayerAccMemObj::getMemHeight() const { return m_memObj->m_memSize.m_height; }

void LayerAccMemObj::setRender(bool render) { m_memObj->setRender(render); }

grlib::CGLibTextureBuffer* LayerAccMemObj::getTexture() { return m_memObj->m_renderTarget.m_pTexture; }

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

LayerAccFontObj::LayerAccFontObj(LayerBase* layer) : LayerAccObjBase(layer) {}

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

LayerAccFormat::LayerAccFormat(const void* data) : m_type(0), m_hasData(false), m_flag(false), m_multi(false) {
    const LyrFormatHeader* header = static_cast<const LyrFormatHeader*>(data);
    switch (header->m_magic) {
    case 'DHAL':
        if (header->m_version == 10001) {
            m_type = 1;
            if (header->m_flags & 0x20) {
                m_flag = true;
            }
            if (header->m_data != 0) {
                m_hasData = true;
            }
            if (*reinterpret_cast<const unsigned short*>(static_cast<const char*>(data) + header->m_entryOfs) >= 2) {
                m_multi = true;
            }
            return;
        }
        break;
    case 'SPAL':
        if (header->m_version == 10001) {
            m_type = 2;
            return;
        }
        break;
    case 'TFAL':
        if (header->m_version == 10001) {
            m_type = 3;
            m_hasData = true;
            return;
        }
        break;
    case 'TSAL':
        if (header->m_version == 10001) {
            m_type = 4;
            return;
        }
        break;
    }
    m_type = 0;
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
    obj->m_viewPort.m_x = x;
    obj->m_viewPort.m_y = y;
    obj->m_viewPort.m_width = width;
    obj->m_viewPort.m_height = height;
}

void LayerAccLayoutObj::createPriorityTbl(unsigned int count) {
    static_cast<LayerObjLayout*>(m_layer)->m_priorityTblCount[LayerManager::s_nStkIdx] = count;
    static_cast<LayerObjLayout*>(m_layer)->offFlag(LayerManager::s_nStkIdx, LayerObj::FLAG_PRIORITY_TBL);
}

void LayerAccLayoutObj::setAutoAnchorMode(LAYER_ANCHOR anchor) { static_cast<LayerObjLayout*>(m_layer)->m_anchorMode = anchor; }

LayerBase* LayerAccLayoutObj::createObj(const void* resource) {
    ml::CS cs(LayerObjManager::getCriticalSection());
    LayerBase* obj = LayerObjManager::createStaticObj(resource);
    static_cast<LayerObjLayout*>(m_layer)->m_childList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

LayerBase* LayerAccLayoutObj::createMaskObj(const void* resource) {
    ml::CS cs(LayerObjManager::getCriticalSection());
    LayerBase* obj = LayerObjManager::createStaticMaskObj(resource);
    static_cast<LayerObjLayout*>(m_layer)->m_childList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

LayerBase* LayerAccLayoutObj::createFontObj() {
    ml::CS cs(LayerObjManager::getCriticalSection());
    LayerBase* obj = LayerObjManager::createStaticFontObj();
    static_cast<LayerObjLayout*>(m_layer)->m_childList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

LayerBase* LayerAccLayoutObj::createLayoutObj() {
    ml::CS cs(LayerObjManager::getCriticalSection());
    LayerBase* obj = LayerObjManager::createStaticLayoutObj();
    static_cast<LayerObjLayout*>(m_layer)->m_childList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

LayerBase* LayerAccLayoutObj::createTexObj(const grlib::CGLibTextureBuffer& texture) {
    ml::CS cs(LayerObjManager::getCriticalSection());
    LayerBase* obj = LayerObjManager::createStaticTexObj(texture);
    static_cast<LayerObjLayout*>(m_layer)->m_childList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

LayerBase* LayerAccLayoutObj::createMemObj(unsigned int width, unsigned int height, LayerMemType type) {
    ml::CS cs(LayerObjManager::getCriticalSection());
    LayerBase* obj = LayerObjManager::createStaticMemObj(width, height, type);
    static_cast<LayerObjLayout*>(m_layer)->m_childList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

LayerBase* LayerAccLayoutObj::createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                                            unsigned short indexCount, LayerPrimitiveType type) {
    ml::CS cs(LayerObjManager::getCriticalSection());
    LayerBase* obj = LayerObjManager::createStaticPolyObj(width, height, vertexCount, indexCount, type);
    static_cast<LayerObjLayout*>(m_layer)->m_childList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

LayerAccLayoutBinary::LayerAccLayoutBinary(const void* binary) {
    m_binary = binary;
    const LyrLayoutBinHeader* header = static_cast<const LyrLayoutBinHeader*>(binary);
    m_posNum = header->m_posNum;
    m_posData = reinterpret_cast<const LyrLayoutPosData*>(static_cast<const char*>(binary) + header->m_posDataOfs);
    if (header->m_tblOfs != 0) {
        const LyrLayoutBinTbl* tbl =
            reinterpret_cast<const LyrLayoutBinTbl*>(static_cast<const char*>(binary) + header->m_tblOfs);
        m_tbl = static_cast<const char*>(binary) + tbl->m_ofs;
        m_tblNum = tbl->m_num;
    } else {
        m_tbl = nullptr;
        m_tblNum = 0;
    }
}

int LayerAccLayoutBinary::getPosIdx(const char* name) const {
    for (int i = 0; i < m_posNum; i++) {
        if (strcmp(name, static_cast<const char*>(m_binary) + m_posData[i].m_nameOfs) == 0) {
            return i;
        }
    }
    return -1;
}

void LayerAccLayoutBinary::setLayoutObj(LayerObj* obj, const char* name, bool apply) {
    int index = getPosIdx(name);
    if (index != -1 && static_cast<unsigned int>(m_posNum) > static_cast<unsigned int>(index)) {
        LayerAccObjBase acc(obj);
        float pos[4];
        LayerObjUtil::getLayoutInfo(pos, m_posData + index, acc.getCenterType(), acc.getPixelWidth(),
                                    acc.getPixelHeight());
        if (apply) {
            obj->setInitPosScl(pos[0], pos[1], pos[2], pos[3]);
        } else {
            obj->setInitPos(pos[0], pos[1]);
        }
    }
}

void LayerAccLayoutBinary::setLayoutPosData(float& x, float& y, float& width, float& height, unsigned int index) {
    if (index < static_cast<unsigned int>(m_posNum)) {
        const LyrLayoutPosData* data = m_posData + index;
        if (mm::mtl::PtrSingleton<LayerManager>::get()->m_coordinate == 0) {
            data->getPixelRect(x, y, width, height);
        } else {
            data->getCorrectionRect(x, y, width, height);
        }
    }
}

void LayerAccLayoutBinary::setLayoutPosData(float& x, float& y, float& width, float& height, const char* name) {
    int index = getPosIdx(name);
    if (index != -1) {
        setLayoutPosData(x, y, width, height, static_cast<unsigned int>(index));
    }
}

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

LayerManager::LayerManager(ml::Scn* scn, mtl::ALLOC_HANDLE handle, unsigned int size) : m_scn(scn) {
    static const FloatPair frameRate = {30.0f, 1.0f / 30.0f};
    static const FloatPair one = {1.0f, 1.0f};
    m_topHandle = mtl::ALLOC_HANDLE();
    m_dataHandle = mtl::ALLOC_HANDLE();
    m_workHandle = mtl::ALLOC_HANDLE();
    m_gxHandle = mtl::ALLOC_HANDLE();
    m_setupFunc = &LayerManager::beginFastSetup;
    m_topHandle = mtl::MemManager::create(handle, size + 0x1000, "LayerTop", false, "no name", 0);
    m_dataHandle = mtl::MemManager::create(m_topHandle, 0x190000, "LayerData", false, "no name", 0);
    m_frameRate = frameRate;
    m_baseColor[0] = one;
    m_baseColor[1] = one;
    m_pixelScale = 0.003125f;
    unsigned int restSize = size - 0x190000;
    unsigned int gxSize = restSize / 5;
    gxSize += (0x100 - (gxSize & 0xFF)) & 0xFF;
    unsigned int workSize = restSize - gxSize;
    m_workHandle = mtl::MemManager::create(m_topHandle, workSize, "LayerWork", true, "no name", 0);
    m_gxHandle = mtl::MemManager::create(m_topHandle, gxSize, "LayerGx", true, "no name", 0);
    m_workAllocator.setMemHandle(m_workHandle);
    m_gxAllocator.setMemHandle(m_gxHandle);
    m_allocator.m_memHandle = m_workHandle;
    m_shdManager = new (m_workHandle, nullptr, 0, 4, false) LayerShdManager(this);
    m_objManager = new (m_workHandle, nullptr, 0, 4, false) LayerObjManager(this);
    m_fontManager = new (m_workHandle, nullptr, 0, 4, false) LayerFontManager(this);
    m_rceManager = new (m_workHandle, nullptr, 0, 4, false) LayerRceManager(this);
    m_flags = FLAG_LOADING;
    if (m_scn->m_renderDrSys != nullptr) {
        m_scn->m_renderDrSys->setCallBack(this);
    }
    s_nDebIdx = 0;
    s_nStkIdx = 1;
    s_nTriIdx = 0;
    m_coordinate = static_cast<LayerCoordinate>(0);
    m_timeScale = 1.0f;
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

void LayerStrInfo::setCol4(const char* name, const mm::Col4& col) {
    m_name = name;
    m_col4.r = col.r;
    m_col4.g = col.g;
    m_col4.b = col.b;
    m_col4.a = col.a;
}

void LayerStrInfo::setS32(const char* name, int value) {
    m_name = name;
    m_s32 = value;
}

void LayerTag::calcParseString(const unsigned char* text) {
    beginParseString();
    calcUTF8ParseString(text);
    endParseString();
}

int LayerTag::calcStringLength(const unsigned char* text) {
    unsigned int pos = 0;
    int length = 0;
    while (text[pos] != 0) {
        unsigned char c = text[pos];
        if (c < 0x80) {
            pos += 1;
        } else if (c >= 0xC2 && c <= 0xDF) {
            pos += 2;
        } else if ((c & 0xF0) == 0xE0) {
            pos += 3;
        } else if ((c & 0xF8) == 0xF0) {
            pos += 4;
        } else {
            pos += 1;
        }
        length++;
    }
    return length;
}

void LayerTag::changeUtf8ToUtf16(unsigned short& code, const unsigned char* text, unsigned int& length) {
    code = ' ';
    unsigned char c = text[0];
    if (c < 0x80) {
        code = c;
        length = 1;
    } else if (c >= 0xC2 && c <= 0xDF) {
        code = ((c & 0x1F) << 6) | (text[1] & 0x3F);
        length = 2;
    } else if ((c & 0xF0) == 0xE0) {
        code = ((c & 0x0F) << 12) | ((text[1] & 0x3F) << 6) | (text[2] & 0x3F);
        length = 3;
    } else if ((c & 0xF8) == 0xF0) {
        length = 4;
    } else {
        length = 1;
    }
}

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

void LayerTagStr::parseNotTag(const wchar_t* str, unsigned int& pos) {
    char* dst = &m_stockTbl[m_stockCount];
    unsigned short c = str[pos];
    int length;
    if (c < 0x80) {
        dst[0] = c;
        length = 1;
    } else if (c < 0x800) {
        dst[0] = 0xC0 | (c >> 6);
        dst[1] = 0x80 | (c & 0x3F);
        length = 2;
    } else {
        dst[0] = 0xE0 | ((c >> 12) & 0x0F);
        dst[1] = 0x80 | ((c >> 6) & 0x3F);
        dst[2] = 0x80 | (c & 0x3F);
        length = 3;
    }
    m_stockCount += length;
    pos++;
}

void LayerTagStr::callTagNoUse(const unsigned char* str) { stockString(reinterpret_cast<const char*>(str)); }

}  // namespace layer
