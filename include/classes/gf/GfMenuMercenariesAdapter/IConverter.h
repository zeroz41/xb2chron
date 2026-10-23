#ifndef CLASSES_GF_GFMENUMERCENARIESADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUMERCENARIESADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuMercenariesAdapter.h"

namespace gf {
// table none (its derived classes'): where a mercenaries adapter's update takes its team from
class GfMenuMercenariesAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getTeamId() = 0;  // slot 2
};
}  // namespace gf

#endif
