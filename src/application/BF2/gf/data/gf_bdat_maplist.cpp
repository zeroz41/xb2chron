#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatMaplist.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the map list tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked up
// once (init) and a row's value read through it (get)
namespace _gfbml {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberMaplistresource;
static unsigned char* s_memberMaplistselect;
static unsigned char* s_memberMaplistrscGmkId;
static unsigned char* s_memberMaplistene_disp_r;
static unsigned char* s_memberMaplistene_disp_h;
static unsigned char* s_memberMaplistene_release_r;
static unsigned char* s_memberMaplistene_release_h;
static unsigned char* s_memberMaplistwa_type;
static unsigned char* s_memberMaplistwa_pop_rate;
static unsigned char* s_memberMaplistwa_time_BNS;
static unsigned char* s_memberMaplistwa_end_time;
static unsigned char* s_memberMaplistwb_type;
static unsigned char* s_memberMaplistwb_pop_rate;
static unsigned char* s_memberMaplistwb_time_BNS;
static unsigned char* s_memberMaplistwb_end_time;
static unsigned char* s_memberMaplistwc_type;
static unsigned char* s_memberMaplistwc_pop_rate;
static unsigned char* s_memberMaplistwc_time_BNS;
static unsigned char* s_memberMaplistwc_end_time;
static unsigned char* s_memberMaplistwd_type;
static unsigned char* s_memberMaplistwd_pop_rate;
static unsigned char* s_memberMaplistwd_time_BNS;
static unsigned char* s_memberMaplistwd_end_time;
static unsigned char* s_memberMaplistwind_mor;
static unsigned char* s_memberMaplistwind_non;
static unsigned char* s_memberMaplistwind_eve;
static unsigned char* s_memberMaplistwind_nit;
static unsigned char* s_memberMaplistwind_mnit;
static unsigned char* s_memberMaplistwind_emor;
static unsigned char* s_memberMaplistwind_WA;
static unsigned char* s_memberMaplistwind_WB;
static unsigned char* s_memberMaplistwind_WC;
static unsigned char* s_memberMaplistwind_WD;
static unsigned char* s_memberMaplistweatherATR;
static unsigned char* s_memberMapliste_repoptime;
static unsigned char* s_memberMaplistm_repoptime;
static unsigned char* s_memberMaplistmapATR;
static unsigned char* s_memberMaplistwa_ON_cndID;
static unsigned char* s_memberMaplistwa_OFF_cndID;
static unsigned char* s_memberMaplistwb_ON_cndID;
static unsigned char* s_memberMaplistwb_OFF_cndID;
static unsigned char* s_memberMaplistwc_ON_cndID;
static unsigned char* s_memberMaplistwc_OFF_cndID;
static unsigned char* s_memberMaplistwd_ON_cndID;
static unsigned char* s_memberMaplistwd_OFF_cndID;
static unsigned char* s_memberMapliststopTIME_cndID;
static unsigned char* s_memberMaplistebb_ON_cndID;
static unsigned char* s_memberMaplistebb_inn_cndID;
static unsigned char* s_memberMaplistebb_pop_rate;
static unsigned char* s_memberMaplistst_allOFF_cndID;
static unsigned char* s_memberMaplistst_OFF_cndID;
static unsigned char* s_memberMaplistbgm_cndID;
static unsigned char* s_memberMaplistname_cndID;
static unsigned char* s_memberMaplistnameID;
static unsigned char* s_memberMaplistchange_nameID;
static unsigned char* s_memberMaplistmapON_cndID;
static unsigned char* s_memberMaplisttextID;
static unsigned char* s_memberMapliste_balloondisp_r;
static unsigned char* s_memberMaplistzone;
static unsigned char* s_memberWeatherInfomsg;
static unsigned char* s_memberWeatherInfoeff;
static unsigned char* s_memberWeatherInfosnd;
static unsigned char* s_memberWeatherInfosnd_ira;
static unsigned char* s_memberWeatherInfosndBegin;
static unsigned char* s_memberTimeInfomsg;

void initMaplistresource(const CBdatWrapper& bdat) {
    s_memberMaplistresource = bdat.getMember("resource");
}

const char* getMaplistresource(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistresource != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberMaplistresource, id, 7);
    }
    return nullptr;
}

void initMaplistselect(const CBdatWrapper& bdat) {
    s_memberMaplistselect = bdat.getMember("select");
}

const char* getMaplistselect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistselect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberMaplistselect, id, 7);
    }
    return nullptr;
}

void initMaplistrscGmkId(const CBdatWrapper& bdat) {
    s_memberMaplistrscGmkId = bdat.getMember("rscGmkId");
}

unsigned int getMaplistrscGmkId(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistrscGmkId != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberMaplistrscGmkId, id, 3);
    }
    return 0;
}

void initMaplistene_disp_r(const CBdatWrapper& bdat) {
    s_memberMaplistene_disp_r = bdat.getMember("ene_disp_r");
}

unsigned int getMaplistene_disp_r(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistene_disp_r != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistene_disp_r, id, 1);
    }
    return 0;
}

void initMaplistene_disp_h(const CBdatWrapper& bdat) {
    s_memberMaplistene_disp_h = bdat.getMember("ene_disp_h");
}

unsigned int getMaplistene_disp_h(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistene_disp_h != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistene_disp_h, id, 1);
    }
    return 0;
}

void initMaplistene_release_r(const CBdatWrapper& bdat) {
    s_memberMaplistene_release_r = bdat.getMember("ene_release_r");
}

unsigned int getMaplistene_release_r(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistene_release_r != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistene_release_r, id, 1);
    }
    return 0;
}

void initMaplistene_release_h(const CBdatWrapper& bdat) {
    s_memberMaplistene_release_h = bdat.getMember("ene_release_h");
}

unsigned int getMaplistene_release_h(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistene_release_h != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistene_release_h, id, 1);
    }
    return 0;
}

void initMaplistwa_type(const CBdatWrapper& bdat) {
    s_memberMaplistwa_type = bdat.getMember("wa_type");
}

unsigned int getMaplistwa_type(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwa_type != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwa_type, id, 1);
    }
    return 0;
}

void initMaplistwa_pop_rate(const CBdatWrapper& bdat) {
    s_memberMaplistwa_pop_rate = bdat.getMember("wa_pop_rate");
}

unsigned int getMaplistwa_pop_rate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwa_pop_rate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwa_pop_rate, id, 1);
    }
    return 0;
}

void initMaplistwa_time_BNS(const CBdatWrapper& bdat) {
    s_memberMaplistwa_time_BNS = bdat.getMember("wa_time_BNS");
}

unsigned int getMaplistwa_time_BNS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwa_time_BNS != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwa_time_BNS, id, 2);
    }
    return 0;
}

void initMaplistwa_end_time(const CBdatWrapper& bdat) {
    s_memberMaplistwa_end_time = bdat.getMember("wa_end_time");
}

unsigned int getMaplistwa_end_time(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwa_end_time != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwa_end_time, id, 1);
    }
    return 0;
}

void initMaplistwb_type(const CBdatWrapper& bdat) {
    s_memberMaplistwb_type = bdat.getMember("wb_type");
}

unsigned int getMaplistwb_type(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwb_type != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwb_type, id, 1);
    }
    return 0;
}

void initMaplistwb_pop_rate(const CBdatWrapper& bdat) {
    s_memberMaplistwb_pop_rate = bdat.getMember("wb_pop_rate");
}

unsigned int getMaplistwb_pop_rate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwb_pop_rate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwb_pop_rate, id, 1);
    }
    return 0;
}

void initMaplistwb_time_BNS(const CBdatWrapper& bdat) {
    s_memberMaplistwb_time_BNS = bdat.getMember("wb_time_BNS");
}

unsigned int getMaplistwb_time_BNS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwb_time_BNS != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwb_time_BNS, id, 2);
    }
    return 0;
}

void initMaplistwb_end_time(const CBdatWrapper& bdat) {
    s_memberMaplistwb_end_time = bdat.getMember("wb_end_time");
}

unsigned int getMaplistwb_end_time(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwb_end_time != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwb_end_time, id, 1);
    }
    return 0;
}

void initMaplistwc_type(const CBdatWrapper& bdat) {
    s_memberMaplistwc_type = bdat.getMember("wc_type");
}

unsigned int getMaplistwc_type(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwc_type != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwc_type, id, 1);
    }
    return 0;
}

void initMaplistwc_pop_rate(const CBdatWrapper& bdat) {
    s_memberMaplistwc_pop_rate = bdat.getMember("wc_pop_rate");
}

unsigned int getMaplistwc_pop_rate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwc_pop_rate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwc_pop_rate, id, 1);
    }
    return 0;
}

void initMaplistwc_time_BNS(const CBdatWrapper& bdat) {
    s_memberMaplistwc_time_BNS = bdat.getMember("wc_time_BNS");
}

unsigned int getMaplistwc_time_BNS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwc_time_BNS != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwc_time_BNS, id, 2);
    }
    return 0;
}

void initMaplistwc_end_time(const CBdatWrapper& bdat) {
    s_memberMaplistwc_end_time = bdat.getMember("wc_end_time");
}

unsigned int getMaplistwc_end_time(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwc_end_time != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwc_end_time, id, 1);
    }
    return 0;
}

void initMaplistwd_type(const CBdatWrapper& bdat) {
    s_memberMaplistwd_type = bdat.getMember("wd_type");
}

unsigned int getMaplistwd_type(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwd_type != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwd_type, id, 1);
    }
    return 0;
}

void initMaplistwd_pop_rate(const CBdatWrapper& bdat) {
    s_memberMaplistwd_pop_rate = bdat.getMember("wd_pop_rate");
}

unsigned int getMaplistwd_pop_rate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwd_pop_rate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwd_pop_rate, id, 1);
    }
    return 0;
}

void initMaplistwd_time_BNS(const CBdatWrapper& bdat) {
    s_memberMaplistwd_time_BNS = bdat.getMember("wd_time_BNS");
}

unsigned int getMaplistwd_time_BNS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwd_time_BNS != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwd_time_BNS, id, 2);
    }
    return 0;
}

void initMaplistwd_end_time(const CBdatWrapper& bdat) {
    s_memberMaplistwd_end_time = bdat.getMember("wd_end_time");
}

unsigned int getMaplistwd_end_time(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwd_end_time != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwd_end_time, id, 1);
    }
    return 0;
}

void initMaplistwind_mor(const CBdatWrapper& bdat) {
    s_memberMaplistwind_mor = bdat.getMember("wind_mor");
}

unsigned int getMaplistwind_mor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_mor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_mor, id, 1);
    }
    return 0;
}

void initMaplistwind_non(const CBdatWrapper& bdat) {
    s_memberMaplistwind_non = bdat.getMember("wind_non");
}

unsigned int getMaplistwind_non(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_non != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_non, id, 1);
    }
    return 0;
}

void initMaplistwind_eve(const CBdatWrapper& bdat) {
    s_memberMaplistwind_eve = bdat.getMember("wind_eve");
}

unsigned int getMaplistwind_eve(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_eve != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_eve, id, 1);
    }
    return 0;
}

void initMaplistwind_nit(const CBdatWrapper& bdat) {
    s_memberMaplistwind_nit = bdat.getMember("wind_nit");
}

unsigned int getMaplistwind_nit(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_nit != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_nit, id, 1);
    }
    return 0;
}

void initMaplistwind_mnit(const CBdatWrapper& bdat) {
    s_memberMaplistwind_mnit = bdat.getMember("wind_mnit");
}

unsigned int getMaplistwind_mnit(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_mnit != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_mnit, id, 1);
    }
    return 0;
}

void initMaplistwind_emor(const CBdatWrapper& bdat) {
    s_memberMaplistwind_emor = bdat.getMember("wind_emor");
}

unsigned int getMaplistwind_emor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_emor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_emor, id, 1);
    }
    return 0;
}

void initMaplistwind_WA(const CBdatWrapper& bdat) {
    s_memberMaplistwind_WA = bdat.getMember("wind_WA");
}

unsigned int getMaplistwind_WA(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_WA != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_WA, id, 1);
    }
    return 0;
}

void initMaplistwind_WB(const CBdatWrapper& bdat) {
    s_memberMaplistwind_WB = bdat.getMember("wind_WB");
}

unsigned int getMaplistwind_WB(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_WB != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_WB, id, 1);
    }
    return 0;
}

void initMaplistwind_WC(const CBdatWrapper& bdat) {
    s_memberMaplistwind_WC = bdat.getMember("wind_WC");
}

unsigned int getMaplistwind_WC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_WC != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_WC, id, 1);
    }
    return 0;
}

void initMaplistwind_WD(const CBdatWrapper& bdat) {
    s_memberMaplistwind_WD = bdat.getMember("wind_WD");
}

unsigned int getMaplistwind_WD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwind_WD != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistwind_WD, id, 1);
    }
    return 0;
}

void initMaplistweatherATR(const CBdatWrapper& bdat) {
    s_memberMaplistweatherATR = bdat.getMember("weatherATR");
}

unsigned int getMaplistweatherATR(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistweatherATR != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistweatherATR, id, 1);
    }
    return 0;
}

void initMapliste_repoptime(const CBdatWrapper& bdat) {
    s_memberMapliste_repoptime = bdat.getMember("e_repoptime");
}

unsigned int getMapliste_repoptime(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMapliste_repoptime != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMapliste_repoptime, id, 1);
    }
    return 0;
}

void initMaplistm_repoptime(const CBdatWrapper& bdat) {
    s_memberMaplistm_repoptime = bdat.getMember("m_repoptime");
}

unsigned int getMaplistm_repoptime(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistm_repoptime != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistm_repoptime, id, 1);
    }
    return 0;
}

void initMaplistmapATR(const CBdatWrapper& bdat) {
    s_memberMaplistmapATR = bdat.getMember("mapATR");
}

unsigned int getMaplistmapATR(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistmapATR != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistmapATR, id, 1);
    }
    return 0;
}

void initMaplistwa_ON_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwa_ON_cndID = bdat.getMember("wa_ON_cndID");
}

unsigned int getMaplistwa_ON_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwa_ON_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwa_ON_cndID, id, 2);
    }
    return 0;
}

void initMaplistwa_OFF_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwa_OFF_cndID = bdat.getMember("wa_OFF_cndID");
}

unsigned int getMaplistwa_OFF_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwa_OFF_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwa_OFF_cndID, id, 2);
    }
    return 0;
}

void initMaplistwb_ON_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwb_ON_cndID = bdat.getMember("wb_ON_cndID");
}

unsigned int getMaplistwb_ON_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwb_ON_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwb_ON_cndID, id, 2);
    }
    return 0;
}

void initMaplistwb_OFF_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwb_OFF_cndID = bdat.getMember("wb_OFF_cndID");
}

unsigned int getMaplistwb_OFF_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwb_OFF_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwb_OFF_cndID, id, 2);
    }
    return 0;
}

void initMaplistwc_ON_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwc_ON_cndID = bdat.getMember("wc_ON_cndID");
}

unsigned int getMaplistwc_ON_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwc_ON_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwc_ON_cndID, id, 2);
    }
    return 0;
}

void initMaplistwc_OFF_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwc_OFF_cndID = bdat.getMember("wc_OFF_cndID");
}

unsigned int getMaplistwc_OFF_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwc_OFF_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwc_OFF_cndID, id, 2);
    }
    return 0;
}

void initMaplistwd_ON_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwd_ON_cndID = bdat.getMember("wd_ON_cndID");
}

unsigned int getMaplistwd_ON_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwd_ON_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwd_ON_cndID, id, 2);
    }
    return 0;
}

void initMaplistwd_OFF_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistwd_OFF_cndID = bdat.getMember("wd_OFF_cndID");
}

unsigned int getMaplistwd_OFF_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistwd_OFF_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistwd_OFF_cndID, id, 2);
    }
    return 0;
}

void initMapliststopTIME_cndID(const CBdatWrapper& bdat) {
    s_memberMapliststopTIME_cndID = bdat.getMember("stopTIME_cndID");
}

unsigned int getMapliststopTIME_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMapliststopTIME_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMapliststopTIME_cndID, id, 2);
    }
    return 0;
}

void initMaplistebb_ON_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistebb_ON_cndID = bdat.getMember("ebb_ON_cndID");
}

unsigned int getMaplistebb_ON_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistebb_ON_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistebb_ON_cndID, id, 2);
    }
    return 0;
}

void initMaplistebb_inn_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistebb_inn_cndID = bdat.getMember("ebb_inn_cndID");
}

unsigned int getMaplistebb_inn_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistebb_inn_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistebb_inn_cndID, id, 2);
    }
    return 0;
}

void initMaplistebb_pop_rate(const CBdatWrapper& bdat) {
    s_memberMaplistebb_pop_rate = bdat.getMember("ebb_pop_rate");
}

unsigned int getMaplistebb_pop_rate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistebb_pop_rate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistebb_pop_rate, id, 1);
    }
    return 0;
}

void initMaplistst_allOFF_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistst_allOFF_cndID = bdat.getMember("st_allOFF_cndID");
}

unsigned int getMaplistst_allOFF_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistst_allOFF_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistst_allOFF_cndID, id, 2);
    }
    return 0;
}

void initMaplistst_OFF_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistst_OFF_cndID = bdat.getMember("st_OFF_cndID");
}

unsigned int getMaplistst_OFF_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistst_OFF_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistst_OFF_cndID, id, 2);
    }
    return 0;
}

void initMaplistbgm_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistbgm_cndID = bdat.getMember("bgm_cndID");
}

unsigned int getMaplistbgm_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistbgm_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistbgm_cndID, id, 2);
    }
    return 0;
}

void initMaplistname_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistname_cndID = bdat.getMember("name_cndID");
}

unsigned int getMaplistname_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistname_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistname_cndID, id, 2);
    }
    return 0;
}

void initMaplistnameID(const CBdatWrapper& bdat) {
    s_memberMaplistnameID = bdat.getMember("nameID");
}

unsigned int getMaplistnameID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistnameID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistnameID, id, 2);
    }
    return 0;
}

void initMaplistchange_nameID(const CBdatWrapper& bdat) {
    s_memberMaplistchange_nameID = bdat.getMember("change_nameID");
}

unsigned int getMaplistchange_nameID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistchange_nameID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistchange_nameID, id, 2);
    }
    return 0;
}

void initMaplistmapON_cndID(const CBdatWrapper& bdat) {
    s_memberMaplistmapON_cndID = bdat.getMember("mapON_cndID");
}

unsigned int getMaplistmapON_cndID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistmapON_cndID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplistmapON_cndID, id, 2);
    }
    return 0;
}

void initMaplisttextID(const CBdatWrapper& bdat) {
    s_memberMaplisttextID = bdat.getMember("textID");
}

unsigned int getMaplisttextID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplisttextID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMaplisttextID, id, 2);
    }
    return 0;
}

void initMapliste_balloondisp_r(const CBdatWrapper& bdat) {
    s_memberMapliste_balloondisp_r = bdat.getMember("e_balloondisp_r");
}

unsigned int getMapliste_balloondisp_r(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMapliste_balloondisp_r != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMapliste_balloondisp_r, id, 1);
    }
    return 0;
}

void initMaplistzone(const CBdatWrapper& bdat) {
    s_memberMaplistzone = bdat.getMember("zone");
}

unsigned int getMaplistzone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMaplistzone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMaplistzone, id, 1);
    }
    return 0;
}

void initWeatherInfomsg(const CBdatWrapper& bdat) {
    s_memberWeatherInfomsg = bdat.getMember("msg");
}

unsigned int getWeatherInfomsg(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWeatherInfomsg != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberWeatherInfomsg, id, 2);
    }
    return 0;
}

void initWeatherInfoeff(const CBdatWrapper& bdat) {
    s_memberWeatherInfoeff = bdat.getMember("eff");
}

const char* getWeatherInfoeff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWeatherInfoeff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberWeatherInfoeff, id, 7);
    }
    return nullptr;
}

void initWeatherInfosnd(const CBdatWrapper& bdat) {
    s_memberWeatherInfosnd = bdat.getMember("snd");
}

const char* getWeatherInfosnd(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWeatherInfosnd != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberWeatherInfosnd, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no WeatherInfosnd_ira accessors (the names are not the original's)
void initWeatherInfosnd_ira(const CBdatWrapper& bdat) {
    s_memberWeatherInfosnd_ira = bdat.getMember("snd_ira");
}

const char* getWeatherInfosnd_ira(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWeatherInfosnd_ira != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberWeatherInfosnd_ira, id, 7);
    }
    return nullptr;
}

void initWeatherInfosndBegin(const CBdatWrapper& bdat) {
    s_memberWeatherInfosndBegin = bdat.getMember("sndBegin");
}

const char* getWeatherInfosndBegin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWeatherInfosndBegin != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberWeatherInfosndBegin, id, 7);
    }
    return nullptr;
}

void initTimeInfomsg(const CBdatWrapper& bdat) {
    s_memberTimeInfomsg = bdat.getMember("msg");
}

unsigned int getTimeInfomsg(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTimeInfomsg != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberTimeInfomsg, id, 2);
    }
    return 0;
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data): clang 3.9 makes a static table constant unless its address is passed on before inlining, so its slot
// getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbml

GfBdatMaplist::GfBdatMaplist() {
    m_fpMaplist = nullptr;
    m_fpWeatherInfo = nullptr;
    m_fpTimeInfo = nullptr;
    bdatRefresh();
}

GfBdatMaplist::~GfBdatMaplist() {
    destroyFP();
}

void GfBdatMaplist::destroyFP() {
    if (m_fpMaplist != nullptr) {
        delete m_fpMaplist;
        m_fpMaplist = nullptr;
    }
    if (m_fpWeatherInfo != nullptr) {
        delete m_fpWeatherInfo;
        m_fpWeatherInfo = nullptr;
    }
    if (m_fpTimeInfo != nullptr) {
        delete m_fpTimeInfo;
        m_fpTimeInfo = nullptr;
    }
}

void GfBdatMaplist::createFP() {
#line 135
    m_fpMaplist = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x5D));
    m_fpWeatherInfo = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x5F));
    m_fpTimeInfo = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x5E));
}

void GfBdatMaplist::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbml::initMaplistresource(*m_fpMaplist);
    _gfbml::initMaplistselect(*m_fpMaplist);
    _gfbml::initMaplistrscGmkId(*m_fpMaplist);
    _gfbml::initMaplistene_disp_r(*m_fpMaplist);
    _gfbml::initMaplistene_disp_h(*m_fpMaplist);
    _gfbml::initMaplistene_release_r(*m_fpMaplist);
    _gfbml::initMaplistene_release_h(*m_fpMaplist);
    _gfbml::initMaplistwa_type(*m_fpMaplist);
    _gfbml::initMaplistwa_pop_rate(*m_fpMaplist);
    _gfbml::initMaplistwa_time_BNS(*m_fpMaplist);
    _gfbml::initMaplistwa_end_time(*m_fpMaplist);
    _gfbml::initMaplistwb_type(*m_fpMaplist);
    _gfbml::initMaplistwb_pop_rate(*m_fpMaplist);
    _gfbml::initMaplistwb_time_BNS(*m_fpMaplist);
    _gfbml::initMaplistwb_end_time(*m_fpMaplist);
    _gfbml::initMaplistwc_type(*m_fpMaplist);
    _gfbml::initMaplistwc_pop_rate(*m_fpMaplist);
    _gfbml::initMaplistwc_time_BNS(*m_fpMaplist);
    _gfbml::initMaplistwc_end_time(*m_fpMaplist);
    _gfbml::initMaplistwd_type(*m_fpMaplist);
    _gfbml::initMaplistwd_pop_rate(*m_fpMaplist);
    _gfbml::initMaplistwd_time_BNS(*m_fpMaplist);
    _gfbml::initMaplistwd_end_time(*m_fpMaplist);
    _gfbml::initMaplistwind_mor(*m_fpMaplist);
    _gfbml::initMaplistwind_non(*m_fpMaplist);
    _gfbml::initMaplistwind_eve(*m_fpMaplist);
    _gfbml::initMaplistwind_nit(*m_fpMaplist);
    _gfbml::initMaplistwind_mnit(*m_fpMaplist);
    _gfbml::initMaplistwind_emor(*m_fpMaplist);
    _gfbml::initMaplistwind_WA(*m_fpMaplist);
    _gfbml::initMaplistwind_WB(*m_fpMaplist);
    _gfbml::initMaplistwind_WC(*m_fpMaplist);
    _gfbml::initMaplistwind_WD(*m_fpMaplist);
    _gfbml::initMaplistweatherATR(*m_fpMaplist);
    _gfbml::initMapliste_repoptime(*m_fpMaplist);
    _gfbml::initMaplistm_repoptime(*m_fpMaplist);
    _gfbml::initMaplistmapATR(*m_fpMaplist);
    _gfbml::initMaplistwa_ON_cndID(*m_fpMaplist);
    _gfbml::initMaplistwa_OFF_cndID(*m_fpMaplist);
    _gfbml::initMaplistwb_ON_cndID(*m_fpMaplist);
    _gfbml::initMaplistwb_OFF_cndID(*m_fpMaplist);
    _gfbml::initMaplistwc_ON_cndID(*m_fpMaplist);
    _gfbml::initMaplistwc_OFF_cndID(*m_fpMaplist);
    _gfbml::initMaplistwd_ON_cndID(*m_fpMaplist);
    _gfbml::initMaplistwd_OFF_cndID(*m_fpMaplist);
    _gfbml::initMapliststopTIME_cndID(*m_fpMaplist);
    _gfbml::initMaplistebb_ON_cndID(*m_fpMaplist);
    _gfbml::initMaplistebb_inn_cndID(*m_fpMaplist);
    _gfbml::initMaplistebb_pop_rate(*m_fpMaplist);
    _gfbml::initMaplistst_allOFF_cndID(*m_fpMaplist);
    _gfbml::initMaplistst_OFF_cndID(*m_fpMaplist);
    _gfbml::initMaplistbgm_cndID(*m_fpMaplist);
    _gfbml::initMaplistname_cndID(*m_fpMaplist);
    _gfbml::initMaplistnameID(*m_fpMaplist);
    _gfbml::initMaplistchange_nameID(*m_fpMaplist);
    _gfbml::initMaplistmapON_cndID(*m_fpMaplist);
    _gfbml::initMaplisttextID(*m_fpMaplist);
    _gfbml::initMapliste_balloondisp_r(*m_fpMaplist);
    _gfbml::initMaplistzone(*m_fpMaplist);
    _gfbml::initWeatherInfomsg(*m_fpWeatherInfo);
    _gfbml::initWeatherInfoeff(*m_fpWeatherInfo);
    _gfbml::initWeatherInfosnd(*m_fpWeatherInfo);
    _gfbml::initWeatherInfosnd_ira(*m_fpWeatherInfo);
    _gfbml::initWeatherInfosndBegin(*m_fpWeatherInfo);
    _gfbml::initTimeInfomsg(*m_fpTimeInfo);
}

unsigned int GfBdatMaplist::getMaplistStart() const {
    return Bdat::getIdTop(m_fpMaplist->m_fp);
}

unsigned int GfBdatMaplist::getMaplistEnd() const {
    return Bdat::getIdTop(m_fpMaplist->m_fp) + Bdat::getIdCount(m_fpMaplist->m_fp);
}

const char* GfBdatMaplist::getMaplistresource(unsigned int id) const {
    return _gfbml::getMaplistresource(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistweatherATR(unsigned int id) const {
    return _gfbml::getMaplistweatherATR(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistebb_ON_cndID(unsigned int id) const {
    return _gfbml::getMaplistebb_ON_cndID(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistebb_inn_cndID(unsigned int id) const {
    return _gfbml::getMaplistebb_inn_cndID(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistbgm_cndID(unsigned int id) const {
    return _gfbml::getMaplistbgm_cndID(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistnameID(unsigned int id) const {
    return _gfbml::getMaplistnameID(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMapliste_balloondisp_r(unsigned int id) const {
    return _gfbml::getMapliste_balloondisp_r(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistzone(unsigned int id) const {
    return _gfbml::getMaplistzone(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistw_type(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbml::getMaplistwa_type,
        _gfbml::getMaplistwb_type,
        _gfbml::getMaplistwc_type,
        _gfbml::getMaplistwd_type,
    };
    return _gfbml::getSlot(s_getters, slot)(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistw_pop_rate(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbml::getMaplistwa_pop_rate,
        _gfbml::getMaplistwb_pop_rate,
        _gfbml::getMaplistwc_pop_rate,
        _gfbml::getMaplistwd_pop_rate,
    };
    return _gfbml::getSlot(s_getters, slot)(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistw_time_BNS(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbml::getMaplistwa_time_BNS,
        _gfbml::getMaplistwb_time_BNS,
        _gfbml::getMaplistwc_time_BNS,
        _gfbml::getMaplistwd_time_BNS,
    };
    return _gfbml::getSlot(s_getters, slot)(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistw_end_time(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbml::getMaplistwa_end_time,
        _gfbml::getMaplistwb_end_time,
        _gfbml::getMaplistwc_end_time,
        _gfbml::getMaplistwd_end_time,
    };
    return _gfbml::getSlot(s_getters, slot)(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistw_ON_cndID(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbml::getMaplistwa_ON_cndID,
        _gfbml::getMaplistwb_ON_cndID,
        _gfbml::getMaplistwc_ON_cndID,
        _gfbml::getMaplistwd_ON_cndID,
    };
    return _gfbml::getSlot(s_getters, slot)(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getMaplistw_OFF_cndID(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbml::getMaplistwa_OFF_cndID,
        _gfbml::getMaplistwb_OFF_cndID,
        _gfbml::getMaplistwc_OFF_cndID,
        _gfbml::getMaplistwd_OFF_cndID,
    };
    return _gfbml::getSlot(s_getters, slot)(*m_fpMaplist, id);
}

unsigned int GfBdatMaplist::getWeatherInfomsg(unsigned int id) const {
    return _gfbml::getWeatherInfomsg(*m_fpWeatherInfo, id);
}

const char* GfBdatMaplist::getWeatherInfoeff(unsigned int id) const {
    return _gfbml::getWeatherInfoeff(*m_fpWeatherInfo, id);
}

const char* GfBdatMaplist::getWeatherInfosnd(unsigned int id) const {
    return _gfbml::getWeatherInfosnd(*m_fpWeatherInfo, id);
}

const char* GfBdatMaplist::fn_710020A2AC(unsigned int id) const {
    return _gfbml::getWeatherInfosnd_ira(*m_fpWeatherInfo, id);
}

const char* GfBdatMaplist::getWeatherInfosndBegin(unsigned int id) const {
    return _gfbml::getWeatherInfosndBegin(*m_fpWeatherInfo, id);
}

unsigned int GfBdatMaplist::getTimeInfomsg(unsigned int id) const {
    return _gfbml::getTimeInfomsg(*m_fpTimeInfo, id);
}

}  // namespace gf
