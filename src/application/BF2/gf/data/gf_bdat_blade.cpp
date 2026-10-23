#include "classes/gf/GfBdatBlade.h"
#include "plugin/Bdat.h"

namespace gf {

GfBdatBlade::~GfBdatBlade() {
    destroyFP();
}

unsigned int GfBdatBlade::getNameListStart() const {
    return Bdat::getIdTop(m_fpNameList->m_fp);
}

unsigned int GfBdatBlade::getNameListEnd() const {
    return Bdat::getIdTop(m_fpNameList->m_fp) + Bdat::getIdCount(m_fpNameList->m_fp);
}

unsigned int GfBdatBlade::getBLD_RareListStart() const {
    return Bdat::getIdTop(m_fpBLD_RareList->m_fp);
}

unsigned int GfBdatBlade::getBLD_RareListEnd() const {
    return Bdat::getIdTop(m_fpBLD_RareList->m_fp) + Bdat::getIdCount(m_fpBLD_RareList->m_fp);
}

}  // namespace gf
