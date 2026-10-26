#ifndef GF_GFDATAHANA_H
#define GF_GFDATAHANA_H

namespace gf {

// Hana's equipment (GfDataHana::getEquipParts hands it out, GfGameUtilHana::getEquip copies its 0x78 bytes). The
// layout is what GfDataHana::getEquipPower and EquipHana::setArtsParts/setNArtsParts read and write; the field names
// are not the original's. It is 4-aligned: getEquipPower reads m_roleParts and m_attributeParts as one 32-bit load,
// which clang widens to only on a 4-aligned object.
struct alignas(4) EquipHana {
    // an arts or n-arts part's slot (12 bytes)
    struct Parts {
        // arts: GfBdatItem::getITM_HanaArtsEnhEnhance(m_item); n-arts: getITM_HanaNArtsSetNArts(m_item)
        unsigned short m_value;
        unsigned short m_value2;  // n-arts: GfBdatItem::getITM_HanaNArtsSetNArtsRecastRev(m_item)
        unsigned short m_item;  // the part's item (getEquipPower counts its need only when m_value is set)
        unsigned char pad_6[0x4];
        unsigned short m_handle;  // the item handle setArtsParts/setNArtsParts store (GfGameUtilHana::execEquip*)
    };
    unsigned short m_roleParts;  // read by GfDataHana::getAutoHate/getArtsHate, GfDataBlade::getHpMaxRev
    unsigned short m_attributeParts;
    Parts m_artsParts[3];
    Parts m_nArtsParts[3];
    unsigned short m_condenserParts[6];
    // the item handles of the equipped parts (GfGameUtilHana::execEquip*Parts store them next to the items; 0 when the
    // part came from no box entry)
    unsigned int m_roleHandle;
    unsigned int m_attributeHandle;
    unsigned int m_condenserHandles[6];

    void setArtsParts(unsigned int item, unsigned int handle, unsigned int slot);
    void setNArtsParts(unsigned int item, unsigned int handle, unsigned int slot);
    // inline: GfGameUtilHana::isEnableEquipCondenserParts/execEquipCondenserParts load the handle before the slot
    // address (the name is not the original's)
    void setCondenserParts(unsigned int item, unsigned int handle, unsigned int slot) {
        m_condenserParts[slot] = item;
        m_condenserHandles[slot] = handle;
    }
    // the three condensers after the first three (the name is not the original's): the original indexes from the
    // fourth slot (no 32-bit slot + 3)
    void setExtendCondenserParts(unsigned int item, unsigned int handle, unsigned int slot) {
        (&m_condenserParts[3])[slot] = item;
        (&m_condenserHandles[3])[slot] = handle;
    }
};

// Hana's (the artificial blade's) data (functions, by their symbols)
class GfDataHana {
public:
    static bool isValid(unsigned int blade);  // the blade is Hana (one of her forms)
    static unsigned int getRole(unsigned int hana);  // her role's message (GfDataBdat 0x115), 0 for none
    static int getAttribute(unsigned int hana);
    static unsigned int getAutoHate(unsigned int hana);
    static unsigned int getArtsHate(unsigned int hana);
    static int getEther();
    static int getPartsPower(unsigned int parts);  // the energy a part uses (GfMenuItemAdapter::update_useEnergy)
    static int getPowerCapacity(unsigned int hana);
    static int getEquipPower(unsigned int hana);
    static unsigned int getCondenserNum(unsigned int hana);
    static unsigned int getNartsNum(unsigned int hana);
    static unsigned int getNeedRolePartsEther(unsigned int hana);
    static unsigned int getNeedAttributePartsEther(unsigned int hana);
    static unsigned int getNeedArtsPartsEther(unsigned int hana);
    static unsigned int getNeedNArtsPartsEther(unsigned int hana);
    static unsigned int getNeedCondenserPartsEther(unsigned int hana);
    static unsigned int getDefaultRoleParts(unsigned int hana);
    static unsigned int getDefaultAttributeParts(unsigned int hana);
    static unsigned int getDefaultNArtsParts(unsigned int hana, unsigned int index);
    static unsigned int getDefaultCondenserParts(unsigned int hana, unsigned int index);
    static unsigned int getOpenCircuitEther(unsigned int hana, unsigned int index);
    static void setEther(unsigned int value);
    static bool isOpenCircuit(unsigned int hana, unsigned int circuit);
    static void setOpenCircuit(unsigned int hana, unsigned int circuit, bool open);
    static const EquipHana* getEquipParts(unsigned int hana);
    static void setEquipParts(unsigned int hana, const EquipHana& equip);
    static int getEquipPower(const EquipHana& equip);  // the energy its parts need
    static unsigned int getEquipPowerRank(unsigned int hana);  // GfGameUtilHana::getPowerRank forwards here
    static bool isEquipRoleParts(unsigned int hana, unsigned int item);  // GfBdatItem::isITM_HanaRoleFlag{JS,JK,JD}
    static bool isEquipAttributeParts(unsigned int hana, unsigned int item);  // GfBdatItem::isITM_HanaAtrFlag{JS,JK,JD}
    static bool isEquipArtsParts(unsigned int hana, unsigned int item);  // GfBdatItem::isITM_HanaArtsEnhFlag{JS,JK,JD}
    static bool isEquipNArtsParts(unsigned int hana, unsigned int item);  // GfBdatItem::isITM_HanaNArtsSetFlag{JS,JK,JD}
    static bool isEquipCondenserParts(unsigned int hana, unsigned int item);  // GfBdatItem::isITM_HanaAssistFlag{JS,JK,JD}
    // whether another condenser slot holds a part with the same effect (extend: the slots after the first three)
    static bool isExistSameEffectCondenserParts(unsigned int hana, unsigned int item, unsigned int slot, bool extend);
    static bool isExistSameEffectNArtsParts(unsigned int hana, unsigned int item, unsigned int slot);
    static void setEquipPowerRank(unsigned int hana, unsigned int rank);
};

}  // namespace gf

#endif
