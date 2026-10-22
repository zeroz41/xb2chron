#include "assert.h"
#include "grlib/GrlTypes.h"
#include "grlib/CGLibTexture.h"
#include "grlib/CGLibAcc2DTexture.h"
#include "ml/font/Color.h"
#include "ml/font/FontSys.h"
#include "ml/SystemErrorApplet.h"
#include "nn/err.h"
#include "grlib/CGLibTextureBuffer.h"
#include "ml/font/File.h"
#include "ml/font/Stream.h"
#include "string.h"

// the font file's header: its signature, its glyphs' count and cell, read in place (read is inline: the original
// emits it after the getters, its strings after theirs). The names of the fields no assertion names are not the
// original's.
struct FontSys::Header {
    Header()
        : m_signature(0), m_version(0), m_count(0), m_offset(0), m_fontSize(0.0f), m_width(0.0f), m_height(0.0f),
          m_cmp(false) {}
    void read(Stream* stream) {
        m_signature = stream->read_u32();
        m_cmp = m_signature == 0x43544e46;
#line 31
        assert(m_signature == 0x00544e46 || m_cmp);
        m_version = stream->read_u32();
        m_count = stream->read_u16();
        m_offset = stream->read_u8();
        m_fontSize = stream->read_u8();
        m_width = stream->read_u8();
        m_height = stream->read_u8();
    }

    unsigned int m_signature;  // "FNT" or "FNTC"
    unsigned int m_version;
    unsigned short m_count;    // the glyphs
    unsigned char m_offset;    // where the glyphs start
    float m_fontSize;          // get_font_size
    float m_width;             // a glyph's cell: get_origin_width
    float m_height;            // get_origin_height
    bool m_cmp;                // "FNTC": the texels packed four bits each
};

// heads this unit's range in 3.0.1, but 1.0.0 places it after WorkRoot's static initializer with
// ml::ErrorApplet::showApplet(Config const&) before it: its own unit's, the rest of which the linker dropped
bool ml::SystemErrorApplet::showApplet(nn::Result& result) {
    if (result.IsFailure()) {
        nn::err::ShowError(result);
    }
    return true;
}

Color::Color() : r(0xFF), g(0xFF), b(0xFF), a(0xFF) {}

Color::Color(const Color& other) {
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

Color::~Color() {}

// copies the four bytes as one word (out of line, but the compiler's memberwise copy)
Color& Color::operator=(const Color& other) = default;

Color::operator unsigned int() const {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

// FontSys::FontSys (0x71006F34B4) is not here yet: the original calls memset with a frame (bl), where this
// compiles to a tail call (b); the body is the original's memset of the whole object:
// FontSys::FontSys() {
//     memset(this, 0, sizeof(*this));
// }

FontSys::~FontSys() {}

// construct (0x71006F34D4) is not here yet: this reading has the original's data flow and most of its code (the
// insertion is FontSys::insert); it still differs in the operand order of `half + texels % half` (instcombine puts
// the remainder first), two float registers of the uw/vh sums, the four-bit loop's schedule and the insertion's
// block layout (the original hoists the loop's count and index updates above the bucket test). Header::read is
// emitted only with it (identical then):
// void FontSys::construct(void* data, int size) {
// #line 113
//     assert(m_data == NULL);
//     m_data = data;
//     File file(data, size);
//     Stream stream(&file);
//     m_head = new Header();
//     m_head->read(&stream);
//     float width = m_head->m_width;
//     float height = m_head->m_height;
//     stream.pos(m_head->m_offset);
//     unsigned short count = m_head->m_count;
//     unsigned int texWidth = (unsigned int)m_head->m_width * 20;
//     unsigned int texHeight = (count / 20 + 1) * (unsigned int)m_head->m_height;
//     m_texobj = new grlib::CGLibTextureBuffer();
//     grlib::CGLibTexture::createTextureBuff(*m_texobj, texWidth, texHeight, GrlSurfaceFormat(1));
//     grlib::CGLibAcc2DTexture acc;
//     acc.lock(*m_texobj);
//     if (count != 0) {
//         int texels = width * height;
//         int half = texels * 0.5f;
//         int bytes = half + texels % half;
//         for (int i = 0; count != 0; count--, i++) {
//             int row = i / 20;
//             int column = i % 20;
//             float x = column * m_head->m_width;
//             float y = row * m_head->m_height;
//             Glyph* glyph = new Glyph();
//             float ux = x / texWidth;
//             float vy = y / texHeight;
//             glyph->m_code = stream.read_u16();
//             unsigned char left = stream.read_u8();
//             unsigned char top = stream.read_u8();
//             unsigned char glyphWidth = stream.read_u8();
//             unsigned char glyphHeight = stream.read_u8();
//             float u0 = ux + (float)left / texWidth;
//             float v0 = vy + (float)top / texHeight;
//             float w = glyphWidth;
//             float h = glyphHeight;
//             glyph->m_ux = u0;
//             glyph->m_vy = v0;
//             glyph->m_width = w;
//             glyph->m_height = h;
//             glyph->m_uw = u0 + w / texWidth;
//             glyph->m_vh = v0 + h / texHeight;
//             if (glyph->m_code >= 0x100) {
//                 glyph->m_code = (glyph->m_code >> 8) | (glyph->m_code << 8);
//             }
//             if (m_head->m_cmp) {
//                 int k = 0;
//                 for (int j = 0; j < bytes; j++, k += 2) {
//                     unsigned char texel = stream.read_u8();
//                     int low = (texel & 0xF) * 15;
//                     int high = (texel >> 4) * 15;
//                     acc.setInt(high == 225 ? 0xFF : high, k % (int)m_head->m_width + (int)x,
//                                k / (int)m_head->m_width + (int)y);
//                     acc.setInt(low == 225 ? 0xFF : low, (k + 1) % (int)m_head->m_width + (int)x,
//                                (k + 1) / (int)m_head->m_width + (int)y);
//                 }
//             } else {
//                 unsigned long pos = stream.pos();
//                 stream.pos((unsigned long)(m_head->m_width * m_head->m_height * 4) + pos);
//                 const unsigned char* texels = static_cast<const unsigned char*>(data) + pos;
//                 for (int v = 0; v < m_head->m_height; v++) {
//                     for (int u = 0; u < m_head->m_width; u++) {
//                         acc.setInt(*texels, u, v);
//                         texels += 4;
//                     }
//                 }
//             }
//             if (!insert(glyph->m_code, glyph)) {
//                 delete glyph;
//             }
//         }
//     }
//     acc.unlock();
// }

void* FontSys::destroy() {
    void* data = m_data;
    m_data = nullptr;
    delete m_head;
    for (;;) {
        Glyph* glyph = nullptr;
        for (long i = TABLE_SIZE - 1; i >= 0; i--) {
            if (m_table[i] != nullptr) {
                Node** link = &m_table[i];
                Node* node = *link;
                if (node->m_next == nullptr) {
                    node->m_code = 0;
                    glyph = node->m_glyph;
                    (*link)->m_glyph = nullptr;
                    delete *link;
                    *link = nullptr;
                } else {
                    Node** prev;
                    do {
                        prev = link;
                        link = &node->m_next;
                        node = node->m_next;
                    } while (node->m_next != nullptr);
                    node->m_code = 0;
                    glyph = node->m_glyph;
                    (*link)->m_glyph = nullptr;
                    delete *link;
                    *link = nullptr;
                    (*prev)->m_next = nullptr;
                }
                break;
            }
        }
        if (glyph == nullptr) {
            break;
        }
        delete glyph;
    }
    delete m_texobj;
    return data;
}

float FontSys::get_font_size() const {
#line 239
    assert(m_head);
    return m_head->m_fontSize;
}

float FontSys::get_origin_width() const {
#line 249
    assert(m_head);
    return m_head->m_width;
}

// 1.0.0's (3.0.1's linker dropped it; its name is still in the unit's strings)
float FontSys::get_origin_height() const {
#line 259
    assert(m_head);
    return m_head->m_height;
}

void FontSys::get_texture(unsigned short code) {
    unsigned short key = code;
    if ((key & 0xFF00) == 0xFF00) {
        key &= 0xFF;
    }
    for (Node* node = m_table[hash(key) % TABLE_SIZE]; node != nullptr; node = node->m_next) {
        if (node->m_code == key) {
            Glyph* glyph = node->m_glyph;
            m_width = glyph->m_width;
            m_height = glyph->m_height;
            m_ux = glyph->m_ux;
            m_vy = glyph->m_vy;
            m_uw = glyph->m_uw;
            m_vh = glyph->m_vh;
            return;
        }
    }
    m_vh = 0.0f;
    m_uw = 0.0f;
    m_vy = 0.0f;
    m_ux = 0.0f;
    m_height = 0.0f;
    m_width = 0.0f;
}

grlib::CGLibTextureBuffer* FontSys::get_texobj() {
    return m_texobj;
}

float FontSys::get_width() const {
    return m_width;
}

float FontSys::get_height() const {
    return m_height;
}

float FontSys::get_ux() const {
    return m_ux;
}

float FontSys::get_vy() const {
    return m_vy;
}

float FontSys::get_uw() const {
    return m_uw;
}

float FontSys::get_vh() const {
    return m_vh;
}
