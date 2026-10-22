#ifndef CLASSES_FW_EFFECTDATA_H
#define CLASSES_FW_EFFECTDATA_H

#include "mm/mtl/FixStr.h"
#include "classes/mm/mtl/ReferenceObject.h"

namespace fw {
// the head of an effect resource as createFromMemory reads it
struct EffectResHeader {
    unsigned int pad_0;
    unsigned int pad_4_bits : 20;
    unsigned int m_version : 12;  // createFromMemory takes only resources where it is 0
};

// table 0x7100B41370; an effect resource kept in memory, counted (createFromMemory adds the first reference)
class EffectData : public mm::mtl::ReferenceObject {
public:
    EffectData(void* data, const char* name, bool unregistered);
    virtual ~EffectData();  // slot 0
    // an effect resource for `data` (`size` bytes) named by `path`; an unregistered one is not registered with
    // the effect system nor added to the EffectManager. Null for data the system does not take.
    static EffectData* createFromMemory(void* data, unsigned int size, const char* path, bool unregistered);
    void* getHandle() const;
    const char* getName() const;

    void* m_handle;                 // the data; the destructor frees it from the effect system
    mm::mtl::FixStr<128> m_name;    // getName's: the path as the file system takes it
    bool m_unregistered;            // createFromMemory's: neither registered nor added to the EffectManager
};
}  // namespace fw

#endif
