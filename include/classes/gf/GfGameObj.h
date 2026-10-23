#ifndef CLASSES_GF_GFGAMEOBJ_H
#define CLASSES_GF_GFGAMEOBJ_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameObj; }
#include "classes/gf/IGfObjListener.h"

namespace fw { class UpdateInfo; }
namespace gf {
// a base of gf::GfGameObj no evidence names yet
class TUnk_B550E0 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B550B8; base at 0x8 unknown (TUnk_B550E0)
class GfGameObj : public ::mm::mtl::PtrSingleton< ::gf::GfGameObj>, public TUnk_B550E0 {
public:
    // SCOM_DESTROY_GAME_OBJ passes its request's object, time and attribute
    static void destroyGameObjWithAttribute(gf::GF_OBJ_HANDLE* handle, float fadeTime, unsigned int);
    static void postUpdate(const fw::UpdateInfo& info);
    static void bdatReload();
    virtual ~GfGameObj();  // slot 0
    static bool isEmpty();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    // whether the object behind handle exists (with checkLoad, also loaded); error takes a reason when given
    static bool isValidGameObj(gf::GF_OBJ_HANDLE* handle, bool checkLoad, mm::mtl::FixStr<128>* error);
    static void destroyGameObj(gf::GF_OBJ_HANDLE* handle, float fadeTime);
};
}  // namespace gf

#endif
