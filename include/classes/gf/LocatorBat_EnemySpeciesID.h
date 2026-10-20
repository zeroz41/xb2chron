#ifndef CLASSES_GF_LOCATORBAT_ENEMYSPECIESID_H
#define CLASSES_GF_LOCATORBAT_ENEMYSPECIESID_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51B38
class LocatorBat_EnemySpeciesID : public ::gf::AFieldLocator {
public:
    virtual ~LocatorBat_EnemySpeciesID();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
};
}  // namespace gf

#endif
