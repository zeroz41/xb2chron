#ifndef CLASSES_FW_PADFILTERSTD_H
#define CLASSES_FW_PADFILTERSTD_H

namespace fw {
// a base of fw::PadFilterStd no evidence names yet
class TUnk_B42870 {
public:
    virtual void filterBtn(unsigned int) = 0;
    virtual void filterALX(float, float) = 0;
    virtual void filterALY(float, float) = 0;
    virtual void filterARX(float, float) = 0;
    virtual void filterARY(float, float) = 0;
    virtual void getFilterName() const = 0;
    virtual ~TUnk_B42870();
};
// a base of fw::PadFilterStd no evidence names yet
class TUnk_B428C0 {
public:
    virtual ~TUnk_B428C0();
};
// table 0x7100B42870; base at 0x0 unknown (TUnk_B42870), base at 0x8 unknown (TUnk_B428C0)
class PadFilterStd : public TUnk_B42870, public TUnk_B428C0 {
public:
    virtual void filterBtn(unsigned int);  // slot 0
    virtual void filterALX(float, float);  // slot 1
    virtual void filterALY(float, float);  // slot 2
    virtual void filterARX(float, float);  // slot 3
    virtual void filterARY(float, float);  // slot 4
    virtual void getFilterName() const;  // slot 5
    virtual ~PadFilterStd();  // slot 6
};
}  // namespace fw

#endif
