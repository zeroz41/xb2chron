#ifndef CLASSES_ML_DEVFILEARCHIVER_H
#define CLASSES_ML_DEVFILEARCHIVER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/DevFileDictionary.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"

namespace ml { class DevFileArchiver; }
namespace ml { enum MEDIA : int; }

namespace ml {
// table 0x7100B76E78
class DevFileArchiver : public ::mm::mtl::PtrSingleton< ::ml::DevFileArchiver> {
public:
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
        unsigned char pad_1e8[0x8];
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

    unsigned char pad_8[0x4];
    mtl::ALLOC_HANDLE m_handle;              // 0xC: the constructor's handle; addArchive allocates with it
    MediaArchives m_medias[8];               // 0x10
    DevFileDicAllocator m_dicAllocator;      // 0x490
};
}  // namespace ml

#endif
