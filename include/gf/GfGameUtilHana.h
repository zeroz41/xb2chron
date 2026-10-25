#ifndef GF_GFGAMEUTILHANA_H
#define GF_GFGAMEUTILHANA_H

namespace gf {

struct EquipHana;

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
    // copies Hana's equipment out (4 when the blade is not Hana)
    static RESULT_HANA getEquip(EquipHana& equip, unsigned int hana);
    // how many of an item can be turned into ether: its box count (without the equipped ones) for item types 16-20,
    // else 0
    static int getConvertToEther(unsigned int item);
    static RESULT_HANA isExecPowerRankup(unsigned int hana, unsigned int rank);
    static int getNeedEtherForExecPowerRankup(unsigned int hana, unsigned int rank);
    // turns one of an item (types 16-20) into its ether: 8 when the party has none outside the equipment
    static RESULT_HANA execConvertToEther(unsigned int item);
    // how many more of an item the box may hold: its stock less every item of its type the party has
    static int getEmptyParts(unsigned int item);
};

}  // namespace gf

#endif
