#ifndef ML_FONT_COLOR_H
#define ML_FONT_COLOR_H

// monolib's 8-bit RGBA color (font.cpp). 1.0.0 also had Color(unsigned int), to_u32, set, operator=(unsigned int)
// and the arithmetic operators; 3.0.1's linker dropped them. The fields' names are not the original's.
class Color {
public:
    Color();
    Color(const Color& other);
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    ~Color();
    Color& operator=(const Color& other);
    // red in the top byte, alpha in the bottom one
    operator unsigned int() const;

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

#endif
