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
    // true while a file read is busy
    bool isRead();
    void readCancel();
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    // sets FLAG_READ_ASYNC when async, else FLAG_READ_SYNC (the flag names are not the original's)
    void setup(bool async);

    enum {
        FLAG_READ_ASYNC = 1 << 2,
        FLAG_READ_SYNC = 1 << 3,
    };
    unsigned char pad_8[0x40];
    // 0x48: a bit per _wkSeamReadCall::m_readIdx, cleared when that stream is in (DrMdoCtlSeamRead::wait*Stream);
    // inside the block the constructor zeroes (the name is not the original's)
    unsigned short m_readWaitBits;
    unsigned char pad_4A[0x2];
    unsigned int m_flags;  // 0x4C (the name is not the original's)
    unsigned char pad_50[0x8];  // the constructor zeroes 0x8-0x58
};
}  // namespace ml

#endif
