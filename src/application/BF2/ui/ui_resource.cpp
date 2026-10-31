#include "classes/ui/UIResource.h"

#include <string.h>

#include "classes/fw/CommonResource.h"
#include "classes/ml/Scn.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "ml/ScnRenderDrViewCtrl.h"
#include "mm/mtl/Hash.h"

namespace ui {

UIResource::UIResource(const char* name) : m_name(name) {}

UIResource::~UIResource() {
    releaseRenderViewList();
    releaseResourceList();
}

void UIResource::releaseRenderViewList() {
    if (m_renderViewList.capacity() != 0) {
        ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
        for (RenderViewInfo* it = m_renderViewList.begin(); it != m_renderViewList.end(); ++it) {
            if (it->m_view != nullptr) {
                acc.deleteAddRenderView(it->m_view);
                if (it->m_view != nullptr) {
                    delete it->m_view;
                    it->m_view = nullptr;
                }
            }
        }
        m_renderViewList.clear();
    }
}

void UIResource::releaseResourceList() {
    if (m_resourceList.capacity() != 0) {
        for (ResourceInfo* it = m_resourceList.begin(); it != m_resourceList.end(); ++it) {
            if (it->m_resource != nullptr) {
                it->m_resource->release();
                it->m_resource = nullptr;
            }
        }
        m_resourceList.destroy();
    }
}

void UIResource::fn_71006943A0() {
    if (m_resourceList.capacity() != 0 && m_resourceList.size() != 0) {
        for (ResourceInfo* it = m_resourceList.begin(); it != m_resourceList.end();) {
            if (it->m_isRemovable && it->m_resource->valid() && it->m_resource->getAssetSize() == 0) {
                it = m_resourceList.erase(it);
            } else {
                ++it;
            }
        }
    }
}

bool UIResource::isValid() const {
    if (m_resourceList.capacity() == 0 || m_resourceList.size() == 0) {
        return false;
    }
    for (const ResourceInfo* it = m_resourceList.begin(); it != m_resourceList.end(); ++it) {
        if (it->m_resource->valid() && it->m_resource->getAssetSize() == 0) {
            return false;
        }
    }
    return true;
}

bool UIResource::isLoading() const {
    if (m_resourceList.capacity() != 0 && m_resourceList.size() != 0) {
        for (const ResourceInfo* it = m_resourceList.begin(); it != m_resourceList.end(); ++it) {
            if (!it->m_resource->valid()) {
                return true;
            }
        }
        if (m_renderViewList.capacity() != 0) {
            for (const RenderViewInfo* it = m_renderViewList.begin(); it != m_renderViewList.end(); ++it) {
                if (!it->m_view->m_isReady) {
                    return true;
                }
            }
        }
    }
    return false;
}

fw::CommonResource* UIResource::search(const char* name) const {
    if (isValid()) {
        for (const ResourceInfo* it = m_resourceList.begin(); it != m_resourceList.end(); ++it) {
            const char* assetName = it->m_resource->getAssetName();
            unsigned char valid = it->m_resource->valid();
            if (assetName != nullptr && valid && strcmp(assetName, name) == 0) {
                return it->m_resource;
            }
        }
    }
    return nullptr;
}

ml::ScnRenderDrViewCtrl* UIResource::searchRednerView(const char* name) const {
    if (isValid() && m_renderViewList.capacity() != 0) {
        unsigned int hash = mm::mtl::hashStrCrc(name);
        for (const RenderViewInfo* it = m_renderViewList.begin(); it != m_renderViewList.end(); ++it) {
            if (it->m_view != nullptr && it->m_hash == hash) {
                return it->m_view;
            }
        }
    }
    return nullptr;
}

UIResource::Capture* UIResource::searchCapture(const char* name) {
    if (isValid() && m_captureList.capacity() != 0) {
        unsigned int hash = mm::mtl::hashStrCrc(name);
        for (CaptureInfo* it = m_captureList.begin(); it != m_captureList.end(); ++it) {
            if (it->m_texture != nullptr && it->m_hash == hash) {
                return &it->m_capture;
            }
        }
    }
    return nullptr;
}

}  // namespace ui
