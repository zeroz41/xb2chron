#ifndef CLASSES_LAYER_LAYERSHDMANAGER_H
#define CLASSES_LAYER_LAYERSHDMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace layer {
// table 0x7100B80360
class LayerShdManager : public ::ml::IWorkEvent {
public:
    virtual ~LayerShdManager();  // slot 0
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 7
    virtual void initColor(unsigned int);  // slot 8
};
}  // namespace layer

#endif
