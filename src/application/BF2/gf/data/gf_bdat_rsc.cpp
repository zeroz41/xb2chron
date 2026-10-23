#include "classes/gf/GfBdatRsc.h"
#include "plugin/Bdat.h"

namespace gf {

GfBdatRsc::~GfBdatRsc() {
    destroyFP();
}

unsigned int GfBdatRsc::getFLD_actorSEStart() const {
    return Bdat::getIdTop(m_fpFLD_actorSE->m_fp);
}

unsigned int GfBdatRsc::getFLD_actorSEEnd() const {
    return Bdat::getIdTop(m_fpFLD_actorSE->m_fp) + Bdat::getIdCount(m_fpFLD_actorSE->m_fp);
}

}  // namespace gf
