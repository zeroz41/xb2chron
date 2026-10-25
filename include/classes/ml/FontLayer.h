#ifndef CLASSES_ML_FONTLAYER_H
#define CLASSES_ML_FONTLAYER_H

namespace ml { enum FONT_STYLE : int; }

namespace ml {
// table 0x7100B763C0
class FontLayer {
public:
    virtual ~FontLayer();  // slot 0

    void font(int x, int y, const char* format, ...);
    void fontStyle(FONT_STYLE style);
    unsigned char pad_8[0x8];  // fields: size from its derived classes
};
}  // namespace ml

#endif
