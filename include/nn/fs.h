#ifndef NN_FS_H
#define NN_FS_H

#include "nn/result.h"

// NintendoSDK's nn::fs, as far as the module imports it
namespace nn { namespace fs {

struct FileHandle {
    void* handle;
};

enum OpenMode {
    OpenMode_Read = 1,
};

Result OpenFile(FileHandle* handle, const char* path, int mode);
void CloseFile(FileHandle handle);
Result GetFileSize(long* size, FileHandle handle);
Result ReadFile(unsigned long* readSize, FileHandle handle, long offset, void* buffer, unsigned long size);

}}  // namespace nn::fs

#endif
