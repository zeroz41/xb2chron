#ifndef CLASSES_ML_FILEHANDLETH_H
#define CLASSES_ML_FILEHANDLETH_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/MemManager.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace ml { class IWorkEvent; }
namespace ml { class DevFileParamTh; }

namespace ml {
// a file request of the file thread (DevFileTh::readFile returns one). Only the fields FileResTh::OnFileEvent reads
// are known; their names are not the original's
class FileHandleTh {
public:
    // hands over the read's data, clearing it (EventFileTh::moveFileData, FileResTh::OnFileEvent; the name is not the
    // original's)
    void* moveData() {
        void* data = m_data;
        m_data = nullptr;
        return data;
    }
    // its slot in DevFileTh::Impl's FixedObjectAllocator is given back through it (FixedObjectAllocator<FileHandleTh,
    // 640>::deallocate inlines it)
    ~FileHandleTh() { clear(); }
    // the data freed and the read's state cleared (DevFileTh::Impl::rfClose and the destructor inline the same code;
    // the name is not the original's)
    void clear() {
        releaseData();
        pad_1f4 = false;
        pad_1e0 = 0;
        if (pad_58 != nullptr) {
            pad_58 = nullptr;
        }
    }
    // the buffer a channel read fills and its size (DevFileNxTh::rfRead, DevFileArchiveNx::rfRead; the name is not
    // the original's)
    void setBuffer(void* data, int size) {
        m_size = size;
        m_data = data;
        pad_10 = size;
    }
    // where the read starts in the file and, unless a size is set, how much it reads; either one makes it a partial
    // read (pad_1f5). DevFileNxTh::rfRead passes its parameter's offset and size; DevFileTh::Impl::writeFile does
    // the same with its last argument and 0. The name is not the original's.
    void setRange(int offset, int size) {
        pad_14 = offset;
        if (m_size == 0) {
            m_size = size;
        }
        if (pad_14 > 0 || m_size > 0) {
            __atomic_store_n(&pad_1f5, true, __ATOMIC_SEQ_CST);
        }
    }
    // named by the symbols: sets a read request up from a parameter (DevFileTh::Impl::checkValidFile)
    void setup(const DevFileParamTh& param);
    // named by the symbols: sets a write request up (DevFileTh::Impl::writeFile)
    void initWriter(const char* path, void* data, int size, int, IWorkEvent* listener);
    // frees the read's data unless a caller's pointer takes it over (DevFileTh::Impl::releaseRequest, clear; the
    // name is not the original's)
    void releaseData() {
        if (m_allocType == 1) {
            if (m_data != nullptr && m_outData == nullptr) {
                if (mtl::MemManager::valid(m_allocHandle, true)) {
                    if (m_data != nullptr) {
                        mtl::MemManager::deallocate(m_data, 0, false);
                        m_data = nullptr;
                    }
                } else {
                    m_data = nullptr;
                }
            }
        } else if (m_allocType == 2) {
            if (m_data != nullptr && m_outData == nullptr) {
                if (m_allocator != nullptr) {
                    m_allocator->deallocate(m_data);
                }
                m_data = nullptr;
            }
        }
    }

    // 0x0: where the data comes from: 1 m_allocHandle's memory, 2 m_allocator (releaseData; the name is not the
    // original's)
    int m_allocType;
    unsigned char pad_4[0x4];
    void* m_data;  // the read's data (OnFileEvent takes it over and clears it)
    int pad_10;  // DevFileNxTh::rfRead stores the read's byte count
    int pad_14;  // DevFileTh::Impl::writeFile stores its last argument, 0 when negative
    int m_size;  // the data's size
    unsigned char pad_1c[0xC];
    int m_readSize;  // 0x28 (DevFileReaderTh::asyncUpdate clears it before each medium's read)
    // 0x2C: the memory the data comes from when m_allocType is 1 (releaseData tests it with MemManager::valid);
    // passed on in the read's end event (DevFileNxTh::tail; the name is not the original's)
    mtl::ALLOC_HANDLE m_allocHandle;
    // copied to FileResTh's m_allocator (FileResTh::release frees the data through it when set)
    mm::mtl::IAllocator* m_allocator;
    unsigned char pad_38[0x20];
    void* pad_58;  // cleared when set by DevFileTh::Impl::rfClose
    // 0x60: who hears the read's end (FileResTh::release clears it before canceling the read)
    IWorkEvent* m_listener;
    unsigned long pad_68;  // passed on in the read's end event (DevFileNxTh::tail)
    // 0x70, 0x78: where the read's end hands its data and size when set (DevFileNxTh::tail; the names are not the
    // original's)
    void** m_outData;
    int* m_outSize;
    unsigned char pad_80[0x14];
    // 0x94: the file's path (DevFileReaderTh::asyncUpdate passes it to PathUtil::getFilePtrFromPath); its length is
    // not known: it runs to the next known field
    char m_path[0x12C];
    unsigned long m_timeStamp;  // copied to FileResTh's m_timeStamp
    unsigned long m_extra;  // copied to FileResTh's m_extra
    unsigned char pad_1d0[0x4];
    // 0x1D4: the read channel it holds (DevFileNxTh::rfOpen/rfClose index their Impl's channels with it; the name is
    // not the original's)
    unsigned int m_channel;
    unsigned char pad_1d8[0x8];
    unsigned long pad_1e0;  // cleared by DevFileTh::Impl::rfClose

    int m_state;  // 0x1E8 (DevFileReaderTh::asyncUpdate: 2 read, 4 failed or canceled)
    unsigned char pad_1ec[0x8];
    bool pad_1f4;  // cleared by DevFileTh::Impl::rfClose
    bool pad_1f5;  // stored atomically by DevFileTh::Impl::writeFile when pad_14 or m_size is positive
    unsigned char pad_1f6[0x3];
    bool pad_1f9;  // stored atomically by DevFileTh::Impl::writeFile when its last argument is negative
    unsigned char pad_1fa[0x2];
    // 0x1FC: read atomically; DevFileTh::Impl::rfClose closes the request through its archive accessors when set,
    // through its plain accessors when not
    bool pad_1fc;
    bool m_canceled;  // 0x1FD (stored atomically when a canceled read ends)
    bool m_failed;    // 0x1FE (stored atomically when no medium could read the file)
    bool m_done;      // 0x1FF (stored atomically when a medium read the file)
    bool pad_200;  // stored atomically (DevFileNxTh::rfRead clears it with the three before it)
    // 0x210 bytes: FixedObjectAllocator<FileHandleTh, 640>::deallocate divides a slot's offset by 0x210
    unsigned char pad_201[0xF];
};
}  // namespace ml

#endif
