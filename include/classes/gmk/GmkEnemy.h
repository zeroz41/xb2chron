#ifndef CLASSES_GMK_GMKENEMY_H
#define CLASSES_GMK_GMKENEMY_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkEnemyInsts.h"
#include "classes/gmk/GmkEnemyWaveExtension.h"
#include "plugin/Bdat.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6D7F8
class GmkEnemy : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x710062CFB8 (8); create fills it
    class BdatInfo {
    public:
        // Vector<BdatInfo>::resize zeroes every field but byte 3, one store each
        BdatInfo() : m_targetPointName(0), m_smnGroups(0), m_dispR(0), m_dispH(0) {}
        // out of line (0x7100586774; defined in the unit, so the unused gmk is passed undefined); reads the row's "tagetpoint_name", "ene_disp_r" and "ene_disp_h"
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        // the field names are not the original's: the columns create reads into them
        unsigned short m_targetPointName;  // 0x0: "tagetpoint_name"
        unsigned char m_smnGroups;  // 0x2: GmkEnemyInsts::BdatInfo::fn_710058356C's summon group bits
        unsigned char pad_3;
        unsigned short m_dispR;  // 0x4: "ene_disp_r"
        unsigned short m_dispH;  // 0x6: "ene_disp_h"
    };
    class PopXformFinder;
    // what its gimmick data (m_createInfo.m_data) holds first: the radius its enemies walk around in (the struct and
    // field names are not the original's)
    struct Data {
        float m_randomWalkRadius;
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // whether pos lies within the random walk radius of its position (1.0.0 name)
    bool isPointInsideRandomWalk(const mm::Vec3& pos) const;
    virtual ~GmkEnemy();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    // its kind (getGmkType's; GmkManager::traverseGmkInst walks the enemies by it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0);

    GmkEnemyInsts m_insts;  // (the name is not the original's)
    // 0x1d0: GfQuestTarget::getIconTypeBattle passes its address as this to GmkEnemyWaveExtension's
    // getBindedGmkEnemyWave (the name is not the original's)
    GmkEnemyWaveExtension pad_1d0;
    // its game objects, as GmkManager::collectGameObjsUnbound<T> reads them inline (the names are not the
    // original's)
    unsigned int getGobInstNum() const { return m_insts.m_popInfo.getGobInstNum(); }
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const { return m_insts.getGobInst(index); }
    // its pop state, as LocatorBat_EnemySpeciesID::update reads it inline (the names are not the original's)
    bool isPopCondMatched() const { return m_insts.m_bdatInfo.isPopCondMatched(); }
    float getPopWait() const { return m_insts.m_popWait; }
    bool hasTypeGenus(unsigned char genus, bool flag) const { return m_insts.m_popInfo.hasTypeGenus(genus, flag); }
};
}  // namespace gmk

#endif
