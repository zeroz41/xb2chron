#ifndef CLASSES_GMK_GMKROUTEDFOOTPRINTPOINT_H
#define CLASSES_GMK_GMKROUTEDFOOTPRINTPOINT_H

#include "classes/gmk/AGmkBase.h"
#include "mm/Vec3NA.h"
#include "plugin/Bdat.h"

namespace gmk {
// table 0x7100B6D2A0
class GmkRoutedFootPrintPoint : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {
    public:
        // inline and empty: initGmkBdatInfo reads the table pointer (getBindedBdatFp) and stores nothing
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {}
    };
    GmkRoutedFootPrintPoint() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    virtual ~GmkRoutedFootPrintPoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x37);
    // its data: where it is (updateConcrete measures the interest position's distance from it,
    // GmkRoutedFootPrint::debugDrawRoute draws its route through it; the name is not the original's)
    struct Data {
        mm::Vec3NA m_pos;  // 0x0 (GmkRoutedFootPrint::debugDrawRoute's copies of it are not 8-byte aligned loads)
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // 2.0.0's symbols name the next two (GmkRoutedFootPrint::update calls updateConcrete with one of its effects)
    void updateConcrete(void* effect, float dt);
    void applyEffectParam(bool) const;
    float pad_48 = 900.0f;
    float pad_4c = 100.0f;
    unsigned int m_effectHandle = 0;  // dispose kills it (EffectManager::dead; the name is not the original's)
    unsigned char pad_54 = 1;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
