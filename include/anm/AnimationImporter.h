#ifndef ANM_ANIMATIONIMPORTER_H
#define ANM_ANIMATIONIMPORTER_H

namespace anm { class Binding; }

namespace anm {
// builds an animation's binding from its binary (an "ANIM" one)
class AnimationImporter {
public:
    // none for anything else
    static Binding* import(void* binary);
};
}  // namespace anm

#endif
