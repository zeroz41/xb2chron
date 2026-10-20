#ifndef CLASSES_GF_GFFIELDMANAGER_H
#define CLASSES_GF_GFFIELDMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfFieldManager; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
namespace gf { enum RELOAD_BDAT : int; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gf {
// a base of gf::GfFieldManager no evidence names yet
class TUnk_B51F68 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// a base of gf::GfFieldManager no evidence names yet
class TUnk_B51F80 {
public:
    virtual ~TUnk_B51F80();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void vf25();
    virtual void vf26();
    virtual void vf27();
    virtual void vf28();
    virtual void vf29();
    virtual void vf30();
    virtual void vf31();
    virtual void vf32();
    virtual void vf33();
    virtual void vf34();
    virtual void vf35();
    virtual void gevPlayEvent(gf::GEV, unsigned int) = 0;
    virtual void gevPause(unsigned int, unsigned int) = 0;
    virtual void vf38();
    virtual void vf39();
    virtual void vf40();
    virtual void vf41();
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) = 0;
    virtual void gevBattleStart() = 0;
    virtual void gevBattleEnd() = 0;
    virtual void vf45();
    virtual void vf46();
    virtual void vf47();
    virtual void gevGameMapModel(gf::GF_OBJ_HANDLE*, bool) = 0;
    virtual void vf49();
    virtual void vf50();
    virtual void vf51();
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int) = 0;
    virtual void vf53();
    virtual void vf54();
    virtual void vf55();
    virtual void vf56();
    virtual void vf57();
    virtual void vf58();
    virtual void vf59();
    virtual void vf60();
    virtual void vf61();
    virtual void vf62();
};
// table 0x7100B51F08; base at 0x8 unknown (TUnk_B51F68), base at 0x10 unknown (TUnk_B51F80)
class GfFieldManager : public ::mm::mtl::PtrSingleton< ::gf::GfFieldManager>, public TUnk_B51F68, public TUnk_B51F80 {
public:
    virtual ~GfFieldManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 3
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int);  // slot 4
    virtual void gevBattleStart();  // slot 5
    virtual void gevBattleEnd();  // slot 6
    virtual void gevGameMapModel(gf::GF_OBJ_HANDLE*, bool);  // slot 7
    virtual void gevPause(unsigned int, unsigned int);  // slot 8
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 9
};
}  // namespace gf

#endif
