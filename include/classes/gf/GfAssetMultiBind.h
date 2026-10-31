#ifndef CLASSES_GF_GFASSETMULTIBIND_H
#define CLASSES_GF_GFASSETMULTIBIND_H

#include "mm/mtl/FixedList.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B43608. The fields' names are not the original's: 1.0.0's bind/loadedAsset fill the two lists,
// isValid compares their sizes with m_objNum.
class GfAssetMultiBind {
public:
    // the parameter names are not the original's: the id goes to m_id, the flag to m_flag
    GfAssetMultiBind(unsigned int id, bool flag);
    virtual ~GfAssetMultiBind();  // slot 0

    // every object bound and every bound object's asset loaded (1.0.0's reads m_bindObj's size, m_objNum and
    // m_loadedObj's size; GfObjManager::isValidMultiBind tail-calls it)
    bool isValid() const;
    // handle added to the bound objects unless it is there already; always true
    bool bind(GF_OBJ_HANDLE* handle);
    // handle taken out of the bound objects; false when it was not bound (GfObjManager::checkTerminate)
    bool unbind(GF_OBJ_HANDLE* handle);
    // a bound handle's asset loaded: added to the loaded objects (counted) unless it is there; false when not bound
    bool loadedAsset(GF_OBJ_HANDLE* handle);
    // a bound handle's asset unloaded: taken out of the loaded objects (counted); false when not bound
    bool unloadedAsset(GF_OBJ_HANDLE* handle);

    mm::mtl::FixedList<GF_OBJ_HANDLE*, 32> m_bindObj;    // 1.0.0's bind adds to it
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 32> m_loadedObj;  // 1.0.0's loadedAsset adds to it
    unsigned int m_id;  // GfObjManager::getAssetMultiBind looks the bind up by it
    int m_objNum;       // how many objects isValid waits for
    int m_loadedNum;    // loadedAsset counts up, unloadedAsset down (the name is not the original's)
    bool m_flag;        // the constructor's second argument (the name is not the original's)
};
}  // namespace gf

#endif
