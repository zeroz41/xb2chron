#include "classes/fw/ParamList.h"
#include "fw/ParamBuilder.h"
#include "bin/BinaryResolver.h"
#include "classes/fw/ParamManager.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/Allocator.h"

namespace fw {

mm::mtl::IntrusivePtr<ParamList> ParamBuilder::create(void* binary, unsigned int index, const char* name) {
    ParamManager* manager = ParamManager::get();
    mm::mtl::IntrusivePtr<ParamList> list;
    list = importBinary(binary, nullptr);
    manager->m_paramLists[index] = list;
    return list;
}

mm::mtl::IntrusivePtr<ParamList> ParamBuilder::importBinary(void* binary, Reflection* reflection) {
    ParamList::Binary* data = static_cast<ParamList::Binary*>(bin::BinaryResolver::resolve(binary));
#line 90
    ParamList* list = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) ParamList;
    if (data != nullptr) {
        list->m_count = data->m_count;
        list->m_entries = data->m_entries;
    }
    if (reflection != nullptr) {
        list->m_reflection = reflection;
    }
    return list;
}

// destroy (0x7100198514) is not here yet: written as
//     ParamManager* manager = ParamManager::get();
//     if (manager->m_paramLists[index]) {
//         manager->m_paramLists[index] = nullptr;
//     }
// it differs only in the slot's address: the original recomputes manager + index * 8 for the store (its own
// address computation in the store's block, from a zero-extended copy of index), where this reuses the load's

ParamList::~ParamList() {}

}  // namespace fw
