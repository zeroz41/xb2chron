#ifndef CLASSES_FW_SOUNDRESSOURCEMANAGER_H
#define CLASSES_FW_SOUNDRESSOURCEMANAGER_H

#include "anm/Array.h"
#include "anm/StringPtr.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Map.h"
#include "mm/mtl/Vector.h"

namespace fw { class SoundResSourceManager; }
namespace fw { enum SoundCategory : int; }
namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// what a sound source plays: a pack's name and the sound's number in it (SoundResSourceManager::playSe finds the pack
// and plays the number; the field names are not the original's)
struct ResSoundData {
    const char* m_packName;
    unsigned int m_id;
};

// the head every sound source of a binary starts with: its name and its kind (0 plays one ResSoundData, 1 picks one
// by the variables of a SoundVariableTable: SoundResSourceManager::playSe; the field names are not the original's)
struct ResSoundSourceBase {
    anm::StringPtr m_name;
    int m_type;
};

// a source of kind 0: one sound (the name is not the original's)
struct ResSimpleSoundSource : ResSoundSourceBase {
    ResSoundData m_data;
};

// one choice of a ResComplexSoundSource: its sound and, per variable, the value it needs (negative: any value;
// findComplexIndex; the names are not the original's)
struct ResComplexSoundEntry {
    ResSoundData m_data;
    anm::Array<int> m_values;
};

// a source of kind 1: the variables it reads, by name, and its choices (the field names are not the original's)
struct ResComplexSoundSource : ResSoundSourceBase {
    anm::Array<const char*> m_variables;
    anm::Array<ResComplexSoundEntry> m_entries;
};

// a sound source binary's root ("SDSB", version 2: SoundResSourceImporter::importBinary): its sources of both kinds
// (the field names are not the original's)
struct ResSoundSource {
    anm::Array<ResSimpleSoundSource> m_simples;
    anm::Array<ResComplexSoundSource> m_complexes;
};

// a sound trigger binary's root ("SDTB", version 1: SoundResTriggerImporter::importBinary); its layout is not read here
struct ResSoundTrigger;

// a sound binary's root as bin::BinaryResolver resolves it: its version, its magic and the resource (both importers
// check the magic with a 4-byte compare and then the version; the names are not the original's)
struct ResSoundRoot {
    unsigned int m_version;
    char m_magic[4];
    const void* m_resource;
};

struct SoundResSourceImporter {
    static const ResSoundSource* importBinary(void* binary);
};

struct SoundResTriggerImporter {
    static const ResSoundTrigger* importBinary(void* binary);
};

// variables by name, which a ResComplexSoundSource's choices are picked by
class SoundVariableTable {
public:
    SoundVariableTable();
    ~SoundVariableTable();
    void setVariable(const char* name, int value);
    bool getVariable(const char* name, int* value) const;

    mm::mtl::Map<mm::mtl::FixStr<64>, int> m_variables;  // the name is not the original's
};

// the choice of source whose values the table's variables meet, -1 for none (or a variable the table lacks)
unsigned int findComplexIndex(const SoundVariableTable& table, const ResComplexSoundSource* source);

// table 0x7100B43440
class SoundResSourceManager : public ::mm::mtl::PtrSingleton< ::fw::SoundResSourceManager> {
public:
    // what a playSe callback may change before the sound plays: a factor on its volume (the name is not the
    // original's: GfComBehaviorPc::callbackSound stores it)
    struct CustomInfo {
        CustomInfo() : m_volume(1.0f) {}
        float m_volume;
    };

    SoundResSourceManager();
    virtual ~SoundResSourceManager();  // slot 0

    static void clearAll();
    static void beginPush(unsigned int count, mm::mtl::IAllocator* allocator);
    static void endPush();
    static void pushResource(const ResSoundSource* resource);
    static unsigned int playSe(const char* name, float volume, const SoundVariableTable& variables,
                               SoundCategory category,
                               const mm::mtl::Delegate<void(const ResSoundData&, CustomInfo*)>& callback);
    static void stopSe(unsigned int handle, float fade);

    // every source of the pushed resources, by name (the names are not the original's)
    mm::mtl::Map<anm::StringPtr, const ResSoundSourceBase*> m_sources;
    mm::mtl::Vector<const ResSoundSource*> m_resources;
    bool pad_48;  // cleared by the constructor; nothing in this unit reads it
};
}  // namespace fw

#endif
