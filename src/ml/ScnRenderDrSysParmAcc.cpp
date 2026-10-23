#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/DrMan.h"
#include "classes/cloud/CloudMan.h"
#include "ml/DrIniSys.h"
#include "ml/DrPixlPostParm.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "ml/ScnRenderDrViewCtrl.h"

namespace ml {

void ScnRenderDrSys::setDefaultEvn() {}

void ScnRenderDrSys::applyCamera(ml::ScnObjCam*) {}

void ScnRenderDrSys::update() {}

void ScnRenderDrSys::setup(const ml::ScnSetup*) {}

ScnRenderDrSys::~ScnRenderDrSys() {
    if (m_drMan != nullptr) {
        delete m_drMan;
        m_drMan = nullptr;
    }
}

void ScnRenderDrSys::applyBegin() { m_drMan->begin(); }

void ScnRenderDrSys::applyEnd() { m_drMan->end(); }

void ScnRenderDrSys::applyLoopCnt() { m_drMan->loopCnt(); }

void ScnRenderDrSys::applyUpdate(int arg) { m_drMan->apply(arg); }

void ScnRenderDrSys::applyRender(int arg) { m_drMan->render(arg); }

void ScnRenderDrSys::tail() { m_drMan->tail(); }

void ScnRenderDrSys::setMdlDblPause(bool pause) { m_drMan->m_mdlDblPause = pause; }

void ScnRenderDrSys::setGlbSpd(float speed) { m_drMan->m_glbSpd = speed; }

void ScnRenderDrSys::setCallBack(IDrDrawCallback* callback) { m_drMan->setCallBack(callback); }

void ScnRenderDrSys::releaseCallBack(IDrDrawCallback* callback) { m_drMan->releaseCallBack(callback); }

void ScnRenderDrSys::openPixelDebugWindow(WinProc* proc) { m_drMan->openPixelDebugWindow(proc); }

void ScnRenderDrSys::openHisgtramDebugWindow(WinProc* proc) { m_drMan->openHistgramDebugWindow(proc); }

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc() : m_drMan(nullptr), m_postParm(nullptr), m_view(0) {
    m_drMan = DrMan::get();
    m_postParm = m_drMan->m_postParm[m_view];
}

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc(ScnRenderDrSys* render, int view)
    : m_drMan(nullptr), m_postParm(nullptr) {
    m_drMan = render->m_drMan;
    m_postParm = m_drMan->m_postParm[view];
    m_view = view;
}

void ScnRenderDrSysParmAcc::setDOFOverride(bool enable) { m_postParm->setOverrideDOF(enable); }

void ScnRenderDrSysParmAcc::setToneMap(bool enable) { m_postParm->m_toneMap = enable; }

void ScnRenderDrSysParmAcc::setOverrideToneMap(float value) { m_postParm->setOverrideToneMap(value); }

void ScnRenderDrSysParmAcc::setMotBlurOverride(bool enable) { m_postParm->setOverrideMotBlur(enable); }

void ScnRenderDrSysParmAcc::setMotBlur(bool enable) { m_postParm->m_motBlur = enable; }

void ScnRenderDrSysParmAcc::setMotBlurDefault(bool enable) { m_drMan->m_iniSys->m_motBlurDefault = enable; }

void ScnRenderDrSysParmAcc::setDOF(bool enable) { m_postParm->setDOF(enable); }

bool ScnRenderDrSysParmAcc::isDOF() const { return m_postParm->m_dofOverride || m_postParm->m_dof; }

void ScnRenderDrSysParmAcc::setDoFPixlRatio(float ratio) { m_postParm->setDoFPixlRatio(ratio); }

void ScnRenderDrSysParmAcc::setDoFDistance(float distance) { m_postParm->setDoFDistance(distance); }

void ScnRenderDrSysParmAcc::setDoFRange(float range) { m_postParm->setDoFRange(range); }

void ScnRenderDrSysParmAcc::setDoFStrength(float strength) { m_postParm->setDoFStrength(strength); }

void ScnRenderDrSysParmAcc::setDoFLens(float lens) { m_postParm->setDoFLens(lens); }

void ScnRenderDrSysParmAcc::setDoFBlend(float blend) { m_postParm->setDoFBlend(blend); }

void ScnRenderDrSysParmAcc::setDofHLvMode(bool enable) { m_postParm->setDOFHlv(enable); }

void ScnRenderDrSysParmAcc::setDofPixlLv(int level) {
    DrPixlPostParm* postParm = m_postParm;
    if (level < 0 || level >= 3) {
        postParm->setDoFPixlLv(0);
        return;
    }
    postParm->setDoFPixlLv(level);
}

void ScnRenderDrSysParmAcc::setDOFAutoFocus(bool enable) { m_postParm->setDOFAutoFocus(enable); }

void ScnRenderDrSysParmAcc::setDOFFocusNum(int num) {
    if (num > 11U) {
        num = 0;
    }
    m_postParm->setDoFocusNum(num);
}

void ScnRenderDrSysParmAcc::setDOFFocusMin(float min) { m_postParm->setDofFocusMin(min); }

float ScnRenderDrSysParmAcc::getDoFPixlRatio() const { return m_postParm->m_dofPixlRatio; }

float ScnRenderDrSysParmAcc::getDoFDistance() const { return m_postParm->m_dofDistance; }

float ScnRenderDrSysParmAcc::getDoFRange() const { return m_postParm->m_dofRange; }

float ScnRenderDrSysParmAcc::getDoFStrength() const { return m_postParm->m_dofStrength; }

float ScnRenderDrSysParmAcc::getDoFLens() const { return m_postParm->m_dofLens; }

float ScnRenderDrSysParmAcc::getDoFBlend() const { return m_postParm->m_dofBlend; }

bool ScnRenderDrSysParmAcc::isDofHLvMode() const { return m_postParm->m_dofHLvMode; }

int ScnRenderDrSysParmAcc::getDofPixlLv() const { return m_postParm->m_dofPixlLv; }

bool ScnRenderDrSysParmAcc::isDOFAutoFocus() const { return m_postParm->m_dofAutoFocus; }

int ScnRenderDrSysParmAcc::getDOFFocusNum() const { return m_postParm->m_dofFocusNum; }

float ScnRenderDrSysParmAcc::getDOFFocusMin() const { return m_postParm->m_dofFocusMin; }

void ScnRenderDrSysParmAcc::setPlaneCloudNum(unsigned int num) {
    cloud::CloudMan* cloudMan = DrMan::getIns()->m_cloudMan;
    if (cloudMan != nullptr) {
        cloudMan->setCldNum(num);
    }
}

void ScnRenderDrSysParmAcc::setGlobalWind(const mm::Vec3& power) { m_drMan->setGlobalWind(power); }

void ScnRenderDrSysParmAcc::setAutoReduction(bool enable) { m_drMan->setAutoReduction(enable); }

void ScnRenderDrSysParmAcc::setColorFilterOverride(bool enable) { m_postParm->setOverrideColorFilter(enable); }

void ScnRenderDrSysParmAcc::setColorFilterNum(int num) { m_postParm->setColorFilterNum(num); }

void ScnRenderDrSysParmAcc::setColorFilterFarNum(int num) { m_postParm->setColorFilterFarNum(num); }

void ScnRenderDrSysParmAcc::setColorFilterFrm(float frame) { m_postParm->setColorFilterFrm(frame); }

void ScnRenderDrSysParmAcc::setRainDrop(bool enable) { m_postParm->m_rainDrop = enable; }

void ScnRenderDrSysParmAcc::setTimeVal(float time) { m_drMan->setTimeVal(time); }

void ScnRenderDrSysParmAcc::setWeather(int weather) { m_postParm->m_weather = weather; }

void ScnRenderDrSysParmAcc::setWeatherFrame(float frame) { m_postParm->setWeatherFrame(frame); }

void ScnRenderDrSysParmAcc::setSeamMapAddPosMode(bool enable) { m_drMan->m_seamMapAddPosMode = enable; }

void ScnRenderDrSysParmAcc::setSeamMapReadPos(const mm::Vec3& pos) {
    m_drMan->m_seamMapReadPos = pos;
}

void ScnRenderDrSysParmAcc::setSelectIdDisp(int index, bool off) {
    if (off) {
        m_drMan->offGblIdx(index);
    } else {
        m_drMan->setGblIdx(index);
    }
}

bool ScnRenderDrSysParmAcc::isMdlAllMiddleTexStm() const { return m_drMan->isAllMiddelTexStmChk(); }

bool ScnRenderDrSysParmAcc::isSeamMapRead() const { return m_drMan->isSeamMapStmOk(); }

void ScnRenderDrSysParmAcc::setToonDirLightScale(bool enable) { m_drMan->m_toonDirLightScale = enable; }

void ScnRenderDrSysParmAcc::setToonAmbient(bool enable) {
    if (enable) {
        m_drMan->m_toonAmbient = 3;
    } else {
        m_drMan->m_toonAmbient = 0;
    }
}

void ScnRenderDrSysParmAcc::setPlayerPos(const mm::Vec3& pos) {}

void ScnRenderDrSysParmAcc::setCameraLight(bool enable) { m_drMan->m_cameraLight = enable; }

void ScnRenderDrSysParmAcc::deleteAddRenderView(ScnRenderDrViewCtrl* view) {
    m_drMan->deleteAddRenderSystem(view->m_viewIndex + 1);
}

void ScnRenderDrSysParmAcc::setModelTexture(const ScnRenderDrMdlTexture& texture) {
    DR_MODEL_TEXTURE modelTexture;
    modelTexture.m_texture = texture.m_texture;
    modelTexture.m_enable = texture.m_enable;
    m_drMan->setModelTexture(&modelTexture, texture.m_slot);
}

void ScnRenderDrSysParmAcc::resetModelTexture(unsigned int slot) { m_drMan->resetModelTexture(slot); }

void ScnRenderDrSysParmAcc::setGlassBr(bool enable, unsigned int arg) { m_postParm->setGlassBrk(enable, arg); }

bool ScnRenderDrSysParmAcc::isGlassBr() { return m_postParm->m_glassBr; }

void ScnRenderDrSysParmAcc::setViewRenderSkip(unsigned int view, bool skip) {
    DrMan* drMan = DrMan::get();
    if (skip) {
        drMan->m_viewRenderSkip |= 1 << view;
    } else {
        drMan->m_viewRenderSkip &= ~(1 << view);
    }
}

void ScnRenderDrSysParmAcc::resetScene() { m_postParm->resetScene(); }

void ScnRenderDrSysParmAcc::setAutoResetScene(bool enable) { DrMan::get()->m_autoResetScene = enable; }

void ScnRenderDrSysParmAcc::setGamma(float gamma) { DrMan::get()->m_gamma = gamma; }

void ScnRenderDrSysParmAcc::setCaptureMode(bool enable) {
    DrMan* drMan = DrMan::get();
    if (enable) {
        drMan->m_captureMode[DrMan::s_nDblStockIdx] = 1;
    } else {
        drMan->m_captureMode[DrMan::s_nDblStockIdx] = 2;
    }
}

}  // namespace ml
