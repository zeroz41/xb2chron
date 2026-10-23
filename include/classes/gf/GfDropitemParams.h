#ifndef CLASSES_GF_GFDROPITEMPARAMS_H
#define CLASSES_GF_GFDROPITEMPARAMS_H

namespace gf {
// table 0x7100B528F0
class GfDropitemParams {
public:
    GfDropitemParams();
    virtual ~GfDropitemParams();  // slot 0
    void update();

    unsigned char pad_0x8[0x30];
};
}  // namespace gf

#endif
