#include "classes/layer/LayerTagStr.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrResMdoInstPartsAnm.h"
#include "classes/ml/DrResMdoInstPartsGlbID.h"
#include "classes/ml/DrResMdoSeamColi.h"
#include "classes/ml/DrResMdoSortMpf.h"
#include "classes/ml/DrResMdoSortPos.h"
#include "classes/ml/DrResMdoSortSeamAll.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtTileBasedDr.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "classes/navi/NvmshAcObjBaseGbl.h"

namespace ml {

DrResMdoInstPartsAnm::~DrResMdoInstPartsAnm() {}

DrResMdoInstPartsGlbID::~DrResMdoInstPartsGlbID() {}

DrResMdoSeamColi::~DrResMdoSeamColi() {}

DrResMdoSortPos::~DrResMdoSortPos() {}

DrResMdoSortMpf::~DrResMdoSortMpf() {}

DrResMdoSortSeamAll::~DrResMdoSortSeamAll() {}

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

DrLightObjLocalIBL::~DrLightObjLocalIBL() {}

void ScnObjModelDrSys::update() {}

}  // namespace ml

namespace navi {

NvmshAcObjBaseGbl::~NvmshAcObjBaseGbl() {}

}  // namespace navi

namespace layer {

LayerTagStr::~LayerTagStr() {}

}  // namespace layer
