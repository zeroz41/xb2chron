#ifndef CLASSES_GF_GFGAMESAVE_H
#define CLASSES_GF_GFGAMESAVE_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace gf {
// table 0x7100B55E50
class GfGameSave : public ::ml::IWorkEvent {
public:
    virtual ~GfGameSave();  // slot 0
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace gf

#endif
