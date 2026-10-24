#ifndef CLASSES_ML_SCNCAMMAN_H
#define CLASSES_ML_SCNCAMMAN_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class WinView; }

namespace ml {
// table 0x7100B77B58
class ScnCamMan : public ::ml::IWorkEvent {
public:
    virtual ~ScnCamMan();  // slot 0
    void setView(WinView* view, int index);
};
}  // namespace ml

#endif
