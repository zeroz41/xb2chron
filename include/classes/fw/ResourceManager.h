#ifndef CLASSES_FW_RESOURCEMANAGER_H
#define CLASSES_FW_RESOURCEMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"
#include "mm/mtl/FixedVector.h"
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
// table 0x7100B42A80; its base at 0x10 is its singleton (its constructor and destructor inline
// PtrSingleton<fw::ResourceManager>'s)
class ResourceManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::ResourceManager> {
public:
    // an object addSafeObject keeps (16 bytes; the names are not the original's)
    struct SafeObject {
        mm::mtl::ReferenceObject* m_object;  // referenced while it is kept
        // the times addSafeObject was asked for it; in the release list, the updates left before it is released
        short m_count;
        eResourceType m_type;  // addSafeObject's
    };

    // a list of `count` resources per type from allocator (the parameter names are not the original's)
    ResourceManager(mm::mtl::IAllocator* allocator, unsigned int count);
    virtual ~ResourceManager();  // slot 0
    virtual void enterFinalizeApplet();  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 8
    // the memory resources are made in (Framework::getMemHandle's)
    static mtl::ALLOC_HANDLE getMemSYS();
    static void setMemTMP(mtl::ALLOC_HANDLE handle);
    static unsigned int getHash(const char* path);  // a path's hash (the resources' m_hash)
    // releases the objects removeSafeObject let go whose updates have run out, all of them when force is set (the
    // parameter name is not the original's)
    void updateSafeReleaseList(bool force);
    // a resource in its type's list, by load priority (ResourceObject's constructor); out of it (its destructor)
    void addResource(ResourceObject* resource);
    void removeResource(ResourceObject* resource);
    // whether a path's extension asks ResourceManager to keep its asset safe (CommonResource::request_detail)
    static bool isDelayReleaseExtention(const char* path);
    // the loaded resource of a type and path, none (RenderResource::request asks for type 1)
    ResourceObject* searchResource(unsigned int type, mtl::ALLOC_HANDLE handle, const char* path);
    ResourceObject* searchResource(unsigned int type, mm::mtl::IAllocator* allocator, const char* path);
    // keeps a reference to an object a resource loaded until removeSafeObject (fw::SoundResource's asset)
    void addSafeObject(mm::mtl::ReferenceObject* object, eResourceType type);
    void removeSafeObject(mm::mtl::ReferenceObject* object);
    // whether every resource is valid
    bool isLoaded();

    static mtl::ALLOC_HANDLE m_hMemoryTemp;  // setMemTMP's

    // the names are not the original's
    mm::mtl::Vector<ResourceObject*> m_resources[32];  // by type, by load priority
    mm::mtl::IAllocator* m_allocator;  // the constructor's
    int m_loadCount;  // update zeroes it
    unsigned char pad_524[0x8];
    int m_finalizeState;  // enterFinalizeApplet sets 2
    bool m_isFinalizeApplet;  // enterFinalizeApplet sets it
    mm::mtl::FixedVector<SafeObject, 1024> m_safeObjects;  // addSafeObject's
    // removeSafeObject's, released after three updates (updateSafeReleaseList)
    mm::mtl::FixedVector<SafeObject, 1024> m_releaseList;
    // the extensions isDelayReleaseExtention looks for
    mm::mtl::FixedVector<const char*, 32> m_delayReleaseExtentions;
};
}  // namespace fw

#endif
