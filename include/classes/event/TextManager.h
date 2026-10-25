#ifndef CLASSES_EVENT_TEXTMANAGER_H
#define CLASSES_EVENT_TEXTMANAGER_H

#include <string.h>

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::TextManager no evidence names yet
class TUnk_B3D650 {
public:
    virtual ~TUnk_B3D650() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::TextManager no evidence names yet
class TUnk_B3D678 {
public:
    virtual ~TUnk_B3D678() {}
};
// table 0x7100B3D650; base at 0x0 unknown (TUnk_B3D650), base at 0x8 unknown (TUnk_B3D678)
class TextManager : public TUnk_B3D650, public TUnk_B3D678 {
public:
    virtual ~TextManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    void update();
    void render();
    // 1.0.0's TextManager::init (0x71000F3B6C); 3.0.1 inlines it into OnEventProc
    void init() {
        m_flags = 0;
        pad_3c4 = 0;
        pad_5c8 = 0;
        pad_3c8 = 0;
        pad_600 = 0;
        memset(pad_358, 0, sizeof(pad_358));
        memset(pad_5d0, 0, sizeof(pad_5d0));
    }

    // bit 5 is cleared by message 18; init() zeroes the word; the name is not the original's
    unsigned int m_flags;  // 0x10
    unsigned char pad_14[0x344];
    // the fields below are zeroed by init(); no reader seen yet
    unsigned char pad_358[0x2d];
    unsigned char pad_385[0x3f];
    unsigned int pad_3c4;
    unsigned char pad_3c8;
    unsigned char pad_3c9[0x1ff];
    unsigned int pad_5c8;
    unsigned char pad_5cc[0x4];
    unsigned char pad_5d0[0x11];
    unsigned char pad_5e1[0x1f];
    unsigned int pad_600;
};
}  // namespace event

#endif
