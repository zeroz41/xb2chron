#include "classes/gf/LocatorBat_EnemyID.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gmk/GmkManager.h"
#include "plugin/Bdat.h"

namespace gf {

void LocatorBat_EnemyID::create(QuestID questId, unsigned short enemyId) {
    dispose();
    m_questId = questId;
    m_enemyId = enemyId;
    // CHR_EnArrange (0x8B): the enemy's zone, 0 when it has none
    unsigned char zoneId = Bdat::getValCheck(GfDataBdat::getFP(0x8B), "ZoneID", m_enemyId, 1);
    if (!zoneId) {
        dispose();
        return;
    }
    m_mapBdatId = zoneId;
    m_gmkSetId = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(getMapBdatId());
    int iconId = gmk::getBdatIdOfQuestTargetIcon(
        GfQuestTarget::getIconTypeBattle(1, enemyId, m_questId, reinterpret_cast<GF_OBJ_HANDLE*>(-1), true));
    m_iconBdatId = iconId < 0 ? 0x19f : iconId;
}

}  // namespace gf
