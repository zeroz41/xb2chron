#ifndef PTLIB_MATERIAL_MATERIALMANAGER_H
#define PTLIB_MATERIAL_MATERIALMANAGER_H

#include "mm/mtl/FixedVector.h"

namespace ptlib { namespace material { class MaterialBase; class MaterialTexture; } }

namespace ptlib { namespace material {

// what a material is made from (create makes textures, 0); no value has a name yet
enum eMaterialType {};

// the effect library's textures: 2048 of them in one block, free or active (particle_material_manager.cpp)
class MaterialManager {
public:
    MaterialManager() : m_textureId(0), pad_8014(1), pad_8018(-1) {}

    static void init();
    // the slot that holds the instance, null before init and after term
    static MaterialManager*& getPtr();
    // the textures, all free
    void initSub();
    static void term();
    // destroys the active textures but the permanent ones; with all, every texture and their block
    void termSub(bool all);
    // the instance; asserts that there is one
    static MaterialManager* get();
    void allClear(bool all);
    // a texture of the type from data (an active one with the same data and size, counted again), or null
    MaterialBase* create(int key, eMaterialType type, void* data, unsigned int size, bool permanent,
                            unsigned char* param, void* owner, int format);
    // a free texture made from the image, or null when none is free
    MaterialTexture* createTexture(void* data, unsigned int size, bool flag, int format);
    MaterialBase* getMaterialByIdx(unsigned int index);
    MaterialBase* getMaterialByKey(const int& key, void* owner);
    // counts the requests for the key's texture down, and frees it at 0 (the symbols spell it so)
    void destroyMateriaByKey(const int& key, void* owner);

    // the names below are not the original's but m_aActiveMaterial's (create's check
    // `!m_aActiveMaterial.find(pMaterial)`)
    mm::mtl::FixedVector<MaterialTexture*, 2048> m_aFreeMaterial;
    mm::mtl::FixedVector<MaterialBase*, 2048> m_aActiveMaterial;
    int m_textureId;  // createTexture gives it to each texture
    int pad_8014;     // unknown: 1 from the constructor
    int pad_8018;     // unknown: -1 from the constructor
    MaterialTexture* m_pTextures;  // initSub's: the 2048 textures
};

}}  // namespace ptlib::material

#endif
