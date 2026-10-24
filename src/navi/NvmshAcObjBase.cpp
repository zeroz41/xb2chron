#include "layer/LayerAccManager.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "classes/layer/LayerObjLayout.h"
#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccFontStyle.h"
#include "layer/LayerAccPolyObj.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccAction.h"
#include "layer/LayerAccDefTexture.h"
#include "layer/LayerAccDefObj.h"
#include "layer/LayerAccLayoutObj.h"
#include "classes/layer/LayerObjWork.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjFont.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/layer/LayerSortObj.h"
#include "classes/layer/LayerObjTopFont.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjSortDef.h"
#include "classes/layer/LayerObjSortFont.h"
#include "classes/layer/LayerObjSortTexObj.h"
#include "classes/layer/LayerObjSortPolyObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerTagStr.h"

#include "classes/ml/DrResMdoInstPartsAnm.h"
#include "classes/ml/DrResMdoInstPartsGlbID.h"
#include "classes/ml/DrResMdoSeamColi.h"
#include "classes/ml/DrResMdoSortMpf.h"
#include "classes/ml/DrResMdoSortPos.h"
#include "classes/ml/DrResMdoSortSeamAll.h"
#include "classes/ml/DrResMdoSortNom.h"
#include "classes/ml/DrResMdoSortNomLastApha.h"
#include "classes/ml/DrResMdoSortNomFastApha.h"
#include "classes/ml/DrResMdoSortNomCldBackApha.h"
#include "classes/ml/DrResMdoSortGrp.h"
#include "classes/ml/DrResMdoSortSeamEnvMap.h"
#include "classes/ml/DrResMdoSortCloud.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/navi/NvmshAcObjBaseGbl.h"
#include "ml/DrResEtcParams.h"
#include "ml/DrResFetch.h"
#include "ml/DrResMdoLight.h"
#include "ml/DrResMdoPosInstAnm.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrResEtcPamObj.h"
#include "ml/DrResMdoLodObj.h"
#include "ml/DrResMdoMeshObj.h"
#include "ml/DrResMdoMorpObj.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrResMdoInstPartsObj.h"
#include "ml/DrResShdShw.h"
#include "ml/DrResShdStreamOut.h"
#include "ml/DrShdDataObj.h"

namespace navi {

void NvmshAcObjBase::setMeshNum(int num) { m_isMeshNum = num > 0; }

NvmshAcObjBaseGbl::~NvmshAcObjBaseGbl() {}

const mm::Vec3& NvmshAcObjBase::getMoveVec() const { return m_moveVec; }

void NvmshAcObjBase::setBeginPos(const mm::Vec3& pos) { m_beginPos = pos; }

void NvmshAcObjBase::setEndPos(const mm::Vec3& pos) { m_endPos = pos; }

void NvmshAcObjBase::setBeginRadius(float radius) { m_beginRadius = radius; }

void NvmshAcObjBase::setEndRadius(float radius) { m_endRadius = radius; }

void NvmshAcObjBase::setBeginSeachRadius(float radius) { m_beginSeachRadius = radius; }

void NvmshAcObjBase::setEndSeachRadius(float radius) { m_endSeachRadius = radius; }

void NvmshAcObjBase::setBeginHeight(float a, float b) {
    m_beginHeight[0] = a;
    m_beginHeight[1] = b;
}

void NvmshAcObjBase::setEndHeight(float a, float b) {
    m_endHeight[0] = a;
    m_endHeight[1] = b;
}

int NvmshAcObjBase::getMeshNum() const { return m_meshNum; }

void NvmshAcObjBase::setMoveSpd(float spd) { m_moveSpd = spd; }

}  // namespace navi
