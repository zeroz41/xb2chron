#include "classes/ui/UIStreamManager.h"
#include "classes/fw/LocalizeResource.h"
#include "classes/fw/RenderResource.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIImageObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Hash.h"
#include "plugin/Bdat.h"
#include "ui/UIUtil.h"

#include <string.h>

namespace ui {

UIStreamManager::UIStreamManager(mm::mtl::IAllocator* allocator) : m_allocator(allocator), m_dummy(nullptr) {
    mm::mtl::FixStr<128> path;
    UIUtil::makeMenuImageFileName(path, "cmn_stream_dummy");
    m_dummy = fw::RenderResource::request(m_allocator, path.m_str, 10);
}

unsigned int UIStreamManager::regist(unsigned char* bdat) {
    for (mm::mtl::IntrusiveList<Contents>::iterator it = m_contents.begin(); it != m_contents.end(); ++it) {
        if (it->m_bdat == bdat) {
            return it->m_id;
        }
    }
#line 224
    Contents* contents = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) Contents();
    if (contents == nullptr) {
        return 0;
    }
    contents->m_bdat = bdat;
    contents->m_id = mm::mtl::hashStrCrc(Bdat::getSheetName(bdat));
    m_contents.push_back(*contents);
    return contents->m_id;
}

void UIStreamManager::start(unsigned int contents, unsigned int handle, unsigned int index) {
    Stream* stream = nullptr;
    for (mm::mtl::IntrusiveList<Stream>::iterator it = m_streams.begin(); it != m_streams.end(); ++it) {
        if (it->m_handle == handle) {
            stream = it.m_node;
            break;
        }
    }
    unsigned char* bdat = nullptr;
    for (mm::mtl::IntrusiveList<Contents>::iterator it = m_contents.begin(); it != m_contents.end(); ++it) {
        if (it->m_id == contents) {
            bdat = it->m_bdat;
            break;
        }
    }
    if (bdat == nullptr) {
        return;
    }
    UIImageObject* object = UIUtil::getImageObject(handle);
    if (object == nullptr) {
        return;
    }
    if (stream == nullptr) {
#line 284
        stream = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) Stream();
        if (stream == nullptr) {
            return;
        }
        stream->m_handle = handle;
        stream->m_resource = nullptr;
        m_streams.push_back(*stream);
    }
    const char* file = "cmn_stream_dummy";
    if (index >= static_cast<unsigned int>(Bdat::getIdTop(bdat)) &&
        index < static_cast<unsigned int>(Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat))) {
        file = reinterpret_cast<const char*>(Bdat::getVal(bdat, "filename", index));
        UIObjectAcc acc(handle);
        if (acc.isStreamImage2nd() && Bdat::getMember(bdat, "filename_2nd") != nullptr) {
            const char* name = reinterpret_cast<const char*>(Bdat::getVal(bdat, "filename_2nd", index));
            if (name != nullptr && *name != '\0') {
                file = name;
            }
        }
        if (acc.fn_7100690ED4() && Bdat::getMember(bdat, "filename_3rd") != nullptr) {
            const char* name = reinterpret_cast<const char*>(Bdat::getVal(bdat, "filename_3rd", index));
            if (name != nullptr && *name != '\0') {
                file = name;
            }
        }
    }
    mm::mtl::FixStr<128> path;
    UIUtil::makeMenuImageFileName(path, file);
    if (stream->m_resource != nullptr && stream->m_resource->valid() && stream->m_resource->getAssetName() != nullptr &&
        strcmp(stream->m_resource->getAssetName(), path.m_str) == 0) {
        return;
    }
    fw::CommonResource* old = stream->m_resource;
    if (object->m_flags.test(16)) {
        stream->m_resource = fw::LocalizeResource::request(m_allocator, path.m_str, 10, false);
    } else {
        stream->m_resource = fw::RenderResource::request(m_allocator, path.m_str, 10);
    }
    if (stream->m_resource == nullptr) {
        stream->m_resource = old;
        return;
    }
    if (stream->m_resource->valid()) {
        object->changeBin(stream->m_resource->getAssetData());
    } else {
        object->m_flags.set(7, true);
        if (old == nullptr) {
            return;
        }
        object->changeBin(m_dummy->getAssetData());
    }
    if (old != nullptr) {
        old->release();
    }
}

unsigned int UIStreamManager::getContentsNum(unsigned int id) {
    unsigned int num = 0;
    for (mm::mtl::IntrusiveList<Contents>::iterator it = m_contents.begin(); it != m_contents.end(); ++it) {
        if (it->m_id == id) {
            num = Bdat::getIdTop(it->m_bdat) + Bdat::getIdCount(it->m_bdat);
            break;
        }
    }
    return num;
}

void UIStreamManager::deleteImage(const mm::mtl::FixStr<32>& name, unsigned int parent) {
    UIObjectAcc acc(parent);
    for (mm::mtl::IntrusiveList<Image>::iterator it = m_images.begin(); it != m_images.end(); ++it) {
        if (strcmp(it->m_name.m_str, name.m_str) == 0) {
            unsigned int child = acc.searchChild(name.m_str);
            if (child != 0) {
                UIObjectAcc(child).setTerm();
            }
            Image* image = it.m_node;
            it = m_images.erase(it);
            if (image->m_resource != nullptr) {
                image->m_resource->release();
                image->m_resource = nullptr;
            }
            if (image->m_request != nullptr) {
                image->m_request->release();
                image->m_request = nullptr;
            }
            delete image;
        }
    }
}

}  // namespace ui
