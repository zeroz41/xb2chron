#ifndef CLASSES_GF_GFMENUEXCTASKADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUEXCTASKADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuExcTaskAdapter.h"

namespace gf {
// table 0x7100B5BD00
class GfMenuExcTaskAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getTaskID(unsigned int&);  // slot 2
    virtual void fromList();  // slot 3
};
}  // namespace gf

#endif
