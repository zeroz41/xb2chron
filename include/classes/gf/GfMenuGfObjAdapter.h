#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_H

#include "classes/gf/GfMenuAdapter.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
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
};
// table 0x7100B5C0D8; base at 0x0 GfMenuAdapter (create constructs it as one, then installs this table), base at 0x30 unknown (TUnk_B5C118), base at 0x38 unknown (TUnk_B5C130), base at 0x40 unknown (TUnk_B5C148)
class GfMenuGfObjAdapter : public ::gf::GfMenuAdapter, public TUnk_B5C118, public TUnk_B5C130, public TUnk_B5C148 {
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
    // an adapter on the handle with a plugin of that type, whose GF object a PartyBladeConverter picks
    static GfMenuGfObjAdapter* createFromPartyBlade(unsigned int handle, unsigned int type, unsigned char, int,
                                                    bool, bool);
    unsigned char pad_48[0x28];
    // which one of its kind it shows: create clears it, callers set it (GfMenuObjSpecialGauge's gauge levels)
    // (the name is not the original's)
    int m_index;
    unsigned char pad_74[4];
    IConverter* m_converter;  // createFromPartyBlade's PartyBladeConverter; create clears it
};
}  // namespace gf

#endif
