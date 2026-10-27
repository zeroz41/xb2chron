#ifndef CLASSES_SSD_FILESTREAM_H
#define CLASSES_SSD_FILESTREAM_H

#include "classes/ssd/IoStreamBase.h"
#include "nn/fs.h"

namespace ssd { class TextRef; }

namespace ssd {
// table 0x7100B82120: a stream over an nn::fs file (D:/ssd/ssd51/ssd/sources/io/file_stream.cpp)
class FileStream : public ::ssd::IoStreamBase {
public:
    FileStream();

    static void Initialize();
    static void Finalize();

    // inline: StreamController's destructor has it inline (IsOpen, then Close, through the table)
    virtual ~FileStream() {
        if (IsOpen()) {
            Close();
        }
    }  // slot 0
    virtual bool IsOpen() const;  // slot 2
    virtual Result Open(const TextRef& path, OpenMode mode);  // slot 3
    virtual Result Close();  // slot 5
    virtual Result GetSize(unsigned long* fileSize) const;  // slot 6
    virtual Result Read(unsigned long size, void* buffer, unsigned long* readSize);  // slot 7
    virtual Result Write(unsigned long size, const void* buffer, unsigned long* writeSize);  // slot 8
    virtual Result Seek(SeekMode mode, unsigned long offset, unsigned long* position);  // slot 9
    virtual Result GetPosition(unsigned long* position) const;  // slot 10
    virtual Result Tell(unsigned long* position);  // slot 11
    virtual unsigned long CheckAccessSize(unsigned long size);  // slot 12

    void Clear();

    // the read position, the file's size (Open) and its handle (the names are not the original's)
    unsigned long position_;
    unsigned long size_;
    nn::fs::FileHandle handle_;
};
}  // namespace ssd

#endif
