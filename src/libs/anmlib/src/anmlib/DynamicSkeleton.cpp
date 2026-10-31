#include "anm/AsmImporter.h"
#include "anm/SkeletonImporter.h"
#include "bin/BinaryResolver.h"
#include "classes/anm/Skeleton.h"
#include "string.h"
#include <new>

namespace anm {

ResStateArray* AsmImporter::import(void* binary) {
    Root* root = static_cast<Root*>(bin::BinaryResolver::resolve(binary));
    if (root == nullptr) {
        return nullptr;
    }
    if (memcmp(root->m_magic, "ASMB", 4) != 0) {
        return nullptr;
    }
    if (root->m_version != 7) {
        return nullptr;
    }
    return root->m_states;
}

Skeleton* SkeletonImporter::import(void* binary) {
    Root* root = static_cast<Root*>(bin::BinaryResolver::resolve(binary));
    if (root == nullptr) {
        return nullptr;
    }
    if (memcmp(root->m_magic, "SKEL", 4) != 0) {
        return nullptr;
    }
    if (root->m_version != 6) {
        return nullptr;
    }
    new (root->m_skeleton) Skeleton;
    return root->m_skeleton;
}

}  // namespace anm
