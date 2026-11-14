#define MM_LIB_FROM_EFLIB
#include "classes/effect/SystemManager.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/DrDrawWorkInfoEF.h"
#include "classes/ptlib/emitter/ComputeManager.h"
#include "ptlib/emitter/EmitterManager.h"
#include "ptlib/forcefield/FfManager.h"
#include "ptlib/renderer/RendererStream.h"
#include "ptlib/renderer/ScreenRenderManager.h"
#include "mm/MMStdBase.h"
#include "effect/SendParam.h"
#include "string.h"
#include <utility>

namespace effect {

// the one manager: create sets it, destroy clears it (proposed name, not the original's: the symbols leave it
// unnamed, lbl_71015E9D28)
static SystemManager* s_pIns;

SystemManager* SystemManager::get() {
#line 64
    MM_ASSERT(getPtr());
    return getPtr();
}

SystemManager*& SystemManager::getPtr() {
    return s_pIns;
}

bool SystemManager::isValid() {
    if (getPtr() != nullptr && getPtr()->m_clearAllCount == 0) {
        return true;
    }
    return false;
}

SystemManager::~SystemManager() {
    m_commands[0].clear();
    m_commands[1].clear();
    m_addForces.clear();
}

SystemManager* SystemManager::create(const ptlib::DrDrawWorkInfoEF* info) {
#line 551
    getPtr() = static_cast<SystemManager*>(ptlib::ParticleManager::sysAlloc(sizeof(SystemManager), 16, __FILE__, __LINE__));
    new (getPtr()) SystemManager;
    if (getPtr() == nullptr) {
        ptlib::efAstMsg("0", "task create error!!");
        return nullptr;
    }
    ptlib::ParticleManager::init(info);
    return getPtr();
}

void SystemManager::destroy() {
    SystemManager* sys = getPtr();
    if (sys != nullptr) {
        ptlib::ParticleManager::get()->term();
        sys->m_destroyFlag = false;
        getPtr()->~SystemManager();
        if (getPtr() != nullptr) {
            ptlib::ParticleManager::sysFree(getPtr());
            getPtr() = nullptr;
        }
    }
    ptlib::screen::ScreenRenderManager::term();
}

void SystemManager::setUserFuncClear() {
    ptlib::ParticleManager::setUserAllocFunc(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    ptlib::ParticleManager::setUserFileFunc(nullptr, nullptr);
    ptlib::ParticleManager::setUserOutputString(nullptr, nullptr);
    ptlib::ParticleManager::setUserDrFunc(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                                          nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

void SystemManager::setUserAllocFunc(void* (*alloc)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                     void (*free)(void*, void*),
                                     void* (*alloc2)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                     void (*free2)(void*, void*), mtl::ALLOC_HANDLE (*handle)(),
                                     mtl::ALLOC_HANDLE (*handle2)()) {
    ptlib::ParticleManager::setUserAllocFunc(alloc, free, alloc2, free2, handle, handle2);
}

void SystemManager::setUserFileFunc(void* (*load)(const char*, int&), void (*release)(void*)) {
    ptlib::ParticleManager::setUserFileFunc(load, release);
}

void SystemManager::setUserOutputString(void (*print)(const char*), void (*warn)(const char*)) {
    ptlib::ParticleManager::setUserOutputString(print, warn);
}

void SystemManager::setUserDrFunc(void* (*a)(const void*, const char*, int, const void*, int), void (*b)(void*),
                                  void* (*c)(unsigned int, int), void (*d)(unsigned int, void*),
                                  void (*e)(void*, void*), void (*f)(void*, void*), void (*g)(void*, void*),
                                  void (*h)(void*, float), void (*i)(void*, void*),
                                  void (*j)(unsigned int, void*, void*), void (*k)(unsigned int, void*, void*),
                                  void (*l)(unsigned int, void*, void*), void (*m)(void*), void* (*n)(int, int),
                                  void (*o)(void*)) {
    ptlib::ParticleManager::setUserDrFunc(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o);
}

void SystemManager::setDisableCollision(bool flag) {
    ptlib::ParticleManager::get()->m_initFlags[1] = flag;
}

// reads no member: the callers pass `this` as whatever x0 holds (LLVM's dead-argument pass)
void SystemManager::updateCam(const ptlib::DrDrawWorkInfoEF* info) {
    if (info == nullptr) {
        return;
    }
    ptlib::CamParam* cam = ptlib::ParticleManager::get()->getCamParam();
    cam->m_viewMtx = info->m_viewMtx;
    cam->m_cameraMtx = info->m_cameraMtx;
    cam->m_view = info->m_view;
    cam->m_viewProjMtx.mulSafe(info->m_viewMtx, info->m_projMtx);
    mm::Mat34& bill = cam->m_billboard;
    bill = mm::Mat34::identity;
    bill.m[0][0] = info->m_cameraMtx.m[0][0];
    bill.m[0][1] = info->m_cameraMtx.m[0][1];
    bill.m[0][2] = info->m_cameraMtx.m[0][2];
    bill.m[1][0] = info->m_cameraMtx.m[1][0];
    bill.m[1][1] = info->m_cameraMtx.m[1][1];
    bill.m[1][2] = info->m_cameraMtx.m[1][2];
    std::swap(bill.m[0][1], bill.m[1][0]);
    std::swap(bill.m[0][2], bill.m[2][0]);
    std::swap(bill.m[1][2], bill.m[2][1]);
    // the eye goes in as a copy: the original loads it before the target and sums x*x + z*z in that order
    mm::Vec3 dir = info->m_target - mm::Vec3(info->m_eye);
    float length = dir.length();
    if (length <= 1e-6f) {
        dir = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        dir.x = scale * dir.x;
        dir.y = scale * dir.y;
        dir.z = scale * dir.z;
    }
    cam->m_pitch = ::atan2f(dir.y, ::sqrtf(dir.x * dir.x + dir.z * dir.z));
    cam->m_yaw = -::atan2f(dir.x, -dir.z);
    cam->m_height = info->m_cameraMtx.m[3][1];
}

void SystemManager::MainLoop(const ptlib::DrDrawWorkInfoEF* info) {
    if (info->m_view == 0) {
        m_frameCount++;
    }
    updateCam(info);
    if (info->m_view == 0) {
        es_command_core();
    }
    ptlib::ParticleManager::get()->move();
    if (info->m_view == 0 && m_clearAllCount >= 3) {
        m_commands[0].clear();
        m_commands[1].clear();
        ptlib::ParticleManager::get()->emitter_set_free_all(m_clearAllFlag);
        m_clearAllFlag = false;
        m_clearAllCount = 0;
    }
    ptlib::emitter::ComputeManager::getPtr()->resetUpdate();
}

void SystemManager::es_pause(bool pause) {
    Command command;
    command.m_type = 1;
    command.m_handle = pause;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void* SystemManager::es_pack_regist(void* data, unsigned int size) {
    Command command;
    command.m_type = 21;
    command.m_data = reinterpret_cast<unsigned long>(data);
    command.m_handle = size;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return data;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < commands.capacity()) {
        commands.push_back(command);
    }
    return data;
}

void SystemManager::es_pack_free(unsigned long pack) {
    Command command;
    command.m_type = 22;
    command.m_data = pack;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < commands.capacity()) {
        commands.push_back(command);
    }
}

void* SystemManager::es_regist(void* data, unsigned int size) {
    Command command;
    command.m_type = 20;
    command.m_data = reinterpret_cast<unsigned long>(data);
    command.m_handle = size;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return data;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < commands.capacity()) {
        commands.push_back(command);
    }
    return data;
}

void SystemManager::es_free(void* handle) {
    if (handle != nullptr) {
        ptlib::ParticleManager::get()->emitter_set_free(static_cast<ptlib::FxHeader*>(handle), 0);
    }
}

unsigned int SystemManager::es_create(void* efb, bool flag) {
    if (efb == nullptr) {
        return 0;
    }
    unsigned int handle = ptlib::HashManager::get()->get_create_key();
    Command command;
    command.m_type = 2;
    command.m_data = reinterpret_cast<unsigned long>(efb);
    command.m_handle = handle;
    command.m_flag = flag;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return handle;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < commands.capacity()) {
        commands.push_back(command);
    }
    return handle;
}

void SystemManager::es_set_param_pos_only(unsigned int handle, const SendParam* param) {
    Command command;
    command.m_type = 6;
    command.m_data = 0;
    command.m_handle = handle;
    command.m_param = *param;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void SystemManager::es_set_param_pos_only2(unsigned int handle, const SendParam* param) {
    Command command;
    command.m_type = 7;
    command.m_data = 0;
    command.m_handle = handle;
    command.m_param = *param;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void SystemManager::es_set_category(unsigned int handle, unsigned int category) {
    Command command;
    command.m_type = 18;
    command.m_data = 0;
    command.m_handle = handle;
    command.m_param.m_category = category;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void SystemManager::es_set_param(unsigned int handle, const SendParam* param) {
    Command command;
    command.m_type = 9;
    command.m_data = 0;
    command.m_handle = handle;
    command.m_param = *param;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void SystemManager::es_set_alpha(unsigned int handle, float alpha) {
    Command command;
    command.m_type = 13;
    command.m_data = 0;
    command.m_handle = handle;
    command.m_param.m_color[3] = alpha;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void SystemManager::es_set_viewnum(unsigned int handle, int viewnum) {
    Command command;
    command.m_type = 14;
    command.m_data = 0;
    command.m_handle = handle;
    command.m_param.m_flagB = viewnum;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

unsigned int SystemManager::es_create(void* efb, const SendParam* param, bool flag) {
    if (efb == nullptr) {
        return 0;
    }
    unsigned int handle = ptlib::HashManager::get()->get_create_key();
    Command command;
    command.m_type = 3;
    command.m_data = reinterpret_cast<unsigned long>(efb);
    command.m_handle = handle;
    command.m_flag = flag;
    command.m_param = *param;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return handle;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < commands.capacity()) {
        commands.push_back(command);
    }
    return handle;
}

void SystemManager::es_set_param_cas(unsigned int handle, const IEffectCallBack* cas, const char* name, int type,
                                     float rate, int flag) {
    Command command;
    command.m_type = 12;
    command.m_handle = handle;
    command.m_cas.m_cas = cas;
    if (name != nullptr) {
        command.m_cas.m_info.m_hasName = true;
        strcpy(command.m_cas.m_name, name);
    } else {
        command.m_cas.m_info.m_hasName = false;
    }
    command.m_cas.m_info.m_type = type;
    command.m_cas.m_info.m_flag = flag;
    command.m_cas.m_rate = rate;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void SystemManager::es_set_disp(unsigned int handle, int disp) {
    Command command;
    command.m_type = 16;
    command.m_data = 0;
    command.m_handle = handle;
    command.m_disp = disp;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < 1024) {
        commands.push_back(command);
    } else {
        ptlib::efWng("command buffer over > 1024");
    }
}

void SystemManager::es_fade_core(void* instance, unsigned int handle, int frames) {
    if (instance == nullptr && handle == 0) {
        return;
    }
    Command command;
    command.m_type = 19;
    command.m_data = reinterpret_cast<unsigned long>(instance);
    command.m_handle = handle;
    command.m_cas.m_cas = nullptr;
    command.m_cas.m_frames = frames;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < commands.capacity()) {
        commands.push_back(command);
    }
}

void SystemManager::es_remove_cas(void* cas) {
    if (cas == nullptr) {
        return;
    }
    Command command;
    command.m_type = 19;
    command.m_data = 0;
    command.m_handle = 0;
    command.m_cas.m_cas = cas;
    command.m_cas.m_frames = -1;
    if (m_clearAllCount != 0) {
        ptlib::efMsg("addCommandError!!");
        return;
    }
    mm::mtl::FixedVector<Command, 1152>& commands = m_writeSide == 0 ? m_commands[0] : m_commands[1];
    if (commands.size() < commands.capacity()) {
        commands.push_back(command);
    }
}

int SystemManager::es_getDeadFlag(unsigned int handle) {
    if (ptlib::HashManager::getPtr() == nullptr) {
        return -1;
    }
    return ptlib::HashManager::getPtr()->searchDead(handle);
}

bool SystemManager::es_is_loop(void* data) const {
    return static_cast<ptlib::FxHeader*>(data)->m_loop != 0;
}

bool SystemManager::es_contais_cam_axis(void* data) {
    return static_cast<ptlib::FxHeader*>(data)->m_containsCamAxis != 0;
}

void SystemManager::es_clearall(bool flag) {
    if (m_clearAllCount == 0) {
        m_clearAllCount = 1;
    }
    m_clearAllFlag = flag;
}

void SystemManager::setGlobalSpeed(float speed) {
    m_globalSpeed[m_writeSide == 0] = speed;
}

void SystemManager::setCategorySpd(unsigned int category, float speed) {
    ptlib::emitter::EmitterManager::getPtr()->m_categorySpeed[category] = speed;
}

void SystemManager::begin() {
    ptlib::renderer::EffStateManager::get()->begin();
}

void SystemManager::end() {}

void SystemManager::apply(const ptlib::DrDrawWorkInfoEF* info) {
    if (m_enableUpdate) {
        MainLoop(info);
    }
}

void SystemManager::opacityRender(const ptlib::DrDrawWorkInfoEF* info) {}

void SystemManager::alphaRender(const ptlib::DrDrawWorkInfoEF* info) {
    if (m_enableAlphaRender) {
        ptlib::ParticleManager::get()->setDrInfo(info);
        updateCam(info);
        ptlib::emitter::ComputeManager::getPtr()->update(info->m_view);
        int view = info->m_view;  // read before ParticleManager::get, as the original does
        ptlib::ParticleManager::get()->draw(info, view, false);
    }
}

void SystemManager::lastRender(const ptlib::DrDrawWorkInfoEF* info) {}

void SystemManager::finalRender(const ptlib::DrDrawWorkInfoEF* info) {
    testRender(info);
}

void SystemManager::blurRender(const ptlib::DrDrawWorkInfoEF* info) {
    if (info->m_view == 0) {
        updateCam(info);
        int view = info->m_view;
        ptlib::ParticleManager::get()->draw(info, view, true);
    }
}

void SystemManager::moveMain() {
    // the original passes nothing it sets: the call goes out with whatever s0 holds
    float delta;
    testUpdate(delta);
}

void SystemManager::updateKizunaPos(int index, KizunaWork& work) {
    ptlib::emitter::EmitterManager* manager = ptlib::emitter::EmitterManager::getPtr();
    if (manager == nullptr) {
        return;
    }
    KizunaWork& dst = *(manager->m_kizunaWorks[manager->m_flip] + index);
    for (int i = 0; i < 20; i++) {
        dst.m_points[i] = work.m_points[i];
    }
    dst.pad_154 = work.pad_154;
    dst.pad_158 = work.pad_158;
    dst.pad_15c = work.pad_15c;
    dst.pad_160 = work.pad_160;
    float scrollA = dst.m_scrollA + work.m_scrollA;
    if (scrollA > 100.0f) {
        scrollA -= 100.0f;
    }
    if (scrollA < -100.0f) {
        scrollA += 100.0f;
    }
    dst.m_scrollA = scrollA;
    float scrollB = dst.m_scrollB + work.m_scrollB;
    if (scrollB > 100.0f) {
        scrollB -= 100.0f;
    }
    if (scrollB < -100.0f) {
        scrollB += 100.0f;
    }
    dst.m_scrollB = scrollB;
    dst.pad_16c = work.pad_16c;
    for (int i = 0; i < 4; i++) {
        dst.pad_148[i][0] = work.pad_148[i][0];
    }
    for (int i = 0; i < 4; i++) {
        dst.pad_148[i][1] = work.pad_148[i][1];
    }
    dst.pad_150 = work.pad_150;
    dst.pad_140 = work.pad_140;
    dst.pad_151 = work.pad_151;
    dst.pad_152 = work.pad_152;
}

}  // namespace effect
