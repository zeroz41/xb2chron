#ifndef FW_PARAMBUILDER_H
#define FW_PARAMBUILDER_H

#include "classes/fw/ParamList.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw {
// builds the param lists fw::ParamManager holds, one per index, from their binaries
class ParamBuilder {
public:
    // the list built from binary, which ParamManager keeps as index's (the xml's path names it)
    static mm::mtl::IntrusivePtr<ParamList> create(void* binary, unsigned int index, const char* name);
    // index's list released
    static void destroy(unsigned int index);
};
}  // namespace fw

#endif
