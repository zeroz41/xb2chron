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
    static const gmk::GmkType TYPE = gmk::GmkType(0x1C);
    unsigned char pad_48[0x25];  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
