// not proven yet: its table differs from the original's (word 4: None where the original has _ZN3btl19EffectMoveComponent12UpdateNormalEffRKN2mm4Vec3E)
#ifndef CLASSES_MM_MTL_PTRSINGLETON_H
#define CLASSES_MM_MTL_PTRSINGLETON_H

#include "mm/MMStdBase.h"

namespace mm { namespace mtl {
// a template: 247 instances in the module; the one instance a class derives from holds that class's object
template <typename T0>
class PtrSingleton {
public:
    PtrSingleton() {
        // the original's mm_mtl/singleton.h, as its include path named it
#line 82 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/singleton.h"
        MM_ASSERT(get()==0);
        sys() = static_cast<T0*>(this);
    }
    virtual ~PtrSingleton() {  // slot 0
        sys() = nullptr;
    }
    static T0*& sys() {
        static T0* s_instance;
        return s_instance;
    }
    static T0* get() {
        return sys();
    }
};
}}  // namespace mm::mtl

#endif
