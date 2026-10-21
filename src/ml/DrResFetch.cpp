#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrResMdoInstPartsAnm.h"
#include "classes/ml/DrResMdoSeamColi.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtTileBasedDr.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjModelDrSys.h"

namespace ml {

DrResMdoInstPartsAnm::~DrResMdoInstPartsAnm() {}

DrResMdoSeamColi::~DrResMdoSeamColi() {}

void DrShdLgtClustered::update() {}

void DrShdLgtClustered::delViewInfo(int) {}

void DrShdLgtClustered::debugRender() {}

void DrShdLgtTileBasedDr::update() {}

void DrShdLgtTileBasedDr::addViewInfo(int) {}

void DrShdLgtTileBasedDr::delViewInfo(int) {}

void DrShdLgtTileBasedDr::debugRender() {}

void ScnObjIBLDr::setReferencePos(const mm::Vec3&) {}

void ScnObjIBLDr::dispDebugWindow(bool, const char*, ml::WinProc*) {}

void ScnObjIBLDr::setName(const char*) {}

void ScnObjLightDrSys::tail() {}

void ScnObjLightDrSys::setLocalIBLName(const char*) {}

void DrCalcClipWorkCone::debugDraw() {}

void ScnObjModelDrSys::update() {}

}  // namespace ml
