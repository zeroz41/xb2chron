#ifndef CLASSES_FW_ISOUNDDRIVER_H
#define CLASSES_FW_ISOUNDDRIVER_H

namespace fw {
// table 0x7100B43168
class ISoundDriver {
public:
    virtual ~ISoundDriver();  // slot 0
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
    virtual void isDeviceEnable() const;  // slot 16
    virtual void vf17() = 0;  // slot 17
    virtual void vf18() = 0;  // slot 18
    virtual void vf19() = 0;  // slot 19
    virtual void vf20() = 0;  // slot 20
    virtual void vf21() = 0;  // slot 21
    virtual void vf22() = 0;  // slot 22
    virtual void vf23() = 0;  // slot 23
    virtual void vf24() = 0;  // slot 24
    virtual void vf25() = 0;  // slot 25
    virtual void vf26() = 0;  // slot 26
    virtual void vf27() = 0;  // slot 27
    virtual void vf28() = 0;  // slot 28
    virtual void vf29() = 0;  // slot 29
    virtual void vf30() = 0;  // slot 30
    virtual void vf31() = 0;  // slot 31
    virtual void vf32() = 0;  // slot 32
    virtual void vf33() = 0;  // slot 33
    virtual void vf34() = 0;  // slot 34
    virtual void vf35() = 0;  // slot 35
    virtual void vf36() = 0;  // slot 36
    virtual void vf37() = 0;  // slot 37
    virtual void vf38() = 0;  // slot 38
    virtual void vf39() = 0;  // slot 39
    virtual void vf40() = 0;  // slot 40
    virtual void vf41() = 0;  // slot 41
    virtual void vf42() = 0;  // slot 42
    virtual void vf43() = 0;  // slot 43
    virtual void vf44() = 0;  // slot 44
    virtual void vf45() = 0;  // slot 45
    virtual void vf46() = 0;  // slot 46
    virtual void vf47() = 0;  // slot 47
    virtual void vf48() = 0;  // slot 48
    virtual void vf49() = 0;  // slot 49
    virtual void vf50() = 0;  // slot 50
    virtual void vf51() = 0;  // slot 51
    virtual void vf52() = 0;  // slot 52
    virtual void attachPoolMemory(void*, unsigned int);  // slot 53
    virtual void detachPoolMemory(void*, unsigned int);  // slot 54
};
}  // namespace fw

#endif
