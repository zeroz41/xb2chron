#ifndef CLASSES_GF_GFRELSMNENEMY_H
#define CLASSES_GF_GFRELSMNENEMY_H

#include <utility>

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gmk/DistHvCond.h"
#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"

namespace gf {
// table 0x7100B59128; the enemies one object summons around itself (GfSmnEnemyManager::execRelSummon makes one)
class GfRelSmnEnemy : public IGfObjListener {
public:
    // whom it summons for, and the summon row (field names are not the original's)
    struct CreateInfo {
        CreateInfo() : handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), id(0), pos(mm::Vec3::zero), flag(false) {}
        GF_OBJ_HANDLE* handle;  // the summoner
        unsigned int id;        // its row of the summon table (BDAT 0x41)
        mm::Vec3 pos;
        bool flag;
    };
    // one enemy to pop (field names are not the original's)
    // one of the summon row's enemies (field names are not the original's)
    struct EnemyInfo {
        EnemyInfo() : posType(0), enemyId(0) {}
        bool isValid() const { return enemyId != 0 && posType < 3; }
        unsigned char posType;   // which of the row's PosA/PosB/PosC (its EnemyID column)
        unsigned short enemyId;  // the row's EnemyID
    };
    struct PopInfo {
        PopInfo() : actType(0), chestHeight(0.0f), pos(mm::Vec3::zero), popped(0) {}
        EnemyInfo enemy;
        unsigned char actType;   // its resource's ActType
        unsigned char pad_5[0x3];
        float chestHeight;       // its resource's ChestHeight, in metres
        mm::Vec3 pos;            // the row's position for it, in metres
        unsigned char popped;  // 1 once its enemy is created (updatePopEnemy)
        // 0x21..0x30: tail padding (Vector<PopInfo>::push_back/expand copy nothing past popped)
    };

    GfRelSmnEnemy()
        : m_popRadius(1.0f), m_limitRadius(5.0f), m_depopCond() {
        GfObjManager::addListener(this, OBJEVT(0));
    }
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    virtual ~GfRelSmnEnemy();  // slot 1
    void create(const CreateInfo& info);
    // 1.0.0's out-of-line dispose (3.0.1 inlines it everywhere)
    void dispose() {
        disposeEnemies(false);
        if (m_popInfos.size() != 0) {
            m_popInfos.destroy();
        }
        m_info = CreateInfo();
    }
    bool isValid() const { return m_info.handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && static_cast<int>(m_info.id) > 0; }
    unsigned int getEnemyNum() const;  // how many enemies it summoned
    gf::GF_OBJ_HANDLE* getEnemy(unsigned int index) const;  // one of them
    void disposeEnemies(bool fade);
    void update(float dt);
    void disposeWaitEnemies();
    void updatePopEnemy();
    void updateDepopEnemy();
    void validatePopPos();
    bool getPopPos(mm::Vec3& pos, const PopInfo& info) const;
    void removeEnemy(GF_OBJ_HANDLE* handle);

    // field names are not the original's
    CreateInfo m_info;                                                 // 0x10
    float m_popRadius;                                                 // 0x40
    float m_limitRadius;                                               // 0x44
    // 0x48: updateDepopEnemy destroys the enemies whose setup position it no longer matches (both distances set)
    gmk::DistHvCond m_depopCond;
    mm::mtl::Vector<PopInfo> m_popInfos;                               // 0x50
    mm::mtl::Vector<std::pair<PopInfo*, GF_OBJ_HANDLE*> > m_waitEnemies;  // 0x78: popped, waiting to appear
    mm::mtl::Vector<GF_OBJ_HANDLE*> m_enemies;                         // 0xA0
};
}  // namespace gf

#endif
