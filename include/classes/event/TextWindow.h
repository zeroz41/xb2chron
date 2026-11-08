#ifndef CLASSES_EVENT_TEXTWINDOW_H
#define CLASSES_EVENT_TEXTWINDOW_H

#include "mm/mtl/FixStr.h"

namespace gf { class GF_OBJ_HANDLE; class GfMenuCallContext; }

namespace event {
// table 0x7100B3D610
class TextWindow {
public:
    // built in place by TextManager's constructor (inlined into every Singleton<TextManager>::getPtr); size 0x298
    TextWindow() : m_flags(0), pad_218(-1), m_context(0), pad_250(0), pad_25c(0) {}
    virtual ~TextWindow() {}  // slot 0
    void update();
    void erase();
    void render();
    void write(const char*, const char*, unsigned char*, unsigned int, gf::GF_OBJ_HANDLE*);
    // bit 0: a window is shown (render draws only then); bits 0-1 cleared together; the name is not the original's
    unsigned int m_flags;
    // the names are not the original's: render draws "[name]" and the text under "TEXTWIN"
    mm::mtl::FixStr<256> m_name;
    mm::mtl::FixStr<256> m_text;
    unsigned int pad_214;
    long pad_218;  // -1 after construction
    // the balloon's call context: erase closes it and releases the reference (the name is not the original's)
    gf::GfMenuCallContext* m_context;
    // update counts it down from 4 once the balloon reports result 1, then erases (the name is not the original's)
    int m_closeWait;
    unsigned char pad_22c[0x4];
    // 0x230..0x25c: zeroed by TextManager::init (one memset of 0x2d bytes)
    // TextManager::render's debug lines "delay(%.1f / %.1f)", "life(%.1f / %.1f)" and "delayBack(%.1f)" draw
    // these (current / total); the names are not the original's
    float m_lifeMax;
    float m_delayMax;
    unsigned char pad_238[0x4];
    float m_life;
    float m_delay;
    float m_delayBack;
    unsigned int pad_248;  // TextManager::write passes it to GfMenuObjEventSubtitle::dispText as the line
    unsigned char pad_24c[0x4];
    unsigned long pad_250;
    unsigned char pad_258[0x4];
    unsigned char pad_25c;
    unsigned char pad_25d[0x3b];
};
}  // namespace event

#endif
