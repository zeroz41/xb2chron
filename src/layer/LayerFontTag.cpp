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

// not identical yet (4 words): the second m_styleData->m_flags & 2 read is scheduled after the tex load, the
// original's after the cellWidth load. Kept as the key function: it emits LayerFontDrawBuffer's table
void LayerFontDrawBuffer::createFontCode(unsigned short code) {
    if (m_lineNum < m_styleData->m_lineNumMax) {
        const LayerFontResObj* res = m_resObj;
        unsigned short index;
        const LayerFontResObj::FontInfo* info = res->getFontInfo(index, code);
        Vertex* vertex = m_vertex;
        float cellWidth = res->m_texInfo->m_cellWidth;
        float cellHeight = res->m_texInfo->m_cellHeight;
        float width = cellWidth;
        if (!(m_styleData->m_flags & 2)) {
            width = info->m_width;
        }
        float advance[2];
        if (m_setting == 1 || m_setting == 2) {
            advance[0] = cellWidth - res->m_borderWidth;
            advance[1] = cellWidth - res->m_borderWidth;
        } else {
            advance[0] = width - res->m_borderWidth;
            advance[1] = cellHeight - res->m_borderWidth;
        }
        float height = cellHeight * m_styleData->m_offsetY;
        width = width * m_styleData->m_offsetX;
        advance[0] = m_styleData->m_offsetX * advance[0];
        advance[1] = m_styleData->m_offsetY * advance[1];
        if (m_doubleNext) {
            if (m_setting == 0) {
                width += width;
                advance[0] += advance[0];
            } else {
                height += height;
                advance[1] += advance[1];
            }
            m_doubleNext = false;
        }
        vertex->m_width = width;
        vertex->m_height = height;
        vertex->m_x = m_pos[0];
        vertex->m_y = m_pos[1];
        bool fixed = m_styleData->m_flags & 2;
        res = m_resObj;
        const LayerFontResObj::TexInfo* tex = res->m_texInfo;
        unsigned int row = index / tex->m_cellNumX;
        unsigned int col = index % tex->m_cellNumX;
        unsigned int u = col + tex->m_cellWidth * col + 1;
        if (!fixed) {
            vertex->m_u = (float)(info->m_left + u) / (float)tex->m_texWidth;
            vertex->m_v = (float)(row + res->m_texInfo->m_cellHeight * row + 1) / (float)res->m_texInfo->m_texHeight;
            vertex->m_uvWidth = (float)info->m_width / (float)res->m_texInfo->m_texWidth;
        } else {
            vertex->m_u = (float)u / (float)tex->m_texWidth;
            vertex->m_v = (float)(row + res->m_texInfo->m_cellHeight * row + 1) / (float)res->m_texInfo->m_texHeight;
            vertex->m_uvWidth = res->m_cellUvWidth;
        }
        vertex->m_uvHeight = res->m_cellUvHeight;
        unsigned char* color = m_vertex->m_color;
        color[0] = (int)(m_color.r * 255.0f);
        color[1] = (int)(m_color.g * 255.0f);
        color[2] = (int)(m_color.b * 255.0f);
        color[3] = (int)(m_color.a * 255.0f);
        const LyrFontStyleData* style = m_styleData;
        if (style->m_lineWidthMax >= m_pos[m_axis] + (int)advance[m_axis]) {
            m_pos[m_axis] += (int)advance[m_axis] + style->m_charSpace;
            if (m_maxSize[m_axis] < m_pos[m_axis]) {
                m_maxSize[m_axis] = m_pos[m_axis];
            }
            int cross = m_pos[m_crossAxis] + (int)advance[m_crossAxis] + style->m_lineSpace;
            if (m_maxSize[m_crossAxis] < cross) {
                m_maxSize[m_crossAxis] = cross;
            }
            m_buffer->m_lines[m_lineNum].m_main.m_width = m_pos[m_axis];
            if (m_buffer->m_lines[m_lineNum].m_main.m_first == -1) {
                m_buffer->m_lines[m_lineNum].m_main.m_first = m_charIndex;
            }
            m_buffer->m_lines[m_lineNum].m_main.m_last = m_charIndex;
            m_charIndex++;
            m_vertex++;
        }
    }
}

LayerFontManager::~LayerFontManager() { allRelease(); }

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
    m_pos[0] = 0;
    m_pos[1] = 0;
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
