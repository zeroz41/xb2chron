#ifndef CLASSES_GRLIB_CGLIBACCUTILTEXTURE_H
#define CLASSES_GRLIB_CGLIBACCUTILTEXTURE_H

namespace grlib {
// table none (its derived classes')
class CGLibAccUtilTexture {
public:
    virtual ~CGLibAccUtilTexture();  // slot 0
    virtual void texaccread_f32_8(unsigned int);  // slot 2
};
}  // namespace grlib

#endif
