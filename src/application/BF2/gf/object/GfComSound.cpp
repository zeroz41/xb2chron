#include "classes/mm/mtl/_ReslistBase.h"
#include "classes/mm/mtl/List.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundLayerManager.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfComSound.h"
#include "gf/GfGameUtil.h"
#include "gf/GfObjUtil.h"
#include "gf/FileStaticVec3.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/UpdatableObject.h"
#include "fw/Message.h"
#include "gf/CallBackCache.h"
#include "gf/SoundVariable.h"
#include "classes/gf/GfComProperty.h"
#include "gf/GfEnvProperty.h"
#include "fw/SoundResTrigger.h"
#include "string.h"

namespace gf {

GfComSound::GfComSound()
    : m_cache(getAllocator(ALLOCATOR(0)), 16), m_triggerFilter(nullptr), m_isSetup(false), m_pViewer(nullptr) {
    m_viewerListener.m_pOwner = this;
}

GfComSound::~GfComSound() {}

void GfComSound::setup() {
    if (GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2)) {
        asmCom->m_callbacks[4].name = SOUND_CALLBACK_EVENT_NAME;
        asmCom->m_callbacks[4].delegate.set(this, &GfComSound::callbackAnim);
    } else if (GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2)) {
        evtAnim->m_asm.m_callbacks[4].name = SOUND_CALLBACK_EVENT_NAME;
        evtAnim->m_asm.m_callbacks[4].delegate.set(this, &GfComSound::callbackAnimForEvent);
    }
    m_soundUpdater.m_delegate.set(this, &GfComSound::flush);
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
        if (m_soundUpdater.m_linked) {
            unsigned int layer = getLayer();
            manager->m_layers[layer].remove(&m_soundUpdater);
            m_soundUpdater.m_linked = false;
        }
    }
    m_isSetup = false;
}

unsigned int GfComSound::flush() {
    flushVariables();
    if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
        CacheIterator end = m_cache.end();
        for (CacheIterator it = m_cache.begin(); it != end;) {
            if (sound->isValid((*it).m_handle)) {
                ++it;
            } else {
                it = m_cache.erase(it);
            }
        }
        end = m_cache.end();
        for (CacheIterator it = m_cache.begin(); it != end; ++it) {
            SoundInfo& info = *it;
            if (info.m_frame.get() != nullptr && info.m_follow) {
                GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
                mm::Vec3 pos;
                transform->getFrame()->getWorldTransform().rotation.rotate(pos, info.m_offset);
                pos += info.m_frame->getWorldTransform().position;
                sound->setPos(info.m_handle, pos);
                if (!sound->isLoop(info.m_handle)) {
                    info.m_follow = false;
                }
            }
        }
    }
    return m_cache.m_size;
}

bool GfComSound::playSe(const char* name, float volume, const mm::Vec3& offset, bool withoutSlow) {
    if (!m_isSetup || GfObjUtil::isGhost(static_cast<GfObj*>(m_owner)->m_handle)) {
        return false;
    }
    fw::SoundCategory category = fw::SoundCategory(
        withoutSlow ? GfObjUtil::getSoundCategoryWithoutSlow(static_cast<GfObj*>(m_owner)->m_handle)
                    : GfObjUtil::getSoundCategoryNormal(static_cast<GfObj*>(m_owner)->m_handle));
    unsigned int handle = fw::SoundResSourceManager::playSe(name, volume, m_variables, category, m_customInfoCallback);
    if (handle == 0) {
        return false;
    }
    SoundInfo info;
    info.m_handle = handle;
    info.m_name = name;
    info.m_frame = m_owner->getComponent<GfComTransform>(0)->getFrame();
    info.m_type = 0;
    info.m_offset = offset;
    m_cache.push_back(info);
    if (fw::SoundLayerManager* manager = mm::mtl::PtrSingleton<fw::SoundLayerManager>::get()) {
        if (!m_soundUpdater.m_linked) {
            unsigned int layer = getLayer();
            manager->m_layers[layer].push_back(&m_soundUpdater);
            m_soundUpdater.m_linked = true;
        }
    }
    return true;
}

bool GfComSound::playSeBone(const char* name, const char* bone, float volume, const mm::Vec3& offset, bool withoutSlow) {
    if (!m_isSetup || GfObjUtil::isGhost(static_cast<GfObj*>(m_owner)->m_handle)) {
        return false;
    }
    fw::SoundCategory category = fw::SoundCategory(
        withoutSlow ? GfObjUtil::getSoundCategoryWithoutSlow(static_cast<GfObj*>(m_owner)->m_handle)
                    : GfObjUtil::getSoundCategoryNormal(static_cast<GfObj*>(m_owner)->m_handle));
    unsigned int handle = fw::SoundResSourceManager::playSe(name, volume, m_variables, category, m_customInfoCallback);
    if (handle == 0) {
        return false;
    }
    SoundInfo info;
    info.m_handle = handle;
    info.m_name = name;
    info.m_frame = m_owner->getComponent<GfComModel>(1)->createBoneReferenceFrame(bone);
    info.m_type = 1;
    info.m_boneName = bone;
    info.m_offset = offset;
    m_cache.push_back(info);
    if (fw::SoundLayerManager* manager = mm::mtl::PtrSingleton<fw::SoundLayerManager>::get()) {
        if (!m_soundUpdater.m_linked) {
            unsigned int layer = getLayer();
            manager->m_layers[layer].push_back(&m_soundUpdater);
            m_soundUpdater.m_linked = true;
        }
    }
    return true;
}

bool GfComSound::playSe2D(const char* name, float volume, bool withoutSlow, bool keep) {
    bool played = false;
    if (m_isSetup && !GfObjUtil::isGhost(static_cast<GfObj*>(m_owner)->m_handle)) {
        fw::SoundCategory category = fw::SoundCategory(
            withoutSlow ? GfObjUtil::getSoundCategoryWithoutSlow(static_cast<GfObj*>(m_owner)->m_handle)
                        : GfObjUtil::getSoundCategoryNormal(static_cast<GfObj*>(m_owner)->m_handle));
        unsigned int handle = 0;
        if (const char* dlcName = GfGameUtil::getDlcSeName(name)) {
            fw::SoundPack* pack = GfGameUtil::getDlcSePack(dlcName);
            if (pack == nullptr) {
                return false;
            }
            if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
                handle = sound->playSe(dlcName, pack, volume, category);
            }
        } else {
            handle = fw::SoundResSourceManager::playSe(name, volume, m_variables, category, m_customInfoCallback);
        }
        played = handle != 0;
        if (handle == 0 || !keep) {
            return played;
        }
        SoundInfo info;
        info.m_handle = handle;
        info.m_name = name;
        info.m_type = 2;
        info.m_follow = false;
        m_cache.push_back(info);
    }
    return played;
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
        if (m_soundUpdater.m_linked) {
            manager->m_layers[prevLayer].remove(&m_soundUpdater);
            m_soundUpdater.m_linked = false;
            manager->m_layers[layer].push_back(&m_soundUpdater);
            m_soundUpdater.m_linked = true;
        }
    }
}

void GfComSound::flushVariables() {
    GfComProperty* property = m_owner->getComponent<GfComProperty>(5);
    if (property == nullptr) {
        return;
    }
    GfEnvProperty* env = property->m_env.get();
    if (env == nullptr) {
        return;
    }
    if (env->m_flags & 1) {
        int threshold = 0;
        m_variables.getVariable(SND_VAR_WATER_THRESOULD_NAME, &threshold);
        float level = threshold * 0.01f;
        m_variables.setVariable(getSoundVariableName(SoundVariable(3)), env->m_water.m_level < level ? 0 : 1);
        unsigned int material = env->m_water.m_material;
        if (material == 11) {
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 11);
        } else {
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 10);
        }
        return;
    }
    if (env->isGround(0)) {
        switch (env->m_grounds[0].m_material) {
        case 2:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 6);
            return;
        case 3:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 3);
            return;
        case 4:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 2);
            return;
        case 5:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 1);
            return;
        case 6:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 4);
            return;
        case 7:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 7);
            return;
        case 8:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 5);
            return;
        case 9:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 9);
            return;
        case 10:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 8);
            return;
        case 12:
            m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 12);
            return;
        }
    }
    m_variables.setVariable(getSoundVariableName(SoundVariable(0)), 0);
}

void GfComSound::callbackAnimImpl(const CallBackCache& cache) {
    if (cache.m_event->m_type != 4) {
        return;
    }
    const fw::ResSoundTriggerInfo* info = static_cast<const fw::ResSoundTriggerInfo*>(cache.m_event->m_data);
    if (m_triggerFilter != nullptr && !m_triggerFilter(this, *info)) {
        return;
    }
    if (info->m_kind == 0) {
        if (info->m_playType == 0) {
            playSe(info->m_seName, info->m_volume, info->m_offset, false);
        } else if (info->m_playType == 1) {
            playSeBone(info->m_seName, info->m_boneName, info->m_volume, info->m_offset, false);
        } else if (info->m_playType == 2) {
            playSe2D(info->m_seName, info->m_volume, false, false);
        }
    } else if (info->m_kind == 1) {
        stopSe(info->m_seName);
    }
}

bool GfComSound::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    bool result = false;
    if (msg.m_id != 0x100004B) {
        if (msg.m_id == 0x1000003) {
            result = true;
        }
    } else {
        if (fw::SoundLayerManager* manager = mm::mtl::PtrSingleton<fw::SoundLayerManager>::get()) {
            if (!m_soundUpdater.m_linked) {
                unsigned int layer = getLayer();
                manager->m_layers[layer].push_back(&m_soundUpdater);
                m_soundUpdater.m_linked = true;
            }
        }
        result = true;
    }
    return result;
}
}  // namespace gf

namespace gf {

mm::mtl::RTTI GfComSound::m_rtti("GfComSound", &GfComponent::m_rtti, nullptr);

}  // namespace gf
