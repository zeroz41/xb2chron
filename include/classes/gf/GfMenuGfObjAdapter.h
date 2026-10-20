// not proven yet: its table differs from the original's (word 17: _ZN2gf11TUnk_B5C14812update_NowHpEPNS_13GF_OBJ_HANDLEE where the original has _ZN2gf18GfMenuGfObjAdapter12update_NowHpEPNS_13GF_OBJ_HANDLEE)
#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_H

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a base of gf::GfMenuGfObjAdapter no evidence names yet
class TUnk_B5C0D8 {
public:
    virtual ~TUnk_B5C0D8();
    virtual void update(fw::UpdateInfo const&) = 0;
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*) = 0;
    virtual void changePartyDriver(unsigned char) = 0;
    virtual void changePartyBlade(unsigned char, unsigned char) = 0;
    unsigned char pad_8[0x28];  // fields: size from where the next base starts
};
// a base of gf::GfMenuGfObjAdapter no evidence names yet
class TUnk_B5C118 {
public:
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*) = 0;
};
// a base of gf::GfMenuGfObjAdapter no evidence names yet
class TUnk_B5C130 {
public:
    virtual void changePartyDriver(unsigned char) = 0;
};
// a base of gf::GfMenuGfObjAdapter no evidence names yet
class TUnk_B5C148 {
public:
    virtual void changePartyBlade(unsigned char, unsigned char) = 0;
    virtual void update_NowHp(gf::GF_OBJ_HANDLE*);
};
// table 0x7100B5C0D8; base at 0x0 unknown (TUnk_B5C0D8), base at 0x30 unknown (TUnk_B5C118), base at 0x38 unknown (TUnk_B5C130), base at 0x40 unknown (TUnk_B5C148)
class GfMenuGfObjAdapter : public TUnk_B5C0D8, public TUnk_B5C118, public TUnk_B5C130, public TUnk_B5C148 {
public:
    class IConverter;
    class PartyBladeConverter;
    class PartyDriverConverter;
    class TargetEnemyConverter;
    virtual ~GfMenuGfObjAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*);  // slot 3
    virtual void changePartyDriver(unsigned char);  // slot 4
    virtual void changePartyBlade(unsigned char, unsigned char);  // slot 5
};
}  // namespace gf

#endif
