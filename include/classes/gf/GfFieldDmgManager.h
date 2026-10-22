#ifndef CLASSES_GF_GFFIELDDMGMANAGER_H
#define CLASSES_GF_GFFIELDDMGMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldDmgManager; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// table 0x7100B514E8
class GfFieldDmgManager : public ::mm::mtl::PtrSingleton< ::gf::GfFieldDmgManager>, public ::gf::IGfEvent {
public:
    virtual ~GfFieldDmgManager();  // slot 0
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 2

    // one terrain damage's row (12 bytes, found by id)
    struct BdatInfo {
        unsigned char pad_0[0x2];
        unsigned short m_id;       // findBdatInfo's key
        float m_interval;          // how long between hits, in seconds
        unsigned char m_damage;    // what each hit deals
        unsigned char pad_9[0x3];
    };

    const BdatInfo* findBdatInfo(unsigned short id) const;
};
}  // namespace gf

#endif
