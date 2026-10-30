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
    void readCancel();
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    // sets FLAG_READ_ASYNC when async, else FLAG_READ_SYNC (the flag names are not the original's)
    void setup(bool async);

    enum {
        FLAG_READ_ASYNC = 1 << 2,
        FLAG_READ_SYNC = 1 << 3,
    };
    unsigned char pad_8[0x44];
    unsigned int m_flags;  // 0x4C (the name is not the original's)
};
}  // namespace ml

#endif
