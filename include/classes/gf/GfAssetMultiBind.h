#ifndef CLASSES_GF_GFASSETMULTIBIND_H
#define CLASSES_GF_GFASSETMULTIBIND_H

#include "mm/mtl/FixedList.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B43608. The fields' names are not the original's: 1.0.0's bind/loadedAsset fill the two lists,
// isValid compares their sizes with m_objNum.
class GfAssetMultiBind {
public:
    virtual ~GfAssetMultiBind();  // slot 0

    // every object bound and every bound object's asset loaded (1.0.0's reads m_bindObj's size, m_objNum and
    // m_loadedObj's size; GfObjManager::isValidMultiBind tail-calls it)
    bool isValid() const;

    mm::mtl::FixedList<GF_OBJ_HANDLE*, 32> m_bindObj;    // 1.0.0's bind adds to it
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 32> m_loadedObj;  // 1.0.0's loadedAsset adds to it
    unsigned int m_id;  // GfObjManager::getAssetMultiBind looks the bind up by it
    int m_objNum;       // how many objects isValid waits for
};
}  // namespace gf

#endif
