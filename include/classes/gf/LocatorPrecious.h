#ifndef CLASSES_GF_LOCATORPRECIOUS_H
#define CLASSES_GF_LOCATORPRECIOUS_H

#include "classes/gf/AFieldLocator.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gmk/GmkAcc.h"

namespace gmk { class AGmkBase; }

namespace gf {
// a base of gf::LocatorPrecious no evidence names yet
class TUnk_B51CF0 {
public:
    virtual void onTraverse(gmk::AGmkBase const&) = 0;
    // GmkManager::traverseGmkInst calls its F with each gimmick (LocatorPrecious::create passes the locator, the
    // call goes through this base's slot 0; inline; the name is not the original's)
    void operator()(gmk::AGmkBase const& gmk) { onTraverse(gmk); }
};
// table 0x7100B51CA0; base at 0x18 unknown (TUnk_B51CF0)
class LocatorPrecious : public ::gf::AFieldLocator, public TUnk_B51CF0 {
public:
    virtual ~LocatorPrecious() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posList.size();
    }
    virtual const mm::Vec3* getPos(unsigned int index) const {  // slot 4
        return &m_posList[index];
    }
    virtual void update();  // slot 6
    virtual void onTraverse(gmk::AGmkBase const&);  // slot 7
    void create(QuestID questId, unsigned short preciousId);
    // the destructor's clearing; 1.0.0's symbols name it dispose() (3.0.1 inlines it)
    void dispose() {
        m_posList.clear();
        m_accs.clear();
        m_preciousId = 0;
    }

    unsigned short m_preciousId;
    mm::mtl::FixedVector<gmk::GmkAcc, 16> m_accs;
    mm::mtl::FixedVector<mm::Vec3, 16> m_posList;
};
}  // namespace gf

#endif
