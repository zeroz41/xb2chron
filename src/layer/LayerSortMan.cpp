#include <math.h>
#include <new>
#include <string.h>
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerObj.h"
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
#include "layer/LayerAnimeObj.h"
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

namespace {
// size rounded up to the sort manager's 32-byte alignment (the name is not the original's)
inline int alignSize(int size) {
    return size + (32 - size % 32) % 32;
}

// the lock createTextureObj and releaseTextureObj share (one static and its guard); the function holding it is
// inline everywhere
ml::CriticalSection& getTextureCS() {
    static ml::CriticalSection s_textureCS;
    return s_textureCS;
}
}  // namespace

LayerAnimeObj::~LayerAnimeObj() {
    m_num = 0;
    if (m_handle.m_handle != 0 && m_infos != nullptr) {
        mtl::MemManager::deallocate(m_infos, 0, false);
        m_infos = nullptr;
    }
    m_capacity = 0;
    m_infos = nullptr;
    m_handle.m_handle = 0;
}

void LayerAnimeObj::calcParm(LayerResParmInfo& info, const LayerAnimeInfo& anime, float frame) {
    if (anime.m_flags & LayerAnimeInfo::FLAG_POS) {
        info.m_pos[0] += (anime.m_pos[0] - info.m_pos[0]) * frame;
        info.m_pos[1] += (anime.m_pos[1] - info.m_pos[1]) * frame;
    }
    if (anime.m_flags & LayerAnimeInfo::FLAG_ROT) {
        info.m_rot += (anime.m_rot - info.m_rot) * frame;
    }
    if (anime.m_flags & LayerAnimeInfo::FLAG_SCALE) {
        info.m_scale[0] += (anime.m_scale[0] - info.m_scale[0]) * frame;
        info.m_scale[1] += (anime.m_scale[1] - info.m_scale[1]) * frame;
    }
    if (anime.m_flags & LayerAnimeInfo::FLAG_SIZE) {
        info.m_size[0] += (anime.m_size[0] - info.m_size[0]) * frame;
        info.m_size[1] += (anime.m_size[1] - info.m_size[1]) * frame;
    }
    if (anime.m_flags & LayerAnimeInfo::FLAG_PARM) {
        info.m_color.m_addCol.r += (anime.m_parm[0] - info.m_color.m_addCol.r) * frame;
        info.m_color.m_addCol.g += (anime.m_parm[1] - info.m_color.m_addCol.g) * frame;
        info.m_color.m_addCol.b += (anime.m_parm[2] - info.m_color.m_addCol.b) * frame;
    }
    if (anime.m_flags & LayerAnimeInfo::FLAG_COLOR) {
        info.m_color.m_mulCol.r += (anime.m_color[0] - info.m_color.m_mulCol.r) * frame;
        info.m_color.m_mulCol.g += (anime.m_color[1] - info.m_color.m_mulCol.g) * frame;
        info.m_color.m_mulCol.b += (anime.m_color[2] - info.m_color.m_mulCol.b) * frame;
        info.m_color.m_mulCol.a += (anime.m_color[3] - info.m_color.m_mulCol.a) * frame;
    }
}

LayerSortMan::~LayerSortMan() {
    if (m_mem != nullptr) {
        mtl::MemManager::deallocate(m_mem, 0, false);
        m_mem = nullptr;
    }
}

void LayerSortMan::begin(const mm::Vec3& pos) {
    int size = alignSize(m_2DBitSize + m_3DBitSize);
    memset(m_2DBits, 0, size);
    m_pos = pos;
    m_top = nullptr;
    m_last = nullptr;
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

void LayerSortMan::end() {
    for (unsigned int i = 0; i < m_3DNum; i++) {
        if (m_3DBits[i >> 5] & (1 << (i & 31))) {
            if (m_top != nullptr) {
                LayerSortObj* last = m_last;
                last->m_next = m_3DHead[i];
            } else {
                m_top = m_3DHead[i];
            }
            m_last = m_3DTail[i];
        }
    }
    for (unsigned int i = 0; i < m_2DNum; i++) {
        if (m_2DBits[i >> 5] & (1 << (i & 31))) {
            if (m_top != nullptr) {
                LayerSortObj* last = m_last;
                last->m_next = m_2DHead[i];
            } else {
                m_top = m_2DHead[i];
            }
            m_last = m_2DTail[i];
        }
    }
}

void LayerSortMan::finalRender() {
    for (LayerSortObj* obj = m_top; obj != nullptr; obj = obj->m_next) {
        obj->finalRender();
    }
}

LayerTextureMan::LayerTextureMan(LayerManager* manager) : m_manager(manager) {}

LayerTextureMan::~LayerTextureMan() { deleteAll(); }

void LayerTextureMan::releaseTextureObj(LayerTextureObj* obj) {
    ml::CS lock(getTextureCS());
    if (obj->subRef()) {
        deleteList(obj);
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

void LayerTextureObj::release() {
    m_owner->releaseTextureObj(this);
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
    m_num = 0;
    m_head = nullptr;
    m_tail = nullptr;
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
    : m_prev(nullptr), m_next(nullptr), m_res(static_cast<const LayerResAddTexHead*>(res)), m_texObj(nullptr) {
    m_flags = 0;
    m_index = index;
}

LayerResAddTexObj::LayerResAddTexObj(grlib::CGLibTextureBuffer* buffer, unsigned int index)
    : m_prev(nullptr), m_next(nullptr) {
    m_flags = FLAG_BUFFER;
    m_index = index;
    m_buffer = buffer;
    m_texObj = nullptr;
}

LayerResAddTexObj::~LayerResAddTexObj() {
    release();
}

inline void LayerResAddTexObj::release() {
    if (m_texObj != nullptr) {
        m_texObj->release();
        m_texObj = nullptr;
    }
}

grlib::CGLibTextureBuffer* LayerResAddTexObj::getTexObj(unsigned int index) {
    if (m_flags & FLAG_BUFFER) {
        return m_buffer;
    }
    return m_texObj->getTexture(index);
}

LayerResSecTexture::~LayerResSecTexture() {
    if (m_texObj != nullptr) {
        mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager->m_textureMan->releaseTextureObj(m_texObj);
        m_texObj = nullptr;
    }
    m_uniform.release();
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
