#ifndef CLASSES_GF_GFSMNENEMYMANAGER_H
#define CLASSES_GF_GFSMNENEMYMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"

namespace gf { class GfRelSmnEnemy; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf { class GfSmnEnemyManager; }

namespace gf {
// table 0x7100B59168
class GfSmnEnemyManager : public ::mm::mtl::PtrSingleton< ::gf::GfSmnEnemyManager> {
public:
    // an absolute summon: every enemy around the summoner joins the battle, and the gimmick enemies of the group pop
    // (field names are not the original's)
    struct AbsSmnInfo {
        GF_OBJ_HANDLE* handle;  // the summoner
        float radius;
        unsigned char group;    // the enemies' group (SDataEnemy's), 0 for all
        unsigned char flagBit;  // the bit of the gimmicks' summon flags
    };
    // a relative summon: a GfRelSmnEnemy pops the summon row's enemies around the summoner (field names are not the
    // original's)
    struct RelSmnInfo {
        GF_OBJ_HANDLE* handle;  // the summoner
        unsigned int id;        // its row of the summon table
    };

    GfSmnEnemyManager();
    virtual ~GfSmnEnemyManager();  // slot 0
    static void create();
    static void dispose();
    static void update(float dt);
    static void clearSmnEnemies();
    static bool execAbsSummon(const AbsSmnInfo& info);
    static bool execRelSummon(const RelSmnInfo& info);
    // how many relative summons it keeps, and one of them (inline: GfGameInsideBattleLock::updateInfos reads them;
    // the names are not the original's)
    unsigned int getRelSmnEnemyNum() const { return m_relSmnEnemies.size(); }
    GfRelSmnEnemy* getRelSmnEnemy(unsigned int index) const { return m_relSmnEnemies[index]; }

    mm::mtl::Vector<GfRelSmnEnemy*> m_relSmnEnemies;  // the relative summons (the name is not the original's)
};
}  // namespace gf

#endif
