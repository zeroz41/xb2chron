#ifndef CLASSES_GF_GFPLAYCOMPLAYERDEAD_H
#define CLASSES_GF_GFPLAYCOMPLAYERDEAD_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// a base of gf::GfPlayComPlayerDead no evidence names yet
class TUnk_B58728 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
    virtual ~TUnk_B58728();
    virtual void getFuncName() const = 0;
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void update(fw::UpdateInfo const&, bool) = 0;
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) = 0;
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of gf::GfPlayComPlayerDead no evidence names yet
class TUnk_B58778 {
public:
    virtual ~TUnk_B58778();
};
// table 0x7100B58728; base at 0x0 unknown (TUnk_B58728), base at 0x10 unknown (TUnk_B58778)
class GfPlayComPlayerDead : public TUnk_B58728, public TUnk_B58778, public ::gf::IGfEvent {
public:
    static bool isDead();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComPlayerDead();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 7
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
