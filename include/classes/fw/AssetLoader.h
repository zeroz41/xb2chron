#ifndef CLASSES_FW_ASSETLOADER_H
#define CLASSES_FW_ASSETLOADER_H

#include "classes/ml/FileResTh.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40DE8
class AssetLoader : public ::ml::FileResTh {
public:
    virtual ~AssetLoader();  // slot 0
    // a loader reading path (fw::SoundResource::update passes its allocator, path, load priority and the int at 0x24
    // of its ResourceObject; the parameter names are not the original's)
    static AssetLoader* Create(mm::mtl::IAllocator* allocator, const char* path, int prio, int arg);
};
}  // namespace fw

#endif
