#ifndef CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCETEAMCONVERTER_H
#define CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCETEAMCONVERTER_H

#include "classes/gf/GfMenuMercenariesAdapter.h"
#include "classes/gf/GfMenuMercenariesAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5D1B0; the team GfMenuReference holds
class GfMenuMercenariesAdapter::ReferenceTeamConverter : public ::gf::GfMenuMercenariesAdapter::IConverter {
public:
    virtual ~ReferenceTeamConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getTeamId() { return GfMenuReference::getReferenceTeamID(); }  // slot 2
};
}  // namespace gf

#endif
