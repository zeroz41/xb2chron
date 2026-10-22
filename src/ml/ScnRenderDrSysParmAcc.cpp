#include "classes/cloud/CloudObjFlow.h"
#include "classes/grlib/CGLibUniformEtcUtility.h"
#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrMdoCtlDammy.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrPixlShadowObjSpt.h"
#include "classes/ml/ScnRenderDrSys.h"

namespace grlib {

void CGLibUniformEtcUtility::updateData() {}

}  // namespace grlib

namespace ml {

void ScnRenderDrSys::setDefaultEvn() {}

void ScnRenderDrSys::applyCamera(ml::ScnObjCam*) {}

void ScnRenderDrSys::update() {}

void ScnRenderDrSys::setup(const ml::ScnSetup*) {}

}  // namespace ml

namespace cloud {

void CloudObjFlow::alphaRender() {}

}  // namespace cloud

namespace ml {

DrFogObjGbl::~DrFogObjGbl() {}

void DrFogObjGbl::update() {}

void DrMdoCtlDammy::resourceInit() {}

void DrMdoCtlDammy::update() {}

void DrMdoCtlDammy::dispOffUpdate() {}

void DrMdoCtlSeamAll::debugRender() {}

void DrPixlShadowObjSpt::renderLight() {}



}  // namespace ml
