#ifndef CLASSES_FW_RESOURCEOBJECT_H
#define CLASSES_FW_RESOURCEOBJECT_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "classes/fw/ResourceManager.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// the priority a resource loads with (fw::SoundResource::request takes one; GfEvtSe::createSe passes 10)
enum LOAD_PRIO : int;

// table 0x7100B42B18; counted: its constructor zeroes the count at 8 before it stores its table (the base's inline
// constructor), SoundResource::request adds a reference through it, and GfEvtSe releases one with
// reference_object.h's assertion and slot 1
class ResourceObject : public ::mm::mtl::ReferenceObject {
public:
    // registers it with ResourceManager (addResource); the parameter names are not the original's
    ResourceObject(unsigned int type, mm::mtl::IAllocator* allocator, LOAD_PRIO prio, int arg);
    virtual ~ResourceObject();  // slot 0
    virtual void update() = 0;  // slot 2
    // whether it has loaded (GfEvtSe::isLoadedSe waits for every SE's)
    virtual bool valid() const = 0;  // slot 3
    // the path a request asked for, and its hash (inline: LocalizeResource's and RenderResource's requests; the
    // name is not the original's)
    void setPath(const char* path) {
        m_path = path;
        m_hash = ResourceManager::getHash(path);
    }

    // the field names are not the original's
    unsigned int m_type;  // the constructor's: ResourceManager::searchResource's first (1: a RenderResource)
    unsigned char pad_10[0x8];
    mm::mtl::IAllocator* m_allocator;  // the constructor's
    unsigned int m_hash;  // ResourceManager::getHash of the path (the requests set it)
    unsigned char pad_24[0x4];
    LOAD_PRIO m_prio;  // the constructor's
    mm::mtl::FixStr<128> m_path;  // the requested path (the requests set it)
};
}  // namespace fw

#endif
