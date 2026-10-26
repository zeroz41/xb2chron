#ifndef CLASSES_GF_GFBDATMAPLIST_H
#define CLASSES_GF_GFBDATMAPLIST_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatMaplist; }

namespace gf {
// table 0x7100B47070; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatMaplist : public ::mm::mtl::PtrSingleton< ::gf::GfBdatMaplist>, public ::gf::IDataBdat {
public:
    GfBdatMaplist();
    virtual ~GfBdatMaplist();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getMaplistStart() const;
    unsigned int getMaplistEnd() const;
    const char* getMaplistresource(unsigned int id) const;
    unsigned int getMaplistweatherATR(unsigned int id) const;
    unsigned int getMaplistebb_ON_cndID(unsigned int id) const;
    unsigned int getMaplistebb_inn_cndID(unsigned int id) const;  // the map's inn condition row (0: none)
    unsigned int getMaplistbgm_cndID(unsigned int id) const;  // the map's BGM condition row
    unsigned int getMaplistnameID(unsigned int id) const;  // the map's name row (GfMapManager::getMapName)
    unsigned int getMapliste_balloondisp_r(unsigned int id) const;
    unsigned int getMaplistzone(unsigned int id) const;
    unsigned int getMaplistw_type(unsigned int id, unsigned int slot) const;  // a map's weather of a type (its w_type columns)
    unsigned int getMaplistw_pop_rate(unsigned int id, unsigned int slot) const;
    unsigned int getMaplistw_time_BNS(unsigned int id, unsigned int slot) const;
    unsigned int getMaplistw_end_time(unsigned int id, unsigned int slot) const;
    unsigned int getMaplistw_ON_cndID(unsigned int id, unsigned int slot) const;
    unsigned int getMaplistw_OFF_cndID(unsigned int id, unsigned int slot) const;
    unsigned int getWeatherInfomsg(unsigned int id) const;
    const char* getWeatherInfoeff(unsigned int id) const;
    const char* getWeatherInfosnd(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpWeatherInfo.
    // What it does: row id's "snd_ira" column (a string) of FLD_WeatherInfo, nullptr when the handle is null or id is out of range
    // (bdatRefresh looks it up between snd and sndBegin; 1.0.0 has no such column).
    const char* fn_710020A2AC(unsigned int id) const;
    const char* getWeatherInfosndBegin(unsigned int id) const;
    unsigned int getTimeInfomsg(unsigned int id) const;
    // the tables, by GfDataBdat id (s_aszGfBdatName), created in this order by createFP; names follow 1.0.0's
    // accessors (getMaplist.., getWeatherInfo.., getTimeInfo..)
    CBdatWrapper* m_fpMaplist;  // 0x10, FLD_maplist
    CBdatWrapper* m_fpWeatherInfo;  // 0x18, FLD_WeatherInfo
    CBdatWrapper* m_fpTimeInfo;  // 0x20, FLD_TimeInfo
};
}  // namespace gf

#endif
