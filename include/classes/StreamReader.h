#ifndef CLASSES_STREAMREADER_H
#define CLASSES_STREAMREADER_H

#include "nn/fs.h"

// table 0x7100B71B18; the stream reader the movie extractor reads the file through (nn::fs)
class StreamReader {
public:
    virtual ~StreamReader();  // slot 0
    virtual bool Open(char const*, void**);  // slot 2
    virtual unsigned long ReadAt(void*, long, void*, unsigned long);  // slot 3
    virtual bool Close(void*);  // slot 4
    virtual void GetSize(void*, long*);  // slot 5

    nn::fs::FileHandle* m_fileHandle;  // the name is not the original's
    long m_fileSize;  // the name is not the original's
};

#endif
