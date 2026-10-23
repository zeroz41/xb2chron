#ifndef CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTERREFERENCEINDEX_H
#define CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTERREFERENCEINDEX_H

#include "classes/gf/GfMenuArtsAdapter.h"
#include "classes/gf/GfMenuArtsAdapter/IConverter.h"
#include "classes/gf/GfMenuArtsList.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5A070; as ListReferenceDriverConverter, the index being a GfMenuReferenceNumber's value
class GfMenuArtsAdapter::ListReferenceDriverConverterReferenceIndex : public ::gf::GfMenuArtsAdapter::IConverter {
public:
    ListReferenceDriverConverterReferenceIndex(GfMenuArtsList* list, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> index,
                                               unsigned int reference)
        : m_list(list), m_index(index), m_reference(reference) {
        m_list->addRef();
    }
    virtual ~ListReferenceDriverConverterReferenceIndex();  // slot 0
    virtual void getArtsInfo(MenuArtsInfo& info);  // slot 2
    virtual unsigned int getDriverId();  // slot 3
    GfMenuArtsList* m_list;  // referenced
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_index;  // its m_value: the index (-1: the selected one)
    unsigned int m_reference;  // GfMenuReference::getReferenceDriverID's index
};
}  // namespace gf

#endif
