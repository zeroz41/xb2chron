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
#include "fw/UpdateInfo.h"

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

void PadManager::update(const UpdateInfo& info) {
    unsigned int padMax = ml::DevPad::getPadMax();
    for (unsigned int i = 0; i < padMax; i++) {
        if (m_activePads.test(i)) {
            unsigned int prevRawBtn = m_rawPads[i].m_btn;
            unsigned int prevBtn = m_pads[i].m_btn;
            makePadData(i);
            updatePadData(i, m_rawPads[i], prevRawBtn, m_rawWorks, info.m_frameTime);
            updatePadData(i, m_pads[i], prevBtn, m_works, info.m_frameTime);
        } else {
            m_rawPads[i].clear();
            m_pads[i].clear();
        }
    }
    updateControlPadNo(0);
    for (int i = 0; i < 12; i++) {
        if (m_controlPadNos[i] >= 0) {
            m_controlPads[i] = m_pads[m_controlPadNos[i]];
        } else {
            m_controlPads[i].clear();
        }
    }
    for (int i = 0; i < 12; i++) {
        if (m_rawControlPadNos[i] >= 0) {
            m_rawControlPads[i] = m_rawPads[m_rawControlPadNos[i]];
        } else {
            m_rawControlPads[i].clear();
        }
    }
}

void PadManager::makePadData(int padNo) {
    TUnk_B42870* filter = m_filters[padNo];
    float lx = ml::DevPad::getALX(padNo, false);
    float ly = ml::DevPad::getALY(padNo, false);
    float rx = ml::DevPad::getARX(padNo, false);
    float ry = ml::DevPad::getARY(padNo, false);
    unsigned int btn = ml::DevPad::getBtn(padNo);
    unsigned int down = ml::DevPad::getDown(padNo);
    unsigned int up = ml::DevPad::getUp(padNo);
    unsigned int dbl = ml::DevPad::getDbl(padNo);
    if (lx != lx) {
        lx = 0.0f;
    }
    if (ly != ly) {
        ly = 0.0f;
    }
    if (rx != rx) {
        rx = 0.0f;
    }
    if (ry != ry) {
        ry = 0.0f;
    }
    PadData& data = m_rawPads[padNo];
    data.m_btn = filter->filterBtn(btn);
    data.m_down = filter->filterBtn(down);
    data.m_up = filter->filterBtn(up);
    data.m_dbl = filter->filterBtn(dbl);
    data.m_lx = filter->filterALX(lx, ly);
    data.m_ly = filter->filterALY(lx, ly);
    data.m_rx = filter->filterARX(rx, ry);
    data.m_ry = filter->filterARY(rx, ry);
    replacePadData(padNo);
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
