#ifndef CLASSES_FW_PADFILTERSTD_H
#define CLASSES_FW_PADFILTERSTD_H

namespace fw {
// a base of fw::PadFilterStd no evidence names yet
class TUnk_B42870 {
public:
    virtual unsigned int filterBtn(unsigned int) = 0;
    virtual float filterALX(float, float) = 0;
    virtual float filterALY(float, float) = 0;
    virtual float filterARX(float, float) = 0;
    virtual float filterARY(float, float) = 0;
    virtual const char* getFilterName() const = 0;
    // inline: fw::PadFilterStd's destructor (a bare ret) calls no base destructor
    virtual ~TUnk_B42870() {}
};
// a base of fw::PadFilterStd no evidence names yet
class TUnk_B428C0 {
public:
    virtual ~TUnk_B428C0() {}
};
// table 0x7100B42870; base at 0x0 unknown (TUnk_B42870), base at 0x8 unknown (TUnk_B428C0)
class PadFilterStd : public TUnk_B42870, public TUnk_B428C0 {
public:
    // the unfiltered button bits are the low 16
    virtual unsigned int filterBtn(unsigned int btn) { return btn & 0xFFFF; }  // slot 0
    virtual float filterALX(float x, float) { return x; }  // slot 1
    virtual float filterALY(float, float y) { return y; }  // slot 2
    virtual float filterARX(float x, float) { return x; }  // slot 3
    virtual float filterARY(float, float y) { return y; }  // slot 4
    virtual const char* getFilterName() const { return "PadFilterStd"; }  // slot 5
    // the key function: defined in PadManager.cpp (its body comes before the inline slots there)
    virtual ~PadFilterStd();  // slot 6
};
}  // namespace fw

#endif
