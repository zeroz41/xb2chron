#include "mm/mtl/IntrusiveList.h"
#include "classes/fw/BdatManager.h"
#include "classes/fw/Camera.h"
#include "classes/ml/FileResTh.h"
#include "plugin/Bdat.h"
#include "classes/fw/AssetManager.h"
#include "classes/fw/AssetData.h"
#include "classes/fw/AssetLoader.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/ml/DevFileTh.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/LangUtil.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Hash.h"
#include "mm/mtl/Map.h"
#include "mtl/MemManager.h"
#include "string.h"

namespace fw {

Camera::Camera(CAMERA_PRIO prio)
    : m_layerNode(nullptr), m_prio(prio), m_fov(40.0f), m_nearClip(0.01f), m_farClip(40000.0f), m_eye(mm::Vec3::zero),
      m_target(mm::Vec3::unitZ), m_pushed(false), m_roll(0.0f) {
    m_view = mm::Mat44::identity;
}

mm::mtl::RTTI Camera::m_rtti("Camera", nullptr, nullptr);

}  // namespace fw
