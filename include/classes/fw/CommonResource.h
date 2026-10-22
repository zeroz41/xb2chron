#ifndef CLASSES_FW_COMMONRESOURCE_H
#define CLASSES_FW_COMMONRESOURCE_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B42980; counted: its destructor hands itself to ResourceManager::removeSafeObject as an
// mm::mtl::ReferenceObject, and GfAssetResource releases its one through the count at 8
class CommonResource : public ::mm::mtl::ReferenceObject {
public:
    virtual ~CommonResource();  // slot 0
    virtual void update();  // slot 2
    virtual bool valid() const;  // slot 3: whether it has loaded (GfAssetResource::isFinishLoad returns it)
    virtual void getAssetName() const;  // slot 4
    static CommonResource* request(mm::mtl::IAllocator* allocator, const char* path, int arg, bool flag);
    void* getAssetData();
    unsigned int getAssetSize() const;
    unsigned char pad_c[0xBC];  // fields: size from its derived classes
};
}  // namespace fw

#endif
