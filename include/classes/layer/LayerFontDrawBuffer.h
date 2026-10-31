#ifndef CLASSES_LAYER_LAYERFONTDRAWBUFFER_H
#define CLASSES_LAYER_LAYERFONTDRAWBUFFER_H

#include "classes/layer/LayerFontTag.h"

namespace layer { class LayerObjFont; }

namespace layer {
// table 0x7100B805C8
class LayerFontDrawBuffer : public ::layer::LayerFontTag {
public:
    struct Work;
    LayerFontDrawBuffer(const LayerFontResObj* res, const LayerFontStyleObj* style, const LyrFontStyleData* styleData,
                        const LayerFontIconObj* icon, LayerFontSetting setting, LayerObjFont* obj);
    // its D1 is LayerTag's (the table's slot 0); the D0 alone is emitted
    virtual ~LayerFontDrawBuffer() {}  // slot 0
    virtual void createFontCode(unsigned short code);  // slot 9
    virtual void createRubyFontCode(unsigned short code);  // slot 10
    virtual void createFontIcon(unsigned short code);  // slot 11
    virtual void createLineBreak();  // slot 12

    Work* createChar(const unsigned char* text);
    void createWorkBuffer(const LayerTagWork& work, const unsigned char* text);
    void endWorkSetup();

    // a line's characters (0x10 bytes; the names are not the original's)
    struct LineRange {
        int m_width;    // where its last character ends
        short m_first;  // its first character's index (-1: none yet)
        short m_last;   // its last character's index
    };
    struct Line {
        LineRange m_main;
        LineRange m_ruby;
    };
    // what createWorkBuffer allocates and createChar returns (0x70 bytes, then its buffers; the names are not the
    // original's)
    struct Work {
        unsigned char pad_0[0x48];
        Line* m_lines;  // 0x48: one per line
        unsigned char pad_50[0x20];
    };

    // The field names are not the original's.
    unsigned char pad_4A8[0x8];
    Work* m_buffer;  // 0x4B0: what createChar returns
    LayerObjFont* m_obj;  // 0x4B8: the constructor's
    int m_charIndex;  // 0x4C0: the next character's index
    unsigned char pad_4C4[0x4];
    int m_maxSize[2];  // 0x4C8: the furthest m_pos reached
};
}  // namespace layer

#endif
