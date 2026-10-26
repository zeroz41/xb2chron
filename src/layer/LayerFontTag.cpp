#define MM_LIB_FROM_LAYER
#include "mm/mtl/Vector.h"
#include "layer/LayerBase.h"
#include "layer/LayerAccFontStyle.h"
#include "classes/layer/LayerTag.h"
#include "classes/layer/LayerFontTag.h"
#include "classes/layer/LayerFontDrawBuffer.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/layer/LayerTag.h"
#include "classes/layer/LayerFontTag.h"
#include "classes/layer/LayerFontDrawBuffer.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/layer/LayerManager.h"
#include "layer/LayerTextureObj.h"
#include "layer/LayerStrInfo.h"
#include "grlib/CGLibTexture.h"
#include "grlib/CGLibTextureBuffer.h"
#include "mtl/MemManager.h"

#include <string.h>

namespace layer {

LayerFontIconObj::~LayerFontIconObj() {
    if (m_texture != nullptr) {
        m_texture->release();
        m_texture = nullptr;
    }
}

void LayerFontIconObj::setupResource() {
    if (m_texture != nullptr) {
        m_texture->setupResource();
    }
}

void LayerFontIconObj::release() {
    m_state = 0x22;
    m_releaseFlags |= 1 << LayerManager::s_nStkIdx;
}

LayerFontResObj::~LayerFontResObj() {
    if (m_texture != nullptr) {
        delete m_texture;
        m_texture = nullptr;
    }
}

void LayerFontResObj::setupResource() {
    const unsigned char* image = m_data + m_head->m_textureOffset;
    m_texture = new (mm::mtl::PtrSingleton<LayerManager>::get()->m_gxHandle, nullptr, 0, 4, false)
        grlib::CGLibTextureBuffer();
    grlib::CGLibTexture::createTextureImagePtrs(*m_texture, image, m_head->m_textureSize, false, nullptr, true);
}

void LayerFontResObj::release() {
    m_state = 0x22;
    m_releaseFlags |= 1 << LayerManager::s_nStkIdx;
}

LayerFontStyleObj::~LayerFontStyleObj() {
    releaseColorInfo();
    releaseIconInfo();
}

const LyrFontStyleData* LayerFontStyleObj::getStyleData(unsigned int style) const {
    return style < m_styleDataMax ? &m_styleData[style] : m_styleData;
}

const char* LayerFontStyleObj::getFontName(unsigned int style) const {
    return m_strings + m_styleData[style].m_fontName;
}

void LayerFontStyleObj::release() {
    m_state = 0x22;
    releaseColorInfo();
    releaseIconInfo();
    m_manager->m_styleList.removeList(this);
    delete this;
}

void LayerFontTag::beginParseString() {
    m_width = 0;
    m_offsetX = 0;
    m_offsetY = 0;
    m_lineNum = 0;
    m_lastCode = 0;
}

bool LayerFontTag::callTagEnd(const char* name) {
    if (m_isCreate) {
        if (strcasecmp(s_resTagTbl[0], name) == 0) {
            m_color = m_defaultColor;
        }
        if (strcasecmp(s_resTagTbl[1], name) == 0) {
            calcTagRubyEnd();
        }
    }
    return true;
}

}  // namespace layer
