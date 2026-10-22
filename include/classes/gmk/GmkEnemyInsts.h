#ifndef CLASSES_GMK_GMKENEMYINSTS_H
#define CLASSES_GMK_GMKENEMYINSTS_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
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
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const;  // the handle of one of them
    unsigned char pad_0[0x98];
    PopInfo m_popInfo;  // (the name is not the original's)
};
}  // namespace gmk

#endif
