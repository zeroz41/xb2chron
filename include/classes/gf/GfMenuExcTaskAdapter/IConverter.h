#ifndef CLASSES_GF_GFMENUEXCTASKADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUEXCTASKADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuExcTaskAdapter.h"

namespace gf {
// table none (its derived classes'): where an exchange task adapter's update takes its id from
class GfMenuExcTaskAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual void getTaskID(unsigned int& taskId) = 0;  // slot 2; leaves it as it is when there is none
    virtual void fromList() = 0;  // slot 3
};
}  // namespace gf

#endif
