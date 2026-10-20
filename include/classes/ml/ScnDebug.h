#ifndef CLASSES_ML_SCNDEBUG_H
#define CLASSES_ML_SCNDEBUG_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkEvent.h"

namespace ml { class Scn; }
namespace ml { enum SCNPRIO_CB : int; }

namespace ml {
// table 0x7100B77BA8
class ScnDebug : public ::ml::IWorkEvent, public ::ml::IScnRender {
public:
    virtual ~ScnDebug();  // slot 0
    virtual void cbRenderAfter(ml::Scn*, ml::SCNPRIO_CB);  // slot 8
};
}  // namespace ml

#endif
