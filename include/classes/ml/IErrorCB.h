#ifndef CLASSES_ML_IERRORCB_H
#define CLASSES_ML_IERRORCB_H

namespace ml {
enum CPUID : int;

// what WorkCpu::registErrorCB / unregistErrorCB take (their symbols spell ml::IErrorCB*): apps::LauncherApp hands
// them its base at 0x1F0, whose table holds the destructor's thunks and errcbCallback's. The binary holds no table of
// its own (every virtual inline or pure; nothing constructs it alone).
class IErrorCB {
public:
    virtual ~IErrorCB() {}  // slot 0
    virtual void errcbCallback(CPUID, unsigned long) = 0;  // slot 2
};
}  // namespace ml

#endif
