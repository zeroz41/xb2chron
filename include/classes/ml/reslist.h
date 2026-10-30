#ifndef CLASSES_ML_RESLIST_H
#define CLASSES_ML_RESLIST_H

#include "classes/ml/_reslist_base.h"

namespace ml { class DevGraphCB; }
namespace ml { class GraphQue; }
namespace ml { class IDevFontInfo; }
namespace ml { class IThreadValue; }
namespace ml { class IWorkEvent; }
namespace ml { class ScnObj; }
namespace ml { class TJOB; }
namespace ml { class WorkObj; }

namespace ml {
// a template: 10 instances in the module
template <typename T0>
class reslist : public ::ml::_reslist_base< T0> {
public:
    virtual ~reslist() {}  // slot 0
};
}  // namespace ml

// after the template: DebDraw holds a reslist of its own
#include "classes/ml/DebDraw.h"

#endif
