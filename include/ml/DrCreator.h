#ifndef ML_DRCREATOR_H
#define ML_DRCREATOR_H

namespace ml {
class DrGpuCheckBase;
class DrStmReadCheck;

// makes draw objects (used on the stack by ScnObjAccGpuCheck::create and ScnObjAccStmReadObj::create)
class DrCreator {
public:
    DrCreator();
    DrGpuCheckBase* createGpuCheckObj(int arg);
    DrStmReadCheck* createStmLoadObj(const char* name);
    unsigned char pad_0[0x8];
};
}  // namespace ml

#endif
