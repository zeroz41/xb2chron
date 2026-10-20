#ifndef CLASSES_FW_ASSETLOADER_H
#define CLASSES_FW_ASSETLOADER_H

#include "classes/ml/FileResTh.h"

namespace fw {
// table 0x7100B40DE8
class AssetLoader : public ::ml::FileResTh {
public:
    virtual ~AssetLoader();  // slot 0
};
}  // namespace fw

#endif
