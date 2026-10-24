#ifndef CLASSES_GF_GFBDATITEM_H
#define CLASSES_GF_GFBDATITEM_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatItem; }

namespace gf {
// table 0x7100B46D30; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatItem : public ::mm::mtl::PtrSingleton< ::gf::GfBdatItem>, public ::gf::IDataBdat {
public:
    GfBdatItem();
    virtual ~GfBdatItem();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    unsigned int getCrystalListStart() const;
    unsigned int getCrystalListEnd() const;
    unsigned int getBoosterStart() const;
    unsigned int getBoosterEnd() const;
    unsigned int getCollectionListStart() const;
    unsigned int getCollectionListEnd() const;
    unsigned int getEmptyOrbStart() const;
    unsigned int getEmptyOrbEnd() const;
    unsigned int getEquipOrbStart() const;
    unsigned int getEquipOrbEnd() const;
    unsigned int getInfoStart() const;
    unsigned int getInfoEnd() const;
    unsigned int getEventStart() const;
    unsigned int getEventEnd() const;
    unsigned int getPcWpnStart() const;
    unsigned int getPcWpnEnd() const;
    unsigned int getPcWpnChipStart() const;
    unsigned int getPcWpnChipEnd() const;
    unsigned int getPcEquipStart() const;
    unsigned int getPcEquipEnd() const;
    unsigned int getSalvageStart() const;
    unsigned int getSalvageEnd() const;
    unsigned int getHealPotStart() const;
    unsigned int getHealPotEnd() const;
    unsigned int getTresureStart() const;
    unsigned int getTresureEnd() const;
    unsigned int getFavoriteStart() const;
    unsigned int getFavoriteEnd() const;
    unsigned int getITM_HanaRoleStart() const;
    unsigned int getITM_HanaRoleEnd() const;
    unsigned int getITM_HanaAtrStart() const;
    unsigned int getITM_HanaAtrEnd() const;
    unsigned int getITM_HanaArtsEnhStart() const;
    unsigned int getITM_HanaArtsEnhEnd() const;
    unsigned int getITM_HanaNArtsSetStart() const;
    unsigned int getITM_HanaNArtsSetEnd() const;
    unsigned int getITM_HanaAssistStart() const;
    unsigned int getITM_HanaAssistEnd() const;
    unsigned int getITM_HanaRoleHpMaxRev(unsigned int parts) const;
    unsigned int getITM_HanaRoleStrengthRev(unsigned int parts) const;
    unsigned int getITM_HanaRolePowEtherRev(unsigned int parts) const;
    unsigned int getITM_HanaRoleDexRev(unsigned int parts) const;
    unsigned int getITM_HanaRoleAgilityRev(unsigned int parts) const;
    unsigned int getITM_HanaRoleLuckRev(unsigned int parts) const;
    unsigned short getPcWpnRscR(unsigned int weapon) const;
    unsigned int getPcWpnWpnType(unsigned int weapon) const;
    unsigned int getPcWpnDamage(unsigned int weapon) const;
    unsigned int getPcWpnStability(unsigned int weapon) const;
    unsigned int getPcWpnPArmor(unsigned int weapon) const;
    unsigned int getPcWpnEArmor(unsigned int weapon) const;
    unsigned int getPcWpnCriRate(unsigned int weapon) const;
    unsigned int getPcWpnGuardRate(unsigned int weapon) const;  // a driver weapon's resource (GfBdatRsc's row)
    // Table wrappers exposed by the range queries; names follow their accessors.
    CBdatWrapper* m_fpCrystalList;  // 0x10
    CBdatWrapper* m_fpCollectionList;  // 0x18
    CBdatWrapper* m_fpEmptyOrb;  // 0x20
    unsigned char pad_28[0x8];
    CBdatWrapper* m_fpPcWpn;  // 0x30
    CBdatWrapper* m_fpPcWpnChip;  // 0x38
    unsigned char pad_40[0x8];
    CBdatWrapper* m_fpPcEquip;  // 0x48
    CBdatWrapper* m_fpEquipOrb;  // 0x50
    unsigned char pad_58[0x10];
    CBdatWrapper* m_fpInfo;  // 0x68
    CBdatWrapper* m_fpEvent;  // 0x70
    CBdatWrapper* m_fpSalvage;  // 0x78
    CBdatWrapper* m_fpHealPot;  // 0x80
    CBdatWrapper* m_fpBooster;  // 0x88
    CBdatWrapper* m_fpTresure;  // 0x90
    CBdatWrapper* m_fpFavorite;  // 0x98
    unsigned char pad_a0[0x10];
    CBdatWrapper* m_fpITM_HanaRole;  // 0xB0
    CBdatWrapper* m_fpITM_HanaAtr;  // 0xB8
    CBdatWrapper* m_fpITM_HanaArtsEnh;  // 0xC0
    CBdatWrapper* m_fpITM_HanaNArtsSet;  // 0xC8
    CBdatWrapper* m_fpITM_HanaAssist;  // 0xD0
    unsigned char pad_d8[0x8];
    unsigned int getPcWpnTypeRole(unsigned int) const;
    unsigned int getPcWpnEnhance1(unsigned int) const;
    unsigned int getPcWpnTypeMotion(unsigned int) const;
    unsigned int getITM_HanaRoleNeedEther(unsigned int) const;
    unsigned int getITM_HanaAtrNeedEther(unsigned int) const;
    unsigned int getITM_HanaArtsEnhNeedEther(unsigned int) const;
    unsigned int getITM_HanaNArtsSetNeedEther(unsigned int) const;
    unsigned int getITM_HanaAssistNeedEther(unsigned int) const;
};
}  // namespace gf

#endif
