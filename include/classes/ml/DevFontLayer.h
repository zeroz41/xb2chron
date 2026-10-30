#ifndef CLASSES_ML_DEVFONTLAYER_H
#define CLASSES_ML_DEVFONTLAYER_H

#include "classes/ml/WorkObj.h"

namespace ml { class FontLayer; }

namespace ml {
// table 0x7100B75BA8
class DevFontLayer : public ::ml::WorkObj {
public:
    virtual ~DevFontLayer();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogout();  // slot 15

    // draws or drops the queued commands (DevFont::fontLayerFlush)
    void flush(bool on);

    unsigned char pad_1a8[0x18];
    const FontLayer* m_layer;  // 0x1C0 the FontLayer it serves (FontLayer's constructor sets it; the name is not the original's)
    unsigned char pad_1c8[0x24];
    bool m_done;               // 0x1EC set: wkUpdate sends event 0 and logout may go on (the name is not the original's)
};
}  // namespace ml

#endif
