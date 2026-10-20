#ifndef CLASSES_MM_MTL_LIST_H
#define CLASSES_MM_MTL_LIST_H

#include "classes/mm/mtl/_ReslistBase.h"

namespace fw { class SoundPack; }
namespace fw { class SoundSsdBank; }
namespace fw { class SoundSsdSource; }
namespace fw { class UpdatableObject; }
namespace ml { class DrLightObjGlobalIBL; }
namespace ssd { class SoundHandle; }

namespace mm { namespace mtl {
// a template: 9 instances in the module
template <typename T0>
class List : public ::mm::mtl::_ReslistBase< T0> {
public:
    virtual ~List();  // slot 0
};
}}  // namespace mm::mtl

#endif
