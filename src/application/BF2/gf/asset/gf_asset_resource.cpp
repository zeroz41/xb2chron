#include "classes/gf/GfAssetResource.h"
#include "classes/gf/GfAllocator.h"
#include "ml/ScnObjAccStmReadObj.h"

namespace gf {

GfAssetResource::~GfAssetResource() {
    destroy();
}

GfAssetResource* GfAssetResource::create(const char* label, const char* name, void* data, unsigned int size) {
#line 147
    GfAssetResource* resource = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfAssetResource();
    resource->m_data = data;
    resource->m_size = size;
    resource->m_name = name;
    resource->m_type = 3;
    resource->m_label = label;
    resource->importSample();
    return resource;
}

GfAssetResource* GfAssetResource::create(const char* label, const char* name, mm::mtl::IAllocator* allocator,
                                         int arg) {
#line 172
    GfAssetResource* resource = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfAssetResource();
    resource->m_resource = fw::CommonResource::request(allocator, name, arg, false);
    resource->m_name = name;
    resource->m_label = label;
    resource->m_allocator = allocator;
    resource->m_type = 1;
    resource->m_requestArg = arg;
    return resource;
}

void* GfAssetResource::getAssetData() const {
    if (m_type == 2 || m_type == 3) {
        return m_data;
    }
    if (m_type == 1) {
        return m_resource->getAssetData();
    }
    return nullptr;
}

unsigned int GfAssetResource::getAssetSize() const {
    if (m_type == 2 || m_type == 3) {
        return m_size;
    }
    if (m_type == 1) {
        return m_resource->getAssetSize();
    }
    return 0;
}

const char* GfAssetResource::getAssetName() const {
    return m_name.m_str;
}

bool GfAssetResource::isFinishLoad() const {
    switch (m_type) {
    case 1:
        return m_resource->valid();
    case 3:
        return true;
    case 2:
        return m_size != 0 && m_data != nullptr;
    }
    return false;
}

bool GfAssetResource::isValidData() const {
    if (!isFinishLoad()) {
        return false;
    }
    return getAssetData() != nullptr;
}

void GfAssetResource::setupStreamObject() {
    if (m_stream == nullptr) {
        m_stream = ml::ScnObjAccStmReadObj::create(m_name.m_str);
    }
}

}  // namespace gf
