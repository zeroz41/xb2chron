#ifndef ML_FONT_WRITECHAR_H
#define ML_FONT_WRITECHAR_H

#include "ml/font/Color.h"

class FontSys;
namespace ml { class DebDraw; }

// monolib's writer of one character of a FontSys at a place, scaled and colored (WriteChar.cpp). 1.0.0 also had
// get_origin_width/height, set_alpha, get_alpha, the gradation mode's and colors' accessors, set_scale(float),
// get_scale_v, get_font_height, enable_fixed_width, set_fixed_width, set_pos(x, y, z), set_pos_z, the set_move
// functions and get_pos_z; 3.0.1's linker dropped them. The fields are named from those accessors (the names are
// not the original's).
class WriteChar {
public:
    // how the color runs over a character (set_gradation_mode's; no value has a name yet)
    enum GradationMode {};

    WriteChar();
    ~WriteChar();
    void set_font(FontSys* font);
    FontSys* get_font() const;
    float get_origin_size() const;
    // code drawn at the place (with its shadow when shadow), on draw
    void print(unsigned short code, bool shadow, ml::DebDraw* draw);
    // the color, the gradation's end color too
    void set_color(Color color);
    void set_scale(float h, float v);
    float get_scale_h() const;
    // the font's cell width, scaled
    float get_font_width() const;
    bool is_fixed_width() const;
    float get_fixed_width() const;
    // the place, at depth 0
    void set_pos(float x, float y);
    void set_pos_x(float x);
    void set_pos_y(float y);
    float get_pos_x() const;
    float get_pos_y() const;

    FontSys* m_font;
    Color m_color;             // the gradation's start (get_color, get_gradation_start_color)
    Color m_gradationEndColor;  // get_gradation_end_color
    unsigned char m_alpha;     // set_alpha
    GradationMode m_gradationMode;
    float m_scaleH;
    float m_scaleV;
    bool m_fixedWidthEnabled;  // enable_fixed_width
    float m_fixedWidth;        // set_font sets it to the font's cell width
    float m_posX;
    float m_posY;
    float m_posZ;
};

#endif
