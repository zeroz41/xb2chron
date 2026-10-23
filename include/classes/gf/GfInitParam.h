#ifndef CLASSES_GF_GFINITPARAM_H
#define CLASSES_GF_GFINITPARAM_H

namespace gf { class GfAssetSetup; }

namespace gf {
// table none (its derived classes')
class GfInitParam {
public:
    virtual bool isAllWeapon() const { return false; }  // slot 0
    virtual unsigned int getBladeID() const;  // slot 1 (GfEvtModelBlade's constructor compares it with 0x451)
    virtual void getEnArrangeID() const;  // slot 2

    // what the object is made for: GfAssetFactory picks the event (2, 3, 11), salvage (9, 13) and UI (6, 7, 12)
    // setups by it (the name is not the original's)
    int m_createType;
    unsigned char pad_c[0x10 - 0xC];
    // the object's id: GfEvtModel keeps it, GfEvtModelDriver reads its blade by it (DataParamAcc(3, id, 0))
    // (the name is not the original's)
    unsigned int m_objId;
    unsigned char pad_14[0x40 - 0x14];
    // GfEvtModelDriver's constructor moves 7..9 to 10..12 in the theater or in full-screen menus of game
    // state 6; what the values mean is not known yet
    int pad_40;
    unsigned char pad_44[0x88 - 0x44];
    // a setup to use instead of the factory's own (the name is not the original's)
    GfAssetSetup* m_assetSetup;
};
}  // namespace gf

#endif
