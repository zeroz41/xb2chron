#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "classes/fw/ResourceManager.h"
#include "classes/fw/ResourceObject.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/RenderResource.h"
#include "classes/fw/LocalizeResource.h"
#include "classes/ml/DevFileTh.h"
#include "ml/EventFileTh.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/LangUtil.h"

namespace fw {

// the body stores the tables (an empty one would not): a statement the build compiles away
LocalizeResource::~LocalizeResource() {
    ;
}

LocalizeResource* LocalizeResource::request(mm::mtl::IAllocator* allocator, const char* path, int prio, bool flag) {
    LocalizeResource* resource = static_cast<LocalizeResource*>(CommonResource::search(allocator, path));
    if (resource != nullptr) {
        resource->addRef();
        return resource;
    }
    resource = new (ResourceManager::getMemSYS(), nullptr, 0, 4, false)
        LocalizeResource(allocator, static_cast<LOAD_PRIO>(prio));
    if (resource != nullptr) {
        resource->m_localizePath = path;
        resource->setPath(path);
        resource->addRef();
        resource->update();
    }
    return resource;
}

const char* LocalizeResource::getAssetName() const {
    return m_localizePath.m_nLen == 0 ? nullptr : m_localizePath.m_str;
}

void LocalizeResource::update() {
    if (m_state == 4) {
        bool valid = this->valid();
        CommonResource::update();
        if (m_localizePath.m_nLen != 0 && valid != this->valid()) {
            m_path = m_localizePath;
        }
        return;
    }
    if (LangUtil::getLangType() == 0) {
        m_state = 4;
        return;
    }
    mm::mtl::FixStr<128> path;
    if (m_state == 0) {
        makeLocalizeFilePath(path, LangUtil::getLangFolder());
        ml::DevFileTh::checkValidFile(path.m_str, this);
        m_state = 2;
    } else if (m_state == 1) {
        makeLocalizeFilePath(path, mm::mtl::FixStr<16>("us"));
        ml::DevFileTh::checkValidFile(path.m_str, this);
        m_state = 3;
    }
}

// makeLocalizeFilePath (0x710019A51C) is 11 instructions off as written below, all in the inlined search for the
// last '.': the original keeps the name's address minus one and indexes it with the count (ldrb [x9, x10]), letting
// the name's address die (one callee-saved register fewer); FixStr::findLast and the index/pointer loops tried here
// (int/long counters, >= 0, != 0, do/while) keep it live (zkit sweep found no rewrite). The rest is identical.
// void LocalizeResource::makeLocalizeFilePath(mm::mtl::FixStr<128>& path, const mm::mtl::FixStr<16>& lang) {
//     mm::mtl::FixStr<128> name;
//     mm::mtl::FixStr<128> ext;
//     name = m_localizePath;
//     int dot = name.findLast('.');
//     name.cutBack(name.m_nLen - dot);
//     ext = m_localizePath;
//     ext = ext.substr(dot, ext.m_nLen - name.m_nLen);
//     path.format("%s_%s%s", name.m_str, lang.m_str, ext.m_str);
// }

bool LocalizeResource::OnFileEvent(ml::EventFileTh* event) {
    if (event == nullptr) {
        return false;
    }
    if (event->m_kind == 9) {
        mm::mtl::FixStr<128> path;
        if (m_state == 2) {
            makeLocalizeFilePath(path, LangUtil::getLangFolder());
        } else if (m_state == 3) {
            makeLocalizeFilePath(path, mm::mtl::FixStr<16>("us"));
        }
        m_path = path;
    } else if (m_state == 2 && LangUtil::getLangType() != 1 && LangUtil::getLangType() != 6 &&
               LangUtil::getLangType() != 11) {
        m_state = 1;
        return true;
    }
    m_state = 4;
    return true;
}

RenderResource* RenderResource::request(mtl::ALLOC_HANDLE handle, const char* path, int prio) {
    RenderResource* resource = search(handle, path);
    if (resource != nullptr) {
        resource->addRef();
        return resource;
    }
    resource = new (ResourceManager::getMemSYS(), nullptr, 0, 4, false) RenderResource(handle, static_cast<LOAD_PRIO>(prio));
    if (resource != nullptr) {
        resource->setPath(path);
        resource->addRef();
        resource->update();
    }
    return resource;
}

RenderResource* RenderResource::request(mm::mtl::IAllocator* allocator, const char* path, int prio) {
    RenderResource* resource = search(allocator, path);
    if (resource != nullptr) {
        resource->addRef();
        return resource;
    }
    resource = new (ResourceManager::getMemSYS(), nullptr, 0, 4, false)
        RenderResource(allocator, static_cast<LOAD_PRIO>(prio));
    if (resource != nullptr) {
        resource->setPath(path);
        resource->addRef();
        resource->update();
    }
    return resource;
}

RenderResource::~RenderResource() {}

}  // namespace fw
