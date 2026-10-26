#include <math.h>
#include <new>
#include <string.h>
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerSortObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibTexture.h"
#include "grlib/CGLibTextureBuffer.h"
#include "grlib/CGLibVtlMemPool.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxVertex.h"
#include "layer/LayerLinkList.h"
#include "layer/LayerObjUtil.h"
#include "layer/LayerResAddTexObj.h"
#include "layer/LayerResSecTexture.h"
#include "layer/LayerSortMan.h"
#include "layer/LayerTextureMan.h"
#include "layer/LayerTextureObj.h"
#include "layer/LayerVertexMan.h"
#include "layer/LayerVertexObj.h"
#include "ml/CriticalSection.h"
#include "mtl/MemManager.h"

namespace layer {

LayerSortMan::~LayerSortMan() {
    if (m_mem != nullptr) {
        mtl::MemManager::deallocate(m_mem, 0, false);
        m_mem = nullptr;
    }
}

void LayerSortMan::set2DSpace(LayerSortObj* obj, unsigned int priority) {
    if (priority < m_2DNum) {
        stock2DObj(obj, priority);
    } else {
        stock2DObj(obj, m_2DNum - 1);
    }
}

void LayerSortMan::stock2DObj(LayerSortObj* obj, int index) {
    if (m_2DBits[index >> 5] & (1 << (index & 31))) {
        m_2DTail[index]->m_next = obj;
    } else {
        m_2DBits[index >> 5] |= 1 << (index & 31);
        m_2DHead[index] = obj;
    }
    obj->m_next = nullptr;
    m_2DTail[index] = obj;
}

void LayerSortMan::finalRender() {
    for (LayerSortObj* obj = m_top; obj != nullptr; obj = obj->m_next) {
        obj->finalRender();
    }
}

LayerTextureMan::LayerTextureMan(LayerManager* manager) : m_manager(manager) {}

LayerTextureMan::~LayerTextureMan() {
    LayerTextureObj* obj = m_head;
    while (obj != nullptr) {
        LayerTextureObj* next = obj->m_next;
        delete obj;
        obj = next;
    }
}

void LayerTextureObj::setupTexture(const unsigned char* res, LayerManager* manager) {
    textureRelease();
    m_res = reinterpret_cast<const LayerResTextureHead*>(res);
    m_texNum = m_res->m_num;
    void* mem = mtl::MemManager::allocate(manager->m_gxHandle, m_texNum * sizeof(grlib::CGLibTextureBuffer), 16,
                                          false, "no name", 0);
    m_mem = mem;
    m_textures = static_cast<grlib::CGLibTextureBuffer*>(mem);
    for (int i = 0; i < m_texNum; i++) {
        new (&m_textures[i]) grlib::CGLibTextureBuffer();
    }
}

LayerTextureObj::~LayerTextureObj() {
    textureRelease();
}

void LayerTextureObj::textureRelease() {
    if (m_mem != nullptr) {
        for (int i = 0; i < m_texNum; i++) {
            m_textures[i].~CGLibTextureBuffer();
        }
        if (m_mem != nullptr) {
            mtl::MemManager::deallocate(m_mem, 0, false);
            m_mem = nullptr;
        }
        m_texNum = 0;
    }
}

const grlib::CGLibTextureBuffer* LayerTextureObj::getTexture(int index) const {
    return &m_textures[index];
}

grlib::CGLibTextureBuffer* LayerTextureObj::getTexture(int index) {
    return &m_textures[index];
}

unsigned short s_nVertexSize[4] = {12, 20, 16, 24};

LayerVertexMan::LayerVertexMan(LayerManager* manager) : m_manager(manager) {}

LayerVertexMan::~LayerVertexMan() {
    LayerVertexObj* obj = m_head;
    while (obj != nullptr) {
        LayerVertexObj* next = obj->m_next;
        obj->vertexRelease();
        delete obj;
        obj = next;
    }
}

void LayerVertexObj::vertexRelease() {
    if (m_mem != nullptr) {
        for (int i = 0; i < m_vertexNum; i++) {
            m_vertices[i].~CGLibVtxVertex();
        }
        for (int i = 0; i < m_indexNum; i++) {
            m_indices[i].~CGLibVtxIndex();
        }
        m_pool->~CGLibVtlMemPool();
        if (m_mem != nullptr) {
            mtl::MemManager::deallocate(m_mem, 0, false);
            m_mem = nullptr;
        }
    }
}

void LayerVertexObj::release() {
    m_owner->releaseVertexObj(this);
}

void LayerVertexObj::begin() {
    m_curVertex = -1;
}

bool LayerVertexObj::setVertex(unsigned int index) {
    if (m_curVertex == index) {
        return false;
    }
    m_curVertex = index;
    grlib::CGLibCtlVertex::setVertex(m_vertices[index]);
    return true;
}

void LayerVertexObj::render(unsigned int index) {
    m_indices[index].drawIndex();
}

LayerResAddTexObj::LayerResAddTexObj(const void* res, unsigned int index)
    : pad_0(), m_res(static_cast<const LayerResAddTexHead*>(res)), m_texObj(nullptr) {
    m_flags = 0;
    m_index = index;
}

grlib::CGLibTextureBuffer* LayerResAddTexObj::getTexObj(unsigned int index) {
    if (m_flags & FLAG_BUFFER) {
        return m_buffer;
    }
    return m_texObj->getTexture(index);
}

void LayerResSecTexture::resourceInit() {
    m_uniform.setup(LayerObjUtil::getUniformBlockSizeAlOff(static_cast<LayerUniType>(10)));
}

void LayerResSecTexture::update() {
    float* buff = reinterpret_cast<float*>(m_uniform.getBuff());
    if (m_hasParm) {
        const LayerResSecTexTable* table = reinterpret_cast<const LayerResSecTexTable*>(
            reinterpret_cast<const unsigned char*>(m_res) + m_res->m_tableOfs);
        const LayerResSecTexParm* parm = reinterpret_cast<const LayerResSecTexParm*>(
                                             reinterpret_cast<const unsigned char*>(table) + table->m_parmOfs) +
                                         m_parmIndex;
        buff[0] = parm->m_parm[0];
        buff[1] = parm->m_parm[1];
        buff[2] = parm->m_parm[2];
        buff[3] = parm->m_parm[3];
    } else {
        buff[0] = 1.0f;
        buff[1] = 1.0f;
        buff[2] = 0.0f;
        buff[3] = 0.0f;
    }
    buff[4] = m_value;
    buff[5] = 0.0f;
    buff[6] = 0.0f;
    buff[7] = 0.0f;
    m_uniform.updateData();
}

grlib::CGLibTextureBuffer* LayerResSecTexture::getTexture() {
    return m_texObj->getTexture(0);
}

}  // namespace layer
