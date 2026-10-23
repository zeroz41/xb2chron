#ifndef ML_FONT_WRITESTR_H
#define ML_FONT_WRITESTR_H

#include "ml/font/WriteChar.h"

class File;

// monolib's writer of a string of a FontSys (WriteStr.cpp): WriteChar's characters one after another, aligned by
// its draw flags and wrapped at its limit width. 1.0.0 also had set_limit_width, get_limit_width,
// reset_limit_width, set_draw_flag and get_draw_flag; 3.0.1's linker dropped them.
class WriteStr : public WriteChar {
public:
    WriteStr();
    ~WriteStr();
    // str (UTF-8; converted to Shift-JIS) drawn from the place (with shadows when shadow)
    void print(const char* str, bool shadow);
    // the widest line of str
    float calc_string_width(const char* str);
    // the width of file's text from its position to the line's end (the limit width); the position is kept
    float calc_string_width_to_new_line(File* file);
    float calc_string_height(const char* str);

    float m_limitWidth;       // get_limit_width: a line wraps when it is this wide (0: never)
    unsigned int m_drawFlag;  // get_draw_flag: alignment bits (0x20/0x40 centre/right, 0x200/0x400/0x800 vertical)
};

// Placeholder name: 1.0.0 has no name for it either (fn_710078FED8, WriteStr.cpp's file-local function between
// print and calc_string_width). A free function because it takes no WriteStr: it converts str (UTF-8) to Shift-JIS
// in the file's one 0x104-byte static buffer (a length, then the text) and points *out at the text; a three-byte
// character goes through mlUTF16toSJIS, a byte below 0xE0 outside 0x81-0x98 is copied as it is, any other byte
// with the one after it. print and calc_string_height convert their string with it.
void fn_71006F4790(const char* str, const char** out);

#endif
