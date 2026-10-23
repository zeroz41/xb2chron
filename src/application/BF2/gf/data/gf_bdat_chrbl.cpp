#include "classes/gf/GfBdatChrBl.h"
#include "plugin/Bdat.h"

namespace gf {

GfBdatChrBl::~GfBdatChrBl() {
    if (m_fpChrBl != nullptr) {
        delete m_fpChrBl;
        m_fpChrBl = nullptr;
    }
}

unsigned int GfBdatChrBl::getChrBlStart() const {
    return Bdat::getIdTop(m_fpChrBl->m_fp);
}

unsigned int GfBdatChrBl::getChrBlEnd() const {
    return Bdat::getIdTop(m_fpChrBl->m_fp) + Bdat::getIdCount(m_fpChrBl->m_fp);
}

}  // namespace gf
