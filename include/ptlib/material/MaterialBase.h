#ifndef PTLIB_MATERIAL_MATERIALBASE_H
#define PTLIB_MATERIAL_MATERIALBASE_H

namespace ptlib { namespace material {

// what MaterialManager keeps active (1.0.0's MaterialManager::addActiveMaterial takes one): its destructor is
// virtual (the manager destroys its materials through their tables). The field names are not the original's but
// m_refCnt's, which particle_material_manager.cpp's check `(m_refCnt < 0)` names.
class MaterialBase {
public:
    MaterialBase()
        : m_key(-1), m_id(0), pad_14(1.0f), m_owner(nullptr), m_data(nullptr), m_size(0), m_refCnt(0),
          m_permanent(false) {}
    virtual ~MaterialBase() {}

    int m_key;          // MaterialManager::create's; getMaterialByKey finds it by it
    int m_id;           // MaterialManager::createTexture's: the manager's m_textureId
    int m_type;         // an eMaterialType: MaterialTexture's is 0
    float pad_14;       // unknown: 1 from the constructor
    void* m_owner;      // create's; getMaterialByKey and destroyMateriaByKey match it (null matches any)
    const void* m_data;  // the material's source: create shares a material made from the same data and size
    unsigned int m_size;
    unsigned char* m_pParam;  // create's
    int m_refCnt;      // create counts each request; destroyMateriaByKey frees it at 0
    bool m_permanent;  // create's: termSub(false) and destroyMateriaByKey keep it, getMaterialByKey matches any owner
};

}}  // namespace ptlib::material

#endif
