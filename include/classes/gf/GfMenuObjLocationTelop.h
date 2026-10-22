#ifndef CLASSES_GF_GFMENUOBJLOCATIONTELOP_H
#define CLASSES_GF_GFMENUOBJLOCATIONTELOP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62DC8
class GfMenuObjLocationTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    // what open shows (gmk::GmkLandmark::beginEvent fills one)
    struct OpenParam {
        unsigned char* m_bdat;  // the message table of the name
        unsigned int m_name;    // the name's id there
        // 0 a landmark, 1 a secret area, 2 an area (the name is not the original's)
        unsigned short m_type;
        unsigned short m_mapId;  // GfGameManager::getMapID's (the name is not the original's)
        bool m_disp;             // open does nothing without it (the name is not the original's)
    };
    GfMenuObjLocationTelop(unsigned int handle);
    virtual ~GfMenuObjLocationTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void open(const OpenParam& param);  // through GfMenuOrderMgr's channel 2
    static void close();
    static void cancel();
};
}  // namespace gf

#endif
