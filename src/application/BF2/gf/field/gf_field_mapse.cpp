#include "mm/mtl/FixedVector.h"
#include "gf/SoundParam.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfFieldMapSe.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfSound.h"
#include "classes/fw/ModelObject.h"
#include "fw/UpdateInfo.h"
#include "ml/ScnObjAccSeamEtcPos.h"
#include "ml/ScnObjAccPartsEtcPos.h"
#include "mm/Mat44.h"
#include <algorithm>
#include <math.h>
#include <string.h>

namespace gf {

GfFieldMapSe::GfFieldMapSe() : m_objMax(0) {}

GfFieldMapSe::~GfFieldMapSe() {}

void GfFieldMapSe::destroy() {
    destroyMapSe();
}

inline void GfFieldMapSe::destroySeObj(SEOBJ* obj) {
    if (GfSound* sound = GfSound::get()) {
        sound->stopSe(obj->m_handle, 1.0f);
        m_seObjs.deallocate(obj);
    }
}

void GfFieldMapSe::destroyMapSe() {
    for (SEDATA*& data : m_datas) {
        for (SEOBJ* obj : data->m_objs) {
            destroySeObj(obj);
        }
        data->m_objs.clear();
        if (data != nullptr) {
            delete data;
            data = nullptr;
        }
    }
    m_datas.clear();
    m_objMax = 0;
}

void GfFieldMapSe::update(const fw::UpdateInfo& info) {
    updateSeObj(info);
}

void GfFieldMapSe::postUpdate(const fw::UpdateInfo& info) {}

void GfFieldMapSe::gevPause(unsigned int flags0, unsigned int flags1) {}

void GfFieldMapSe::gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag) {
    if (flag) {
        createMapSe();
    } else {
        destroyMapSe();
    }
}

void GfFieldMapSe::createMapSe() {
    destroyMapSe();
    fw::ModelObject* model = GfMapManager::getModelObject();
    if (model == nullptr) {
        return;
    }
    ml::ScnObjModel* scn = model->getInterface();
    if (scn == nullptr) {
        return;
    }
    ml::ScnObjAccSeamEtcPos acc(scn);
    m_objMax = acc.getObjMax();
    GfBdatRsc* bdat = GfBdatRsc::get();
    for (int i = 0; i < m_objMax; ++i) {
        ml::ScnObjAccPartsEtcPos obj = acc.getObj(i);
        unsigned int id = bdat->getFLD_actorSEStart();
        unsigned int end = bdat->getFLD_actorSEEnd();
        for (; id < end; ++id) {
            if (strcmp(obj.getObjName(), bdat->getFLD_actorSELOD(id)) == 0) {
#line 227
                SEDATA* data = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SEDATA(i, obj.getMatrixMax(), id);
                m_datas.push_back(data);
                break;
            }
        }
    }
}

float GfFieldMapSe::getVolume(const SEOBJ* obj) {
    GfBdatRsc* bdat = GfBdatRsc::get();
    float maxDist = bdat->getFLD_actorSEmax_volume_Dist(obj->m_seId);
    float minDist = bdat->getFLD_actorSEmin_volume_Dist(obj->m_seId);
    float volumeMax = bdat->getFLD_actorSEvolumeMAX(obj->m_seId) * 0.01f;
    float volumeMin = bdat->getFLD_actorSEvolumeMIN(obj->m_seId) * 0.01f;
    float dist = sqrtf(obj->m_second.m_dist);
    float volume;
    if (dist <= maxDist) {
        volume = volumeMax;
    } else if (dist >= minDist) {
        volume = volumeMin;
    } else {
        volume = volumeMin + (volumeMax - volumeMin) * (1.0f - (dist - maxDist) / (minDist - maxDist));
        if (volume < 0.0f) {
            volume = 0.0f;
        } else if (volume > 1.0f) {
            volume = 1.0f;
        }
    }
    return volume;
}

}  // namespace gf

// updateSeObjDataForActivate's std::sort (not written yet) instantiates the libc++ sort core for the sound list.
template void std::__sort<gf::GfFieldMapSe::DistCompare&, gf::GfFieldMapSe::SEOBJ**>(
    gf::GfFieldMapSe::SEOBJ**, gf::GfFieldMapSe::SEOBJ**, gf::GfFieldMapSe::DistCompare&);
