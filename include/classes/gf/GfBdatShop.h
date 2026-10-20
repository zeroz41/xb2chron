#ifndef CLASSES_GF_GFBDATSHOP_H
#define CLASSES_GF_GFBDATSHOP_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatShop; }

namespace gf {
// a base of gf::GfBdatShop no evidence names yet
class TUnk_B47D48 {
public:
    virtual ~TUnk_B47D48();
    virtual void bdatRefresh() = 0;
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
    virtual void vf42();
    virtual void vf43();
    virtual void vf44();
    virtual void vf45();
    virtual void vf46();
    virtual void vf47();
    virtual void vf48();
    virtual void vf49();
    virtual void vf50();
    virtual void vf51();
    virtual void vf52();
    virtual void vf53();
};
// table 0x7100B47D20; base at 0x8 unknown (TUnk_B47D48)
class GfBdatShop : public ::mm::mtl::PtrSingleton< ::gf::GfBdatShop>, public TUnk_B47D48 {
public:
    virtual ~GfBdatShop();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
