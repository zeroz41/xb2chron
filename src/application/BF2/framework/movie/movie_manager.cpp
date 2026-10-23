#include "classes/fw/ModelManager.h"
#include "classes/fw/ModelObject.h"
#include "classes/fw/VisibleObject.h"
#include "classes/fw/MovieManager.h"
#include "classes/ICMovie.h"
#include "classes/CMovieNX/CMovie.h"
#include "classes/CMovie.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/WorkCpu.h"
#include "ml/ScnObjAccResMdlInfo.h"
#include "ml/ScnObjAccGpuCheck.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccMemObj.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIObject.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "mtl/MemManager.h"
#include "ui/UIUtil.h"

namespace fw {

ModelManager::~ModelManager() {}

ModelObject::~ModelObject() {
    if (m_scn != nullptr) {
        if (m_model != nullptr) {
            m_scn->releaseItem(m_model);
            m_model = nullptr;
        }
        m_scn = nullptr;
    }
    ModelManager::get()->m_groups[m_layer].remove(this);
}

ml::ScnObjModel* ModelObject::getInterface() {
    return m_model;
}

bool ModelObject::isRender() const {
    return ml::ScnObjAccResMdlInfo(m_model).isGpuRender();
}

bool VisibleObject::isRender() const {
    if (m_gpuCheck == nullptr) {
        return false;
    }
    return ml::ScnObjAccGpuCheck(m_gpuCheck).isRender();
}

void MovieManager::stop() {
    if (m_movie != nullptr) {
        m_movie->stop();
    }
    m_playing = false;
}

void MovieManager::update() {
    ++m_frame;
    if (m_movie == nullptr) {
        return;
    }
    if (m_layerObj != nullptr) {
        layer::LayerAccMemObj memObj(m_layerObj);
        void* buffer = memObj.getMemBufer();
        unsigned int width = memObj.getMemWidth();
        unsigned int height = memObj.getMemHeight();
        m_movie->update(static_cast<unsigned char*>(buffer), width, height, m_pixelSize);
        memObj.updateMemBufer();
    } else if (m_layer != 0) {
        ui::UIObjectAcc acc(m_layer);
        if (acc.m_object != nullptr) {
            acc.setDisp(m_playing);
            short width;
            short height;
            acc.getSize(false, width, height);
            void* buffer = acc.getOnMemoryBuffer();
            m_movie->update(static_cast<unsigned char*>(buffer), width, height, m_pixelSize);
            acc.swapOnMemoryBuffer();
        }
    }
}

float MovieManager::get_length() {
    if (m_movie != nullptr) {
        return m_movie->get_length();
    }
    return 0.0f;
}

void MovieManager::play() {
    if (m_movie != nullptr) {
        m_movie->play();
        if (m_movie->isplaying()) {
            m_playing = true;
        }
    }
}

void MovieManager::pause() {
    if (m_movie != nullptr) {
        m_movie->pause();
    }
}

bool MovieManager::isstandby() {
    if (m_movie != nullptr) {
        return m_movie->isstandby();
    }
    return false;
}

bool MovieManager::ispause() {
    if (m_movie != nullptr) {
        return m_movie->ispause();
    }
    return false;
}

bool MovieManager::isplaying() {
    if (m_movie != nullptr) {
        return m_movie->isplaying();
    }
    return false;
}

void MovieManager::bkgHomeMenu(bool enter) {
    if (m_movie != nullptr) {
        m_movie->doHomeMenu(true);
        if (!enter) {
            m_movie->doHomeMenu(false);
        }
    }
}

MovieManager::~MovieManager() {
    if (m_movie != nullptr) {
        close();
    }
    ml::WorkCpu::removeBackgroundListener(this);
}

const char* MovieManager::getName() const {
    return "MovieManager";
}

}  // namespace fw
