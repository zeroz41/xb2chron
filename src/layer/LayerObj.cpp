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
#include "layer/LayerAccManager.h"
#include "layer/LayerAccPolyObj.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccAction.h"
#include "layer/LayerAccDefTexture.h"
#include "layer/LayerAccDefObj.h"
#include "layer/LayerAccLayoutObj.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjWork.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjFont.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/layer/LayerSortObj.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopFont.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjSortDef.h"
#include "classes/layer/LayerObjSortFont.h"
#include "classes/layer/LayerObjSortTexObj.h"
#include "classes/layer/LayerObjSortPolyObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerTagStr.h"

namespace layer {

void LayerObjManager::end() {}

bool LayerActBase::actend_no(const LyrActionData* data, bool cmdEnd) { return false; }
bool LayerActBase::actend_cmdend(const LyrActionData* data, bool cmdEnd) { return !cmdEnd; }
bool LayerActBase::actend_on(const LyrActionData* data, bool cmdEnd) { return true; }

void LayerObjSortDef::finalRender() { static_cast<LayerObjTopDef*>(m_obj)->finalRender(); }
void LayerObjSortFont::finalRender() { static_cast<LayerObjTopFont*>(m_obj)->finalRender(); }
void LayerObjSortTexObj::finalRender() { static_cast<LayerObjTopTexObj*>(m_obj)->finalRender(); }
void LayerObjSortPolyObj::finalRender() { static_cast<LayerObjTopPolyObj*>(m_obj)->finalRender(); }

}  // namespace layer

