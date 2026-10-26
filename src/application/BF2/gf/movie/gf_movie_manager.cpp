#include "classes/fw/EffectManager.h"
#include "classes/fw/MovieManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComAnimation.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfMenuObjMovieLayer.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjUtil.h"
#include "gf/GfVolumeFade.h"

namespace gf {

GfVolumeFade::GfVolumeFade(GF_OBJ_HANDLE* handle, ml::ScnObjModel* model) : m_handle(handle), m_model(model) {
    initializeParam();
}

void GfVolumeFade::setEffectType(VFEFF type) {
    if (m_effectType == type) {
        return;
    }
    m_effectType = type;
    switch (type) {
    case 0:
        break;
    case 9:
        setupVolumeFadeParamForDead(m_params, type);
        break;
    default:
        setupVolumeFadeParamForDead(m_params, type);
        break;
    }
}

bool GfVolumeFade::setupVolumeFadeParamForDead(ml::VolumeFadeParams& params, VFEFF type) {
    unsigned int index = type;
    if (index < 32) {
        if (const fw::VolumeFadeParams* src = fw::EffectManager::get()->m_volumeFadeParams[index]) {
            copyVolumeFadeParams(params, *src);
            return true;
        }
        return false;
    }
    return false;
}

// the clamp is the original's integer selects only when written in place and the whole row stored through
// FixedArray::assign (which reads the ratio by reference); mm::clamp or a plain loop give fmin/fcsel
void GfVolumeFade::setFadeRatio(VFACC acc, VFPARTS parts, float ratio) {
    if (ratio < 0.0f) {
        ratio = 0.0f;
    } else if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    if (parts == VFPARTS(-1)) {
        m_ratio[acc].assign(ratio);
    } else {
        m_ratio[acc][parts] = ratio;
    }
    m_dirty = true;
    applyFadeRatio();
}

void GfVolumeFade::applyFadeRatio() {
    if (!GfObjUtil::isValid(m_handle)) {
        return;
    }
    if (!m_dirty) {
        return;
    }
    m_dirty = false;
    if (m_effectType == VFEFF(0)) {
        return;
    }
    ml::ScnObjAccVolumeFade acc(m_model);
    acc.getMax();
    for (int parts = 0; parts < 6; parts++) {
        float ratio = getFadeRatioForParts(VFPARTS(parts));
        acc.setParams(m_params, -1);
        if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
            if (GfComModel* model = obj->getComponent<GfComModel>(1)) {
                model->m_volumeFade.m_partsAlpha[parts] = 1.0f - ratio;
            }
        }
    }
}

float GfVolumeFade::getFadeRatio(VFACC acc, VFPARTS parts) const {
    if (parts == VFPARTS(-1)) {
        float sum = 0.0f;
        for (int i = 0; i < 6; i++) {
            sum += m_ratio[acc][i];
        }
        return sum / 6.0f;
    }
    return m_ratio[acc][parts];
}

float GfVolumeFade::getFadeRatioForParts(VFPARTS parts) const {
    float ratio = 1.0f;
    for (int acc = 0; acc < 5; acc++) {
        ratio *= getFadeRatio(VFACC(acc), parts);
    }
    return ratio;
}

void GfVolumeFade::setupKeyFrame(mm::mtl::FixedVector<VFKEYDATA, 4>& keys, VFEFF type) {
    keys.clear();
    const fw::VolumeFadeParams* src = fw::EffectManager::get()->getVolumeFadeParams(type);
    if (src == nullptr) {
        return;
    }
    int count;
    if (src->m_keyFrames[3] == 0.0f) {
        if (src->m_keyFrames[2] == 0.0f) {
            if (src->m_keyFrames[1] == 0.0f) {
                if (src->m_keyFrames[0] == 0.0f) {
                    return;
                }
                count = 1;
            } else {
                count = 2;
            }
        } else {
            count = 3;
        }
    } else {
        count = 4;
    }
    const float* frame = src->m_keyFrames;
    const float* fade = src->m_keyFades;
    for (int i = count; i != 0; frame++, fade++, i--) {
        VFKEYDATA key;
        key.m_time = *frame * GfInfo::m_fSecPerFrame;
        key.m_ratio = 1.0f - *fade;
        keys.push_back(key);
    }
}

void GfMovieManager::build(const GfSetupParam& param) {
#line 31
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMovieManager();
}

void GfMovieManager::destroy() {
    GfMovieManager* manager = get();
    fw::MovieManager::get()->close();
    delete manager;
}

void GfMovieManager::close() {
    fw::MovieManager::get()->close();
}

void GfMovieManager::open(mm::mtl::IAllocator* allocator) {
    ui::UIScreenObject::OnMemoryInfo info;
    info.m_modelTexture = 0;
    info.m_memType = 3;
    unsigned int layer = GfMenuObjMovieLayer::createMovieLayer(1280, 720, info);
    if (layer != 0) {
        fw::MovieManager::get()->open(allocator, layer);
    }
}

void GfMovieManager::open(mm::mtl::IAllocator* allocator, int width, int height) {
    ui::UIScreenObject::OnMemoryInfo info;
    info.m_modelTexture = 1;
    info.m_memType = 3;
    unsigned int layer = GfMenuObjMovieLayer::createMovieLayer(width, height, info);
    if (layer != 0) {
        fw::MovieManager::get()->open(allocator, width, height, layer);
    }
}

bool GfMovieManager::set_file(const char* file) {
    return fw::MovieManager::get()->set_file(file);
}

float GfMovieManager::get_length() {
    return fw::MovieManager::get()->get_length();
}

void GfMovieManager::play() {
    fw::MovieManager::get()->play();
}

void GfMovieManager::pause() {
    fw::MovieManager::get()->pause();
}

void GfMovieManager::stop() {
    fw::MovieManager::get()->stop();
}

bool GfMovieManager::isstandby() {
    return fw::MovieManager::get()->isstandby();
}

bool GfMovieManager::ispause() {
    return fw::MovieManager::get()->ispause();
}

bool GfMovieManager::isplaying() {
    return fw::MovieManager::get()->isplaying();
}

}  // namespace gf
