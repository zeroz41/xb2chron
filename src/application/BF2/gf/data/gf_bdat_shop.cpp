#include "classes/gf/GfBdatShop.h"
#include "plugin/Bdat.h"

namespace gf {

GfBdatShop::~GfBdatShop() {
    destroyFP();
}

unsigned int GfBdatShop::getShopChangeTaskStart() const {
    return Bdat::getIdTop(m_fpShopChangeTask->m_fp);
}

unsigned int GfBdatShop::getShopChangeTaskEnd() const {
    return Bdat::getIdTop(m_fpShopChangeTask->m_fp) + Bdat::getIdCount(m_fpShopChangeTask->m_fp);
}

unsigned int GfBdatShop::getMNU_EventTheaterStart() const {
    return Bdat::getIdTop(m_fpMNU_EventTheater->m_fp);
}

unsigned int GfBdatShop::getMNU_EventTheaterEnd() const {
    return Bdat::getIdTop(m_fpMNU_EventTheater->m_fp) + Bdat::getIdCount(m_fpMNU_EventTheater->m_fp);
}

}  // namespace gf
