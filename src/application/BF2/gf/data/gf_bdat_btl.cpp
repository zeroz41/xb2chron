#include "classes/gf/GfBdatBtl.h"
#include "plugin/Bdat.h"

namespace gf {

GfBdatBtl::~GfBdatBtl() {
    destroyFP();
}

unsigned int GfBdatBtl::getArtsDrStart() const {
    return Bdat::getIdTop(m_fpArtsDr->m_fp);
}

unsigned int GfBdatBtl::getArtsDrEnd() const {
    return Bdat::getIdTop(m_fpArtsDr->m_fp) + Bdat::getIdCount(m_fpArtsDr->m_fp);
}

unsigned int GfBdatBtl::getArtsBlStart() const {
    return Bdat::getIdTop(m_fpArtsBl->m_fp);
}

unsigned int GfBdatBtl::getArtsBlEnd() const {
    return Bdat::getIdTop(m_fpArtsBl->m_fp) + Bdat::getIdCount(m_fpArtsBl->m_fp);
}

unsigned int GfBdatBtl::getArtsBlSpStart() const {
    return Bdat::getIdTop(m_fpArtsBlSp->m_fp);
}

unsigned int GfBdatBtl::getArtsBlSpEnd() const {
    return Bdat::getIdTop(m_fpArtsBlSp->m_fp) + Bdat::getIdCount(m_fpArtsBlSp->m_fp);
}

unsigned int GfBdatBtl::getGrowStart() const {
    return Bdat::getIdTop(m_fpGrow->m_fp);
}

unsigned int GfBdatBtl::getGrowEnd() const {
    return Bdat::getIdTop(m_fpGrow->m_fp) + Bdat::getIdCount(m_fpGrow->m_fp);
}

unsigned int GfBdatBtl::getBTL_ClassStart() const {
    return Bdat::getIdTop(m_fpBTL_Class->m_fp);
}

unsigned int GfBdatBtl::getBTL_ClassEnd() const {
    return Bdat::getIdTop(m_fpBTL_Class->m_fp) + Bdat::getIdCount(m_fpBTL_Class->m_fp);
}

unsigned int GfBdatBtl::getBTL_Skill_BlStart() const {
    return Bdat::getIdTop(m_fpBTL_Skill_Bl->m_fp);
}

unsigned int GfBdatBtl::getBTL_Skill_BlEnd() const {
    return Bdat::getIdTop(m_fpBTL_Skill_Bl->m_fp) + Bdat::getIdCount(m_fpBTL_Skill_Bl->m_fp);
}

unsigned int GfBdatBtl::getBTL_Bl_PersonalityStart() const {
    return Bdat::getIdTop(m_fpBTL_Bl_Personality->m_fp);
}

unsigned int GfBdatBtl::getBTL_Bl_PersonalityEnd() const {
    return Bdat::getIdTop(m_fpBTL_Bl_Personality->m_fp) + Bdat::getIdCount(m_fpBTL_Bl_Personality->m_fp);
}

unsigned int GfBdatBtl::getVo_Field_FilterStart() const {
    return Bdat::getIdTop(m_fpVo_Field_Filter->m_fp);
}

unsigned int GfBdatBtl::getVo_Field_FilterEnd() const {
    return Bdat::getIdTop(m_fpVo_Field_Filter->m_fp) + Bdat::getIdCount(m_fpVo_Field_Filter->m_fp);
}

}  // namespace gf
