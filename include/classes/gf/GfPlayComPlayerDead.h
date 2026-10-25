#ifndef CLASSES_GF_GFPLAYCOMPLAYERDEAD_H
#define CLASSES_GF_GFPLAYCOMPLAYERDEAD_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }
namespace gf { enum GfPlayerDead : int; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// a base of gf::GfPlayComPlayerDead no evidence names yet
class TUnk_B58728 : public GfPlayCom {
public:
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) = 0;
};
// a base of gf::GfPlayComPlayerDead no evidence names yet
class TUnk_B58778 {
public:
    virtual ~TUnk_B58778();
};
// table 0x7100B58728; base at 0x0 unknown (TUnk_B58728), base at 0x10 unknown (TUnk_B58778)
class GfPlayComPlayerDead : public TUnk_B58728, public TUnk_B58778, public ::gf::IGfEvent {
public:
    static GfPlayComPlayerDead* create(GfPlayerDead dead);
    static bool isDead();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComPlayerDead();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 7
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_20[0x1A];
    // GfPlayComEvent::update sets it while its event is still playing (the name is not the original's)
    bool m_eventPlaying;
};
}  // namespace gf

#endif
