#ifndef CLASSES_FW_SOUNDPACK_H
#define CLASSES_FW_SOUNDPACK_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/fw/SoundSsdBank.h"
#include "classes/fw/SoundSsdSource.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { enum SoundCategory : int; }
namespace fw { enum SoundPriority : int; }
namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// table 0x7100B42E80: a pack of sound effects, its waves registered in a SoundSsdBank of its own; counted as an
// mm::mtl::ReferenceObject (fw::SoundResource's destructor releases its pack with reference_object.h's inline
// release: its assertion, then the deleting destructor through the table)
class SoundPack : public ::mm::mtl::ReferenceObject {
public:
    // what create and createFromStream make a pack from (the names are not the original's; pad_8c and assetName
    // are not read). Inline constructor: fw::SoundResource::update holds its stores.
    struct SetupInfo {
        SetupInfo()
            : category(static_cast<SoundCategory>(3)), priority(static_cast<SoundPriority>(0)), assetName(nullptr),
              data(nullptr), size(0), maxSound(0x80) {}

        mm::mtl::FixStr<128> name;
        SoundCategory category;
        SoundPriority priority;
        unsigned char pad_8c[0x4];
        const char* assetName;  // fw::SoundResource::update's: its asset's name
        void* data;
        unsigned int size;
        unsigned int maxSound;  // the bank's (SoundSsdBank::create and setMaxSound)
    };

    // a registered source's ID and its name's hash (the names are not the original's)
    struct SourceId {
        SourceId(unsigned int id, unsigned int nameHash) : id(id), nameHash(nameHash) {}

        unsigned int id;
        unsigned int nameHash;
    };

    // the pack binary registSource reads: a header, then the entries from entryOffset (0x40 bytes each before
    // version 0x200, 0x60 from it); the names are not the original's
    struct BinaryHeader {
        unsigned int pad_0[2];
        unsigned int version;
        unsigned int entryNum;
        unsigned int entryOffset;
    };
    // the size of an entry before version 0x200
    static const unsigned long OldEntrySize = 0x40;
    struct BinaryEntry {
        unsigned int dataOffset;
        unsigned int dataSize;
        unsigned int nameHash;
        char name[0x20];
        SoundSsdBank::WaveParam param;
        short priority;
        unsigned short id;
        // from version 0x200 (zero before it)
        unsigned int pad_40[3];
        unsigned short pad_4c;
        unsigned char pad_4e[0x12];
    };

    static SoundPack* createFromStream(mm::mtl::IAllocator* allocator, const SetupInfo& info);
    static SoundPack* create(const SetupInfo& info);
    SoundPack(SoundCategory category, mm::mtl::IAllocator* allocator, const char* name, SoundPriority priority);
    virtual ~SoundPack();  // slot 0

    // registers a source per entry of the pack's binary
    void registSource(void* data, unsigned int size);
    mm::mtl::IntrusivePtr<SoundSsdSource> findSource(const char* name) const;
    mm::mtl::IntrusivePtr<SoundSsdSource> findSourceFromID(unsigned int id) const;

    // the names are not the original's
    SoundCategory m_category;
    mm::mtl::IAllocator* m_allocator;
    void* m_data;  // registSource's
    unsigned int m_size;  // registSource's
    mm::mtl::FixStr<256> m_name;
    unsigned int m_nameHash;  // mm::mtl::hashStrCrc of the name
    mm::mtl::FixStr<64> m_fileName;  // the name without folders and extension
    SoundPriority m_priority;
    SoundSsdBank* m_bank;
    mm::mtl::FixedVector<mm::mtl::IntrusivePtr<SoundSsdSource>, 256> m_sources;
    mm::mtl::FixedVector<SourceId, 256> m_sourceIds;  // m_sources' IDs, in the same order
};
}  // namespace fw

#endif
