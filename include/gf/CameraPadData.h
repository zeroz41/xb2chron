#ifndef GF_CAMERAPADDATA_H
#define GF_CAMERAPADDATA_H

#include "fw/PadRelay.h"

namespace gf {

// the camera's pad: a relay whose actions raise one flag each and whose axes keep the right stick (no table; no
// code in 3.0.1 constructs one). The fields' names are not the original's: each is named by the handler that sets it
class CameraPadData : public ::fw::PadRelay {
public:
    CameraPadData();
    ~CameraPadData();
    // out of line in 1.0.0; inline in 3.0.1
    void reset() {
        m_arx = 0.0f;
        m_ary = 0.0f;
        m_reset = false;
        m_allReset = false;
        m_zoom = false;
        m_height = false;
        m_sideLeft = false;
        m_sideRight = false;
        m_sideReset = false;
    }
    void bind();
    // out of line in 1.0.0; inline in 3.0.1
    void unbind() { PadRelay::unbind(); }
    void update();
    void resetAction();
    void zoomCamera();
    void heightCamera();
    void sideLeftCamera();
    void sideRightCamera();
    void sideResetCamera();
    void allResetAction();
    void setARX(float value);
    void setARY(float value);

    float m_arx;  // setARX
    float m_ary;  // setARY
    bool m_reset;  // resetAction
    bool m_allReset;  // allResetAction
    bool m_zoom;  // zoomCamera
    bool m_height;  // heightCamera
    bool m_sideLeft;  // sideLeftCamera
    bool m_sideRight;  // sideRightCamera
    bool m_sideReset;  // sideResetCamera
};

}  // namespace gf

#endif
