#ifndef ML_DRPIXLPOSTOBJCAPTURE_H
#define ML_DRPIXLPOSTOBJCAPTURE_H

#include "grlib/CGLibRenderTarget.h"
#include "ml/DrPixlPostObj.h"

namespace ml {

// DrPixlPostMan::m_capture: a screen capture into its own render target (the field names are not the original's)
class DrPixlPostObjCapture : public DrPixlPostObj {
public:
    DrPixlPostObjCapture(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjCapture();
    void update();
    void render();
    void renderCaputre();
    void renderDef();

    grlib::CGLibRenderTarget m_target;  // 0x18
    // 0x3E0: the constructor and destructor set 3; update clears 1 (sizing m_target) and sets 8 while 4 is set;
    // render skips while 4 is set and clears 2
    unsigned int m_flags;
};

}  // namespace ml

#endif
