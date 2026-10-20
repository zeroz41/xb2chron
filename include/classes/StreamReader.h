#ifndef CLASSES_STREAMREADER_H
#define CLASSES_STREAMREADER_H

// table 0x7100B71B18
class StreamReader {
public:
    virtual ~StreamReader();  // slot 0
    virtual void Open(char const*, void**);  // slot 2
    virtual void ReadAt(void*, long, void*, unsigned long);  // slot 3
    virtual void Close(void*);  // slot 4
    virtual void GetSize(void*, long*);  // slot 5
};

#endif
