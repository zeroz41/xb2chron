#ifndef CLASSES_ML_PROCEXCEPTION_H
#define CLASSES_ML_PROCEXCEPTION_H

namespace ml {

class IException;

// ml::ProcException: 1.0.0's symbols name the class and these members; 3.0.1's linker dropped all of its code, but
// WinView.cpp still defines the exception list entry/remove keep (the file statics GlobalMerge places at +0 and
// +0x38 of WinView.cpp's merged .bss block, lbl_7100ECFBD0). Only those two static members are declared here.
class ProcException {
public:
    static void entry(IException* exception);
    static void remove(IException* exception);
};

}  // namespace ml

#endif
