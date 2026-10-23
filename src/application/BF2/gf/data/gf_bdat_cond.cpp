#include "classes/gf/GfBdatCond.h"
#include "plugin/Bdat.h"

namespace gf {

GfBdatCond::~GfBdatCond() {
    destroyFP();
}

}  // namespace gf
