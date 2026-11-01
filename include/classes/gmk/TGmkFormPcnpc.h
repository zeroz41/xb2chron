#ifndef CLASSES_GMK_TGMKFORMPCNPC_H
#define CLASSES_GMK_TGMKFORMPCNPC_H

#include "classes/gmk/AGmkBase.h"

namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module
template <gmk::GmkType T0>
class TGmkFormPcnpc : public ::gmk::AGmkBase {
public:
    // its row of the list's BDAT table: nothing of it is kept (Vector<BdatInfo>::resize allocates a byte an element)
    class BdatInfo {};
    // what m_createInfo.m_data points at (GmkForm::create<T, U> reads a position and rotation from it; the struct and
    // field names are not the original's)
    struct Data {
        float m_posX;
        float m_posY;
        float m_posZ;
        float m_rotY;
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    TGmkFormPcnpc() : pad_48(nullptr) {}  // inline: resize/extend construct in place with these stores
    virtual ~TGmkFormPcnpc() { dispose(); }  // slot 0
    virtual gmk::GmkType getGmkType() const { return T0; }  // slot 2
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const& info) { AGmkBase::create(info); }  // slot 4
    virtual void dispose() { AGmkBase::dispose(); }  // slot 5
    virtual void debugUpdateMmf() {}  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = T0;
    // an 8-byte field the constructor clears (Vector<T>::resize stores 0 at 0x48); meaning unknown
    void* pad_48;
};
}  // namespace gmk

#endif
