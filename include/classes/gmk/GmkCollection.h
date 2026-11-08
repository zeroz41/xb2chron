#ifndef CLASSES_GMK_GMKCOLLECTION_H
#define CLASSES_GMK_GMKCOLLECTION_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// table 0x7100B6C880
class GmkCollection : public ::gmk::AGmkBase {
public:
    // a gimmick row (its size: the element size of its Vector<BdatInfo>::resize)
    class BdatInfo {
    public:
        BdatInfo() {}  // user-provided: Vector<BdatInfo>::resize stores only the defaults (pads left)
        // its row (out of line: TGmkList::initGmkBdatInfo calls it); the column names are the original's, the field
        // names not
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatchedExceptDist() const;
        bool isPopCondMatched(const AGmkBase& gmk) const;
        unsigned short m_nameRadius = 10;     // 0x0: its "nameRadius" column
        unsigned char m_rarity = 0;           // 0x2: its "rarity" column
        unsigned short m_collectionTable = 0; // 0x4: its "CollectionTable" column (a row of BDAT 0x1E0)
        // the item it gives: it does not pop once the box holds GfItemUtil::getEnableStock of it (the field names
        // are not the original's)
        unsigned short m_itemId = 0;     // 0x6
        unsigned short m_condition = 0;  // 0x8: a GfGameCond id (0: none)
        TimeCond m_popTime;          // 0x10
        WeatherCond m_popWeather;    // 0x20
        float m_popDistSq = 0.0f;    // 0x30: BDAT 0x7B's row 1 member 0, squared
    };
    GmkCollection() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    virtual ~GmkCollection();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    // takes the point's icon down (GfFieldCollect::seqWaitDrop passes true once every item has dropped)
    void disposeIcon(bool flag);
    // 2.0.0's symbols name it. What it does: isValid() and its BdatInfo's CollectionTable (m_collectionTable) equals
    // the given BDAT 0x1E0 row (gf_field_locator's collection locator update passes its row)
    bool isSameTableID(unsigned short collectionId) const;
    // 2.0.0's symbols name it. What it does: true unless isGameTypeIra() holds and the row id is in 4401..4900, then
    // whether local flag (1, id + 51429) is set (GfGmkLocator::getPosNum calls it).
    bool isFound() const;
    // 2.0.0's symbols name it. What it does: while isValid(), its CollectionTable row's "categoryName" in BDAT 0x1E0,
    // else 0 (GfComBehaviorGmk::createMenuObj).
    unsigned int getCategoryName_fld_gmkname() const;
    bool isWaitRepop() const;
    void setTargetable(bool targetable);
    void seqUpdateRepopCounter(float dt);
    void seqUpdatePopDepop(float dt);
    void createGfObjHandle();
    void createIcon();
    void validateIconPos();
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    }
    static const gmk::GmkType TYPE = gmk::GmkType(0x1C);
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    unsigned int m_iconEffect = 0;  // an EffectManager handle (disposeIcon removes it; the name is not the original's)
    // BDAT 0x7B's row 1 member 0, squared (create stores it; the name is not the original's)
    float m_popDistSq = 0.0f;
    // the step update runs (seqUpdateRepopCounter is one; the name is not the original's)
    void (GmkCollection::*m_seq)(float dt) = nullptr;
    float m_repopCounter = 0.0f;  // seqUpdateRepopCounter counts it down (the name is not the original's)
    unsigned char pad_6c = 1;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
