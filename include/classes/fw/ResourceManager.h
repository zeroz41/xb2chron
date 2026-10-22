#ifndef CLASSES_FW_RESOURCEMANAGER_H
#define CLASSES_FW_RESOURCEMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "mtl/AllocHandle.h"

namespace fw { class ResourceObject; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw { class UpdateInfo; }
namespace mm { namespace mtl { class ReferenceObject; } }

namespace fw {
// a resource's type (fw::SoundResource's are 5: it asks searchResource for them and hands its asset to addSafeObject
// as one)
enum eResourceType : int;
}  // namespace fw

namespace fw {
// a base of fw::ResourceManager no evidence names yet
class TUnk_B42AD8 {
public:
    virtual ~TUnk_B42AD8();
};
// table 0x7100B42A80; base at 0x10 unknown (TUnk_B42AD8)
class ResourceManager : public ::fw::ManagerObject, public TUnk_B42AD8 {
public:
    virtual ~ResourceManager();  // slot 0
    virtual void enterFinalizeApplet();  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 8
    // the memory resources are made in (Framework::getMemHandle's)
    static mtl::ALLOC_HANDLE getMemSYS();
    static unsigned int getHash(const char* path);  // a path's hash (the resources' m_hash)
    // the loaded resource of a type and path, none (RenderResource::request asks for type 1)
    ResourceObject* searchResource(unsigned int type, mtl::ALLOC_HANDLE handle, const char* path);
    ResourceObject* searchResource(unsigned int type, mm::mtl::IAllocator* allocator, const char* path);
    // keeps a reference to an object a resource loaded until removeSafeObject (fw::SoundResource's asset)
    void addSafeObject(mm::mtl::ReferenceObject* object, eResourceType type);
    void removeSafeObject(mm::mtl::ReferenceObject* object);
};
}  // namespace fw

#endif
