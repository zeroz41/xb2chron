#ifndef CLASSES_GF_GFDROPITEMPARAMS_H
#define CLASSES_GF_GFDROPITEMPARAMS_H

#include "mm/mtl/Vector.h"

namespace gf {
// a row of RSC_dropitemParam (Vector<GfDropitemParam>::resize, by its symbols, steps 0x5C bytes). The field names
// follow the table's column names loadFromBdat reads into them (the names are not the original's)
struct GfDropitemParam {
    // the defaults Vector<GfDropitemParam>::resize stores in each new row
    GfDropitemParam()
        : m_height(2.0f), m_heightRand(0.0f), m_distance(1.0f), m_distanceRand(0.0f), m_time(0.5f),
          m_speedAtte(0.5f), m_rotYRand(0.0f), m_lifeTime(5.0f), m_flashTime(9.0f), m_flashInterval1(0.5f),
          m_flashInterval2(0.5f), m_vanishTime1(0.2f), m_vanishTime2(0.05f), m_radius(0.1f), m_initHeight(0.0f),
          m_startScale(0.0f), m_endScale(1.0f), m_scaleTime(0.5f), m_isSpin(false), m_spinSpeed(360.0f),
          m_startSpinBound(0), m_startSpinTime(1.0f), m_boundNum(2) {}
    // reads row id of RSC_dropitemParam
    void loadFromBdat(int& id);

    float m_height;  // "height"
    float m_heightRand;  // "heightRand"
    float m_distance;  // "distance"
    float m_distanceRand;  // "distanceRand"
    float m_time;  // "time"
    float m_speedAtte;  // "speedAtte"
    float m_rotYRand;  // "rotYRand"
    float m_lifeTime;  // "lifeTime"
    float m_flashTime;  // "flashTime"
    float m_flashInterval1;  // "flashInterval1"
    float m_flashInterval2;  // "flashInterval2"
    float m_vanishTime1;  // "vanishTime1"
    float m_vanishTime2;  // "vanishTime2"
    float m_radius;  // "radius"
    float m_initHeight;  // "initHeight"
    float m_startScale;  // "startScale"
    float m_endScale;  // "endScale"
    float m_scaleTime;  // "scaleTime"
    bool m_isSpin;  // "isSpin"
    float m_spinSpeed;  // "spinSpeed"
    unsigned int m_startSpinBound;  // "startSpinBound" (a u8 column)
    float m_startSpinTime;  // "startSpinTime"
    unsigned int m_boundNum;  // "boundNum" (a u8 column)
};

// table 0x7100B528F0
class GfDropitemParams {
public:
    GfDropitemParams();
    virtual ~GfDropitemParams();  // slot 0
    void update();

    mm::mtl::Vector<GfDropitemParam> m_params;  // RSC_dropitemParam's rows (the name is not the original's)
    int m_idTop;  // RSC_dropitemParam's first id (Bdat::getIdTop's; the name is not the original's)
};
}  // namespace gf

#endif
