#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/Framework.h"
#include "classes/fw/ResourceManager.h"
#include "classes/fw/ResourceObject.h"
#include "ml/PathUtil.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Hash.h"
#include "mtl/MemManager.h"
#include <string.h>

namespace fw {

ResourceObject::ResourceObject(unsigned int type, mtl::ALLOC_HANDLE handle, LOAD_PRIO prio, int arg)
    : m_type(type), m_handle(handle), m_allocator(nullptr), m_hash(0), m_arg(arg), m_prio(prio) {
    mm::mtl::PtrSingleton<ResourceManager>::get()->addResource(this);
}

ResourceObject::ResourceObject(unsigned int type, mm::mtl::IAllocator* allocator, LOAD_PRIO prio, int arg)
    : m_type(type), m_allocator(allocator), m_hash(0), m_arg(arg), m_prio(prio) {
    mm::mtl::PtrSingleton<ResourceManager>::get()->addResource(this);
}

ResourceObject::~ResourceObject() {
    mm::mtl::PtrSingleton<ResourceManager>::get()->removeResource(this);
}

}  // namespace fw
