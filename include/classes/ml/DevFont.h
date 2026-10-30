// not proven yet: its table differs from the original's (word 29: =-440 where the original has =-448)
#ifndef CLASSES_ML_DEVFONT_H
#define CLASSES_ML_DEVFONT_H

#include "classes/ml/FontLayer.h"
#include "classes/ml/WorkObj.h"

namespace mm { class Col4; }

namespace ml {
// a base of ml::DevFont no evidence names yet
class TUnk_B75B88 {
public:
    virtual ~TUnk_B75B88();
};
// table 0x7100B75AA0; base at 0x1C0 unknown (TUnk_B75B88)
class DevFont : public ::ml::FontLayer, public ::ml::WorkObj, public TUnk_B75B88 {
public:
    virtual ~DevFont();  // slot 0
    virtual bool wkStandbyLogin();  // slot 2
    virtual bool wkStandbyLogout();  // slot 3
    virtual void wkUpdate();  // slot 4
    virtual void wkTail();  // slot 5
    virtual bool createFont() = 0;  // slot 6
    virtual void releaseFont() = 0;  // slot 7

    static void fontLayerStyle(const FontLayer* layer, FONT_STYLE style);
    static void fontLayer(const FontLayer* layer, int x, int y, const char* text);
    static void fontLayerColor(const FontLayer* layer, const mm::Col4& col);
    static void fontLayerShadow(const FontLayer* layer, bool on);
    static void fontLayerFlush(const FontLayer* layer, bool on);
    static void fontLayerScale(const FontLayer* layer, float x, float y);
};
}  // namespace ml

#endif
