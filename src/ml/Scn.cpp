#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjClip.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ThreadNx.h"

namespace ml {

void ScnDebugManipuRot::update() {}

void ScnDebugManipuTrans::setRadius(float) {}

void ScnDebugManipuTrans::update() {}

void ScnObjCam::renderDebug(ml::DebDraw*) {}

ScnObjClip::~ScnObjClip() {}

ScnObjEnvColi::~ScnObjEnvColi() {}

void ScnObjModel::renderDebug(ml::DebDraw*) {}

ScnObjIBL::~ScnObjIBL() {}

ScnRender::~ScnRender() {}

bool ThreadNx::isSuspended() const {
    return false;
}

}  // namespace ml
