#ifndef CLASSES_MM_MTL_PTRSINGLETON_H
#define CLASSES_MM_MTL_PTRSINGLETON_H

#include "mm/MMStdBase.h"

// mm_lib's mm_mtl/singleton.h, as the including file's include path named it: monolib_mm's own files
// (MM_LIB_FROM_MONOLIB_MM: ml::LibMain::create cites it so) reach it from monolib_mm's build folder, the game's from
// application/BF2
#if defined(MM_LIB_FROM_MONOLIB_MM)
#define MM_MTL_SINGLETON_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/singleton.h"
#elif defined(MM_LIB_FROM_GRLIB)
// grlib's (CGLibManager's constructor cites it so)
#define MM_MTL_SINGLETON_PATH \
    "D:/Monolithsoft/BF2/prog/libs/grlib/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/singleton.h"
#elif defined(MM_LIB_FROM_LAYER)
// layer's (LayerManager's constructor cites it so)
#define MM_MTL_SINGLETON_PATH \
    "D:/Monolithsoft/BF2/prog/libs/layer/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/singleton.h"
#elif defined(MM_LIB_FROM_IDCOLI)
// idcoli's (IDColiManager's constructor cites it so)
#define MM_MTL_SINGLETON_PATH \
    "D:/Monolithsoft/BF2/prog/libs/idcoli/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/singleton.h"
#elif defined(MM_LIB_FROM_NAVI)
// navi's (NvmshManager's constructor cites it so)
#define MM_MTL_SINGLETON_PATH \
    "D:/Monolithsoft/BF2/prog/libs/navi/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/singleton.h"
#elif defined(MM_LIB_FROM_XBRD)
// xbrd's (DrCalcTexStreamMan's, DrPixlMemMan's and cloud::CloudMan's constructors cite it so)
#define MM_MTL_SINGLETON_PATH \
    "D:/Monolithsoft/BF2/prog/libs/xbrd/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/singleton.h"
#else
#define MM_MTL_SINGLETON_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/singleton.h"
#endif

namespace mm { namespace mtl {
// a template: 248 instances in the module; the one instance a class derives from holds that class's object
template <typename T0>
class PtrSingleton {
public:
    PtrSingleton() {
        // the original's mm_mtl/singleton.h, as its include path named it
#line 82 MM_MTL_SINGLETON_PATH
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
