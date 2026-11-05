#ifndef NN_FS_H
#define NN_FS_H

#include "nn/account.h"
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
// reads size bytes at offset, failing unless all of them come (ml::detail::FileLoader::readFile)
Result ReadFile(FileHandle handle, long offset, void* buffer, unsigned long size);

// the file system's allocator hooks (ml::DeviceNx::initializeSDK hands it device_detail::allocateFile and
// deallocateFile)
void SetAllocator(void* (*allocate)(unsigned long), void (*deallocate)(void*, unsigned long));

enum DirectoryEntryType {
    DirectoryEntryType_Directory = 0,
    DirectoryEntryType_File = 1,
};
// whether path names a file or a directory (ml::DevFileJobValidNxTh::asyncUpdate)
Result GetEntryType(DirectoryEntryType* type, const char* path);

// deletes the file at path (ml::DevFileNxTh::deleteFileBlock)
Result DeleteFile(const char* path);

// commits a mounted save data's writes (DevFileTh::flushSave passes "save")
Result CommitSaveData(const char* name);

// the save data of a user: whether it exists, its creation, its mount under `name` (ml::DevFileNxTh::initializeSave
// mounts "save")
bool IsSaveDataExisting(const account::Uid& uid);
Result EnsureSaveData(const account::Uid& uid);
Result MountSaveData(const char* name, const account::Uid& uid);
// releases the mount `name` (ml::DevFileNxTh::finalizeSDK: "save", "rom", "aoc%d")
void Unmount(const char* name);

// the results of a lack of space (module 2, descriptions 30 to 45): EnsureSaveData's failure initializeSave gives
// up on (the SDK's name for the range)
struct ResultUsableSpaceNotEnough {
    static bool Includes(Result result) {
        return (result.m_value & 0x1FF) == 2 && ((result.m_value >> 9) & 0x1FFF) - 30 < 16;
    }
};
}}  // namespace nn::fs

#endif
