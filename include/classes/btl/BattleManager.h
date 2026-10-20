#ifndef CLASSES_BTL_BATTLEMANAGER_H
#define CLASSES_BTL_BATTLEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BattleManager; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace btl {
// a base of btl::BattleManager no evidence names yet
class TUnk_B3A5D8 {
public:
    virtual ~TUnk_B3A5D8();
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
    virtual void vf36();
    virtual void vf37();
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
    virtual void vf48();
    virtual void vf49();
    virtual void vf50();
    virtual void vf51();
    virtual void vf52();
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
// table 0x7100B3A5A0; base at 0x8 unknown (TUnk_B3A5D8)
class BattleManager : public ::mm::mtl::PtrSingleton< ::btl::BattleManager>, public TUnk_B3A5D8 {
public:
    virtual ~BattleManager();  // slot 0
    virtual void gevBattleStart();  // slot 2
    virtual void gevBattleEnd();  // slot 3
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 4
    static bool isInitialized();
    unsigned char pad_10[4];
    bool m_initialized;     // set by Initialize, cleared by Finalize
    unsigned char pad_15;   // a flag Initialize sets with it
};
}  // namespace btl

#endif
