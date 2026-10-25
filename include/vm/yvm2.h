#ifndef VM_YVM2_H
#define VM_YVM2_H

// monolib's script virtual machine (libs/monolib_mm/source/vm/yvm2, C): fw::ScriptInfo hands it the script it read.
// The parameter names are not the original's; the return values are what its callers test.
#ifdef __cplusplus
extern "C" {
#endif

int vmLink(void* program);
int vmUnlink(void* program);
void vmStart(void* program);
int vmThreadIsFinish(void* program);

// Reports an argument of the wrong type for the current thread (s_vmWork.pCurThread).
void vmArgErr(void);

// The VM's assertion report (defined in WriteStr.cpp): message, file, line.
void vmMlAssert(const char* message, const char* file, int line);

#ifdef __cplusplus
}
#endif

#endif
