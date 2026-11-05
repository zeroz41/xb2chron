#ifndef CLASSES_ML_DEVFILEARCHIVER_H
#define CLASSES_ML_DEVFILEARCHIVER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/DevFileDictionary.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"

namespace ml { class DevFileArchiver; }
// MEDIA is unsigned: DevFileArchiver::getFileInfo zero-extends it to index m_medias (umaddl)
namespace ml { enum MEDIA : unsigned int; }

namespace ml {
// table 0x7100B76E78
class DevFileArchiver : public ::mm::mtl::PtrSingleton< ::ml::DevFileArchiver> {
public:
    // One file's entry in an archive's table (0x18 bytes; getFileInfo copies the dictionary value's entry). The
    // struct name is not the original's; what each word holds is not known yet (DevFileArchiveNx::rfOpen builds
    // one zeroed with -1 at 0x14, tests bit 0 at 0x10 and keeps the word at 0).
    struct FileEntry {
        FileEntry() : pad_0(0), pad_8(0), pad_C(0), pad_10(0), pad_14(-1) {}

        unsigned long pad_0;  // the file's offset in its archive (DevFileArchiveNx::rfOpen keeps it in pad_190)
        int pad_8;
        int pad_C;
        unsigned int pad_10;
        int pad_14;  // -1 until getFileInfo finds the file
    };
    // What getFileInfo fills (symbol-named): the media, the archive's name and the file's entry.
    struct FileInfoResult {
        // media 8 (one past the last), no name, an empty entry (DevFileArchiveNx::rfOpen's stores)
        FileInfoResult() : m_media(static_cast<MEDIA>(8)), m_archiveName(), m_entry() {}

        MEDIA m_media;                       // 0x0
        mm::mtl::FixStr<128> m_archiveName;  // 0x4: the archive's m_name84
        FileEntry m_entry;                   // 0x88
    };
    // One archive addArchive loads (new 0x1F0); the destructor's code is inlined into ~DevFileArchiver.
    // The struct and member names are not the original's: no symbol names them.
    struct Archive {
        ~Archive() {
            if (m_data != nullptr) {
                mtl::MemManager::deallocate(m_data, 0, false);
                m_data = nullptr;
            }
        }

        mm::mtl::FixStr<128> m_name0;    // 0x0
        mm::mtl::FixStr<128> m_name84;   // 0x84
        mm::mtl::FixStr<128> m_name108;  // 0x108
        DevFileDictionary<int, DevFileDicAllocator, -1, -2, true> m_dictionary;  // 0x190
        void* m_data;                    // 0x1E0: addArchive's MemManager::allocate'd copy of the archive table
        FileEntry* m_files;              // 0x1E8: indexed by the dictionary's value (getFileInfo)
    };
    // The archives of one MEDIA (the constructor numbers the 8 lists 0..7). Names not the original's.
    struct MediaArchives {
        // the constructor's first stores: 8 (one past the last list's MEDIA), not valid, empty
        MediaArchives() : m_media(static_cast<MEDIA>(8)), m_valid(false) {}

        MEDIA m_media;                                    // 0x0
        bool m_valid;                                     // 0x4
        mm::mtl::FixedVector<Archive*, 16> m_archives;    // 0x8
    };

    explicit DevFileArchiver(mtl::ALLOC_HANDLE handle);
    virtual ~DevFileArchiver();  // slot 0

    bool getFileInfo(MEDIA media, const char* path, FileInfoResult& result) const;
    // named by the symbols: adds the archive table data (size bytes) of a medium (DevFileTh::registArchive passes
    // its last two arguments swapped; the return type and parameter names are not known)
    void addArchive(MEDIA media, const void* data, unsigned long size, const char* root, const char* name);

    unsigned char pad_8[0x4];
    mtl::ALLOC_HANDLE m_handle;              // 0xC: the constructor's handle; addArchive allocates with it
    MediaArchives m_medias[8];               // 0x10
    DevFileDicAllocator m_dicAllocator;      // 0x490
};
}  // namespace ml

#endif
