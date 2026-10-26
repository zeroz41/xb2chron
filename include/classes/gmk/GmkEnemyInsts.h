#ifndef CLASSES_GMK_GMKENEMYINSTS_H
#define CLASSES_GMK_GMKENEMYINSTS_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// what GmkEnemyInsts::reqForcePopGobInst is asked to pop (layout not proven yet)
struct ForcePopEnemyInfo;

// a class with no table: an enemy gimmick's objects (GmkEnemy's at 0x48, GmkRoutedEnemy's at 0x50) and how they
// pop (its PopInfo at 0x98)
class GmkEnemyInsts {
public:
    class PopInfo {
    public:
        class PopEnemyInfo;
        unsigned int getGobInstNum() const;  // how many objects pop
        unsigned char pad_0[0x8];  // fields: size unknown
    };
    // the gimmick's row as it pops (GmkEnemy's at 0x80)
    class BdatInfo {
    public:
        // whether the row's pop conditions hold for a summon (GfSmnEnemyManager::execAbsSummon asks before popping)
        bool isPopCondMatchedOfSmn() const;
        unsigned char pad_0[0x3];
        // the summon groups the gimmick answers, one bit each (execAbsSummon tests its info's bit; clearSmnEnemies
        // destroys a GmkEnemy's object when any is set); the name is not the original's
        unsigned char m_smnGroups;
        unsigned char pad_4[0x5c];  // fields: size from PopInfo's offset
    };
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const;  // the handle of one of them
    // pops the gimmick's objects now (GfSmnEnemyManager::execAbsSummon)
    void reqForcePopGobInst(const ForcePopEnemyInfo& info) const;
    unsigned char pad_0[0x1c];
    // the distances its objects pop within and depop beyond (GfRelSmnEnemy::create squares them; the names are not
    // the original's)
    float m_popDist;
    float m_depopDist;
    unsigned char pad_24[0x14];
    BdatInfo m_bdatInfo;  // 0x38 (the name is not the original's)
    PopInfo m_popInfo;  // (the name is not the original's)
};
}  // namespace gmk

#endif
