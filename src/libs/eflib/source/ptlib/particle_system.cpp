#define MM_LIB_FROM_EFLIB
#include "ptlib/ParticleSystem.h"
#include "ptlib/emitter/EmitterManager.h"
#include "ptlib/renderer/RendererManager.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/emitter/EmitterManager.h"
#include "ptlib/renderer/RendererManager.h"
#include "ptlib/material/MaterialManager.h"
#include "classes/ptlib/HeapAllocator.h"
#include "ptlib/math/KeyFrameIP.h"
#include "mm/MMStdBase.h"
#include <stdio.h>
#include <stdarg.h>

namespace ptlib {

// efAstMsg's, efMsg's and efWng's text (the name is not the original's: the symbols leave it unnamed)
static char s_message[0x1000];
// the line efAstMsg prints around its text (the name is not the original's)
static const char s_separator[] = "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_";

// the instance init makes (the name is not the original's: the symbols leave it unnamed)
static ParticleManager* s_pIns;
// the instance particle_hash.cpp's HashManager::init makes (the name is not the original's)
static HashManager* s_pHashIns;

ParticleManager*& ParticleManager::getPtr() {
    return s_pIns;
}

ParticleManager* ParticleManager::get() {
#line 40
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

void ParticleManager::emitter_pack_free(unsigned long pack) {
    emitter::EmitterManager::get()->emitter_pack_free(pack);
}

void ParticleManager::emitter_set_free(FxHeader* pHeader, int frames) {
    emitter::EmitterManager::get()->emitter_set_free(pHeader, frames);
}


void ParticleManager::emitter_alloc01_set_draw(emitter::EmitterObj* pObj, emitter::EmitterArg* pArg) {
    renderer::RenderManager::get()->setEmitterDraw(pObj, pArg);
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
