#ifndef CLASSES_GF_LOCATORBAT_ENEMYID_H
#define CLASSES_GF_LOCATORBAT_ENEMYID_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51AA8
class LocatorBat_EnemyID : public ::gf::AFieldLocator {
public:
    virtual ~LocatorBat_EnemyID();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
};
}  // namespace gf

#endif
