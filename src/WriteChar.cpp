#include "ml/font/Color.h"
#include "ml/font/FontSys.h"
#include "ml/font/WriteChar.h"

WriteChar::WriteChar()
    : m_font(nullptr), m_alpha(0xFF), m_gradationMode(GradationMode(0)), m_scaleH(1.0f), m_scaleV(1.0f),
      m_fixedWidthEnabled(false), m_fixedWidth(0.0f), m_posX(0.0f), m_posY(0.0f), m_posZ(0.0f) {}

WriteChar::~WriteChar() {}

void WriteChar::set_font(FontSys* font) {
    m_font = font;
    if (font != nullptr) {
        m_fixedWidth = font->get_origin_width();
    }
}

FontSys* WriteChar::get_font() const {
    return m_font;
}

float WriteChar::get_origin_size() const {
    return m_font->get_font_size();
}

// print (0x71006F3E04) is not here yet

void WriteChar::set_color(Color color) {
    m_color = m_gradationEndColor = color;
}

void WriteChar::set_scale(float h, float v) {
    m_scaleH = h;
    m_scaleV = v;
}

float WriteChar::get_scale_h() const {
    return m_scaleH;
}

float WriteChar::get_font_width() const {
    return m_font->get_origin_width() * m_scaleH;
}

bool WriteChar::is_fixed_width() const {
    return m_fixedWidthEnabled;
}

float WriteChar::get_fixed_width() const {
    return m_fixedWidth;
}

void WriteChar::set_pos(float x, float y) {
    m_posX = x;
    m_posY = y;
    m_posZ = 0.0f;
}

void WriteChar::set_pos_x(float x) {
    m_posX = x;
}

void WriteChar::set_pos_y(float y) {
    m_posY = y;
}

float WriteChar::get_pos_x() const {
    return m_posX;
}

float WriteChar::get_pos_y() const {
    return m_posY;
}
