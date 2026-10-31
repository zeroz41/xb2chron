#include "mm/mtl/FixedQueue.h"
#include "classes/ml/MicroThread.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/GfReqManager.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfInfo.h"
#include "gf/GfReqParam.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataBlade.h"
#include "gf/SDataBlade.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

inline void GfReqManager::initialize(const GfSetupParam& param) {
    m_group = ml::MicroThread::get()->createGroup();
    m_thread = ml::MicroThread::get()->createThread(m_group, fnReqUpdate, this);
#line 94
    m_smallCom = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfReqSmallCom();
    m_initialized = true;
}

GfReqManager::GfReqManager(const GfSetupParam& param)
    : m_group(reinterpret_cast<ml::MLTHG*>(-1)), m_thread(reinterpret_cast<ml::MLTH*>(-1)), m_smallCom(nullptr),
      m_terminate(false), m_initialized(false) {
    initialize(param);
}

GfReqManager::~GfReqManager() {}

void GfReqManager::build(const GfSetupParam& param) {
#line 54
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfReqManager(param);
}

void GfReqManager::destroy() {
    GfReqManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfReqManager::finalize() {
    while (m_thread != reinterpret_cast<ml::MLTH*>(-1)) {
        GfSleep(1);
    }
    if (m_group != reinterpret_cast<ml::MLTHG*>(-1)) {
        ml::MicroThread::get()->releaseGroup(m_group);
        m_group = reinterpret_cast<ml::MLTHG*>(-1);
    }
    while (GfReqSmallCom::isExistCommand()) {
        GfSleep(1);
    }
    if (m_smallCom != nullptr) {
        delete m_smallCom;
        m_smallCom = nullptr;
    }
    m_initialized = false;
}

nn::os::FiberType* GfReqManager::fnReqUpdate(void* arg) {
    GfReqManager* manager = get();
    manager->reqUpdate();
    manager->m_thread = reinterpret_cast<ml::MLTH*>(-1);
    ml::MicroThread::get()->exit();
    return nullptr;
}

void GfReqManager::update(const fw::UpdateInfo& info) {
    m_updateInfo = info;
    ml::MicroThread::get()->update(m_group);
    m_smallCom->update(info);
}

void GfReqManager::reqUpdate() {
    while (true) {
        if (m_commands.size() != 0) {
            Command& command = m_commands.front();
            command.m_func(command.m_param);
            if (command.m_param != nullptr) {
                delete command.m_param;
                command.m_param = nullptr;
            }
            m_commands.pop();
        } else if (GfManager::isDestroyNow()) {
            return;
        }
        GfSleep(1);
    }
}

unsigned int GfReqManager::addCommand(GfReqParam* param, void (*func)(const GfReqParam*)) {
    GfReqManager* manager = get();
    if (manager->m_terminate) {
        delete param;
        return static_cast<unsigned int>(-1);
    }
    unsigned int handle = manager->getHandle();
    Command command;
    command.m_param = param;
    command.m_func = func;
    command.m_handle = handle;
    manager->m_commands.push_back(command);
    return handle;
}

void GfReqManager::terminateCommand() {
    get()->m_terminate = true;
}

bool GfReqManager::isExistCommand(void (*func)(const GfReqParam*)) {
    GfReqManager* manager = get();
    if (manager == nullptr) {
        return false;
    }
    if (func == nullptr) {
        if (manager->m_commands.size() != 0) {
            return true;
        }
        return GfReqSmallCom::isExistCommand();
    } else {
        for (CommandQueue::iterator it = manager->m_commands.begin(); it != manager->m_commands.end(); ++it) {
            if ((*it).m_func == func) {
                return true;
            }
        }
    }
    return GfReqSmallCom::isExistCommand();
}

const fw::UpdateInfo& GfReqManager::getUpdateInfo() {
    return get()->m_updateInfo;
}

bool GfReqManager::isValid(unsigned int handle) {
    if (handle == static_cast<unsigned int>(-1)) {
        return false;
    }
    GfReqManager* manager = get();
    for (CommandQueue::iterator it = manager->m_commands.begin(); it != manager->m_commands.end(); ++it) {
        if ((*it).m_handle == handle) {
            return true;
        }
    }
    return false;
}

void RQ_SETUP_PARTY::getAllBlade(mm::mtl::FixedVector<unsigned int, 32>& blades) const {
    for (int i = 0; i < 10; i++) {
        int count = GfDataDriver::getMaxSetBladeNum(m_drivers[i].m_driver);
        for (int j = 0; j < count; j++) {
            unsigned int blade = m_drivers[i].m_blades[j];
            if (blade != 0) {
                blades.push_back(blade);
            }
        }
    }
}

void GfMapjumpInfo::setupForSaveData(unsigned int map, const mm::Vec3& pos, const mm::Vec3& rot, bool startChapter) {
    m_map = map;
    m_fromSaveData = true;
    float rotY = rot.y;
    m_pos = pos;
    m_rotY = rotY;
    m_setRotY = true;
    m_startChapter = startChapter;
    m_kind = 1;
}

void RQ_SETUP_PARTY::replaceActBlade() {
    // an act blade's common blade, its data copied from the act blade the first time (the name is not the original's)
    auto toCommon = [](unsigned int blade) -> unsigned int {
        unsigned int common = GfDataBlade::getActBlade2CommonBlade(blade);
        if (common == blade) {
            return blade;
        }
        SDataBlade* data = GfDataBlade::getSDataBlade(common);
        if (data->m_bladeId == 0) {
            *data = *GfDataBlade::getSDataBlade(blade);
            data->m_bladeId = common;
        }
        return common;
    };
    for (int i = 0; i < 2; i++) {
        if (m_extras[i].m_type == 4) {
            m_extras[i].m_id = toCommon(m_extras[i].m_id);
        }
    }
    for (Driver& driver : m_drivers) {
        for (unsigned short& blade : driver.m_blades) {
            blade = toCommon(blade);
        }
    }
    for (Driver& driver : m_drivers) {
        if (GfDataDriver::fn_710023F9A8(driver.m_driver)) {
            memset(driver.m_blades, 0, sizeof(driver.m_blades));
            driver.m_blades[0] = mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrDrDefBlade1(driver.m_driver);
            driver.m_activeIndex = 0;
        }
    }
}

RQ_SETUP_BLADE::RQ_SETUP_BLADE() : m_driver(0), m_activeBlade(0) {
    for (int i = 0; i < 5; i++) {
        m_blades[i] = 0;
    }
}

}  // namespace gf
