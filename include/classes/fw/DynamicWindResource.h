#ifndef CLASSES_FW_DYNAMICWINDRESOURCE_H
#define CLASSES_FW_DYNAMICWINDRESOURCE_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "wnd/ResWind.h"

namespace fw {
// table 0x7100B43480; counted (its constructor clears the count at 8): a wind resource made at run time
// (WindFactory::createWindResource) rather than loaded
class DynamicWindResource : public mm::mtl::ReferenceObject {
public:
    DynamicWindResource();
    virtual ~DynamicWindResource();  // slot 0

    wnd::ResWind m_resWind;  // createWindResource sets its box; no area winds
};
}  // namespace fw

#endif
