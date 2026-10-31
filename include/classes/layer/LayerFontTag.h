#ifndef CLASSES_LAYER_LAYERFONTTAG_H
#define CLASSES_LAYER_LAYERFONTTAG_H

#include "classes/layer/LayerTag.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccFontStyle.h"
#include "mm/Col4.h"

namespace layer { class LayerFontResObj; }
namespace layer { class LayerFontStyleObj; }
namespace layer { class LayerFontIconObj; }

namespace layer {
// what LayerFontDrawBuffer::createChar hands calcParseString's passes (0x18 bytes; the names are not the original's)
struct LayerTagWork {
    unsigned int m_charNum;  // parseNotTag counts the characters of the sizing pass here
    unsigned char pad_4[0x4];
    unsigned char pad_8[0x8];
    unsigned int m_length;  // createChar: the text's length in bytes
    unsigned int m_bufferLength;  // the same
};

// LayerFontDrawBuffer's base: a LayerTag that lays out a message's characters (1.0.0 has its table, constructor and
// destructor out of line; 3.0.1's linker kept only LayerFontDrawBuffer's table)
class LayerFontTag : public ::layer::LayerTag {
public:
    // a character's quad in the vertex buffer (0x24 bytes; the type's name is not the original's)
    struct Vertex {
        float m_width;
        float m_height;
        float m_x;
        float m_y;
        float m_uvWidth;
        float m_uvHeight;
        float m_u;
        float m_v;
        unsigned char m_color[4];
    };
    virtual ~LayerFontTag() {}  // slot 0
    virtual void beginParseString();  // slot 2
    virtual void parseNotTag(unsigned char const* text, unsigned int& pos);  // slot 4
    virtual void parseNotTag(wchar_t const* text, unsigned int& pos);  // slot 5
    virtual bool callTagStart(char const* name, layer::LayerTagTbl const* tbl, unsigned int num);  // slot 6
    virtual bool callTagEnd(char const* name);  // slot 7
    virtual void createFontCode(unsigned short code) = 0;  // slot 9 (parseNotTag's creation pass)
    virtual void createRubyFontCode(unsigned short code) = 0;  // slot 10
    virtual void createFontIcon(unsigned short code) = 0;  // slot 11
    virtual void createLineBreak() = 0;  // slot 12 (parseNotTag's creation pass, at a line feed)

    void calcTagColorStart(const LayerTagTbl* tbl, unsigned int num);
    void calcTagIconStart(const LayerTagTbl* tbl, unsigned int num);
    void calcTagRubyEnd();

    // its tags' names: "System:Color", "System:Ruby" and two more (callTagStart, callTagEnd)
    static const char* s_resTagTbl[4];

    // The field names are not the original's.
    const LayerFontStyleObj* m_styleObj;  // 0x8
    const LayerFontResObj* m_resObj;      // 0x10
    const LayerFontIconObj* m_iconObj;    // 0x18
    const LyrFontStyleData* m_styleData;  // 0x20
    bool m_isCreate;  // 0x28: false in createChar's sizing pass, true in its creation pass
    bool m_doubleNext;  // 0x29: the next character takes twice its advance (createFontCode clears it)
    unsigned char pad_2A[0x6];
    LayerTagWork* m_work;  // 0x30: createChar's
    LayerFontSetting m_setting;  // 0x38: the constructor's (1 and 2 lay characters out at the cell's width)
    unsigned int m_axis;       // 0x3C: m_pos's index along a line (setting != 0)
    unsigned int m_crossAxis;  // 0x40: the other one (setting == 0)
    unsigned char pad_44[0x4];
    Vertex* m_vertexTop;      // 0x48: createWorkBuffer's
    Vertex* m_vertex;         // 0x50: the next character's
    Vertex* m_rubyVertexTop;  // 0x58: the same for ruby characters
    Vertex* m_rubyVertex;     // 0x60
    mm::Col4 m_color;         // 0x68: what the characters take (System:Color sets it)
    mm::Col4 m_defaultColor;  // 0x78: what callTagEnd puts back at the end of a System:Color tag
    unsigned char pad_88[0x408];
    int m_width;     // 0x490: zeroed by beginParseString (its use is not known yet)
    // 0x494: the next character's position (the constructor starts it at minus the font's border times the
    // style's scale); createFontCode advances m_pos[m_axis]
    int m_pos[2];
    unsigned int m_lineNum;  // 0x49C: parseNotTag counts the sizing pass's line feeds
    unsigned short m_lastCode;  // 0x4A0: the last printable character parseNotTag saw
};
}  // namespace layer

#endif
