#include "classes/ui/UIObjFactory.h"
#include "classes/ui/UIBuildInfo.h"
#include "classes/ui/UIBuildInfoBdat.h"
#include "classes/ui/UIBuildInfoUIO.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIGroup.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIObjBuildData.h"
#include "classes/ui/UIResource.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/Allocator.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"
#include <string.h>

namespace ui {

UIObjFactory::UIObjFactory() {
    UIUtil::initObjectMap(0x1fa0);
    UIObjBuildData::initialize();
    m_orders.setAllocator(UIUtil::getProgAllocator());
    m_orders.reserve(32, 8);
}

UIObjFactory::~UIObjFactory() {
    for (OrderInfo* it = m_orders.begin(); it != m_orders.end(); ++it) {
        if (it->m_info != nullptr) {
            delete it->m_info;
            it->m_info = nullptr;
        }
        if (it->m_resource != nullptr) {
            it->m_resource->release();
            it->m_resource = nullptr;
        }
    }
    m_orders.destroy();
    fn_71006757FC();
    UIUtil::termObjectMap();
}

void UIObjFactory::update(const fw::UpdateInfo&) {
    PreloadInfo* it = m_preloads.begin();
    while (it != m_preloads.end()) {
        if (it->m_resource == nullptr) {
            it->m_info->update();
            if (it->m_info->isReady()) {
#line 109
                it->m_resource = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIResource(it->m_info->getName());
                it->m_resource->addRef();
                it->m_resource->load(it->m_info, UIUtil::getResourceAllocator());
                // looked at again: it now has its resource
                continue;
            }
        }
        ++it;
    }
    for (OrderInfo* order = m_orders.begin(); order != m_orders.end(); ++order) {
        if (order->m_resource == nullptr) {
            order->m_info->update();
            if (!order->m_info->isValid()) {
                m_orders.erase(order);
                return;
            }
            if (order->m_info->isReady()) {
#line 170
                order->m_resource = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIResource(order->m_name);
                order->m_resource->addRef();
                order->m_resource->load(order->m_info, UIUtil::getResourceAllocator());
            }
        } else if (!order->m_resource->isLoading()) {
            order->m_resource->fn_71006943A0();
            if (order->m_resource->isValid()) {
                createRootObject(*order);
            }
            if (!order->m_preloaded) {
                if (order->m_info != nullptr) {
                    delete order->m_info;
                    order->m_info = nullptr;
                }
                if (order->m_resource != nullptr) {
                    order->m_resource->release();
                    order->m_resource = nullptr;
                }
            } else {
                order->m_info = nullptr;
                order->m_resource = nullptr;
            }
            m_orders.erase(order);
            return;
        }
    }
}

// createRootObject (0x710067545C) is in the worker's wip: it matches only once setupChildObject and
// setupObjectInput are defined in this file (their unused `this` is then passed undefined).

void UIObjFactory::registPreloadResource(unsigned int type, const char* name) {
    for (PreloadInfo* it = m_preloads.begin(); it != m_preloads.end(); ++it) {
        if (it->m_info != nullptr && strcmp(it->m_info->getName(), name) == 0) {
            return;
        }
    }
    UIBuildInfo* info;
    switch (type) {
    case 0:
#line 215
        info = new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIBuildInfoBdat(name);
        break;
    case 1:
#line 219
        info = new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIBuildInfoUIO(name);
        break;
    default:
        return;
    }
    if (info != nullptr) {
        PreloadInfo preload;
        preload.m_info = info;
        preload.m_resource = nullptr;
        m_preloads.push_back(preload);
    }
}

void UIObjFactory::fn_71006757FC() {
    for (PreloadInfo* it = m_preloads.begin(); it != m_preloads.end(); ++it) {
        if (it->m_info != nullptr) {
            delete it->m_info;
            it->m_info = nullptr;
        }
        if (it->m_resource != nullptr) {
            it->m_resource->release();
            it->m_resource = nullptr;
        }
    }
    m_preloads.clear();
}

void UIObjFactory::order(const OrderParam& param) {
    for (OrderInfo* it = m_orders.begin(); it != m_orders.end(); ++it) {
        if (it->m_group == param.m_group && strcmp(it->m_name, param.m_name) == 0) {
            return;
        }
    }
    OrderInfo info;
    info.m_target = param.m_target;
    info.m_priority = param.m_priority;
    info.m_group = param.m_group;
    info.m_layer = param.m_layer;
    bool preloaded = false;
    for (PreloadInfo* it = m_preloads.begin(); it != m_preloads.end(); ++it) {
        if (it->m_resource != nullptr && strcmp(it->m_resource->m_name.m_str, param.m_name) == 0) {
            info.m_name = it->m_resource->m_name.m_str;
            info.m_info = it->m_info;
            info.m_resource = it->m_resource;
            info.m_preloaded = true;
            preloaded = true;
            break;
        }
    }
    if (!preloaded) {
        info.m_resource = nullptr;
        switch (param.m_count) {
        case 0:
#line 323
            info.m_info = new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIBuildInfoBdat(param.m_name);
            break;
        case 1:
#line 327
            info.m_info = new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIBuildInfoUIO(param.m_name);
            break;
        }
        if (info.m_info != nullptr) {
            info.m_name = param.m_name;
            info.m_preloaded = false;
        }
    }
    m_orders.push_back(info);
}

bool UIObjFactory::isLoading() const {
    if (m_orders.size() != 0) {
        return true;
    }
    for (const PreloadInfo* it = m_preloads.begin(); it != m_preloads.end(); ++it) {
        if (it->m_resource != nullptr && it->m_resource->isLoading()) {
            return true;
        }
    }
    return false;
}

}  // namespace ui
