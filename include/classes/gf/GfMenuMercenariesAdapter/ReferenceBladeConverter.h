#ifndef CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCEBLADECONVERTER_H
#define CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCEBLADECONVERTER_H

#include "classes/gf/GfMenuMercenariesAdapter.h"
#include "classes/gf/GfMenuMercenariesAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfDataMercenaries.h"

namespace gf {
// table 0x7100B5D1D8; the team of the blade at an index of GfMenuReference's (0 for none)
class GfMenuMercenariesAdapter::ReferenceBladeConverter : public ::gf::GfMenuMercenariesAdapter::IConverter {
public:
    ReferenceBladeConverter(unsigned int index) : m_index(index) {}
    virtual ~ReferenceBladeConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getTeamId() {  // slot 2
        unsigned int blade = GfMenuReference::getReferenceBladeID(m_index);
        if (blade == 0) {
            return 0;
        }
        return GfDataMercenaries::getTeamID(blade);
    }
    unsigned int m_index;  // GfMenuReference::getReferenceBladeID's
};
}  // namespace gf

#endif
