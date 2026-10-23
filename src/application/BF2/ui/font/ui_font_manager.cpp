#include "mm/mtl/Algorithm.h"
#include "lms/libms.h"
#include "ms/MsWrapper.h"
#include "layer/LayerBase.h"
#include "layer/LayerAccManager.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIBuildInfoBdat.h"
#include "classes/ui/UIResource.h"
#include "classes/ui/UIFontManager.h"
#include "layer/LayerAccFontStyle.h"
#include "layer/LayerStrInfo.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/FrameworkMemory.h"
#include "fw/Allocator.h"
#include "mm/mtl/Hash.h"
#include "ms/MsWrapper.h"
#include "plugin/Bdat.h"
#include "string.h"

namespace ui {

UIFontManager::UIFontManager()
    : m_resource(nullptr), m_style(), m_loaded(false), m_colorMap(nullptr), m_icon(nullptr) {
    ms::MsWrapper::init(fw::FrameworkMemory::getMem(5));
    m_facePatterns.setAllocator(UIUtil::getProgAllocator());
    m_facePatterns.reserve(8);
}

UIFontManager::~UIFontManager() {
    for (FontRes* it = m_fontRes.begin(); it != m_fontRes.end(); ++it) {
        if (it->m_font != nullptr) {
            it->m_font->release();
            it->m_font = nullptr;
        }
    }
    m_fontRes.clear();
    m_facePatterns.clear();
    if (m_facePatterns.capacity() != 0) {
        m_facePatterns.destroy();
    }
    if (m_style.m_font != nullptr) {
        m_style.m_font->release();
        m_style.m_font = nullptr;
    }
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
    if (m_colorMap != nullptr) {
        m_colorMap->release();
        m_colorMap = nullptr;
    }
    if (m_icon != nullptr) {
        m_icon->release();
        m_icon = nullptr;
    }
}

void UIFontManager::update(const fw::UpdateInfo& info) {
    if (!m_loaded && m_resource != nullptr && !m_resource->isLoading()) {
        layer::LayerAccManager acc;
        mm::mtl::FixStr<128> path;
        unsigned char* fp = Bdat::getFP(m_resource->m_name.m_str);
        unsigned char* fontFp = UIUtil::getBdatFP(2);
        unsigned char* styleFp = UIUtil::getBdatFP(3);
        unsigned char* imageFp = UIUtil::getBdatFP(0);
        for (int i = 0; i < Bdat::getIdCount(fp); ++i) {
            int id = Bdat::getIdTop(fp) + i;
            unsigned char type = (unsigned char)(unsigned long)Bdat::getVal(fp, "type", id);
            unsigned short resource = (unsigned short)(unsigned long)Bdat::getVal(fp, "resource", id);
            switch (type) {
            case 6: {
                const char* file = Bdat::getVal(imageFp, "file", resource);
                UIUtil::makeMenuImageFileName(path, file);
                fw::CommonResource* res = m_resource->search(path.m_str);
                if (res != nullptr) {
                    unsigned char imageType = (unsigned char)(unsigned long)Bdat::getVal(fp, "image_type", id);
                    if (imageType == 1) {
                        if (m_colorMap == nullptr) {
                            m_colorMap = acc.createFontColorMapObj(res->getAssetData());
                        }
                    } else if (imageType == 2 && m_icon == nullptr) {
                        m_icon = acc.createFontIconObj(res->getAssetData());
                    }
                }
                break;
            }
            case 8: {
                const char* file = Bdat::getVal(fontFp, "file", resource);
                UIUtil::makeMenuFontDataFileName(path, file);
                fw::CommonResource* res = m_resource->search(path.m_str);
                if (res != nullptr) {
                    FontRes font;
                    font.m_id = resource;
                    font.m_hash = mm::mtl::hashStrCrc(file);
                    font.m_font = acc.createFontResObj(res->getAssetData());
                    m_fontRes.push_back(font);
                }
                break;
            }
            case 9: {
                const char* file = Bdat::getVal(styleFp, "file", resource);
                UIUtil::makeMenuFontStyleFileName(path, file);
                fw::CommonResource* res = m_resource->search(path.m_str);
                if (res != nullptr) {
                    m_style.m_id = resource;
                    m_style.m_hash = 0;
                    m_style.m_font = acc.createFontStyleObj(res->getAssetData());
                }
                break;
            }
            case 10: {
                const char* file = Bdat::getVal(styleFp, "file", resource);
                UIUtil::makeMSProjFileName(path, file);
                fw::CommonResource* res = m_resource->search(path.m_str);
                if (res != nullptr) {
                    importMSBP(res->getAssetData(), res->getAssetSize());
                }
                break;
            }
            }
        }
        unsigned char* faceFp = UIUtil::getBdatFP(13);
        if (faceFp != nullptr) {
            for (int i = 0; i < Bdat::getIdCount(faceFp); ++i) {
                int id = Bdat::getIdTop(faceFp) + i;
                const char* name = Bdat::getVal(faceFp, "name", id);
                if (name != nullptr && *name != '\0') {
                    m_facePatterns.push_back(FacePattern(
                        mm::mtl::hashStrCrc(name), (unsigned char)(unsigned long)Bdat::getVal(faceFp, "image_no", id)));
                }
            }
        }
        m_loaded = true;
    }
}

void UIFontManager::importMSBP(const void* data, unsigned int size) {
    layer::LayerAccFontStyle style(m_style.m_font);
    if (data != nullptr && size != 0) {
        ms::MsWrapper::regist(static_cast<const char*>(data));
        unsigned int colorNum = ms::MsWrapper::getColorNum();
        if (colorNum != 0) {
            mm::mtl::Vector<layer::LayerStrInfo>* colors = style.createColorInfo(colorNum);
            for (unsigned int i = 0; i != colorNum; ++i) {
                LMSColor color;
                char name[32];
                if (ms::MsWrapper::getColorName(i, name, sizeof(name)) && ms::MsWrapper::getColor(i, &color)) {
                    layer::LayerStrInfo info;
                    info.setCol4(name, mm::Col4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f,
                                                color.a / 255.0f));
                    colors->push_back(info);
                }
            }
        }
        for (int tag = 0; tag < ms::MsWrapper::getTagNum(1); ++tag) {
            if (strcmp(ms::MsWrapper::getTagName(1, tag), "icon") == 0) {
                unsigned int iconNum = ms::MsWrapper::getTagParamListItemNum(1, tag, 0);
                if (tag != -1) {
                    mm::mtl::Vector<layer::LayerStrInfo>* icons = style.createIconInfo(iconNum);
                    if (icons != nullptr) {
                        for (int item = 0; item < ms::MsWrapper::getTagParamListItemNum(1, tag, 0); ++item) {
                            layer::LayerStrInfo info;
                            info.setS32(ms::MsWrapper::getTagParamListItemName(1, tag, 0, item), item);
                            icons->push_back(info);
                        }
                    }
                }
                break;
            }
        }
        ms::MsWrapper::unregist();
    }
}

void UIFontManager::loadFontSet(const char* name, mm::mtl::IAllocator* allocator) {
    UIBuildInfoBdat info(name);
#line 263
    UIResource* resource = new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIResource(name);
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
    resource->addRef();
    resource->load(&info, allocator);
    if (resource->isValid()) {
        m_resource = resource;
    } else if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
    m_loaded = false;
}

bool UIFontManager::isLoading() const {
    return m_resource != nullptr && m_resource->isLoading();
}

UIFontManager::FontRes* UIFontManager::getFontResFromStyle(unsigned short style) {
    if (m_style.m_font != nullptr) {
        layer::LayerAccFontStyle acc(m_style.m_font);
        unsigned int hash = mm::mtl::hashStrCrc(acc.getFontName(style));
        for (FontRes* it = m_fontRes.begin(); it != m_fontRes.end(); ++it) {
            if (it->m_hash == hash) {
                return it;
            }
        }
    }
    return nullptr;
}

bool UIFontManager::getFontStyleInfo(unsigned short style, StyleInfo& info) {
    layer::LayerAccFontStyle acc(m_style.m_font);
    if (style < acc.getStyleDataMax()) {
        info.m_offsetX = acc.getStyleInfo(style).m_data->m_offsetX;
        info.m_offsetY = acc.getStyleInfo(style).m_data->m_offsetY;
        return true;
    }
    return false;
}

bool UIFontManager::findFacePattern(const char* name, unsigned int& index) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    index = 0;
    for (FacePattern* it = m_facePatterns.begin(); it != m_facePatterns.end(); ++it) {
        if (it->m_hash == hash) {
            index = it->m_imageNo;
            return true;
        }
    }
    return false;
}

}  // namespace ui
