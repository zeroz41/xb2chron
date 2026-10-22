#ifndef ML_SYSTEMERRORAPPLET_H
#define ML_SYSTEMERRORAPPLET_H

#include "nn/result.h"

namespace ml {
// the system's error applet (1.0.0 kept ml::ErrorApplet::showApplet(Config const&) next to it; 3.0.1's linker
// dropped it)
class SystemErrorApplet {
public:
    // shows the applet for a failed result; always true
    static bool showApplet(nn::Result& result);
};
}  // namespace ml

#endif
