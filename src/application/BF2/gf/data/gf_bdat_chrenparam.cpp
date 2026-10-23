#include "classes/gf/GfBdatChrEnParam.h"
#include "plugin/Bdat.h"

namespace gf {

unsigned int GfBdatChrEnParam::getChrEnParamTableEnd() const {
    return Bdat::getIdTop(m_fpChrEnParamTable->m_fp) + Bdat::getIdCount(m_fpChrEnParamTable->m_fp);
}

}  // namespace gf
