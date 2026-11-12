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

LayerFontDrawBuffer::Work* LayerFontDrawBuffer::createChar(const unsigned char* text) {
    LayerTagWork work = {};
    m_isCreate = false;
    m_work = &work;
    calcParseString(text);
    unsigned int length = 0;
    for (unsigned long i = 0; i < 10000 && text[i] != 0; i++) {
        length++;
    }
    work.m_length = length;
    work.m_bufferLength = length;
    createWorkBuffer(work, text);
    m_isCreate = true;
    calcParseString(text);
    endWorkSetup();
    return m_buffer;
}

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

inline void LayerFontIconObj::getFontUvParms(float* parms, unsigned short code) const {
    if (m_uvHead != nullptr) {
        unsigned int index = m_uvNum <= code ? 0 : code;
        const LayerFontIconUvData* data =
            reinterpret_cast<const LayerFontIconUvData*>(reinterpret_cast<const unsigned char*>(m_uvHead) +
                                                         m_uvHead->m_dataOffset) +
            index;
        parms[0] = m_texHeight * data->m_scale[0];
        parms[1] = m_cellHeight * data->m_scale[1];
        parms[2] = data->m_uv[0];
        parms[3] = data->m_uv[1];
        parms[4] = data->m_uv[2];
        parms[5] = data->m_uv[3];
    } else {
        parms[0] = m_texHeight;
        parms[1] = m_cellHeight;
        parms[2] = 1.0f;
        parms[3] = 1.0f;
        parms[4] = 0.0f;
        parms[5] = 0.0f;
    }
}

void LayerFontDrawBuffer::createFontIcon(unsigned short code) {
    if (m_iconObj != nullptr && m_lineNum < m_styleData->m_lineNumMax) {
        const LayerFontResObj::TexInfo* tex = m_resObj->m_texInfo;
        float parms[6];
        m_iconObj->getFontUvParms(parms, code);
        Vertex* vertex = m_rubyVertex;
        float size[2];
        size[0] = parms[0] * m_styleData->m_offsetY;
        size[1] = parms[1] * m_styleData->m_offsetY;
        vertex->m_width = size[0];
        vertex->m_height = size[1];
        vertex->m_x = m_pos[0];
        vertex->m_y = m_pos[1];
        if (m_setting == 0) {
            vertex->m_y += (((float)tex->m_cellHeight - m_resObj->m_borderWidth) * m_styleData->m_offsetY - parms[1]) * 0.5f;
        } else {
            vertex->m_x += (((float)tex->m_cellWidth - m_resObj->m_borderWidth) * m_styleData->m_offsetY - parms[0]) * 0.5f;
        }
        vertex->m_uvWidth = parms[2];
        vertex->m_uvHeight = parms[3];
        vertex->m_u = parms[4];
        vertex->m_v = parms[5];
        unsigned char* color = m_rubyVertex->m_color;
        color[0] = (int)(m_color.r * 255.0f);
        color[1] = (int)(m_color.g * 255.0f);
        color[2] = (int)(m_color.b * 255.0f);
        color[3] = (int)(m_color.a * 255.0f);
        const LyrFontStyleData* style = m_styleData;
        if (style->m_lineWidthMax >= m_pos[m_axis] + (int)size[m_axis]) {
            m_pos[m_axis] += (int)size[m_axis] + style->m_charSpace;
            if (m_maxSize[m_axis] < m_pos[m_axis]) {
                m_maxSize[m_axis] = m_pos[m_axis];
            }
            int cross = m_pos[m_crossAxis] + (int)size[m_crossAxis] + style->m_lineSpace;
            if (m_maxSize[m_crossAxis] < cross) {
                m_maxSize[m_crossAxis] = cross;
            }
            m_buffer->m_lines[m_lineNum].m_main.m_width = m_pos[m_axis];
            if (m_buffer->m_lines[m_lineNum].m_ruby.m_first == -1) {
                m_buffer->m_lines[m_lineNum].m_ruby.m_first = m_iconIndex;
            }
            m_buffer->m_lines[m_lineNum].m_ruby.m_last = m_iconIndex;
            m_rubyVertex++;
            m_iconIndex++;
        }
    }
}

LayerFontManager::~LayerFontManager() { allRelease(); }

LayerBase* LayerFontManager::createFontResObj(const void* data) {
    LayerFontResObj* obj = new (m_manager->m_workHandle, nullptr, 0, 4, false) LayerFontResObj(this);
    obj->setFontData(data);
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    if (m_defaultResObj == nullptr) {
        m_defaultResObj = obj;
    }
    return obj;
}

LayerBase* LayerFontManager::createFontIconObj(const void* data) {
    LayerFontIconObj* obj =
        new (m_manager->m_workHandle, nullptr, 0, 4, false) LayerFontIconObj(this, data, static_cast<LAYER_TYPE>(11));
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    if (m_defaultObj == nullptr) {
        m_defaultObj = obj;
    }
    return obj;
}

LayerBase* LayerFontManager::createFontColMapObj(const void* data) {
    LayerFontIconObj* obj =
        new (m_manager->m_workHandle, nullptr, 0, 4, false) LayerFontIconObj(this, data, static_cast<LAYER_TYPE>(12));
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}

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

void LayerFontIconObj::getFontUvOnlyParms(float* uv, unsigned short code) const {
    if (m_uvHead != nullptr) {
        unsigned int index = m_uvNum <= code ? 0 : code;
        const LayerFontIconUvData* data =
            reinterpret_cast<const LayerFontIconUvData*>(reinterpret_cast<const unsigned char*>(m_uvHead) +
                                                         m_uvHead->m_dataOffset) +
            index;
        uv[0] = data->m_uv[0];
        uv[1] = data->m_uv[1];
        uv[2] = data->m_uv[2];
        uv[3] = data->m_uv[3];
    } else {
        uv[0] = 1.0f;
        uv[1] = 1.0f;
        uv[2] = 0.0f;
        uv[3] = 0.0f;
    }
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
    m_rubyNum = 0;
    m_pos[0] = 0;
    m_pos[1] = 0;
    m_lineNum = 0;
    m_lastCode = 0;
}

void LayerFontTag::parseNotTag(const unsigned char* text, unsigned int& pos) {
    signed char c = text[pos];
    if (m_isCreate) {
        if ((unsigned char)c == '\n') {
            pos = text[pos + 1] == '\r' ? pos + 2 : pos + 1;
            createLineBreak();
            return;
        }
        if ((unsigned char)c == '\\') {
            pos++;
        }
        unsigned short code;
        unsigned int length;
        changeUtf8ToUtf16(code, text + pos, length);
        pos += length;
        if (code >= 0x20 && code != 0x7F) {
            switch (code) {
            case 0x20:
            case 0x3000:
                break;
            default:
                m_lastCode = code;
                break;
            }
        }
        createFontCode(code);
    } else {
        if ((unsigned char)c == '\n') {
            pos = text[pos + 1] == '\r' ? pos + 2 : pos + 1;
            m_lineNum++;
            return;
        }
        if (c >= 0) {
            pos += 1;
        } else if (c >= (signed char)0xC2 && c <= (signed char)0xDF) {
            pos += 2;
        } else if ((c & 0xF0) == 0xE0) {
            pos += 3;
        } else if ((c & 0xF8) == 0xF0) {
            pos += 4;
        } else {
            pos += 1;
        }
        m_work->m_charNum++;
    }
}

void LayerFontTag::calcTagColorStart(const LayerTagTbl* tbl, unsigned int num) {
    if (num != 0) {
        const mm::mtl::Vector<LayerStrInfo>* colors = m_styleObj->m_colorInfo;
        if (colors != nullptr) {
            for (int i = 0; i < (int)colors->size(); i++) {
                if (strcmp(tbl->m_value, (*colors)[i].m_name.m_str) == 0) {
                    m_defaultColor = m_color;
                    m_color = mm::Col4((*colors)[i].m_col4.r, (*colors)[i].m_col4.g, (*colors)[i].m_col4.b, 1.0f);
                    return;
                }
            }
        }
    }
}

void LayerFontTag::calcTagIconStart(const LayerTagTbl* tbl, unsigned int num) {
    if (num != 0) {
        const mm::mtl::Vector<LayerStrInfo>* icons = m_styleObj->m_iconInfo;
        if (icons != nullptr) {
            for (int i = 0; i < (int)icons->size(); i++) {
                if (strcmp(tbl->m_value, (*icons)[i].m_name.m_str) == 0) {
                    int code = (*icons)[i].m_s32;
                    createFontIcon(code);
                    return;
                }
            }
        }
    }
}

// fn_710083DB30's particles: [whether m_lastCode ends in a consonant][fn_710083DDD8's index]
// (lbl_7100B806F0; the name is not the original's)
static const wchar_t* const s_particleTbl[2][8] = {
    {nullptr, L"\uB294", L"\uB97C", L"\uAC00", L"\uC640", L"\uB85C", nullptr, L"\uC57C"},
    {nullptr, L"\uC740", L"\uC744", L"\uC774", L"\uACFC", L"\uC73C\uB85C", L"\uC774", L"\uC544"},
};

void LayerFontTag::fn_710083DB30(const LayerTagTbl* tbl, unsigned int num) {
    const wchar_t* particle = nullptr;
    for (unsigned int i = 0; i < num; i++) {
        if (strcmp(tbl[i].m_name, "char") == 0) {
            unsigned short code = m_lastCode;
            int kind = fn_710083DDD8(tbl->m_value);
            unsigned int consonant = 0;
            unsigned int syllable = code - 0xAC00;
            unsigned int digit = code - '0';
            if (syllable < 0x2BA4) {
                // a Hangul syllable: its final consonant (none, or for "ni" a final rieul, takes the first row)
                unsigned int final = syllable % 28;
                if (final != 0) {
                    consonant = kind != 5 || final != 8;
                }
            } else if (digit <= 9) {
                // the digits read with a final consonant: 0 3 6, and 1 7 8 (rieul) except for "ni"
                unsigned int mask = kind == 5 ? 0x49 : 0x1CB;
                consonant = (mask & (1 << digit)) != 0;
            }
            particle = s_particleTbl[consonant][kind];
        }
    }
    if (particle != nullptr) {
        for (; *particle != 0; particle++) {
            createFontCode(*particle);
        }
    }
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

int LayerFontTag::fn_710083DDD8(const char* name) {
    if (strcmp(name, "ha") == 0) {
        return 1;
    }
    if (strcmp(name, "wo") == 0) {
        return 2;
    }
    if (strcmp(name, "ga") == 0) {
        return 3;
    }
    if (strcmp(name, "to") == 0) {
        return 4;
    }
    if (strcmp(name, "ni") == 0) {
        return 5;
    }
    if (strcmp(name, "ya") == 0) {
        return 6;
    }
    if (strcmp(name, "san") == 0) {
        return 7;
    }
    return 0;
}

}  // namespace layer
