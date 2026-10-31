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
#include "layer/LayerBase.h"
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

void ModelObject::update() {
    if (m_active) {
        ReferenceFrame* frame = m_frame.get();
        if (frame != nullptr) {
            const mm::Mat44& mat = frame->m_worldMatrix;
            if (m_model != nullptr) {
                m_model->setMat(mat);
                if (m_addOffsetEnabled) {
                    m_model->getOffsetInfo(true) = m_addOffsetPos;
                }
            }
        }
    }
}

ml::ScnObjModel* ModelObject::getInterface() {
    return m_model;
}

bool ModelObject::isRender() const {
    return ml::ScnObjAccResMdlInfo(m_model).isGpuRender();
}

void ModelObject::setScale(float scale) {
    m_scale = scale;
    if (m_model != nullptr) {
        mm::Vec3 scl(scale, scale, scale);
        m_model->setScl(scl);
    }
}

VisibleObject::~VisibleObject() {
    ModelManager::get()->m_groups[m_layer].remove(this);
    if (m_gpuCheck != nullptr) {
        m_gpuCheck->release();
        m_gpuCheck = nullptr;
    }
}

void VisibleObject::update() {
    if (m_gpuCheck != nullptr && m_frame.get() != nullptr) {
        mm::Vec3 pos = m_frame->m_worldTransform.position;
        pos += m_offset;
        ml::ScnObjAccGpuCheck check(m_gpuCheck);
        check.setPos(pos, 10.0f);
    }
}

bool VisibleObject::isRender() const {
    if (m_gpuCheck == nullptr) {
        return false;
    }
    return ml::ScnObjAccGpuCheck(m_gpuCheck).isRender();
}

void MovieManager::open(mm::mtl::IAllocator* allocator, unsigned int layer) {
    if (m_movie != nullptr) {
        close();
    }
    m_layer = layer;
#line 33
    m_movie = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) CMovie;
    m_movie->initialize(FrameworkMemory::getAllocator(9));
    if (m_layer != 0) {
        ui::UIObjectAcc acc(m_layer);
        if (acc.m_object != nullptr) {
            m_pixelSize = acc.getOnMemoryPixelSize();
            acc.setDisp(false);
        }
    }
}

void MovieManager::close() {
    stop();
    if (m_movie != nullptr) {
        m_movie->finalize();
        if (m_movie != nullptr) {
            delete m_movie;
        }
        m_movie = nullptr;
    }
    if (m_layerObj != nullptr) {
        ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
        acc.resetModelTexture(0);
        acc.resetModelTexture(1);
        if (m_layer == 0) {
            if (m_layerObj != nullptr) {
                m_layerObj->release();
            }
            m_layer = 0;
        }
        m_layerObj = nullptr;
    }
    if (m_layer != 0) {
        ui::UIObjectAcc acc(m_layer);
        if (acc.m_object != nullptr) {
            acc.setTerm();
        }
        m_layer = 0;
    }
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

bool MovieManager::set_file(const char* file) {
    if (m_movie != nullptr) {
        if (m_movie->set_file(file) == 0) {
            return true;
        }
    }
    return false;
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
