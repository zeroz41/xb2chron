#ifndef CLASSES_GF_GFMENUHANAADAPTER_REFERENCEINDEXCONVERTER_H
#define CLASSES_GF_GFMENUHANAADAPTER_REFERENCEINDEXCONVERTER_H

#include "classes/gf/GfMenuHanaAdapter.h"
#include "classes/gf/GfMenuHanaAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5C920; the blade GfMenuReference has at a reference index
class GfMenuHanaAdapter::ReferenceIndexConverter : public ::gf::GfMenuHanaAdapter::IConverter {
public:
    ReferenceIndexConverter(unsigned int index) : m_index(index) {}
    virtual ~ReferenceIndexConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getHanaId() { return GfMenuReference::getReferenceBladeID(m_index); }  // slot 2
    unsigned int m_index;  // GfMenuReference::getReferenceBladeID's
};
}  // namespace gf

#endif
