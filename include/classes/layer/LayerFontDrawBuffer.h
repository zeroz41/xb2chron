#ifndef CLASSES_LAYER_LAYERFONTDRAWBUFFER_H
#define CLASSES_LAYER_LAYERFONTDRAWBUFFER_H

#include "classes/layer/LayerFontTag.h"

namespace grlib { class CGLibDblUniformBlock; class CGLibVtxOneInstans; }
namespace layer { class LayerObjFont; class LayerObjSortFont; }

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
        unsigned char pad_0[0x38];
        // 0x38: a LayerObjSortFont constructed in its buffers; LayerObjTopFont::setDrawList sorts it
        LayerObjSortFont* m_sortObj;
        unsigned char pad_40[0x8];
        Line* m_lines;  // 0x48: one per line
        unsigned char pad_50[0x10];
        // 0x60, 0x68: constructed in place in its buffers; LayerObjFont destroys them before it frees the work
        grlib::CGLibVtxOneInstans* m_instans;
        grlib::CGLibDblUniformBlock* m_uniform;
    };

    // The field names are not the original's.
    // 0x4A4 (in LayerFontTag's tail padding), 0x4A8: LayerObjFont::setMsg copies the object's alignment in
    LayerFontHorizontal m_horizontal;
    LayerFontVertical m_vertical;
    unsigned char pad_4AC[0x4];
    Work* m_buffer;  // 0x4B0: what createChar returns
    LayerObjFont* m_obj;  // 0x4B8: the constructor's
    int m_charIndex;  // 0x4C0: the next character's index
    int m_iconIndex;  // 0x4C4: the next icon's index (createFontIcon; its vertices go to m_rubyVertex)
    int m_maxSize[2];  // 0x4C8: the furthest m_pos reached
};
}  // namespace layer

#endif
