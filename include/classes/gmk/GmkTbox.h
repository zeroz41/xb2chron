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
        // 2.0.0's symbols name them (update calls them with the gimmick's position)
        bool isPopCondMatched(const mm::Vec3& pos) const;
        bool isDepopCondMatched(const mm::Vec3& pos) const;
        unsigned short m_condition;  // the row's "Condition" (a GfGameCond id; 0: none)
        // the fields its create stores (names from the columns/flags it reads, not the original's)
        bool m_dig;                  // 0x2: "flag" bit "Digflg"
        unsigned char m_msgVisible;      // 0x3: "msgVisible"
        unsigned char m_msgdigVisible;   // 0x4: "msgdigVisible"
        bool m_category;             // 0x5: its RSC_ID row's "flag" bit "TBOX_category" (BDAT 0xAC)
        bool m_digPop;               // 0x6: "flag" bit "DigPopflg" (when the table has it)
        bool m_noponBarrel;          // 0x7: "flag" bit "NoponBarrel" (when the table has it)
        float m_visibleRadiusSq;      // 0x8: its RSC_ID row's "visible_Radius", squared
        float m_invisibleRadiusSq;    // 0xC: its RSC_ID row's "invisible_Radius", squared
    };
    GmkTbox() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    virtual ~GmkTbox();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    void setTargetable(bool targetable) const;
    // 2.0.0's symbols name them (GfFieldTbox::seqCheckFs calls successToAccess; update calls createGobInst)
    void successToAccess();
    void createGobInst();
    int getProgress() const;
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(9);
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
    unsigned char pad_50 = 1;
    unsigned char pad_51[0x3];
    // update counts pad_58 up by dt to pad_54 once the box is opened, then has the object destroyed
    float pad_54 = 0.0f;
    float pad_58 = 0.0f;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
