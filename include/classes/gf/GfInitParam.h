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
    virtual unsigned int getBladeID() const { return m_objId; }  // slot 1 (GfEvtModelBlade's constructor compares it with 0x451)
    virtual unsigned int getEnArrangeID() const { return 0; }  // slot 2

    // inline: no copy of it exists. GfObjFactory's createGmk* and createMapLodAnim build their parameters on the
    // stack with these values (kind is pad_c's); m_assetSetup is the derived class's
    // (GfInitParamGimmick's zeroing of it merges with its own members')
    GfInitParam(int kind, int value40 = 4)
        : m_createType(0), pad_c(kind), m_objId(0), pad_18(nullptr), pad_20(-1), pad_24(0), pad_28(-1),
          pad_30(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_38(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_40(value40),
          pad_44(0), m_gimmickType(GimmickType(0)), m_scale(1.0f), pad_50(1.0f), m_hasTransform(false), pad_81(true),
          pad_82(0), pad_83(false), pad_84(0) {}

    // what the object is made for: GfAssetFactory picks the event (2, 3, 11), salvage (9, 13) and UI (6, 7, 12)
    // setups by it (the name is not the original's)
    int m_createType;
    // set by the derived classes' constructors: 8 for a gimmick, 1 for a map's LOD animation (what it means is not
    // known yet)
    int pad_c;
    // the object's id: GfEvtModel keeps it, GfEvtModelDriver reads its blade by it (DataParamAcc(3, id, 0))
    // (the name is not the original's)
    unsigned int m_objId;
    unsigned char pad_14[0x18 - 0x14];
    // a field object's BDAT file: GfObjSetup::createSetupParam reads its "paramid<n>" column from *pad_18
    unsigned char** pad_18;
    // GfObjSetup's constructor copies these two (the first into its m_partyId)
    unsigned int pad_20;
    unsigned int pad_24;
    int pad_28;  // -1 at first
    unsigned char pad_2c[0x30 - 0x2C];
    // the objects GfInitParamWeapon::setupForEventBlade and GfInitParamBlade::setupForParty are given
    GF_OBJ_HANDLE* pad_30;
    GF_OBJ_HANDLE* pad_38;
    // GfEvtModelDriver's constructor moves 7..9 to 10..12 in the theater or in full-screen menus of game
    // state 6; what the values mean is not known yet
    int pad_40;
    unsigned short pad_44;
    unsigned char pad_46[0x48 - 0x46];
    // the third DataParamAcc argument for the object: GfObjSetup's constructor copies it into its own
    // (the name is not the original's)
    GimmickType m_gimmickType;
    // the object's uniform scale: GfObjSetup's constructor passes it to setInitialScale (the name is not the
    // original's)
    float m_scale;
    // GfObjSetup's constructor copies it into its pad_50 (a float)
    float pad_50;
    // (0x54..0x5f: alignment only: the copy assignments copy 0x08..0x53 as one block)
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
    unsigned char pad_84;
    // the base ends here (0x85): the copy assignments copy 0x80..0x84 as the base's last block, and each kind's
    // own fields (m_assetSetup first) start at 0x88 in the base's tail padding
};
}  // namespace gf

#endif
