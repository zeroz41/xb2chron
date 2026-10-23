#include "classes/gf/GfBdatChrDr.h"
#include "plugin/Bdat.h"

namespace gf {

unsigned int GfBdatChrDr::getChrDrStart() const {
    return Bdat::getIdTop(m_fpChrDr->m_fp);
}

unsigned int GfBdatChrDr::getChrDrEnd() const {
    return Bdat::getIdTop(m_fpChrDr->m_fp) + Bdat::getIdCount(m_fpChrDr->m_fp);
}

}  // namespace gf
