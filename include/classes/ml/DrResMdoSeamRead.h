#ifndef CLASSES_ML_DRRESMDOSEAMREAD_H
#define CLASSES_ML_DRRESMDOSEAMREAD_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace ml {
// table 0x7100B7DA28
class DrResMdoSeamRead : public ::ml::IWorkEvent {
public:
    virtual ~DrResMdoSeamRead();  // slot 0
    void release();
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace ml

#endif
