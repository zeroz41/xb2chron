#ifndef GF_GFDATAENEMY_H
#define GF_GFDATAENEMY_H

namespace gf { class SDataEnemy; }

namespace gf {
// the enemies' data, by their row ids (functions, by its symbols)
class GfDataEnemy {
public:
    static const char* getName(unsigned int arrange);
    // the message table and row of the enemy's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int arrange);
    static const char* getVoiceStr(unsigned int arrange);
    static unsigned int getEquipBlade(unsigned int arrange);  // the enemy's blade, 0 for none
    static bool getExtraParts(unsigned int rsc, unsigned int part);
    static void setupSDataEnemy(SDataEnemy& data, unsigned int arrange, unsigned int arg);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfDataEnemy's functions and, like getExtraParts, it takes an enemy's GfBdatRsc row. What it does: true when
    // GfBdatRsc::getRscEnExtraParts(rsc, part) is 2. DataObjEnemy's new table slot 42 returns it for its part.
    static bool fn_7100235424(unsigned int rsc, unsigned int part);
};
}  // namespace gf

#endif
