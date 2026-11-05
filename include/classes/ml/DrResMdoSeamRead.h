#ifndef CLASSES_ML_DRRESMDOSEAMREAD_H
#define CLASSES_ML_DRRESMDOSEAMREAD_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }
namespace ml { class DrResMdoSeamMemObj; }
namespace ml { class FileHandleTh; }

namespace ml {
// table 0x7100B7DA28
class DrResMdoSeamRead : public ::ml::IWorkEvent {
public:
    DrResMdoSeamRead();
    virtual ~DrResMdoSeamRead();  // slot 0
    // closes (opened) or cancels (read) every handle and clears the read bits
    void release();
    // opens a handle per slot on m_path for the async mode (the name is the original's)
    void setOpenInit();
    // takes the file and the wanted mode, switches the mode once no read is busy, opens or releases the handles
    // (the parameter names are not the original's)
    void update(const char* path, bool async);
    // true while a file read is busy
    bool isRead();
    void readCancel();
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    // sets FLAG_READ_ASYNC when async, else FLAG_READ_SYNC (the flag names are not the original's)
    void setup(bool async);
    // starts reading size bytes at ofs into obj; idx gets the read's bit in m_readWaitBits (the parameter names are
    // not the original's)
    bool read(int& idx, unsigned int ofs, unsigned int size, DrResMdoSeamMemObj* obj);
    int getReadMax();
    // the first slot with no read waiting whose handle is free, -1 if none
    int getFileHandleNum();

    enum {
        FLAG_OPEN = 1 << 0,  // setOpenInit opened every handle
        FLAG_READ_FILE = 1 << 1,  // the handles come from DevFileTh::readFile (release cancels them)
        FLAG_READ_ASYNC = 1 << 2,
        FLAG_READ_SYNC = 1 << 3,
        FLAG_MODE_CHANGE = 1 << 4,  // update switches the mode once no read is busy
        FLAG_WANT_ASYNC = 1 << 5,
        FLAG_WANT_SYNC = 1 << 6,
        FLAG_MODE_WAIT = 1 << 7,  // update saw no read busy once
        FLAG_OPEN_ERR = 1 << 8,  // setOpenInit could not open a handle
    };
    // 0x8: a file handle per read slot (rfOpen's in the async mode, readFile's in the sync mode; the name is not the
    // original's)
    FileHandleTh* m_handles[8];
    // 0x48: a bit per _wkSeamReadCall::m_readIdx, cleared when that stream is in (DrMdoCtlSeamRead::wait*Stream);
    // inside the block the constructor zeroes (the name is not the original's)
    unsigned short m_readWaitBits;
    // 0x4A: a bit per _wkSeamReadCall::m_readIdx whose read has finished (DrMdoCtlSeamRead::updateReadList tests
    // it; the name is not the original's)
    unsigned short m_readDoneBits;
    unsigned int m_flags;  // 0x4C (the name is not the original's)
    const char* m_path;  // 0x50: the file update was given (the constructor zeroes 0x8-0x58; name inferred)
};
}  // namespace ml

#endif
