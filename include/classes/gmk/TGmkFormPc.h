#ifndef CLASSES_GMK_TGMKFORMPC_H
#define CLASSES_GMK_TGMKFORMPC_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/IGmkList.h"

namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module
template <gmk::GmkType T0, typename T1>
class TGmkFormPc : public ::gmk::AGmkBase {
public:
    // its row of the list's BDAT table: nothing of it is kept (Vector<BdatInfo>::resize allocates a byte an element)
    class BdatInfo {};
    // what m_createInfo.m_data points at (GmkForm::create<T, U> reads it: the first position and rotation, then the
    // bound TGmkFormPcnpc list's elements m_npcFirst..m_npcLast; the struct and field names are not the original's)
    struct Data {
        float m_posX;
        float m_posY;
        float m_posZ;
        float m_rotY;
        unsigned int m_npcFirst;
        unsigned int m_npcLast;
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    TGmkFormPc() : pad_48(nullptr) {}  // inline: resize/extend construct in place with these stores
    virtual ~TGmkFormPc() { dispose(); }  // slot 0
    virtual gmk::GmkType getGmkType() const { return T0; }  // slot 2
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const& info) { AGmkBase::create(info); }  // slot 4
    virtual void dispose() { AGmkBase::dispose(); }  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf() {}  // slot 10
    // the list of its bound TGmkFormPcnpc kind in the gimmick set that made its list (the set's own m_gmkLists
    // entry of T1's type; GmkSet::createGmkLists passes the set as the list's CreateInfo::m_param)
    virtual IGmkList* getBindedFormPcnpcList() const {  // slot 11
        return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[T1::TYPE];
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = T0;
    // an 8-byte field the constructor clears (Vector<T>::resize stores 0 at 0x48); meaning unknown
    void* pad_48;
};
}  // namespace gmk

#endif
