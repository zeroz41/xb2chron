#include "layer/LayerAccObjBase.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObjectParam.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "layer/LayerBase.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccManager.h"
#include "mm/mtl/Hash.h"
#include "ui/UIUtil.h"

namespace ui {

// the layer's centre type for each display mode (UIObject::apply)
static const layer::LayerCenterType s_centerTypes[] = {(layer::LayerCenterType)0, (layer::LayerCenterType)2};

}  // namespace ui
