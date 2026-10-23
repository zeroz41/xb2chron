#include "classes/gf/GfBdatChrEnArrange.h"
#include "plugin/Bdat.h"

namespace gf {

unsigned int GfBdatChrEnArrange::getChrEnArrangeStart() const {
    return Bdat::getIdTop(m_fpChrEnArrange->m_fp);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeEnd() const {
    return Bdat::getIdTop(m_fpChrEnArrange->m_fp) + Bdat::getIdCount(m_fpChrEnArrange->m_fp);
}

}  // namespace gf
