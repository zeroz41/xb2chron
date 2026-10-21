#ifndef CLASSES_GF_GFPLAYCOMBATTLESTART_H
#define CLASSES_GF_GFPLAYCOMBATTLESTART_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::GfPlayComBattleStart no evidence names yet
class TUnk_B58A08 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
    virtual ~TUnk_B58A08();
    virtual void getFuncName() const = 0;
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void update(fw::UpdateInfo const&, bool) = 0;
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of gf::GfPlayComBattleStart no evidence names yet
class TUnk_B58A50 {
public:
    virtual ~TUnk_B58A50();
};
// table 0x7100B58A08; base at 0x0 unknown (TUnk_B58A08), base at 0x10 unknown (TUnk_B58A50)
class GfPlayComBattleStart : public TUnk_B58A08, public TUnk_B58A50 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComBattleStart();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start() {}  // slot 4
    virtual void end() {}  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
