#ifndef CLASSES_EVENT_TEXTMANAGER_H
#define CLASSES_EVENT_TEXTMANAGER_H

#include <string.h>
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/TextCaption.h"
#include "classes/event/TextWindow.h"

namespace event { enum MSG_TYPE : int; class CharaObj; }

namespace event {
// table 0x7100B3D650; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::TextManager>
class TextManager : public IManager, public mm::mtl::Singleton<TextManager> {
public:
    // inlined into every Singleton<TextManager>::getPtr (no out-of-line copy)
    TextManager()
        : m_flags(0), pad_14(0), pad_3c4(0), pad_3c8(0), pad_5c8(0), pad_5d0(0), pad_5e0(0), pad_600(0) {}
    virtual ~TextManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    void update();
    void render();
    // the symbol _ZN5event11TextManager5replyEPKciPNS_8CharaObjE (RandPlayer::Reply::update calls it)
    void reply(const char* msb, int id, CharaObj* chara);
    // 1.0.0's TextManager::init (0x71000F3B6C); 3.0.1 inlines it into OnEventProc
    void init() {
        m_flags = 0;
        pad_3c4 = 0;
        pad_5c8 = 0;
        pad_3c8 = 0;
        pad_600 = 0;
        memset(m_window.pad_230, 0, 0x2d);
        memset(&pad_5d0, 0, 0x11);
    }

    // bit 5 is cleared by message 18; init() zeroes the word; the name is not the original's
    unsigned int m_flags;  // 0x10
    unsigned int pad_14;
    // the names are not the original's
    TextCaption m_caption;  // 0x18
    TextWindow m_window;    // 0x128
    // the fields below are zeroed by init(); no reader seen yet
    unsigned int pad_3c0;
    unsigned int pad_3c4;
    unsigned char pad_3c8;
    unsigned char pad_3c9[0x1ff];
    unsigned int pad_5c8;
    unsigned char pad_5cc[0x4];
    unsigned long pad_5d0;
    unsigned char pad_5d8[0x8];
    unsigned char pad_5e0;
    unsigned char pad_5e1[0x1f];
    unsigned int pad_600;
};
}  // namespace event

#endif
