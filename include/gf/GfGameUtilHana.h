#ifndef GF_GFGAMEUTILHANA_H
#define GF_GFGAMEUTILHANA_H

namespace gf {

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
    static RESULT_HANA isExecPowerRankup(unsigned int hana, unsigned int rank);
    static int getNeedEtherForExecPowerRankup(unsigned int hana, unsigned int rank);
};

}  // namespace gf

#endif
