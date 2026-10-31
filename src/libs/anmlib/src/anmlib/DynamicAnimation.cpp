#include "anm/AnimationImporter.h"
#include "anm/SerialiseArg.h"
#include "bin/BinaryResolver.h"
#include "classes/anm/Binding.h"
#include "classes/anm/CubicAnimation.h"
#include "classes/anm/EmptyAnimation.h"
#include "classes/anm/UncompressAnimation.h"
#include "string.h"
#include <new>

namespace anm {

Binding* AnimationImporter::import(void* binary) {
    Root* root = static_cast<Root*>(bin::BinaryResolver::resolve(binary));
    if (root == nullptr) {
        return nullptr;
    }
    if (memcmp(root->m_magic, "ANIM", 4) != 0) {
        return nullptr;
    }
    if (root->m_version != 4) {
        return nullptr;
    }
    SerialiseArg arg;
    Animation* pAnimation = const_cast<Animation*>(root->m_binding->m_pAnimation);
    // the animation's implementation, as the binary spells it (getImplType's values)
    signed char type = pAnimation->m_kind;
    switch (type) {
    case 0:
        new (pAnimation) UncompressAnimation(arg);
        break;
    case 1:
        new (pAnimation) CubicAnimation(arg);
        break;
    case 2:
        new (pAnimation) EmptyAnimation(arg);
        break;
    default:
        return nullptr;
    }
    return new (root->m_binding) Binding(arg);
}

bool AnimationImporter::restore(void* binary) {
    return bin::BinaryResolver::restore(binary);
}

}  // namespace anm
