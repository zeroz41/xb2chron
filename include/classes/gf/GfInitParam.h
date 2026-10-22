#ifndef CLASSES_GF_GFINITPARAM_H
#define CLASSES_GF_GFINITPARAM_H

namespace gf { class GfAssetSetup; }

namespace gf {
// table none (its derived classes')
class GfInitParam {
public:
    virtual bool isAllWeapon() const { return false; }  // slot 0
    virtual void getBladeID() const;  // slot 1
    virtual void getEnArrangeID() const;  // slot 2

    // what the object is made for: GfAssetFactory picks the event (2, 3, 11), salvage (9, 13) and UI (6, 7, 12)
    // setups by it (the name is not the original's)
    int m_createType;
    unsigned char pad_c[0x88 - 0xC];
    // a setup to use instead of the factory's own (the name is not the original's)
    GfAssetSetup* m_assetSetup;
};
}  // namespace gf

#endif
