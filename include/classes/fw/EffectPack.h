#ifndef CLASSES_FW_EFFECTPACK_H
#define CLASSES_FW_EFFECTPACK_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "ml/StlCustomAllocator.h"
#include "mtl/MemManager.h"
#include <string>
#include <unordered_map>

namespace fw {
class EffectData;

// table 0x7100B41628; counted (gf::MapEff::destroy releases the one it keeps, asserting reference_object.h's
// `m_RefCount > 0`)
class EffectPack : public ::mm::mtl::ReferenceObject {
public:
    // the pack's effect resource (efb) by name, null when it has none
    void* searchEfb(const char* name) const;
    // files the pack's effects (each a fw::EffectData) by name, registers the pack with the effect system and
    // adds it to the EffectManager, which then holds the first reference
    EffectPack(mtl::ALLOC_HANDLE handle, void* data, unsigned int size, const char* name, bool flag);
    virtual ~EffectPack();  // slot 0
    // a pack made from a resource in memory (gf::MapEff::create passes the map's effect asset)
    static EffectPack* createFromMemory(void* data, unsigned int size, const char* name, bool flag);

    // one entry of the pack resource: its magic ('a' at 8) and the offset of the next entry from this one (0 for
    // none); the effect resources are entries named at 0x14, chained from the head (the names are not the
    // original's)
    struct ResEntry {
        void* pad_0;
        char m_magic;
        unsigned char pad_9[3];
        unsigned int m_next;
        unsigned int pad_10;
        char m_name[1];

        ResEntry* next() { return m_next != 0 ? reinterpret_cast<ResEntry*>(reinterpret_cast<char*>(this) + m_next) : nullptr; }
    };

    // the pack's effect data by name (the constructor files them, the destructor releases them; the names are not
    // the original's)
    typedef std::unordered_map<std::string, EffectData*, std::hash<std::string>, std::equal_to<std::string>,
                               ml::StlCustomAllocator<std::pair<const std::string, EffectData*> > >
        DataMap;

    unsigned char pad_c[0x4];
    void* m_data;            // the pack resource; the destructor frees it from the effect system
    DataMap m_datas;
    unsigned int m_size;     // the resource's size, as es_pack_regist takes it
    bool m_flag;             // the constructor's flag (the names are not the original's)
    unsigned char pad_55[0x3];
    // the name fw::EffectManager files the pack under (addPack/removePack key its pack map with it; createFromMemory
    // makes it "<name>+<data address>"; the field name is not the original's). sizeof(EffectPack) is 0xE0
    // (createFromMemory's allocation)
    mm::mtl::FixStr<128> m_name;
    unsigned char pad_dc[0x4];
};
}  // namespace fw

#endif
