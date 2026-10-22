#include "nn/os.h"
#include "mm/mtl/MTRand.h"
#include "classes/ml/ErrViewer.h"

namespace ml {

// the generator ml::mtInit seeds and ml::mtRand* draw from, seeded with the system tick at startup
static mm::mtl::MTRand s_rand(nn::os::GetSystemTick().GetInt64Value());

void ErrViewer::upErrViewer() {}

void ErrViewer::setup() {}

void ErrViewer::bkgHomeMenu(bool) {}

}  // namespace ml
