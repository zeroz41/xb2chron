#ifndef CLASSES_GF_GFINITPARAM_H
#define CLASSES_GF_GFINITPARAM_H

#include "mm/Vec3.h"
#include "classes/gf/DataParamAcc.h"

namespace gf { class GfAssetSetup; class GF_OBJ_HANDLE; }

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
    unsigned char pad_14[0x18 - 0x14];
    // a field object's BDAT file: GfObjSetup::createSetupParam reads its "paramid<n>" column from *pad_18
    unsigned char** pad_18;
    // GfObjSetup's constructor copies these two (the first into its m_partyId)
    unsigned int pad_20;
    unsigned int pad_24;
    unsigned char pad_28[0x30 - 0x28];
    // the objects GfInitParamWeapon::setupForEventBlade and GfInitParamBlade::setupForParty are given
    GF_OBJ_HANDLE* pad_30;
    GF_OBJ_HANDLE* pad_38;
    // GfEvtModelDriver's constructor moves 7..9 to 10..12 in the theater or in full-screen menus of game
    // state 6; what the values mean is not known yet
    int pad_40;
    unsigned char pad_44[0x48 - 0x44];
    // the third DataParamAcc argument for the object: GfObjSetup's constructor copies it into its own
    // (the name is not the original's)
    GimmickType m_gimmickType;
    // the object's uniform scale: GfObjSetup's constructor passes it to setInitialScale (the name is not the
    // original's)
    float m_scale;
    // GfObjSetup's constructor copies it into its pad_50 (a float)
    float pad_50;
    unsigned char pad_54[0x60 - 0x54];
    // the object's position, used when m_hasTransform is set (GfObjSetup's constructor; the name is not the
    // original's)
    mm::Vec3 m_initialPos;
    // copied with m_initialPos when m_hasTransform is set (GfObjSetup's constructor)
    mm::Vec3 pad_70;
    // whether m_initialPos and pad_70 hold values: GfObjSetup's constructor zeroes both otherwise (the name is
    // not the original's)
    bool m_hasTransform;
    bool pad_81;
    unsigned char pad_82;
    // a weapon's files from db/ in place of wp/: GfAssetSetupWeapon's file getters pass it to gf::fn_71001C0EE0
    bool pad_83;
    unsigned char pad_84[0x88 - 0x84];
    // a setup to use instead of the factory's own (the name is not the original's)
    GfAssetSetup* m_assetSetup;
};
}  // namespace gf

#endif
