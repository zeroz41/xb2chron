#ifndef CLASSES_SSD_SOUNDCORE_H
#define CLASSES_SSD_SOUNDCORE_H

namespace ssd {
// table 0x7100B81B70
class SoundCore {
public:
    virtual void vf0() = 0;  // slot 0
    virtual void vf1() = 0;  // slot 1
    virtual void vf2() = 0;  // slot 2
    virtual void vf3() = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
    virtual void vf5() = 0;  // slot 5
    virtual void vf6() = 0;  // slot 6
    virtual void vf7() = 0;  // slot 7
    virtual void vf8() = 0;  // slot 8
    virtual void vf9() = 0;  // slot 9
    virtual void vf10() = 0;  // slot 10
    virtual void vf11() = 0;  // slot 11
    virtual void vf12() = 0;  // slot 12
    virtual void vf13() = 0;  // slot 13
    virtual void vf14() = 0;  // slot 14
    virtual void vf15() = 0;  // slot 15
    virtual void vf16() = 0;  // slot 16
    virtual void vf17() = 0;  // slot 17
    virtual void vf18() = 0;  // slot 18
    virtual ~SoundCore();  // slot 19
    virtual void vf21() = 0;  // slot 21
};
}  // namespace ssd

#endif
