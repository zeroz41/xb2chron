#ifndef CLASSES_EVENT_CHARAOBJ_H
#define CLASSES_EVENT_CHARAOBJ_H

namespace event {
// table 0x7100B3CAF8
class CharaObj {
public:
    virtual ~CharaObj();  // slot 0
    void playMotion(const char* name, float a, float b, float c);
    void playFade(bool fade, float time);
    void playWink(int a, float b, bool c, float d, float e, int f, bool g, bool h);
    void playTalk(bool a, float b, bool c, bool d, float e, float f, float g, float h);

    unsigned char pad_8[0xc98];
    // bit 5: playFade's flag (it sets or clears it); the name is not the original's
    unsigned int m_flags;  // 0xca0
};
}  // namespace event

#endif
