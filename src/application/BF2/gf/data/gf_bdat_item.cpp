#include "classes/gf/GfBdatItem.h"
#include "plugin/Bdat.h"

namespace gf {

GfBdatItem::~GfBdatItem() {
    destroyFP();
}

unsigned int GfBdatItem::getCrystalListStart() const {
    return Bdat::getIdTop(m_fpCrystalList->m_fp);
}

unsigned int GfBdatItem::getCrystalListEnd() const {
    return Bdat::getIdTop(m_fpCrystalList->m_fp) + Bdat::getIdCount(m_fpCrystalList->m_fp);
}

unsigned int GfBdatItem::getBoosterStart() const {
    return Bdat::getIdTop(m_fpBooster->m_fp);
}

unsigned int GfBdatItem::getBoosterEnd() const {
    return Bdat::getIdTop(m_fpBooster->m_fp) + Bdat::getIdCount(m_fpBooster->m_fp);
}

unsigned int GfBdatItem::getCollectionListStart() const {
    return Bdat::getIdTop(m_fpCollectionList->m_fp);
}

unsigned int GfBdatItem::getCollectionListEnd() const {
    return Bdat::getIdTop(m_fpCollectionList->m_fp) + Bdat::getIdCount(m_fpCollectionList->m_fp);
}

unsigned int GfBdatItem::getEmptyOrbStart() const {
    return Bdat::getIdTop(m_fpEmptyOrb->m_fp);
}

unsigned int GfBdatItem::getEmptyOrbEnd() const {
    return Bdat::getIdTop(m_fpEmptyOrb->m_fp) + Bdat::getIdCount(m_fpEmptyOrb->m_fp);
}

unsigned int GfBdatItem::getEquipOrbStart() const {
    return Bdat::getIdTop(m_fpEquipOrb->m_fp);
}

unsigned int GfBdatItem::getEquipOrbEnd() const {
    return Bdat::getIdTop(m_fpEquipOrb->m_fp) + Bdat::getIdCount(m_fpEquipOrb->m_fp);
}

unsigned int GfBdatItem::getInfoStart() const {
    return Bdat::getIdTop(m_fpInfo->m_fp);
}

unsigned int GfBdatItem::getInfoEnd() const {
    return Bdat::getIdTop(m_fpInfo->m_fp) + Bdat::getIdCount(m_fpInfo->m_fp);
}

unsigned int GfBdatItem::getEventStart() const {
    return Bdat::getIdTop(m_fpEvent->m_fp);
}

unsigned int GfBdatItem::getEventEnd() const {
    return Bdat::getIdTop(m_fpEvent->m_fp) + Bdat::getIdCount(m_fpEvent->m_fp);
}

unsigned int GfBdatItem::getPcWpnStart() const {
    return Bdat::getIdTop(m_fpPcWpn->m_fp);
}

unsigned int GfBdatItem::getPcWpnEnd() const {
    return Bdat::getIdTop(m_fpPcWpn->m_fp) + Bdat::getIdCount(m_fpPcWpn->m_fp);
}

unsigned int GfBdatItem::getPcWpnChipStart() const {
    return Bdat::getIdTop(m_fpPcWpnChip->m_fp);
}

unsigned int GfBdatItem::getPcWpnChipEnd() const {
    return Bdat::getIdTop(m_fpPcWpnChip->m_fp) + Bdat::getIdCount(m_fpPcWpnChip->m_fp);
}

unsigned int GfBdatItem::getPcEquipStart() const {
    return Bdat::getIdTop(m_fpPcEquip->m_fp);
}

unsigned int GfBdatItem::getPcEquipEnd() const {
    return Bdat::getIdTop(m_fpPcEquip->m_fp) + Bdat::getIdCount(m_fpPcEquip->m_fp);
}

unsigned int GfBdatItem::getSalvageStart() const {
    return Bdat::getIdTop(m_fpSalvage->m_fp);
}

unsigned int GfBdatItem::getSalvageEnd() const {
    return Bdat::getIdTop(m_fpSalvage->m_fp) + Bdat::getIdCount(m_fpSalvage->m_fp);
}

unsigned int GfBdatItem::getHealPotStart() const {
    return Bdat::getIdTop(m_fpHealPot->m_fp);
}

unsigned int GfBdatItem::getHealPotEnd() const {
    return Bdat::getIdTop(m_fpHealPot->m_fp) + Bdat::getIdCount(m_fpHealPot->m_fp);
}

unsigned int GfBdatItem::getTresureStart() const {
    return Bdat::getIdTop(m_fpTresure->m_fp);
}

unsigned int GfBdatItem::getTresureEnd() const {
    return Bdat::getIdTop(m_fpTresure->m_fp) + Bdat::getIdCount(m_fpTresure->m_fp);
}

unsigned int GfBdatItem::getFavoriteStart() const {
    return Bdat::getIdTop(m_fpFavorite->m_fp);
}

unsigned int GfBdatItem::getFavoriteEnd() const {
    return Bdat::getIdTop(m_fpFavorite->m_fp) + Bdat::getIdCount(m_fpFavorite->m_fp);
}

unsigned int GfBdatItem::getITM_HanaRoleStart() const {
    return Bdat::getIdTop(m_fpITM_HanaRole->m_fp);
}

unsigned int GfBdatItem::getITM_HanaRoleEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaRole->m_fp) + Bdat::getIdCount(m_fpITM_HanaRole->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAtrStart() const {
    return Bdat::getIdTop(m_fpITM_HanaAtr->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAtrEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaAtr->m_fp) + Bdat::getIdCount(m_fpITM_HanaAtr->m_fp);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhStart() const {
    return Bdat::getIdTop(m_fpITM_HanaArtsEnh->m_fp);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaArtsEnh->m_fp) + Bdat::getIdCount(m_fpITM_HanaArtsEnh->m_fp);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetStart() const {
    return Bdat::getIdTop(m_fpITM_HanaNArtsSet->m_fp);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaNArtsSet->m_fp) + Bdat::getIdCount(m_fpITM_HanaNArtsSet->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAssistStart() const {
    return Bdat::getIdTop(m_fpITM_HanaAssist->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAssistEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaAssist->m_fp) + Bdat::getIdCount(m_fpITM_HanaAssist->m_fp);
}

}  // namespace gf
