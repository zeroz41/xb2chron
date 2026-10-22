#ifndef ML_FONT_FONTSYS_H
#define ML_FONT_FONTSYS_H

class Stream;
namespace grlib { class CGLibTextureBuffer; }

// monolib's font: a font file's glyphs drawn into one texture, found by character code (font.cpp). The names of
// the fields no assertion names are not the original's.
class FontSys {
public:
    // the font file's header (font.cpp defines it)
    struct Header;
    // one glyph: its code, its size and its place in the texture
    struct Glyph {
        Glyph() : m_code(0), m_width(0.0f), m_height(0.0f), m_ux(0.0f), m_vy(0.0f), m_uw(0.0f), m_vh(0.0f) {}

        unsigned short m_code;
        float m_width;
        float m_height;
        float m_ux;
        float m_vy;
        float m_uw;
        float m_vh;
    };
    // a glyph in the table's chain of its hash
    struct Node {
        Node() : m_next(nullptr), m_code(0), m_glyph(nullptr) {}

        Node* m_next;
        unsigned short m_code;
        Glyph* m_glyph;
    };
    enum { TABLE_SIZE = 101 };

    FontSys();
    ~FontSys();
    // the glyphs of the font file at data (size bytes), drawn into the texture
    void construct(void* data, int size);
    // everything freed; the font file's data is returned
    void* destroy();
    float get_font_size() const;
    float get_origin_width() const;
    float get_origin_height() const;
    // the glyph of code made current (a code 0xFFxx is xx); none clears the current one
    void get_texture(unsigned short code);
    grlib::CGLibTextureBuffer* get_texobj();
    // the current glyph's
    float get_width() const;
    float get_height() const;
    float get_ux() const;
    float get_vy() const;
    float get_uw() const;
    float get_vh() const;

    // a key's hash: its bytes, last first, from 5381 by 65599
    static unsigned int hash(const unsigned short& code) {
        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&code);
        unsigned int value = 5381;
        for (int i = sizeof(code) - 1; i >= 0; i--) {
            value = value * 65599 + bytes[i];
        }
        return value;
    }

    // glyph entered under code; false, entering nothing, when the code has one (inline: construct inlines it; the
    // name is not the original's)
    bool insert(const unsigned short& code, Glyph* glyph) {
        Node** link = &m_table[hash(code) % TABLE_SIZE];
        if (*link == nullptr) {
            *link = new Node();
            (*link)->m_code = code;
            (*link)->m_glyph = glyph;
            return true;
        }
        Node* node = *link;
        for (;;) {
            if (node->m_code == code) {
                return false;
            }
            if (node->m_next == nullptr) {
                break;
            }
            node = node->m_next;
        }
        node->m_next = new Node();
        node->m_next->m_code = code;
        node->m_next->m_glyph = glyph;
        return true;
    }

    Header* m_head;             // read's (the getters assert `m_head`)
    Node* m_table[TABLE_SIZE];  // the glyphs by their code's hash
    void* m_data;               // the font file (construct asserts `m_data == NULL`)
    float m_width;              // the current glyph's (get_texture)
    float m_height;
    float m_ux;
    float m_vy;
    float m_uw;
    float m_vh;
    grlib::CGLibTextureBuffer* m_texobj;  // the glyphs' texture
};

#endif
