#ifndef GF_GFGAMEUTILHANA_H
#define GF_GFGAMEUTILHANA_H

namespace gf {

struct EquipHana;
struct GfItemHandle;

// what Hana's checks give (GfMenuHanaAdapter passes it on): 0 when the thing can be done; the circuit checks give 10
// for a circuit that ether can open, the power rank check 6 for a rank that cannot be raised
enum RESULT_HANA {};

// Hana's (the artificial blade's) helpers (functions, by their symbols): her circuits and power rank
class GfGameUtilHana {
public:
    static RESULT_HANA isOpenArtsCircuit(unsigned int hana, unsigned int circuit);
    static int getEtherForOpenArtsCircuit(unsigned int hana, unsigned int circuit);
    static RESULT_HANA isOpenCondenserCircuit(unsigned int hana, unsigned int circuit);
    static int getEtherForOpenCondenserCircuit(unsigned int hana, unsigned int circuit);
    static unsigned int getPowerRank(unsigned int hana);
    // GfGameManager::gevBladeEnable calls it with the enabled blade
    static void setupDefaultParts(unsigned int blade);
    // opens a circuit for its ether: 4 when the blade is not Hana, 1 when it is open already, 2 when ether cannot
    // open it, 3 when there is not enough ether
    static RESULT_HANA openArtsCircuit(unsigned int hana, unsigned int circuit);
    static RESULT_HANA openCondenserCircuit(unsigned int hana, unsigned int circuit);
    // whether a part can be bought for ether: 7 when the box has no room for it, 3 when there is not enough ether
    static RESULT_HANA isExchangeRoleParts(unsigned int item);
    static RESULT_HANA isExchangeAttributeParts(unsigned int item);
    static RESULT_HANA isExchangeArtsParts(unsigned int item);
    static RESULT_HANA isExchangeNArtsParts(unsigned int item);
    static RESULT_HANA isExchangeCondenserParts(unsigned int item);
    // whether a part can go into Hana's slot: 4 when the blade is not Hana, 12 when the part does not fit her, 8 when
    // the party has none, 9 when every one is equipped, 13 when another condenser has its effect, 5 when her power
    // capacity cannot carry it
    static RESULT_HANA isEnableEquipRoleParts(unsigned int hana, unsigned int item);
    static RESULT_HANA isEnableEquipAttributeParts(unsigned int hana, unsigned int item);
    static RESULT_HANA isEnableEquipArtsParts(unsigned int hana, unsigned int item, unsigned int slot);
    static RESULT_HANA isEnableEquipNArtsParts(unsigned int hana, unsigned int item, unsigned int slot);
    static RESULT_HANA isEnableEquipCondenserParts(unsigned int hana, unsigned int item, unsigned int slot);
    static RESULT_HANA isEnableEquipExtendCondenserParts(unsigned int hana, unsigned int item, unsigned int slot);
    // puts a part into Hana's slot (a free box entry when the handle is 0) and gives the old part back to the box
    static RESULT_HANA execEquipRoleParts(unsigned int hana, unsigned int item, GfItemHandle handle);
    static RESULT_HANA execEquipAttributeParts(unsigned int hana, unsigned int item, GfItemHandle handle);
    // the slot versions take item 0 to empty the slot
    static RESULT_HANA execEquipArtsParts(unsigned int hana, unsigned int item, GfItemHandle handle, unsigned int slot);
    static RESULT_HANA execEquipNArtsParts(unsigned int hana, unsigned int item, GfItemHandle handle, unsigned int slot);
    static RESULT_HANA execEquipCondenserParts(unsigned int hana, unsigned int item, GfItemHandle handle, unsigned int slot);
    static RESULT_HANA execEquipExtendCondenserParts(unsigned int hana, unsigned int item, GfItemHandle handle,
                                                     unsigned int slot);
    // copies Hana's equipment out (4 when the blade is not Hana)
    static RESULT_HANA getEquip(EquipHana& equip, unsigned int hana);
    // how many of an item can be turned into ether: its box count (without the equipped ones) for item types 16-20,
    // else 0
    static int getConvertToEther(unsigned int item);
    // raises her power rank for ether: 4 when the blade is not Hana, 3 when the ether runs out, 6 when the rank
    // cannot be reached
    static RESULT_HANA execPowerRankup(unsigned int hana, unsigned int rank);
    static RESULT_HANA isExecPowerRankup(unsigned int hana, unsigned int rank);
    static int getNeedEtherForExecPowerRankup(unsigned int hana, unsigned int rank);
    // turns one of an item (types 16-20) into its ether: 8 when the party has none outside the equipment
    static RESULT_HANA execConvertToEther(unsigned int item);
    // how many more of an item the box may hold: its stock less every item of its type the party has
    static int getEmptyParts(unsigned int item);
};

}  // namespace gf

#endif
