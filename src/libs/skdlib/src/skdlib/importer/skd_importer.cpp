#include "skd/DynamicsImporter.h"
#include "bin/BinaryResolver.h"
#include "classes/skd/ResDynamics.h"
#include "string.h"
#include <new>

// bin::BinaryResolver::resolve (0x7100887F3C) and restore (0x7100887FE8) sit in this unit's range but were
// compiled in another translation unit with other flags: here clang turns memcmp(binary, "BG", 2) into a
// halfword compare and inlines resolve into import, the original calls both

namespace skd {

ResDynamics* DynamicsImporter::import(void* binary) {
    Root* root = static_cast<Root*>(bin::BinaryResolver::resolve(binary));
    if (root == nullptr) {
        return nullptr;
    }
    if (memcmp(root->m_magic, "SKDY", 4) != 0) {
        return nullptr;
    }
    if (root->m_version != 2) {
        return nullptr;
    }
    return new (root->m_dynamics) ResDynamics;
}

}  // namespace skd
