#include "classes/ui/UIMotionLibrary.h"
#include "classes/ui/UIMotionData.h"
#include "ui/UIUtil.h"
#include "classes/fw/CommonResource.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Hash.h"
#include "mm/mtl/Vector.h"

namespace ui {

UIMotionLibrary::UIMotionLibrary() {}

UIMotionLibrary::~UIMotionLibrary() {
    reset();
}

void UIMotionLibrary::reset() {
    if (m_motions.capacity() != 0) {
        for (mm::mtl::Vector<MotionInfo>::iterator it = m_motions.begin(); it != m_motions.end(); ++it) {
            if (it->m_data != nullptr) {
                delete it->m_data;
                it->m_data = nullptr;
            }
            if (it->m_resource != nullptr) {
                it->m_resource->release();
                it->m_resource = nullptr;
            }
        }
        m_motions.destroy();
    }
}

void UIMotionLibrary::update(const fw::UpdateInfo& info) {
    for (mm::mtl::Vector<MotionInfo>::iterator it = m_motions.begin(); it != m_motions.end();) {
        bool erased = false;
        if (it->m_data == nullptr && it->m_resource != nullptr && it->m_resource->valid()) {
            if (it->m_resource->getAssetSize() != 0) {
#line 78
                UIMotionData* data = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__)
                    UIMotionData(UIUtil::getProgAllocator());
                data->deserialize(it->m_resource->getAssetData(), it->m_resource->getAssetSize());
                it->m_data = data;
            } else {
                if (it->m_resource != nullptr) {
                    it->m_resource->release();
                    it->m_resource = nullptr;
                }
                it = m_motions.erase(it);
                erased = true;
            }
        }
        if (!erased) {
            ++it;
        }
    }
}

}  // namespace ui

// the motion list's erase (its user is update)
template mm::mtl::Vector<ui::UIMotionLibrary::MotionInfo>::iterator mm::mtl::Vector<ui::UIMotionLibrary::MotionInfo>::erase(
    ui::UIMotionLibrary::MotionInfo*);

namespace ui {

bool UIMotionLibrary::add(const char* name) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    if (m_motions.capacity() == 0) {
        m_motions.setAllocator(UIUtil::getProgAllocator());
        m_motions.reserve(8, 8);
    } else {
        for (mm::mtl::Vector<MotionInfo>::iterator it = m_motions.begin(); it != m_motions.end(); ++it) {
            if (it->m_hash == hash) {
                return true;
            }
        }
    }
    mm::mtl::FixStr<128> path;
    UIUtil::makeMenuUIMFileName(path, name);
    MotionInfo info;
    info.m_hash = mm::mtl::hashStrCrc(name);
    info.m_resource = fw::CommonResource::request(UIUtil::getResourceAllocator(), path.m_str, 10, false);
    info.m_data = nullptr;
    if (info.m_resource != nullptr) {
        m_motions.push_back(info);
    }
    return true;
}

UIMotionData* UIMotionLibrary::find(const char* name) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (mm::mtl::Vector<MotionInfo>::iterator it = m_motions.begin(); it != m_motions.end(); ++it) {
        if (it->m_hash == hash) {
            return it->m_data;
        }
    }
    return nullptr;
}

}  // namespace ui
