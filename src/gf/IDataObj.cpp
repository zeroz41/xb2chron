#include "classes/gf/DataObjEnemyBlade.h"
#include "classes/gf/DataObjPcWpn.h"
#include "classes/gf/DataObjUiObj.h"

namespace gf {

DataObjPcWpn::~DataObjPcWpn() {}

DataObjEnemyBlade::~DataObjEnemyBlade() {}

bool DataObjUiObj::isDispInitExtraParts(unsigned int) const {
    return false;
}

}  // namespace gf
