#include "classes/layer/LayerTag.h"
#include "classes/layer/LayerTagStr.h"
#include "classes/ui/UITagConv.h"
#include "classes/ui/UITagParser.h"
#include "classes/ui/UITextFile.h"
#include "plugin/Bdat.h"
#include <string.h>
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UITagConv.h"
#include "classes/ui/UITagParser.h"
#include "classes/ui/UITextFile.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Map.h"
#include "mtl/MemManager.h"
#include "plugin/Bdat.h"
#include "ui/UIUtil.h"

namespace ui {

UITagParser::UITagParser(mm::mtl::IAllocator* allocator)
    : m_allocator(allocator), m_buffer(nullptr), m_converters(), m_ownerId(0), m_mode(MODE_CONVERT), m_tag(nullptr),
      m_param(nullptr), m_result() {
    m_buffer = static_cast<char*>(m_allocator->allocate(0x400, 4));
    setStockTbl(m_buffer, 0x400);
}

UITagParser::~UITagParser() {
    releaseConverter();
    if (m_buffer != nullptr) {
        mtl::MemManager::deallocate(m_buffer, 0, false);
        m_buffer = nullptr;
    }
}

void UITagParser::releaseConverter() {
    for (UITagConv** it = m_converters.begin(); it != m_converters.end(); ++it) {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
    m_converters.clear();
}

void UITagParser::registConverter(UITagConv* conv) {
    if (m_converters.size() >= m_converters.capacity()) {
        return;
    }
    for (UITagConv** it = m_converters.begin(); it != m_converters.end(); ++it) {
        if (strcmp((*it)->getTagName(), conv->getTagName()) == 0) {
            return;
        }
    }
    m_converters.push_back(conv);
}

void UITagParser::parse(const char* text) {
    if (text != nullptr) {
        m_mode = MODE_CONVERT;
        calcParseString(reinterpret_cast<const unsigned char*>(text));
    }
}

const char* UITagParser::getResult() {
    return m_stockTbl;
}

const char* UITagParser::parseTagParam(const char* text, const char* tag, const char* param) {
    if (text == nullptr || tag == nullptr || param == nullptr) {
        return nullptr;
    }
    m_mode = MODE_PARAM;
    m_tag = tag;
    m_param = param;
    m_result.clear();
    calcParseString(reinterpret_cast<const unsigned char*>(text));
    if (m_result.m_nLen == 0) {
        return nullptr;
    }
    return m_result.m_str;
}

bool UITagParser::parseTag(const char* text, const char* tag) {
    if (text == nullptr || tag == nullptr) {
        return false;
    }
    m_tag = tag;
    m_mode = MODE_TAG;
    m_result.clear();
    calcParseString(reinterpret_cast<const unsigned char*>(text));
    return m_result.m_nLen != 0;
}

bool UITagParser::callTagStart(const char* tag, const layer::LayerTagTbl* tbl, unsigned int num) {
    if (m_mode == MODE_CONVERT) {
        for (UITagConv** it = m_converters.begin(); it != m_converters.end(); ++it) {
            if (strcmp((*it)->getTagName(), tag) == 0) {
                mm::mtl::FixedVector<mm::mtl::MapPair<const char*, const char*>, 8> params;
                for (unsigned int i = 0; i < num; i++) {
                    params.push_back(mm::mtl::MapPair<const char*, const char*>(tbl[i].m_name, tbl[i].m_value));
                }
                const char* str = (*it)->convBegin(params, m_ownerId);
                if (str == nullptr) {
                    return false;
                }
                stockString(str);
                return true;
            }
        }
    } else if (m_mode == MODE_PARAM) {
        if (strcmp(m_tag, tag) != 0) {
            return false;
        }
        for (unsigned int i = 0; i < num; i++) {
            if (strcmp(m_param, tbl[i].m_name) == 0) {
                m_result = tbl[i].m_value;
                return true;
            }
        }
    } else if (m_mode == MODE_TAG) {
        if (strcmp(m_tag, tag) == 0) {
            m_result = tag;
            return true;
        }
    }
    return false;
}

bool UITagParser::callTagEnd(const char* tag) {
    for (UITagConv** it = m_converters.begin(); it != m_converters.end(); ++it) {
        if (strcmp((*it)->getTagName(), tag) == 0) {
            const char* str = (*it)->convEnd();
            if (str == nullptr) {
                return false;
            }
            stockString(str);
            return true;
        }
    }
    return false;
}

UITextFile::~UITextFile() {
    ;  // stores the table (a statement the build compiles away)
}

UITextFile* UITextFile::create(unsigned char* data) {
#line 42
    UITextFile* file = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UITextFile(data);
    file->m_name = Bdat::getSheetName(data);
    return file;
}

void UITextFile::reload() {
    m_data = Bdat::getFP(m_name.m_str);
}

const char* UITextFile::getText(unsigned int id) const {
    if (m_data == nullptr) {
        return nullptr;
    }
    return Bdat::getMSText(m_data, id);
}

unsigned short UITextFile::getStyle(unsigned int id) const {
    if (m_data == nullptr) {
        return 0xFFFF;
    }
    return Bdat::getMSStyle(m_data, id);
}

}  // namespace ui
