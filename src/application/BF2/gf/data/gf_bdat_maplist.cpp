#include "classes/gf/GfBdatMaplist.h"
#include "plugin/Bdat.h"

namespace gf {

unsigned int GfBdatMaplist::getMaplistStart() const {
    return Bdat::getIdTop(m_fpMaplist->m_fp);
}

unsigned int GfBdatMaplist::getMaplistEnd() const {
    return Bdat::getIdTop(m_fpMaplist->m_fp) + Bdat::getIdCount(m_fpMaplist->m_fp);
}

}  // namespace gf
