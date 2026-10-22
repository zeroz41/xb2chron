#include "classes/fw/CameraPlugin.h"
#include "classes/gf/GimmickCameraParams.h"
#include "classes/gf/ShipRollPlugin.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {

// the plugin ShipRollPlugin::setEnable creates and pushes onto the camera layer while rolling is enabled
static mm::mtl::IntrusivePtr<fw::CameraPlugin> s_plugin;

GimmickCameraParams::~GimmickCameraParams() {}

ShipRollPlugin::~ShipRollPlugin() {}

}  // namespace gf
