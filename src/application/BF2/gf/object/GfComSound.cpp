#include "classes/mm/mtl/_ReslistBase.h"
#include "classes/mm/mtl/List.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundLayerManager.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfComSound.h"
#include "gf/GfGameUtil.h"
#include "gf/FileStaticVec3.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/UpdatableObject.h"
#include "fw/Message.h"
#include "gf/CallBackCache.h"
#include "gf/SoundVariable.h"
#include "string.h"

namespace gf {

GfComSound::~GfComSound() {}

void GfComSound::setup() {
    if (GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2)) {
        asmCom->m_callbacks[4].name = SOUND_CALLBACK_EVENT_NAME;
        asmCom->m_callbacks[4].delegate.set(this, &GfComSound::callbackAnim);
    } else if (GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2)) {
        evtAnim->m_callback.name = SOUND_CALLBACK_EVENT_NAME;
        evtAnim->m_callback.delegate.set(this, &GfComSound::callbackAnimForEvent);
    }
    m_flushDelegate.set(this, &GfComSound::flush);
    m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 0);
    int attribute = GfGameUtil::getObjAttribute(static_cast<GfObj*>(m_owner)->m_handle);
    m_variables.setVariable(getSoundVariableName(SoundVariable(1)), attribute);
    m_variables.setVariable(SND_VAR_WATER_THRESOULD_NAME, 10);
    m_variables.setVariable(getSoundVariableName(SoundVariable(4)), 0);
    m_variables.setVariable(getSoundVariableName(SoundVariable(2)), 0);
    m_variables.setVariable(getSoundVariableName(SoundVariable(3)), 0);
    m_isSetup = true;
}

void GfComSound::callbackAnim(GfComAsm* asmCom, const CallBackCache& cache) {
    callbackAnimImpl(cache);
}

void GfComSound::callbackAnimForEvent(GfComEvtAnim* evtAnim, const CallBackCache& cache) {
    callbackAnimImpl(cache);
}

void GfComSound::cleanup() {
    while (m_cache.m_size != 0) {
        eraseCache(m_cache.begin());
    }
    if (fw::SoundLayerManager* manager = mm::mtl::PtrSingleton<fw::SoundLayerManager>::get()) {
        if (m_inLayer) {
            unsigned int layer = getLayer();
            manager->m_layers[layer].remove(&m_layerNode);
            m_inLayer = false;
        }
    }
    m_isSetup = false;
}

bool GfComSound::stopSe(const char* name) {
    CacheIterator it = m_cache.begin();
    CacheIterator end = m_cache.end();
    while (it != end) {
        if (strcmp((*it).m_name.m_str, name) == 0) {
            eraseCache(it);
            return true;
        }
        ++it;
    }
    return false;
}

GfComSound::CacheIterator GfComSound::eraseCache(CacheIterator it) {
    fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get();
    if (sound != nullptr && sound->isValid((*it).m_handle)) {
        fw::SoundResSourceManager::stopSe((*it).m_handle, 0.05f);
    }
    if ((*it).m_type == 1) {
        m_owner->getComponent<GfComModel>(1)->destroyBoneReferenceFrame((*it).m_boneName.m_str);
    }
    return m_cache.erase(it);
}

void GfComSound::setAttributeVariable(int value) {
    m_variables.setVariable(getSoundVariableName(SoundVariable(1)), value);
}

int GfComSound::getAttributeVariable() const {
    int value;
    return m_variables.getVariable(getSoundVariableName(SoundVariable(1)), &value) ? value : 0;
}

void GfComSound::changeLayer(unsigned int prevLayer, unsigned int layer) {
    if (fw::SoundLayerManager* manager = mm::mtl::PtrSingleton<fw::SoundLayerManager>::get()) {
        if (m_inLayer) {
            manager->m_layers[prevLayer].remove(&m_layerNode);
            m_inLayer = false;
            manager->m_layers[layer].push_back(&m_layerNode);
            m_inLayer = true;
        }
    }
}

mm::mtl::RTTI GfComSound::m_rtti("GfComSound", &GfComponent::m_rtti, nullptr);

}  // namespace gf
