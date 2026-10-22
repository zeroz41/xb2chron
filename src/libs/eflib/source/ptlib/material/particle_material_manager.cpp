#define MM_LIB_FROM_EFLIB
#include "mm/mtl/FixedVector.h"
#include "grlib/CGLibTexture.h"
#include "grlib/CGLibTextureBuffer.h"
#include "ptlib/material/MaterialBase.h"
#include "classes/ptlib/material/MaterialTexture.h"
#include "ptlib/material/MaterialManager.h"
#include "ptlib/ParticleSystem.h"
#include "mm/MMStdBase.h"
#include "new"

namespace ptlib { namespace material {

static MaterialManager* s_pIns;

void MaterialManager::init() {
#line 35
    MM_ASSERT(!getPtr());
    MaterialManager* manager = static_cast<MaterialManager*>(
#line 36
        ParticleManager::sysAlloc(sizeof(MaterialManager), 16, __FILE__, __LINE__));
    getPtr() = manager;
    if (manager != nullptr) {
        new (manager) MaterialManager();
        manager->initSub();
    }
}

MaterialManager*& MaterialManager::getPtr() {
    return s_pIns;
}

void MaterialManager::initSub() {
    m_aFreeMaterial.clear();
    m_aActiveMaterial.clear();
    m_pTextures = static_cast<MaterialTexture*>(
#line 99
        ParticleManager::sysAlloc(sizeof(MaterialTexture) * 2048, 16, __FILE__, __LINE__));
    if (m_pTextures != nullptr) {
        for (int i = 0; i < 2048; i++) {
            new (&m_pTextures[i]) MaterialTexture();
            m_aFreeMaterial.push_back(&m_pTextures[i]);
        }
    }
}

void MaterialManager::term() {
#line 49
    MM_ASSERT(getPtr());
    getPtr()->termSub(true);
    getPtr()->~MaterialManager();
    ParticleManager::sysFree(getPtr());
    getPtr() = nullptr;
}

void MaterialManager::termSub(bool all) {
    if (all) {
        for (mm::mtl::FixedVector<MaterialTexture*, 2048>::iterator it = m_aFreeMaterial.begin();
             it != m_aFreeMaterial.end(); ++it) {
            (*it)->~MaterialTexture();
        }
        for (mm::mtl::FixedVector<MaterialBase*, 2048>::iterator it = m_aActiveMaterial.begin();
             it != m_aActiveMaterial.end(); ++it) {
            (*it)->~MaterialBase();
        }
        m_aFreeMaterial.clear();
        m_aActiveMaterial.clear();
        if (m_pTextures != nullptr) {
            ParticleManager::sysFree(m_pTextures);
            m_pTextures = nullptr;
        }
    } else {
        for (mm::mtl::FixedVector<MaterialBase*, 2048>::iterator it = m_aActiveMaterial.begin();
             it != m_aActiveMaterial.end();) {
            MaterialBase* texture = *it;
            if (!texture->m_permanent) {
                texture->~MaterialBase();
                m_aFreeMaterial.push_back(static_cast<MaterialTexture*>(texture));
                it = m_aActiveMaterial.erase(it);
            } else {
                ++it;
            }
        }
    }
}

MaterialManager* MaterialManager::get() {
#line 62
    MM_ASSERT(getPtr());
    return getPtr();
}

void MaterialManager::allClear(bool all) {
    termSub(all);
}

MaterialBase* MaterialManager::create(int key, eMaterialType type, void* data, unsigned int size, bool permanent,
                                         unsigned char* param, void* owner, int format) {
    for (mm::mtl::FixedVector<MaterialBase*, 2048>::iterator it = m_aActiveMaterial.begin();
         it != m_aActiveMaterial.end(); ++it) {
        MaterialBase* texture = *it;
        if (texture->m_type == type && texture->m_data == data && texture->m_size == size) {
            texture->m_refCnt++;
            return texture;
        }
    }
    switch (static_cast<int>(type)) {
    case 0: {
        MaterialTexture* texture = createTexture(data, size, false, format);
        if (texture != nullptr) {
            texture->m_permanent = permanent;
            texture->m_pParam = param;
            texture->m_owner = owner;
            texture->m_key = key;
            texture->m_type = 0;
            texture->m_data = data;
            texture->m_size = size;
            texture->m_refCnt++;
            efAstMsg("!m_aActiveMaterial.find(pMaterial)", "double registration error!!!");
            m_aActiveMaterial.push_back(texture);
            return texture;
        }
        break;
    }
    case 1:
    case 2:
        break;
    default:
#line 188
        MM_ASSERT(0);
        break;
    }
#line 194
    MM_ASSERT(0);
    return nullptr;
}

MaterialTexture* MaterialManager::createTexture(void* data, unsigned int size, bool flag, int format) {
    MaterialTexture* texture;
    if (m_aFreeMaterial.empty()) {
        texture = nullptr;
    } else {
        texture = *m_aFreeMaterial.begin();
        m_aFreeMaterial.erase(m_aFreeMaterial.begin());
        if (texture != nullptr) {
            texture->m_id = m_textureId;
            grlib::CGLibTexSwizzle swizzle;
            switch (format) {
            case 4:
                swizzle = {2, 2, 2, 2};
                break;
            case 5:
                swizzle = {2, 2, 2, 1};
                break;
            case 6:
                swizzle = {1, 1, 1, 2};
                break;
            default:
                swizzle = {2, 3, 4, 5};
                break;
            }
            grlib::CGLibTexture::createTextureImagePtrs(texture->m_texture, data, size, flag, &swizzle, false);
            if (texture->m_texture.isTexture3D()) {
                texture->m_is3D = true;
            }
        }
    }
    return texture;
}

MaterialBase* MaterialManager::getMaterialByIdx(unsigned int index) {
    if (index < m_aActiveMaterial.size()) {
        return m_aActiveMaterial.begin()[index];
    }
    return nullptr;
}

MaterialBase* MaterialManager::getMaterialByKey(const int& key, void* owner) {
    for (mm::mtl::FixedVector<MaterialBase*, 2048>::iterator it = m_aActiveMaterial.begin();
         it != m_aActiveMaterial.end(); ++it) {
        MaterialBase* texture = *it;
        if (texture->m_key == key) {
            if (texture->m_owner == nullptr || texture->m_owner == owner) {
                return texture;
            }
            if (texture->m_permanent) {
                return texture;
            }
        }
    }
    return nullptr;
}

void MaterialManager::destroyMateriaByKey(const int& key, void* owner) {
    for (mm::mtl::FixedVector<MaterialBase*, 2048>::iterator it = m_aActiveMaterial.begin();
         it != m_aActiveMaterial.end();) {
        MaterialBase* material = *it;
        if (material->m_key == key && !material->m_permanent && material->m_owner == owner) {
            material->m_refCnt--;
            efAstMsg("(m_refCnt < 0)", "refCount minus!!!");
            material = *it;
            if (material->m_refCnt == 0) {
                material->~MaterialBase();
                it = m_aActiveMaterial.erase(it);
                m_aFreeMaterial.push_back(static_cast<MaterialTexture*>(material));
                continue;
            }
        }
        ++it;
    }
}

MaterialTexture::~MaterialTexture() {}

}}  // namespace ptlib::material
