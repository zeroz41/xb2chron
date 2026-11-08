#ifndef CLASSES_GMK_GMKKIZUNATALK_H
#define CLASSES_GMK_GMKKIZUNATALK_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkKizunaTalkGob; }

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// table 0x7100B6DFD0
class GmkKizunaTalk : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // inline: TGmkList::initGmkBdatInfo has no call of it
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_conditionId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "ConditionID", row, 2);
            m_title = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Title", row, 2);
            m_evCondition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "EVCondition", row, 2);
        }
        bool isCondMatched() const;
        unsigned short m_conditionId;  // the row's "ConditionID" (a GfGameCond id; 0: none)
        unsigned short m_title;        // the row's "Title"
        unsigned short m_evCondition;  // the row's "EVCondition"
    };
    GmkKizunaTalk() {}
    virtual ~GmkKizunaTalk();  // slot 0
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // makes its object (a collection object from its sheet's row), shows it, makes it targetable and puts it at the
    // gimmick's position; sets local game flag 2 of its row to 1
    void createGfObjHandle();
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(36);
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    float m_popDistSq = 0.0f;  // create squares BDAT 0x7B's row 0 member 0x1E into it; update reads it (the name is not the original's)
    unsigned char pad_54 = 1;          // meaning not known
};
}  // namespace gmk

#endif
