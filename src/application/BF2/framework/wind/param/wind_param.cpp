#include "mm/mtl/Map.h"
#include "anm/StringPtr.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundResSourceManager.h"

#include <string.h>

#include "bin/BinaryResolver.h"
#include "fw/Allocator.h"

namespace fw {

const ResSoundTrigger* SoundResTriggerImporter::importBinary(void* binary) {
    const ResSoundRoot* root = static_cast<const ResSoundRoot*>(bin::BinaryResolver::resolve(binary));
    if (root == nullptr) {
        return nullptr;
    }
    if (memcmp(root->m_magic, "SDTB", 4) != 0) {
        return nullptr;
    }
    if (root->m_version != 1) {
        return nullptr;
    }
    return static_cast<const ResSoundTrigger*>(root->m_resource);
}

SoundVariableTable::SoundVariableTable() : m_variables(Allocator::getProcAllocator()) {}

SoundVariableTable::~SoundVariableTable() {}

void SoundVariableTable::setVariable(const char* name, int value) {
    mm::mtl::FixStr<64> key(name);
    if (mm::mtl::Map<mm::mtl::FixStr<64>, int>::node* node = m_variables.find(key)) {
        node->value.second = value;
        return;
    }
    mm::mtl::MapPair<mm::mtl::FixStr<64>, int> pair(key, value);
    m_variables.insert(pair);
}

bool SoundVariableTable::getVariable(const char* name, int* value) const {
    mm::mtl::FixStr<64> key(name);
    mm::mtl::Map<mm::mtl::FixStr<64>, int>::node* node = m_variables.find(key);
    if (node == nullptr) {
        return false;
    }
    *value = node->value.second;
    return true;
}

}  // namespace fw
