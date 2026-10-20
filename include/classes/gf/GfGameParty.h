#ifndef CLASSES_GF_GFGAMEPARTY_H
#define CLASSES_GF_GFGAMEPARTY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameParty; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gf {
// a base of gf::GfGameParty no evidence names yet
class TUnk_B553D8 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B553B0; base at 0x8 unknown (TUnk_B553D8)
class GfGameParty : public ::mm::mtl::PtrSingleton< ::gf::GfGameParty>, public TUnk_B553D8 {
public:
    virtual ~GfGameParty();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
};
}  // namespace gf

#endif
