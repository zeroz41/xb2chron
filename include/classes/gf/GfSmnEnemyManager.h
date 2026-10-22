#ifndef CLASSES_GF_GFSMNENEMYMANAGER_H
#define CLASSES_GF_GFSMNENEMYMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"

namespace gf { class GfRelSmnEnemy; }

namespace gf { class GfSmnEnemyManager; }

namespace gf {
// table 0x7100B59168
class GfSmnEnemyManager : public ::mm::mtl::PtrSingleton< ::gf::GfSmnEnemyManager> {
public:
    virtual ~GfSmnEnemyManager();  // slot 0
    // how many relative summons it keeps, and one of them (inline: GfGameInsideBattleLock::updateInfos reads them;
    // the names are not the original's)
    unsigned int getRelSmnEnemyNum() const { return m_relSmnEnemies.size(); }
    GfRelSmnEnemy* getRelSmnEnemy(unsigned int index) const { return m_relSmnEnemies[index]; }

    mm::mtl::Vector<GfRelSmnEnemy*> m_relSmnEnemies;  // the relative summons (the name is not the original's)
};
}  // namespace gf

#endif
