#ifndef CLASSES_GF_GFGAMEPARTY_H
#define CLASSES_GF_GFGAMEPARTY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameParty; }
#include "classes/gf/IGfObjListener.h"

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
    static gf::GF_OBJ_HANDLE* getLeader();  // the party's leader, -1 for none
    static bool isBtlLeaderDirver();
    // the bdat ID of the party member driver at an index, and of the blade in a slot of its driver
    // (3.0.1 passes a second argument, 0 here, through to the party data; 1.0.0 has only the first)
    static unsigned int getDriverBdatId(unsigned int index, unsigned int party);
    static unsigned int getBladeBdatId(unsigned int index, int slot);
    static unsigned int getPartyId(gf::GF_OBJ_HANDLE* handle);
    static gf::GF_OBJ_HANDLE* getLeaderDriver();
};
}  // namespace gf

#endif
