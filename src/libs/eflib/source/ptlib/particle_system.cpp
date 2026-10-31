#define MM_LIB_FROM_EFLIB
#include "ptlib/ParticleSystem.h"
#include "ptlib/emitter/EmitterManager.h"
#include "ptlib/emitter/EmitterObj.h"
#include "ptlib/renderer/RendererManager.h"
#include "ptlib/material/MaterialManager.h"
#include "classes/ptlib/HeapAllocator.h"
#include "ptlib/math/KeyFrameIP.h"
#include "mm/MMStdBase.h"
#include "ptlib/IntrusiveList.h"
#include "mm/Vec3.h"
#include "ptlib/Utility.h"
#include "ptlib/forcefield/FfManager.h"
#include "ptlib/forcefield/TurbulenceN.h"
#include "idcoli/IDColiDef.h"
#include "new"
#include <stdio.h>
#include <stdarg.h>

namespace ptlib {

// efAstMsg's, efMsg's and efWng's text (the name is not the original's: the symbols leave it unnamed)
static char s_message[0x1000];
// the line efAstMsg prints around its text (the name is not the original's)
static const char s_separator[] = "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_";

// the speed update_model_spd hands the models (Proposed name, not the original's: the symbols leave it unnamed
// (lbl_71015E9E30))
static float s_mdlSpd;

// the instance init makes (the name is not the original's: the symbols leave it unnamed)
static ParticleManager* s_pIns;
// the instance particle_hash.cpp's HashManager::init makes (the name is not the original's)
static HashManager* s_pHashIns;

ParticleManager*& ParticleManager::getPtr() {
    return s_pIns;
}

ParticleManager* ParticleManager::get() {
#line 40 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/particle_system.cpp"
    MM_ASSERT(getPtr());
    return getPtr();
}

void ParticleManager::setUserAllocFunc(void* (*allocSys)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                       void (*freeSys)(void*, void*),
                                       void* (*allocRes)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                       void (*freeRes)(void*, void*), mtl::ALLOC_HANDLE (*getSysHandle)(),
                                       mtl::ALLOC_HANDLE (*getResHandle)()) {
    s_pAllocFuncSys = allocSys;
    s_pFreeFuncSys = freeSys;
    s_pAllocFuncRes = allocRes;
    s_pFreeFuncRes = freeRes;
    s_pGetSysHandle = getSysHandle;
    s_pGetResHandle = getResHandle;
}

void ParticleManager::setUserFileFunc(void* (*read)(const char*, int&), void (*readEnd)(void*)) {
    s_pReadFunc = read;
    s_pReadEndFunc = readEnd;
}

void ParticleManager::setUserOutputString(void (*debug)(const char*), void (*warn)(const char*)) {
    s_pOutputDebugStringFunc = debug;
    s_pOutputWarnStringFunc = warn;
}

void ParticleManager::setUserDrFunc(void* (*createMdl)(const void*, const char*, int, const void*, int),
                                    void (*deleteMdl)(void*), void* (*createLgt)(unsigned int, int),
                                    void (*deleteLgt)(unsigned int, void*), void (*setMdlPos)(void*, void*),
                                    void (*setMdlMatrix)(void*, void*), void (*setMdlColor)(void*, void*),
                                    void (*setMdlAlpha)(void*, float), void (*setMdlSpd)(void*, void*),
                                    void (*setLgtPos)(unsigned int, void*, void*),
                                    void (*setLgtMatrix)(unsigned int, void*, void*),
                                    void (*setLgtParam)(unsigned int, void*, void*), void (*debugRenderer)(void*),
                                    void* (*createGrp)(int, int), void (*destroyGrp)(void*)) {
    s_pDrFunc.createMdl = createMdl;
    s_pDrFunc.deleteMdl = deleteMdl;
    s_pDrFunc.createLgt = createLgt;
    s_pDrFunc.deleteLgt = deleteLgt;
    s_pDrFunc.setMdlPos = setMdlPos;
    s_pDrFunc.setMdlMatrix = setMdlMatrix;
    s_pDrFunc.setMdlColor = setMdlColor;
    s_pDrFunc.setMdlAlpha = setMdlAlpha;
    s_pDrFunc.setMdlSpd = setMdlSpd;
    s_pDrFunc.setLgtPos = setLgtPos;
    s_pDrFunc.setLgtMatrix = setLgtMatrix;
    s_pDrFunc.setLgtParam = setLgtParam;
    s_pDrFunc.createGrp = createGrp;
    s_pDrFunc.destroyGrp = destroyGrp;
    s_pDrFunc.debugRenderer = debugRenderer;
}

void* ParticleManager::sysAlloc(unsigned int size, unsigned int align, const char* file, unsigned int line) {
    void* ptr = s_pAllocFuncSys(nullptr, size, align, file, line);
#line 213
    MM_ASSERT(ptr);
    return ptr;
}

void ParticleManager::init(const DrDrawWorkInfoEF* pDrInfo) {
    HeapAllocaterManager::init();
#line 122
    getPtr() = static_cast<ParticleManager*>(sysAlloc(sizeof(ParticleManager), 16, __FILE__, __LINE__));
    getPtr()->m_fxParam.reset();
    efAstMsg("getPtr()", "particle system cannot create");
    getPtr()->clear();
    getPtr()->m_initFlags[0] = true;
    getPtr()->m_initFlags[1] = false;
    emitter::EmitterManager::init();
    HashManager::init();
    material::MaterialManager::init();
    getPtr()->m_fxParam.reset();
    renderer::RenderManager::init(pDrInfo, &getPtr()->m_fxParam);
    if (renderer::RenderManager::getPtr() != nullptr) {
        renderer::RenderManager::getPtr()->fxcore_setup_target();
    }
    for (int i = 0; i < 4; i++) {
        getPtr()->m_pGrp[i] = createGrp(i, 11);
    }
}

void efAstMsg(const char* expression, const char* format, ...) {
    if (expression == nullptr) {
        va_list arguments;
        va_start(arguments, format);
        vsnprintf(s_message, sizeof(s_message), format, arguments);
        va_end(arguments);
        ParticleManager::s_pOutputDebugStringFunc(s_separator);
        ParticleManager::s_pOutputDebugStringFunc(s_message);
        ParticleManager::s_pOutputDebugStringFunc(s_separator);
        asm volatile(".inst 0xe7ffdefe");  // stops here: an undefined instruction
    }
}

FxParam* ParticleManager::getFxParam() {
    return &m_fxParam;
}

void ParticleManager::term() {
    HashManager::term();
    material::MaterialManager::term();
    renderer::RenderManager::term();
    emitter::EmitterManager::term();
    for (int i = 0; i < 4; i++) {
        destroyGrp(getPtr()->m_pGrp[i]);
    }
    getPtr()->m_pGrp[0] = nullptr;
    getPtr()->m_pGrp[1] = nullptr;
    getPtr()->m_pGrp[2] = nullptr;
    getPtr()->m_pGrp[3] = nullptr;
    if (getPtr() != nullptr) {
        sysFree(getPtr());
        getPtr() = nullptr;
    }
    HeapAllocaterManager::term();
}

void ParticleManager::sysFree(void* p) {
    s_pFreeFuncSys(nullptr, p);
}

void ParticleManager::resFree(void* p) {
    s_pFreeFuncRes(nullptr, p);
}

void* ParticleManager::readFileBlock(const char* path, int& size) {
    return s_pReadFunc(path, size);
}

void* ParticleManager::createMdl(const void* a, const char* b, int c, const void* d, int e) {
    return s_pDrFunc.createMdl(a, b, c, d, e);
}

void ParticleManager::deleteMdl(void* pMdl) {
    s_pDrFunc.deleteMdl(pMdl);
}

void* ParticleManager::createLgt(unsigned int a, int b) {
    return s_pDrFunc.createLgt(a, b);
}

void ParticleManager::deleteLgt(unsigned int a, void* pLgt) {
    s_pDrFunc.deleteLgt(a, pLgt);
}

void ParticleManager::debugRenderer(void* p) {
    s_pDrFunc.debugRenderer(p);
}

void* ParticleManager::getGrp(int index) {
    if (index >= 0 && index < 4) {
        if (s_pIns != nullptr) {
            return s_pIns->m_pGrp[index];
        }
    }
    return nullptr;
}

unsigned char* ParticleManager::parseEfb(unsigned char* pData, const char*, unsigned long param) {
    FxHeader* pHeader = reinterpret_cast<FxHeader*>(pData);
    if (pHeader->m_magic == 0x30626665) {
        if (pHeader->m_type == 1) {
            pHeader->m_userParam = param;
            emitter::EmitterManager::get()->emitter_set_link(pHeader);
            parse_efb_type0001(pData);
        } else if (pHeader->m_type == 'P') {
            FxHeader::TexTable* pTable = static_cast<FxHeader::TexTable*>(pHeader->getBlock());
            renderer::RenderManager* pRender = renderer::RenderManager::get();
            for (unsigned int i = 0; i < pTable->m_num; i++) {
                FxHeader::TexTable::Entry& entry = pTable->m_entries[i];
                pRender->tex_loadmem(entry.m_key, pTable->getData(entry), entry.m_size, entry.m_format, pData, true,
                                     nullptr);
            }
        } else if (pHeader->m_type == 'Q') {
            m_pReserved = pHeader->getBlock();
        } else {
            efAstMsg("0", "illegal EFB format:%04x", pHeader->m_type);
        }
    } else {
        efMsg("corrupted data %10x-", pData);
        pData = nullptr;
    }
    return pData;
}

void ParticleManager::getCamParam() {}

void efMsg(const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(s_message, sizeof(s_message), format, arguments);
    va_end(arguments);
    ParticleManager::s_pOutputDebugStringFunc(s_message);
}

void ParticleManager::emitter_set_free_all(bool flag) {
    emitter::EmitterManager::get()->emitter_set_free_all_sub(flag);
}

void ParticleManager::emitter_set_search(int a, const char* b, void* c, unsigned int d) {
    emitter::EmitterManager::get()->emitter_set_search(a, b, c, d);
}

void ParticleManager::emitter_set_param_pos_only(unsigned int handle, emitter::EmitterParam* pParam) {
    emitter::EmitterManager::get()->emitter_set_param_pos_only(handle, pParam);
}

void ParticleManager::emitter_set_param_pos_only2(unsigned int handle, emitter::EmitterParam* pParam) {
    emitter::EmitterManager::get()->emitter_set_param_pos_only2(handle, pParam);
}

void ParticleManager::emitter_set_param(unsigned int handle, emitter::EmitterParam* pParam) {
    emitter::EmitterManager::get()->emitter_set_param(handle, pParam);
}

void ParticleManager::emitter_set_param(FxHeader* pHeader, emitter::EmitterParam* pParam) {
    emitter::EmitterManager::get()->emitter_set_param(pHeader, pParam);
}

void ParticleManager::emitter_set_casname(unsigned int handle, const void* a, const char* b, int c, float d, int e) {
    emitter::EmitterManager::get()->emitter_set_casname(handle, a, b, c, d, e);
}

void ParticleManager::emitter_set_casparam(unsigned int handle, const void* a, emitter::EmitterParam* pParam) {
    emitter::EmitterManager::get()->emitter_set_casparam(handle, a, pParam);
}

void ParticleManager::emitter_set_disp(unsigned int handle, int disp) {
    emitter::EmitterManager::get()->emitter_set_disp(handle, disp);
}

void ParticleManager::emitter_set_alpha(unsigned int handle, float alpha) {
    emitter::EmitterManager::get()->emitter_set_alpha(handle, alpha);
}

void ParticleManager::emitter_set_speed(unsigned int handle, float speed) {
    emitter::EmitterManager::get()->emitter_set_speed(handle, speed);
}

void ParticleManager::emitter_set_category(unsigned int handle, unsigned int category) {
    emitter::EmitterManager::get()->emitter_set_category(handle, category);
}

void ParticleManager::emitter_set_viewnum(unsigned int handle, int view) {
    emitter::EmitterManager::get()->emitter_set_viewnum(handle, view);
}

void ParticleManager::emitter_set_nowait(unsigned int handle, int nowait) {
    emitter::EmitterManager::get()->emitter_set_nowait(handle, nowait);
}

void ParticleManager::emitter_set_fadeout(unsigned int handle, int frames) {
    emitter::EmitterManager::get()->emitter_set_fadeout(handle, frames);
}

void ParticleManager::emitter_set_fadeout(FxHeader* pHeader, int frames) {
    emitter::EmitterManager::get()->emitter_set_fadeout(pHeader, frames);
}

void ParticleManager::emitter_set_fadeout(void* p, int frames) {
    emitter::EmitterManager::get()->emitter_set_fadeout(p, frames);
}

void ParticleManager::update_pause() {
    m_fxParam.m_paused = m_fxParam.m_pause;
    update_model_spd(nullptr, 1.0f);
}

void ParticleManager::update_model_spd(emitter::EmitterObj* pEmitter, float speed) {
    float spd = m_fxParam.m_paused ? 0.0f : speed;
    if (pEmitter != nullptr) {
        for (IntrusiveList<emitter::ParticleObj>::iterator it = pEmitter->m_particleList.begin();
             it != pEmitter->m_particleList.end(); ++it) {
            s_mdlSpd = spd * pEmitter->m_speed;
            if (it->m_hasMdl && it->m_pWork->m_pMdl != nullptr) {
                s_pDrFunc.setMdlSpd(it->m_pWork->m_pMdl, &s_mdlSpd);
            }
        }
    } else {
        emitter::EmitterManager* pManager = emitter::EmitterManager::getPtr();
        for (IntrusiveList<emitter::EmitterObj>::iterator em = pManager->getEmitterActiveList()->begin();
             em != pManager->getEmitterActiveList()->end(); ++em) {
            s_mdlSpd = spd * em->m_speed;
            for (IntrusiveList<emitter::ParticleObj>::iterator it = em->m_particleList.begin();
                 it != em->m_particleList.end(); ++it) {
                if (it->m_hasMdl && it->m_pWork->m_pMdl != nullptr) {
                    s_pDrFunc.setMdlSpd(it->m_pWork->m_pMdl, &s_mdlSpd);
                }
            }
        }
    }
}

void ParticleManager::set_pause(bool pause) {
    m_fxParam.m_pause = pause;
}

int ParticleManager::convert_key_by_material_index(int index, FxHeader* pHeader) const {
    if (index > 0xfffffff) {
        return index;
    }
    const FxMaterialTable* pTable = pHeader->getMaterialTable();
    if (pTable == nullptr) {
        return index;
    }
    if (index >= static_cast<int>(pTable->m_count)) {
        return index;
    }
    return pTable->getEntry(index)->m_key;
}

unsigned char* ParticleManager::parse_efs(const char*, void* pData, unsigned int) {
    if (pData == nullptr) {
        return nullptr;
    }
    FxHeader* pHeader = static_cast<FxHeader*>(pData);
    if (pHeader->m_magic != 0x30626665) {
        return nullptr;
    }
    ParticleManager* pManager = getPtr();
    // the original passes parseEfb a name it never sets (no register is loaded for it)
    const char* pName;
    if (pHeader->m_type == 'a') {
        FxHeader* pFile = pHeader->getNext();
        do {
            pManager->parseEfb(reinterpret_cast<unsigned char*>(pFile), pName, reinterpret_cast<unsigned long>(pData));
            pFile = pFile->getNext();
        } while (pFile != nullptr);
        return static_cast<unsigned char*>(pData);
    }
    return pManager->parseEfb(static_cast<unsigned char*>(pData), pName, 0);
}

void ParticleManager::emitter_pack_free(unsigned long pack) {
    emitter::EmitterManager::get()->emitter_pack_free(pack);
}

void ParticleManager::emitter_set_free(FxHeader* pHeader, int frames) {
    emitter::EmitterManager::get()->emitter_set_free(pHeader, frames);
}


void ParticleManager::emitter_alloc01_set_draw(emitter::EmitterObj* pObj, emitter::EmitterArg* pArg) {
    renderer::RenderManager::get()->setEmitterDraw(pObj, pArg);
}

void ParticleManager::move() {
    if (m_fxParam.m_flag10) {
        return;
    }
    if (!m_fxParam.m_paused) {
        m_frame += 1.0f;
        if (m_frame >= 1.0f) {
            do {
                emitter::EmitterManager::get()->emitter_update(0, 1.0f, false);
                m_frame -= 1.0f;
            } while (m_frame >= 1.0f);
        } else {
            emitter::EmitterManager::get()->emitter_update(0, 1.0f, true);
        }
    }
    emitter::EmitterManager::get()->move();
}

void ParticleManager::tail() {
    emitter::EmitterManager::get()->moveAfter();
    // the original passes build an emitter it never sets (no register is loaded for it)
    emitter::EmitterObj* pEmitter;
    HashManager::get()->build(pEmitter);
    emitter::EmitterManager* pManager = emitter::EmitterManager::get();
    pManager->m_flip = !(pManager->m_flip & 1);
    // the original asserts the instances here without using them
    get();
    renderer::RenderManager::get();
}

void ParticleManager::draw(const DrDrawWorkInfoEF* pDrInfo, int view, bool blur) {
    // the original asserts the instance first without using it
    get();
    renderer::RenderManager* pRender = renderer::RenderManager::get();
    pRender->setDrInfo(pDrInfo);
    emitter::EmitterManager* pManager = emitter::EmitterManager::get();
    if (blur) {
        pRender->draw(*pManager, m_fxParam, view, 1);
    } else {
        pRender->draw(*pManager, m_fxParam, view, 0);
    }
}

void ParticleManager::setDrInfo(const DrDrawWorkInfoEF* pDrInfo) {
    // the original asserts the instance first without using it
    get();
    renderer::RenderManager::get()->setDrInfo(pDrInfo);
}

bool ParticleManager::testRayGround(mm::Vec3& outNormal, mm::Vec3& outPos, const mm::Vec3& pos, const mm::Vec3& dir,
                                    float a, float b) {
    if (m_initFlags[1]) {
        return false;
    }
    idcoli::IDColiDef def;
    def.m_result.m_type = 1;
    def.pad_0 = false;
    def.pad_1 = true;
    if (!def.testRay(pos, dir, a, b)) {
        return false;
    }
    if (def.m_result.m_nearHit) {
        outNormal = def.m_result.m_near.m_normal;
        outPos = def.m_result.m_near.m_pos;
#line 1584
        MM_ASSERT(!outPos.isError());
    } else {
        outNormal = def.m_result.m_secNear.m_normal;
        outPos = def.m_result.m_secNear.m_pos;
#line 1589
        MM_ASSERT(!outPos.isError());
    }
    return true;
}

bool ParticleManager::testLineGround(mm::Vec3& outNormal, mm::Vec3& outPos, const mm::Vec3& start,
                                     const mm::Vec3& end) {
    if (m_initFlags[1]) {
        return false;
    }
    idcoli::IDColiDef def;
    def.m_result.m_type = 1;
    def.pad_0 = false;
    def.pad_1 = true;
    if (!def.testLine(start, end)) {
        return false;
    }
    outNormal = def.m_result.m_near.m_normal;
    outPos = def.m_result.m_near.m_pos;
    return true;
}

}  // namespace ptlib

// particle_hash.cpp, which particle_system.cpp includes: its strings and statics sit in this unit
#line 1 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/particle_hash.cpp"
namespace ptlib {

void HashManager::init() {
#line 56
    getPtr() = static_cast<HashManager*>(ParticleManager::sysAlloc(sizeof(HashManager), 16, __FILE__, __LINE__));
    getPtr()->m_createKey = math::fxMath_RandI() + 1;
    if (getPtr()->m_createKey == 0) {
        getPtr()->m_createKey++;
    }
    getPtr()->reset();
}

void HashManager::term() {
    if (getPtr() != nullptr) {
        ParticleManager::sysFree(getPtr());
        getPtr() = nullptr;
    }
}

HashManager* HashManager::get() {
#line 19
    MM_ASSERT(getPtr());
    return getPtr();
}

HashManager*& HashManager::getPtr() {
    return s_pHashIns;
}

void HashManager::add(unsigned int handle) {
    if (handle != 0) {
        add_core(handle, nullptr);
    }
}

bool HashManager::check(unsigned int handle) {
    if (handle != 0) {
        if (m_entries[check_core(handle)].m_handle == handle) {
            return true;
        }
    }
    return false;
}

unsigned int HashManager::get_create_key() {
    unsigned int key = m_createKey++;
    if (m_createKey == 0) {
        m_createKey++;
    }
    add(key);
    return key;
}

int HashManager::searchDead(unsigned int handle) {
    for (unsigned int i = 0; i < m_deadCount; i++) {
        if (m_dead[i].m_handle == handle) {
            return m_dead[i].m_value;
        }
    }
    return -1;
}

// back in particle_system.cpp
void efWng(const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(s_message, sizeof(s_message), format, arguments);
    va_end(arguments);
    ParticleManager::s_pOutputWarnStringFunc(s_message);
}

}  // namespace ptlib

// particle_intrusive_list.cpp and forcefield/particle_force_field.cpp are one compile with this file: FfManager::init
// and addForce inline ParticleManager::sysAlloc, and the FfManager pointer sits inside this unit's .bss
#line 1 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/particle_intrusive_list.cpp"
namespace ptlib {

IntrusiveListBase::IntrusiveListBase() : m_size(0) {}

void IntrusiveListBase::linkNode(IntrusiveListNode* node, IntrusiveListNode* next) {
#line 34 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/particle_intrusive_list.cpp"
    MM_ASSERT(!node->intoNode());
    IntrusiveListNode* prev = next->m_prev;
    node->m_prev = prev;
    prev->m_next = node;
    next->m_prev = node;
    node->m_next = next;
}

void IntrusiveListBase::unlinkNode(IntrusiveListNode* node) {
#line 43
    MM_ASSERT(node->intoNode());
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
    node->m_next = node;
    node->m_prev = node;
}

unsigned int Utility::conv_rgba(mm::Vec3* color, float alpha) {
    float r = color->x;
    float g = color->y;
    float b = color->z;
    r = r < 0.0f ? 0.0f : r;
    g = g < 0.0f ? 0.0f : g;
    b = b < 0.0f ? 0.0f : b;
    r = r > 1.0f ? 1.0f : r;
    g = g > 1.0f ? 1.0f : g;
    b = b > 1.0f ? 1.0f : b;
    r *= 255.0f;
    g *= 255.0f;
    float a = alpha * 255.0f;
    a = a < 0.0f ? 0.0f : a;
    a = a > 255.0f ? 255.0f : a;
    b *= 255.0f;
    unsigned char ir = (int)r;
    unsigned char ig = (int)g;
    unsigned char ib = (int)b;
    unsigned char ia = (int)a;
    return ir | (ig << 8) | (ib << 16) | (ia << 24);
}

}  // namespace ptlib

#line 1 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/forcefield/particle_force_field.cpp"
#define PTLIB_FORCE_FIELD_PATH "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/forcefield/particle_force_field.cpp"

namespace ptlib {

// the gradients ImprovedNoise::noise picks with a hash's low four bits (Perlin's twelve and four of them again)
// (Proposed name, not the original's: the symbols leave it unnamed (lbl_71015EAE50))
static mm::Vec3 s_grad[16] = {
    mm::Vec3(1.0f, 1.0f, 0.0f),  mm::Vec3(-1.0f, 1.0f, 0.0f),  mm::Vec3(1.0f, -1.0f, 0.0f), mm::Vec3(-1.0f, -1.0f, 0.0f),
    mm::Vec3(1.0f, 0.0f, 1.0f),  mm::Vec3(-1.0f, 0.0f, 1.0f),  mm::Vec3(1.0f, 0.0f, -1.0f), mm::Vec3(-1.0f, 0.0f, -1.0f),
    mm::Vec3(0.0f, 1.0f, 1.0f),  mm::Vec3(0.0f, -1.0f, 1.0f),  mm::Vec3(0.0f, 1.0f, -1.0f), mm::Vec3(0.0f, -1.0f, -1.0f),
    mm::Vec3(1.0f, 1.0f, 0.0f),  mm::Vec3(0.0f, -1.0f, 1.0f),  mm::Vec3(-1.0f, 1.0f, 0.0f), mm::Vec3(0.0f, -1.0f, -1.0f),
};

// Perlin's permutation, which ImprovedNoise's constructor copies twice
// (Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B80840))
static int s_permutation[256] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
    140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148,
    247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
    57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
    74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
    60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
    65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169,
    200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64,
    52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212,
    207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213,
    119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
    129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104,
    218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
    81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157,
    184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93,
    222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
};

namespace forcefield {

// the manager init makes (Proposed name, not the original's: the symbols leave it unnamed (lbl_71015EAE38))
static FfManager* s_pIns;

void FfManager::init() {
#line 22 PTLIB_FORCE_FIELD_PATH
    getPtr() = static_cast<FfManager*>(ParticleManager::sysAlloc(sizeof(FfManager), 16, __FILE__, __LINE__));
    if (getPtr() != nullptr) {
        new (getPtr()) FfManager;
    }
}

FfManager*& FfManager::getPtr() {
    return s_pIns;
}

void FfManager::term() {
    if (getPtr() != nullptr) {
        FfManager* pIns = getPtr();
        for (ForceList::iterator it = pIns->m_forces.begin(); it != pIns->m_forces.end(); ++it) {
            if (*it != nullptr) {
                ParticleManager::sysFree(*it);
            }
        }
        pIns->m_forces.clear();
        getPtr()->~FfManager();
        if (getPtr() != nullptr) {
            ParticleManager::sysFree(getPtr());
            getPtr() = nullptr;
        }
    }
}

void FfManager::update(float frame) {
    for (ForceList::iterator it = m_forces.begin(); it != m_forces.end();) {
        Force* pForce = *it;
        pForce->m_frame += (int)frame;
        if (pForce->m_param.m_life != -1 && pForce->m_param.m_life <= pForce->m_frame) {
            it = m_forces.erase(it);
            if (pForce != nullptr) {
                ParticleManager::sysFree(pForce);
            }
        } else {
            ++it;
        }
    }
}

void FfManager::addForce(const AddForceParam& param) {
#line 306 PTLIB_FORCE_FIELD_PATH
    Force* pForce = new (ParticleManager::sysAlloc(sizeof(Force), 16, __FILE__, __LINE__)) Force;
    if (pForce != nullptr) {
        pForce->m_param = param;
        if (pForce->m_param.m_life != -1) {
            pForce->m_param.m_life++;
        }
        pForce->m_frame = 0;
        m_forces.push_back(pForce);
        return;
    }
    efMsg("memory empty");
}

}  // namespace forcefield

void TurbulenceN::init() {
    s_fTotalTime = 0.0f;
}

void TurbulenceN::updateTime(float time) {
    s_fTotalTime += time;
}

// turb3d (0x7100859DFC) and ImprovedNoise::noise (0x7100859F9C) are not identical yet: session31/pforce/wip

ImprovedNoise::ImprovedNoise() {
    for (int i = 0; i < 256; i++) {
        p[256 + i] = p[i] = s_permutation[i];
    }
}

float TurbulenceN::s_fTotalTime;
ImprovedNoise TurbulenceN::s_noise;

}  // namespace ptlib
