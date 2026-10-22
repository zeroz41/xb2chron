#ifndef GF_SDATAENEMY_H
#define GF_SDATAENEMY_H

namespace gf {
// no table: an enemy's data, as GfDataEnemy::setupSDataEnemy fills it in from the enemy's bdat rows
class SDataEnemy {
public:
    SDataEnemy(unsigned int, unsigned int);

    unsigned char pad_0[0x9A];
    // GfBdatRsc::getRscEnActType's for the enemy (setupSDataEnemy; the name is not the original's)
    unsigned char m_actType;
};
}  // namespace gf

#endif
