#ifndef CLASSES_GMK_GMKTBOX_H
#define CLASSES_GMK_GMKTBOX_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkTboxGob; }

namespace gmk {
// table 0x7100B6C3B0
class GmkTbox : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x71005DFFBC (zero-filled)
    class BdatInfo {
    public:
        // out of line: initGmkBdatInfo calls it with the table itself (symbol 0x7100592E90)
        void create(unsigned char* fp, int row, const AGmkBase& gmk);
        bool isPopCondMatchedExceptDist() const;
        unsigned short m_condition = 0;  // the row's "Condition" (a GfGameCond id; 0: none)
        // the fields its create stores (names from the columns/flags it reads, not the original's)
        bool m_dig = false;                  // 0x2: "flag" bit "Digflg"
        unsigned char m_msgVisible = 0;      // 0x3: "msgVisible"
        unsigned char m_msgdigVisible = 0;   // 0x4: "msgdigVisible"
        bool m_category = false;             // 0x5: its RSC_ID row's "flag" bit "TBOX_category" (BDAT 0xAC)
        bool m_digPop = false;               // 0x6: "flag" bit "DigPopflg" (when the table has it)
        bool m_noponBarrel = false;          // 0x7: "flag" bit "NoponBarrel" (when the table has it)
        float m_visibleRadiusSq = 0.0f;      // 0x8: its RSC_ID row's "visible_Radius", squared
        float m_invisibleRadiusSq = 0.0f;    // 0xC: its RSC_ID row's "invisible_Radius", squared
    };
    virtual ~GmkTbox();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    void setTargetable(bool targetable) const;
    int getProgress() const;
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_bdatInfo);
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(9);
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;
    unsigned char pad_50[0x10];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
