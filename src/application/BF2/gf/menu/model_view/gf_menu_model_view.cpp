#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfMenuModelView.h"
#include "classes/gf/GfComModel.h"
#include "gf/GfObjFactory.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectPoint.h"
#include "classes/gf/GfMenuModelView.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectPack.h"
#include "classes/fw/EffectPoint.h"
#include "classes/fw/ModelObject.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/RenderResource.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/EffectCaster.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfInitParamUiObj.h"
#include "classes/gf/GfMenuModelViewCamera.h"
#include "classes/gf/GimmickCamera.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjFactory.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ml/ScnObjAccVolumeFade.h"
#include "mm/mtl/Vector.h"

namespace gf {

GfMenuModelView::~GfMenuModelView() {
}

fw::Transform& GfMenuModelView::getObjectTransformLocal(GF_OBJ_HANDLE* handle) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EA7130)
    static fw::Transform s_transform;
    GfObjAcc acc(handle);
    if (GfComTransform* transform = acc.getObj()->getComponent<GfComTransform>(0)) {
        return transform->getFrame()->getLocalTransformForWrite();
    }
    return s_transform;
}

void GfMenuModelView::setVanishRatio(GF_OBJ_HANDLE* handle, float ratio) {
    GfObjAcc acc(handle);
    if (GfComModel* model = acc.getObj()->getComponent<GfComModel>(1)) {
        if (model->m_model != nullptr) {
            ml::ScnObjAccVolumeFade fade(model->m_model->getInterface());
            fade.setRatio(ratio, -1);
        }
    }
}

void GfMenuModelView::addMapObjObject(unsigned int index) {
    if (m_objs.size() == 16) {
        return;
    }
    unsigned int id = getMapObjID(index);
    if (id == 0) {
        return;
    }
    GfInitParamUiObj param;
    param.m_createType = 6;
    param.m_objId = id;
    param.pad_81 = true;
    param.pad_24 = 1;
    GF_OBJ_HANDLE* handle = GfObjFactory::createUiObj(param);
    ObjEntry entry;
    entry.m_handle = handle;
    m_objs.push_back(entry);
}

unsigned int GfMenuModelView::getMapObjID(unsigned int index) {
    unsigned char* bdat = GfDataBdat::getFP(0xFC);
    GfMenuBdat::isValidBdatID(bdat, m_bdatId);
    mm::mtl::FixStr<16> column;
    column.format("obj_model%02d", index);
    return Bdat::getMember(bdat, column.m_str) != nullptr ? static_cast<unsigned short>(Bdat::getVal(bdat, column.m_str, m_bdatId)) : 0;
}

void GfMenuModelView::sendObjectCommand(GF_OBJ_HANDLE* handle, const char* cmd) {
    GfObjAcc acc(handle);
    if (GfComAsm* com = acc.getObj()->getComponent<GfComAsm>(2)) {
        if (!com->execCmd(cmd, static_cast<AnimLayer>(0))) {
            com->setState("S_idle", static_cast<AnimLayer>(0));
        }
    }
}

void GfMenuModelView::attachObject(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* parent, const char* bone) {
    GfObjAcc acc(handle);
    if (GfComTransform* transform = acc.getObj()->getComponent<GfComTransform>(0)) {
        GfObjAcc parentAcc(parent);
        if (GfComModel* model = parentAcc.getObj()->getComponent<GfComModel>(1)) {
            model->addBoneReferenceFrame(bone, transform->m_frame);
        }
    }
}

fw::Transform& GfMenuModelView::getObjectTransform(GF_OBJ_HANDLE* handle) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EA7100)
    static fw::Transform s_transform;
    GfObjAcc acc(handle);
    if (GfComTransform* transform = acc.getObj()->getComponent<GfComTransform>(0)) {
        return transform->getFrame()->getWorldTransformForWrite();
    }
    return s_transform;
}

bool GfMenuModelView::getObjectEffectPoint(GF_OBJ_HANDLE* handle, const char* name, mm::Vec3& pos) {
    GfObjAcc acc(handle);
    fw::EffectPoint* point = acc.getObj()->getComponent<GfComEffectCaster>(7)->getEffectPoint();
    int index = point->getPointIndex(name);
    if (index == -1) {
        return false;
    }
    pos = point->getPointTransform(index).getTrans();
    return true;
}

void GfMenuModelView::setObjectScale(GF_OBJ_HANDLE* handle, const mm::Vec3& scale) {
    GfObjAcc acc(handle);
    acc.setModelScaleForMenu(scale);
}

void GfMenuModelView::setObjectDisp(GF_OBJ_HANDLE* handle, bool disp) {
    GfObjAcc acc(handle);
    acc.setDisp(static_cast<OBJDISP>(1), disp);
}

float GfMenuModelView::getVanishRatio(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (GfComModel* model = acc.getObj()->getComponent<GfComModel>(1)) {
        if (model->m_model != nullptr) {
            ml::ScnObjAccVolumeFade fade(model->m_model->getInterface());
            return fade.getRatio(0);
        }
    }
    return 0.0f;
}

bool GfMenuModelView::isObjectCtrlBusy(GF_OBJ_HANDLE* handle) {
    for (ObjEntry* it = m_objs.begin(); it != m_objs.end(); ++it) {
        if (it->m_handle == handle) {
            return it->m_ctrl.isBusy();
        }
    }
    return false;
}

const char* GfMenuModelView::getObjectAnimationState(GF_OBJ_HANDLE* handle) {
    for (ObjEntry* it = m_objs.begin(); it != m_objs.end(); ++it) {
        if (it->m_handle == handle) {
            GfObjAcc acc(handle);
            if (GfComAsm* com = acc.getObj()->getComponent<GfComAsm>(2)) {
                return com->getStateName(static_cast<AnimLayer>(0));
            }
        }
    }
    return nullptr;
}

void GfMenuModelView::setObjectVanishParam(GF_OBJ_HANDLE* handle, unsigned int type) {
    if (type == 0) {
        return;
    }
    for (ObjEntry* it = m_objs.begin(); it != m_objs.end(); ++it) {
        if (it->m_handle == handle) {
            ml::VolumeFadeParams params;
            if (!fw::EffectManager::sys()->getVolumeFadeParam(type, params)) {
                return;
            }
            GfObjAcc acc(handle);
            if (GfComModel* model = acc.getObj()->getComponent<GfComModel>(1)) {
                if (model->m_model != nullptr) {
                    ml::ScnObjAccVolumeFade fade(model->m_model->getInterface());
                    fade.setParams(params, -1);
                }
            }
        }
    }
}

void GfMenuModelView::setObjectVanishRatio(GF_OBJ_HANDLE* handle, float ratio) {
    for (ObjEntry* it = m_objs.begin(); it != m_objs.end(); ++it) {
        if (it->m_handle == handle) {
            setVanishRatio(handle, ratio);
        }
    }
}

unsigned int GfMenuModelView::addCamera(mm::mtl::IntrusivePtr<fw::Camera> camera) {
    unsigned int index = m_cameras.size();
    m_cameras.push_back(camera);
    return index;
}

void GfMenuModelView::pushCamera(unsigned int index, float time) {
    if (index < m_cameras.size()) {
        if (m_cameras[index]->m_pushed) {
            return;
        }
        if (fw::CameraManager* manager = fw::CameraManager::sys()) {
            unsigned int view = m_renderIndex + 1;
            mm::mtl::IntrusivePtr<fw::Camera>& camera = m_cameras[index];
            manager->m_layers[view].push(camera, time);
            m_cameraStack.push_back(index);
        }
    }
}

void GfMenuModelView::popCamera(float time) {
    if (fw::CameraManager* manager = fw::CameraManager::sys()) {
        unsigned int view = m_renderIndex + 1;
        mm::mtl::IntrusivePtr<fw::Camera>& camera = m_cameras[m_cameraStack.back()];
        manager->m_layers[view].pop(camera, time);
        m_cameraStack.pop_back();
    }
}

void GfMenuModelView::resetCamera(unsigned int index, float time) {
    if (fw::CameraManager* manager = fw::CameraManager::sys()) {
        fw::CameraLayer& layer = manager->m_layers[m_renderIndex + 1];
        for (unsigned int i = 0; i < m_cameras.size(); i++) {
            if (m_cameras[i]->m_pushed) {
                layer.pop(m_cameras[i], 0.0f);
            }
        }
    }
    m_cameraStack.clear();
    pushCamera(index, time);
}

mm::Vec3 GfMenuModelView::getCameraPos(unsigned int index) {
    if (index < m_cameras.size()) {
        fw::Camera* camera = m_cameras[index].get();
        if (camera != nullptr && camera->getRTTI()->isKindOf(&GfMenuModelViewCamera::m_rtti)) {
            return static_cast<GfMenuModelViewCamera*>(camera)->m_pos;
        }
    }
    return mm::Vec3::zero;
}

void GfMenuModelView::setCameraPos(unsigned int index, const mm::Vec3& pos) {
    if (index < m_cameras.size()) {
        fw::Camera* camera = m_cameras[index].get();
        if (camera != nullptr && camera->getRTTI()->isKindOf(&GfMenuModelViewCamera::m_rtti)) {
            static_cast<GfMenuModelViewCamera*>(camera)->setPos(pos);
        }
    }
}

mm::Vec3 GfMenuModelView::getCameraRot(unsigned int index) {
    if (index < m_cameras.size()) {
        fw::Camera* camera = m_cameras[index].get();
        if (camera != nullptr && camera->getRTTI()->isKindOf(&GfMenuModelViewCamera::m_rtti)) {
            return static_cast<GfMenuModelViewCamera*>(camera)->m_rot;
        }
    }
    return mm::Vec3::zero;
}

void GfMenuModelView::setCameraRotY(unsigned int index, float rotY) {
    if (index < m_cameras.size()) {
        fw::Camera* camera = m_cameras[index].get();
        if (camera != nullptr && camera->getRTTI()->isKindOf(&GfMenuModelViewCamera::m_rtti)) {
            static_cast<GfMenuModelViewCamera*>(camera)->setRotY(rotY);
        }
    }
}

bool GfMenuModelView::playCameraMotion(const char* name, const mm::Vec3& pos, float rotY) {
    if (name == nullptr || *name == '\0') {
        return false;
    }
    mm::mtl::IntrusivePtr<fw::Camera> camera = GimmickCamera::create(name, pos, rotY);
    if (camera.get() == nullptr) {
        return false;
    }
    if (GimmickCamera* gimmick = mm::mtl::rttiCast<GimmickCamera>(camera.get())) {
        gimmick->setNearClip(0.01f);
        gimmick->play();
    }
    if (fw::CameraManager::sys() != nullptr) {
        fw::CameraManager::sys()->m_layers[m_renderIndex + 1].push(camera, 0.5f);
        m_motionCamera = camera;
    }
    return true;
}

void GfMenuModelView::stopCameraMotion() {
    if (m_motionCamera.get() != nullptr) {
        if (mm::mtl::rttiCast<GimmickCamera>(m_motionCamera.get()) != nullptr && fw::CameraManager::sys() != nullptr) {
            fw::CameraManager::sys()->m_layers[m_renderIndex + 1].pop(m_motionCamera, 0.5f);
            m_motionCamera = nullptr;
        }
    }
}

void GfMenuModelView::playEffect(unsigned int slot, const char* name, const mm::Vec3& pos, GF_OBJ_HANDLE* handle) {
    if (fw::EffectManager::sys() != nullptr && m_effectPack.get() != nullptr) {
        EffectEntry& entry = m_effects[slot];
        if (entry.m_handle == 0) {
            unsigned int effect = fw::EffectManager::sys()->create(name, m_effectPack.get(), true);
            fw::EffectManager::sys()->setViewnum(effect, m_renderIndex + 1);
            entry.m_handle = effect;
            if (effect != 0) {
                m_effects[slot].m_obj = handle;
            }
        }
    }
}

void GfMenuModelView::playEffectFromCAS(unsigned int slot, const char* name, GF_OBJ_HANDLE* handle) {
    if (fw::EffectManager::sys() != nullptr && m_effectPack.get() != nullptr) {
        EffectEntry& entry = m_effects[slot];
        if (entry.m_handle == 0) {
            unsigned int effect = fw::EffectManager::sys()->create(name, m_effectPack.get(), true);
            fw::EffectManager::sys()->setViewnum(effect, m_renderIndex + 1);
            entry.m_handle = effect;
            if (effect != 0) {
                GfObjAcc acc(handle);
                GfComEffectCaster* caster = acc.getObj()->findComponent<GfComEffectCaster>(7);
                fw::EffectManager::sys()->setParam(effect, caster->m_caster, 1.0f);
            }
        }
    }
}

void GfMenuModelView::stopEffect(unsigned int slot) {
    EffectEntry& entry = m_effects[slot];
    if (entry.m_handle != 0) {
        fw::EffectManager::sys()->dead(entry.m_handle);
    }
}

void GfMenuModelView::removeEffect(unsigned int slot) {
    EffectEntry& entry = m_effects[slot];
    if (entry.m_handle != 0) {
        fw::EffectManager::sys()->kill(entry.m_handle);
        entry.m_handle = 0;
        m_effects[slot].m_obj = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
}

bool GfMenuModelView::isLoading() const {
    if (!m_isReady) {
        return true;
    }
    for (unsigned int i = 0; i < m_objs.size(); i++) {
        if (!GfObjUtil::isUpdate(m_objs[i].m_handle)) {
            return true;
        }
    }
    return false;
}

GF_OBJ_HANDLE* GfMenuModelView::findGfObj(unsigned int type, unsigned int bdatId) {
    GF_OBJ_HANDLE* handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    for (unsigned int i = 0; i < m_objs.size(); i++) {
        GfObjAcc acc(m_objs[i].m_handle);
        if (acc.getType() == type && acc.getBdatId() == bdatId) {
            handle = m_objs[i].m_handle;
            break;
        }
    }
    return handle;
}

bool GfMenuModelView::checkGfObj(unsigned int type, unsigned int bdatId) {
    for (unsigned int i = 0; i < m_objs.size(); i++) {
        GfObjAcc acc(m_objs[i].m_handle);
        if (acc.getType() == type && acc.getBdatId() == bdatId) {
            return GfObjUtil::isUpdate(acc.getHandle());
        }
    }
    return false;
}

void GfMenuModelView::CtrlParam::setAddPosY(float y) {
    fw::Transform& transform = getObjectTransformLocal(m_handle);
    m_flags |= 2;
    m_posY = transform.position.y + y;
}

void GfMenuModelView::CtrlParam::setMoveSclX(float x) {
    m_flags |= 8;
    m_scaleX = x;
}

void GfMenuModelView::CtrlParam::setMoveSclZ(float z) {
    m_flags |= 0x20;
    m_scaleZ = z;
}

void GfMenuModelView::CtrlParam::setMoveAlpha(float alpha) {
    m_flags |= 0x40;
    m_alpha = alpha;
}

void GfMenuModelView::CtrlParam::setMoveVanish(float ratio) {
    m_flags |= 0x100;
    m_vanishRatio = ratio;
}
}  // namespace gf

// instantiated for gf::GfMenuModelView::GfMenuModelView, gf::GfMenuModelView::~GfMenuModelView (not written yet)
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::Camera> >::destroy();

namespace gf {

}  // namespace gf
