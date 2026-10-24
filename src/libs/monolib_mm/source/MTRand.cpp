#include "nn/os.h"
#include "mm/mtl/MTRand.h"

namespace ml {

// the generator ml::mtInit seeds and ml::mtRand* draw from, seeded with the system tick at startup (proposed name,
// not the original's: the symbols leave it unnamed, lbl_7100ECE430)
static mm::mtl::MTRand s_rand(nn::os::GetSystemTick().GetInt64Value());

}  // namespace ml
