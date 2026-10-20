// not proven yet: its table differs from the original's (word 21: _ZN2gf11TUnk_B5A93012update_HpMaxERKNS_12DataParamAccE where the original has _ZN2gf21GfMenuCharDataAdapter12update_HpMaxERKNS_12DataParamAccE)
#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_H

namespace fw { class UpdateInfo; }
namespace gf { class DataParamAcc; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A8A0 {
public:
    virtual ~TUnk_B5A8A0();
    virtual void update(fw::UpdateInfo const&) = 0;
    virtual void changeCharData(unsigned char, unsigned int) = 0;
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*) = 0;
    virtual void changePartyDriver(unsigned char) = 0;
    virtual void changePartyBlade(unsigned char, unsigned char) = 0;
    unsigned char pad_8[0x28];  // fields: size from where the next base starts
};
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A8E8 {
public:
    virtual void changeCharData(unsigned char, unsigned int) = 0;
};
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A900 {
public:
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*) = 0;
};
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A918 {
public:
    virtual void changePartyDriver(unsigned char) = 0;
};
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A930 {
public:
    virtual void changePartyBlade(unsigned char, unsigned char) = 0;
    virtual void update_HpMax(gf::DataParamAcc const&);
};
// table 0x7100B5A8A0; base at 0x0 unknown (TUnk_B5A8A0), base at 0x30 unknown (TUnk_B5A8E8), base at 0x38 unknown (TUnk_B5A900), base at 0x40 unknown (TUnk_B5A918), base at 0x48 unknown (TUnk_B5A930)
class GfMenuCharDataAdapter : public TUnk_B5A8A0, public TUnk_B5A8E8, public TUnk_B5A900, public TUnk_B5A918, public TUnk_B5A930 {
public:
    class BladeListConverter;
    class DriverListConverter;
    class EnBookListConverter;
    class EnemyListConverter;
    class GfObjConverter;
    class IConverter;
    class PartyBladeConverter;
    class PartyDriverConverter;
    class ReferenceBladeConverter;
    class ReferenceDriverConverter;
    virtual ~GfMenuCharDataAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void changeCharData(unsigned char, unsigned int);  // slot 3
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*);  // slot 4
    virtual void changePartyDriver(unsigned char);  // slot 5
    virtual void changePartyBlade(unsigned char, unsigned char);  // slot 6
};
}  // namespace gf

#endif
