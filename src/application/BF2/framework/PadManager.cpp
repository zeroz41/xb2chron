#include "fw/PadData.h"
#include "classes/ml/DevGraphCB.h"
#include "classes/ml/DevPad.h"
#include "classes/fw/PadManager.h"
#include "classes/fw/PadManager.h"
#include "classes/ml/DevPad.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/PadFilterStd.h"
#include "classes/fw/PadFilterStd.h"
#include "ml/MlMem.h"
#include "mm/mtl/FixStr.h"
#include "ctype.h"

namespace fw {

// the vibration files initVibData loads, by ml::DevPad vibration id (/bnvib/<name lowercased>.bnvib; id 0 is none).
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B42790)
static const char* s_vibNames[24] = {
    "INVALID",     "AUDIO_BAM_1", "AUDIO_BAM_2", "AUDIO_BOOM_1", "AUDIO_BOOM_2", "AUDIO_BOOM_3",
    "AUDIO_BUBOOM", "AUDIO_BUBUBU", "AUDIO_BUBU_1", "AUDIO_BUBU_2", "AUDIO_BU_1",  "AUDIO_BU_2",
    "AUDIO_BU_3",  "BEAT_20",     "BEAT_40",     "DAMPED_1",     "DAMPED_2",     "DAMPED_3",
    "DAMPED_FM_1", "DAMPED_FM_2", "DAMPED_LONG", "SIMPLE_1",     "SIMPLE_2",     "SIMPLE_3",
};

// the name of vibration id in table (the original keeps the table in .data, as a table read through a helper that
// takes it stays; the name is not the original's)
static inline const char* getVibName(const char** table, unsigned long id) {
    return table[id];
}

PadManager::~PadManager() {}

bool PadManager::finalize() {
    PadManager* manager = get();
    if (manager != nullptr && manager->m_controlPads[0].m_isConnect && manager->m_controlPads[0].m_padNo != -1) {
        ml::DevPad::stopVibration(manager->m_controlPads[0].m_padNo);
    }
    return true;
}

bool PadManager::isInitialized() const {
    return ml::DevPad::isInitialized() && ManagerObject::isInitialized();
}

const PadData& PadManager::getControlPadData(int padNo) {
    PadManager* manager = get();
    if (manager == nullptr) {
        return m_nullPad;
    }
    return manager->m_controlPads[padNo];
}

void PadManager::playVibration(const ml::PadVibrationInfo& info) {
    PadManager* manager = get();
    if (manager != nullptr && manager->m_controlPads[0].m_isConnect && manager->m_controlPads[0].m_padNo != -1) {
        ml::DevPad::playVibration(manager->m_controlPads[0].m_padNo, info);
    }
}

void PadManager::initVibData() {
    for (unsigned long id = 1; id < 24; ++id) {
        mm::mtl::FixStr<256> path;
        path.format("/bnvib/%s.bnvib", getVibName(s_vibNames, id));
        for (char *p = path.m_str, *end = path.m_str + path.m_nLen; p != end; ++p) {
            *p = tolower(*p);
        }
        CommonResource* resource = CommonResource::blockRequest(ml::MlMem::getDebugMem(), path.m_str, false);
        if (resource != nullptr) {
            if (resource->valid()) {
                void* data = resource->getAssetData();
                int size = resource->getAssetSize();
                ml::DevPad::loadVibration(id, data, size);
            }
            resource->release();
        }
    }
}

PadFilterStd::~PadFilterStd() {}

}  // namespace fw
