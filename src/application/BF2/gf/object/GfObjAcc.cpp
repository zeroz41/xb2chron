#include "gf/GfObjAcc.h"
#include "gf/GfAlphaProperty.h"
#include "gf/MsgObjectAlpha.h"
#include "gf/GfObjInfo.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfComProperty.h"
#include "gf/GfObjAcc.h"
#include "gf/GfAlphaProperty.h"
#include "gf/MsgObjectAlpha.h"
#include "gf/GfObjInfo.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComModel.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfAppendHandles.h"
#include "classes/fw/ModelObject.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/fw/Framework.h"
#include "gf/GfDataEnemy.h"
#include "fw/Transform.h"

namespace gf {

GfObjAcc::GfObjAcc(GfObj* obj) {
    m_obj = obj;
    m_info = obj != nullptr ? GfObjManager::getObjInfo(obj->m_handle) : nullptr;
}

GfObjAcc::GfObjAcc(GF_OBJ_HANDLE* handle) {
    m_info = GfObjManager::getObjInfo(handle);
    if (m_info != nullptr) {
        m_obj = m_info->m_obj;
    } else {
        m_obj = nullptr;
    }
}

const fw::Transform& GfObjAcc::getWorldTransform() const {
    static fw::Transform s_transform;
    if (m_obj != nullptr) {
        if (GfComTransform* transform = m_obj->getComponent<GfComTransform>(0)) {
            return transform->m_frame->getWorldTransform();
        }
    }
    if (m_info == nullptr) {
        s_transform.position = mm::Vec3::zero;
        s_transform.rotation = mm::Quat::identity;
        return s_transform;
    }
    return m_info->m_transform;
}

const fw::Transform& GfObjAcc::getWorldTransformNoSync() const {
    static fw::Transform s_transform;
    if (m_obj != nullptr) {
        if (GfComTransform* transform = m_obj->getComponent<GfComTransform>(0)) {
            return transform->m_frame->m_worldTransform;
        }
    }
    if (m_info == nullptr) {
        s_transform.position = mm::Vec3::zero;
        s_transform.rotation = mm::Quat::identity;
        return s_transform;
    }
    return m_info->m_transform;
}

bool GfObjAcc::isValidTransform() const {
    if (m_obj != nullptr && m_obj->m_components[0] != nullptr) {
        return m_obj->m_components[0]->getRTTI()->isKindOf(&GfComTransform::m_rtti);
    }
    return false;
}

float GfObjAcc::getAlpha(OBJ_ALPHA kind) const {
    float alpha = 1.0f;
    if (m_obj != nullptr) {
        if (GfComProperty* property = m_obj->getComponent<GfComProperty>(5)) {
            if (property->m_alpha.get() != nullptr) {
                alpha = property->m_alpha->m_alpha[kind];
            }
        }
    }
    return alpha;
}

void GfObjAcc::setAlpha(OBJ_ALPHA kind, float alpha) {
    if (m_obj == nullptr) {
        return;
    }
    if (getAlpha(kind) != alpha) {
        MsgObjectAlpha msg(kind, alpha);
        m_obj->sendMessage(m_obj, msg);
        if (isAlphaChanged()) {
            if (GfObjManager* manager = GfObjManager::get()) {
                manager->addApplyParam(getHandle());
            }
        }
    }
}

bool GfObjAcc::isAlphaChanged() const {
    if (m_obj != nullptr) {
        if (GfComProperty* property = m_obj->getComponent<GfComProperty>(5)) {
            if (GfAlphaProperty* alpha = property->m_alpha.get()) {
                GfObjAcc parent(GfObjUtil::getParentObj(m_obj));
                if (parent.isAlphaChanged()) {
                    return true;
                }
                return alpha->m_changed;
            }
        }
    }
    return false;
}

void GfObjAcc::setAlphaEvent(float alpha) { setAlpha(static_cast<OBJ_ALPHA>(3), alpha); }

float GfObjAcc::getAlphaEvent() const { return getAlpha(static_cast<OBJ_ALPHA>(3)); }

void GfObjAcc::setAlphaEvtDisp(float alpha) { setAlpha(static_cast<OBJ_ALPHA>(5), alpha); }

void GfObjAcc::setAlphaCamera(float alpha) { setAlpha(static_cast<OBJ_ALPHA>(2), alpha); }

float GfObjAcc::getAlphaCamera() const { return getAlpha(static_cast<OBJ_ALPHA>(2)); }

void GfObjAcc::setAlphaLife(float alpha) { setAlpha(static_cast<OBJ_ALPHA>(4), alpha); }

float GfObjAcc::getAlphaLife() const { return getAlpha(static_cast<OBJ_ALPHA>(4)); }

void GfObjAcc::setAlphaNormal(float alpha) { setAlpha(static_cast<OBJ_ALPHA>(0), alpha); }

float GfObjAcc::getAlphaNormal() const { return getAlpha(static_cast<OBJ_ALPHA>(0)); }

float GfObjAcc::getAlpha() const {
    float alpha = 1.0f;
    if (m_obj != nullptr) {
        if (GfComProperty* property = m_obj->getComponent<GfComProperty>(5)) {
            if (property->m_alpha.get() != nullptr) {
                alpha = property->m_alpha->m_total;
                if (GfObj* parent = GfObjUtil::getParentObj(m_obj)) {
                    if (GfComProperty* parentProperty = parent->getComponent<GfComProperty>(5)) {
                        if (parentProperty->m_alpha.get() != nullptr) {
                            alpha *= parentProperty->m_alpha->m_total;
                            if (GfObj* grand = GfObjUtil::getParentObj(parent)) {
                                if (GfComProperty* grandProperty = grand->getComponent<GfComProperty>(5)) {
                                    if (grandProperty->m_alpha.get() != nullptr) {
                                        alpha *= grandProperty->m_alpha->m_total;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return alpha;
}

void GfObjAcc::applyAlpha() {
    if (m_obj != nullptr) {
        if (GfComModel* model = m_obj->getComponent<GfComModel>(1)) {
            if (model->m_model != nullptr) {
                if (ml::ScnObjModel* scn = model->m_model->getInterface()) {
                    scn->setAlpha(getAlpha());
                }
            }
        }
    }
}

ml::ScnObjModel* GfObjAcc::getScnModel() const {
    if (m_obj != nullptr) {
        if (GfComModel* model = m_obj->getComponent<GfComModel>(1)) {
            if (model->m_model != nullptr) {
                return model->m_model->getInterface();
            }
        }
    }
    return nullptr;
}

void GfObjAcc::setFrameSpeed(float speed) {
    if (ml::ScnObjModel* scn = getScnModel()) {
        scn->setFrameSpd(speed);
    }
}

void GfObjAcc::setCameraFade(bool on) { GfObjUtil::setFlag(m_info, 10, on); }

void GfObjAcc::setFlag(unsigned int flag, bool on) { GfObjUtil::setFlag(m_info, flag, on); }

bool GfObjAcc::testFlag(unsigned int flag) const { return GfObjUtil::testFlag(m_info, flag); }

bool GfObjAcc::isCameraFadeDisableForEvent() const { return GfObjUtil::testFlag(m_info, 11); }

void GfObjAcc::setCameraFadeDisableForEvent(bool on) { GfObjUtil::setFlag(m_info, 11, on); }

bool GfObjAcc::isCameraFadeDisableForBattle() const { return GfObjUtil::testFlag(m_info, 12); }

void GfObjAcc::setCameraFadeDisableForBattle(bool on) { GfObjUtil::setFlag(m_info, 12, on); }

bool GfObjAcc::hasParent() const {
    return m_obj != nullptr && GfObjUtil::getParentObj(m_obj) != nullptr;
}

void GfObjAcc::setDisp(OBJDISP disp, bool on) {
    if (m_obj == nullptr) {
        return;
    }
    if (((m_info->m_dispOff & disp) != 0) == on) {
        m_info->m_dispOff = on ? (m_info->m_dispOff & ~disp) : (m_info->m_dispOff | disp);
        GfObjUtil::setFlag(m_info, 1, true);
        mm::mtl::IntrusiveList<fw::UpdatableObject>& children = m_obj->m_children;
        for (mm::mtl::IntrusiveList<fw::UpdatableObject>::iterator it = children.begin(), end = children.end();
             it != end; ++it) {
            fw::UpdatableObject& child = *it;
            GfObj* obj = child.getRTTI()->isKindOf(&GfObj::m_rtti) ? static_cast<GfObj*>(&child) : nullptr;
            GfObjUtil::setFlag(GfObjManager::getObjInfo(obj->m_handle), 1, true);
        }
    }
    if (GfAppendHandles* handles = GfObjUtil::getExtraMountObject(getHandle())) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && handle != getHandle()) {
                GfObjAcc(handle).setDisp(static_cast<OBJDISP>(2), on);
            }
        }
    }
}

GfObj* GfObjAcc::getObj() const { return m_obj; }

GF_OBJ_HANDLE* GfObjAcc::getHandle() const {
    return m_info != nullptr ? m_info->m_handle : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

bool GfObjAcc::isDisp(OBJDISP disp) const {
    if (m_obj == nullptr) {
        return true;
    }
    if (disp == 0) {
        return m_info->m_dispOff == 0;
    }
    return (m_info->m_dispOff & disp) == 0;
}

bool GfObjAcc::isDispChanged() const {
    if (m_obj == nullptr) {
        return false;
    }
    GfObjAcc parent(GfObjUtil::getParentObj(m_obj));
    if (parent.isDispChanged()) {
        return true;
    }
    return testFlag(1);
}

void GfObjAcc::applyDisp() {
    if (m_obj == nullptr) {
        return;
    }
    bool disp = false;
    if (isDisp(static_cast<OBJDISP>(0))) {
        GfObj* parent = GfObjUtil::getParentObj(m_obj);
        disp = parent == nullptr || GfObjAcc(parent).isDisp(static_cast<OBJDISP>(0));
    }
    if (ml::ScnObjModel* scn = getScnModel()) {
        scn->setDisp(disp);
    }
    if (testFlag(1)) {
        setFlag(1, false);
    }
}

void GfObjAcc::setGpuClip(bool on) { GfObjUtil::setFlag(m_info, 3, on); }

void GfObjAcc::setModelScale(float scale) {
    if (m_obj == nullptr) {
        return;
    }
    m_info->m_modelScale = mm::Vec3(scale, scale, scale);
    if (GfComModel* model = m_obj->getComponent<GfComModel>(1)) {
        model->setModelScale(scale);
    }
}

const mm::Vec3& GfObjAcc::getModelScaleXYZ() const {
    return m_info != nullptr ? m_info->m_modelScale : mm::Vec3::unit;
}

float GfObjAcc::getModelScale() const { return getModelScaleXYZ().x; }

// empty in 3.0.1
void GfObjAcc::setGravity(bool on) {}

bool GfObjAcc::isReload() const {
    if (testFlag(5)) {
        return true;
    }
    return GfAssetManager::isReload(m_info->m_assetHandle);
}

bool GfObjAcc::isRebuild() const { return GfObjUtil::testFlag(m_info, 6); }

void GfObjAcc::setAttribute(unsigned int attribute) {
    if (m_obj != nullptr) {
        m_obj->pad_110 = attribute;
    }
}

unsigned int GfObjAcc::getAttribute() const {
    return m_obj != nullptr ? m_obj->pad_110 : 0;
}

bool GfObjAcc::isValidProperty() const {
    if (m_obj != nullptr && m_obj->m_components[5] != nullptr) {
        return m_obj->m_components[5]->getRTTI()->isKindOf(&GfComProperty::m_rtti);
    }
    return false;
}

bool GfObjAcc::isValidModel() const {
    if (m_obj != nullptr && m_obj->m_components[1] != nullptr) {
        return m_obj->m_components[1]->getRTTI()->isKindOf(&GfComModel::m_rtti);
    }
    return false;
}

bool GfObjAcc::isDestroy() const { return GfObjUtil::testFlag(m_info, 0); }

int GfObjAcc::getType() const { return m_obj != nullptr ? m_obj->m_type : 0; }

void GfObjAcc::setCalcCameraAlpha() { GfObjUtil::setFlag(m_info, 13, true); }

unsigned int GfObjAcc::getMultiBindUniqId() const {
    return m_info != nullptr ? m_info->m_multiBindUniqId : 0;
}

bool GfObjAcc::isMultiBindWaiting() const {
    if (m_info == nullptr || m_info->m_multiBindUniqId == 0) {
        return false;
    }
    return !GfObjManager::get()->isValidMultiBind(m_info->m_handle, m_info->m_multiBindUniqId);
}

GF_ASSET_HANDLE* GfObjAcc::getAssetHandle() const {
    return m_info != nullptr ? m_info->m_assetHandle : reinterpret_cast<GF_ASSET_HANDLE*>(-1);
}

void GfObjAcc::setUserData(GfObjUserData kind, unsigned long data) {
    if (m_info != nullptr) {
        m_info->m_userData[kind] = data;
    }
}

void* GfObjAcc::getUserData(GfObjUserData kind) const {
    return m_info != nullptr ? reinterpret_cast<void*>(m_info->m_userData[kind]) : nullptr;
}

unsigned int GfObjAcc::getDriverId() const { return getBdatId(); }

unsigned int GfObjAcc::getBladeId() const {
    GfObjSetup* setup = GfObjUtil::getObjSetup(getHandle());
    if (setup == nullptr) {
        return getBdatId();
    }
    int type = setup->m_createType;
    unsigned int id = getBdatId();
    if (type == 5) {
        return GfDataEnemy::getBladeID(id);
    }
    return id;
}

bool GfObjAcc::isEnemyBlade() const {
    GfObjSetup* setup = GfObjUtil::getObjSetup(getHandle());
    return setup != nullptr && setup->m_createType == 5;
}

unsigned int GfObjAcc::getEnArrangeId() const { return getBdatId(); }

unsigned int GfObjAcc::getEnRscId() const {
    if (m_obj == nullptr || m_obj->m_type != 5) {
        return 0;
    }
    GfObjSetup* setup = GfObjManager::getObjInfo(getHandle())->m_setup;
    GfObjSetupEnemy* enemy =
        setup->getRTTI()->isKindOf(&GfObjSetupEnemy::m_rtti) ? static_cast<GfObjSetupEnemy*>(setup) : nullptr;
    return enemy->m_bdatId;
}

unsigned int GfObjAcc::getPcWeaponId() const { return getBdatId(); }

bool GfObjAcc::isLoadedWaitOK() const {
    if (m_info != nullptr && m_info->m_subHandle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) &&
        GfObjUtil::isValid(m_info->m_subHandle) && !GfObjUtil::isUpdate(m_info->m_subHandle)) {
        return false;
    }
    if (testFlag(26)) {
        return false;
    }
    if (testFlag(8)) {
        return testFlag(9);
    }
    return true;
}

unsigned int GfObjAcc::getView() const { return m_info != nullptr ? m_info->m_view : 0; }

unsigned int GfObjAcc::getLayer() const { return m_obj != nullptr ? m_obj->m_updateBit : 4; }

bool GfObjAcc::isLayerPause() const { return fw::Framework::isLayerPause(getLayer()); }

mm::mtl::RTTI GfComponent::m_rtti("GfComponent", &fw::ComponentObject::m_rtti, nullptr);

}  // namespace gf
