#ifndef ANM_ANIMATIONIMPORTER_H
#define ANM_ANIMATIONIMPORTER_H

namespace anm { class Binding; }

namespace anm {
// builds an animation's binding from its binary (an "ANIM" one, version 4)
class AnimationImporter {
public:
    // the root of an animation binary: its version, kind and the binding (whose animation lies in the binary too)
    struct Root {
        int m_version;      // 4
        char m_magic[4];    // "ANIM"
        Binding* m_binding;
    };

    // none for anything else
    static Binding* import(void* binary);
    // turns the binary's pointers back into offsets (bin::BinaryResolver::restore's result)
    static bool restore(void* binary);
};
}  // namespace anm

#endif
