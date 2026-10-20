// not proven yet: its table differs from the original's (word 4: None where the original has _ZN3btl19EffectMoveComponent12UpdateNormalEffRKN2mm4Vec3E)
#ifndef CLASSES_MM_MTL_PTRSINGLETON_H
#define CLASSES_MM_MTL_PTRSINGLETON_H

namespace mm { namespace mtl {
// a template: 228 instances in the module
template <typename T0>
class PtrSingleton {
public:
    virtual ~PtrSingleton();  // slot 0
    static T0*& sys() {
        static T0* s_instance;
        return s_instance;
    }
};
}}  // namespace mm::mtl

#endif
