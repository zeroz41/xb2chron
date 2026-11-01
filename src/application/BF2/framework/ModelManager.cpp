#include "classes/fw/ModelManager.h"
#include "classes/fw/ModelObject.h"
#include "classes/fw/VisibleObject.h"
#include "classes/fw/MovieManager.h"
#include "classes/ICMovie.h"
#include "classes/CMovieNX/CMovie.h"
#include "classes/CMovie.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/WorkCpu.h"
#include "ml/ScnObjAccResMdlInfo.h"
#include "ml/ScnObjAccGpuCheck.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerBase.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIObject.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "mtl/MemManager.h"
#include "ui/UIUtil.h"

#include <algorithm>

namespace fw {

// every element of the groups whose bits layers holds, updated in list order; the loop is an algorithm's
// (the end iterator is worked out with begin before the first element is tested, as for by-value arguments)
void ModelManager::update(const UpdateInfo&, unsigned int layers) {
    for (unsigned int i = 0; i < 32; ++i) {
        if ((1 << i) & layers) {
            std::for_each(m_groups[i].begin(), m_groups[i].end(), [](Element& obj) { obj.update(); });
        }
    }
}

ModelManager::~ModelManager() {}

}  // namespace fw
