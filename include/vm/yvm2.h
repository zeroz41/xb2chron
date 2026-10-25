#ifndef VM_YVM2_H
#define VM_YVM2_H

// monolib's script virtual machine (libs/monolib_mm/source/vm/yvm2, C): fw::ScriptInfo hands it the script it read.
// The parameter names are not the original's; the return values are what its callers test.
#ifdef __cplusplus
extern "C" {
#endif

// One script value (12 bytes, 2-byte aligned: a string pointer sits at +4). Plugin functions build one on the stack
// to hand vmRetValSet their result.
#pragma pack(push, 2)
typedef struct VMData {
    unsigned char type;
    unsigned char pad_1;
    unsigned short hi;  // VMDATA_OC: the id the object's constructor was handed
    union {
        int i;
        float f;
        const char* str;
        unsigned short lo;
        void* obj;  // VMDATA_OC: the object
    } v;
} VMData;
#pragma pack(pop)

enum {
    VMDATA_NIL = 0,
    VMDATA_TRUE = 1,
    VMDATA_FALSE = 2,
    VMDATA_INT = 3,
    VMDATA_FIXED = 4,
    VMDATA_STRING = 5,
    VMDATA_ARRAY = 6,
    VMDATA_FUNCTION = 7,
    // an object of a class (VMOC) a plugin registers; the name is not the original's
    VMDATA_OC = 9,
};

// The script thread a plugin function runs on (yvm2.c defines it).
typedef struct VMThread VMThread;

// One entry of a plugin's table (what a script calls as "<plugin>.<name>"), which ends with a null entry. A plugin
// function returns 1 when it set a return value, else 0. The name is not the original's.
typedef struct VMPluginFunc {
    const char* name;
    int (*func)(VMThread* pThread);
} VMPluginFunc;

void vmPluginRegist(const char* name, VMPluginFunc* pPlugin);

// A method of a script class: the VM looks it up by name (vmOCRegist fills nameLen).
typedef struct VMOCMethod {
    const char* name;
    void* func;
    int nameLen;
    unsigned char pad_14[4];
} VMOCMethod;

// A property of a script class (vmOCRegist fills nameLen); the layout past the name is unknown.
typedef struct VMOCProperty {
    const char* name;
    unsigned char pad_8[0x10];
    int nameLen;
    unsigned char pad_1C[4];
} VMOCProperty;

// A script class a plugin registers with vmOCRegist (ocAiDataRegist: "aiData").
typedef struct VMOC {
    const char* name;
    // makes the object a script asks for: (thread, ?, id), returns 1 after pushing a VMDATA_OC value
    void* ctor;
    VMOCProperty* properties;
    VMOCMethod* methods;
} VMOC;

int vmOCRegist(VMOC* pOC);

// argument no (from 1) of the running call; nonzero from vmArgOmitChk when the call left it out
VMData* vmArgPtrGet(VMThread* pThread, int no);
int vmArgOmitChk(VMThread* pThread, int no);
// the value of an argument; no (the argument's number, which every caller passes) is not read
int vmArgBoolGet(int no, VMData* pData);
int vmArgIntGet(int no, VMData* pData);
float vmArgFixedGet(int no, VMData* pData);
const char* vmArgStringGet(int no, VMData* pData);
int vmArgFunctionGet(int no, VMData* pData);
void vmRetValSet(VMThread* pThread, VMData* pData);
void vmWaitModeSet(VMThread* pThread);
// the running call's work state (yvm2.c): an index kept across waits, and three 8-byte work slots
int vmWkIdxGet(VMThread* pThread);
void vmWkIdxSet(VMThread* pThread, short idx);
void** vmWkGet(VMThread* pThread, int idx);
void splitFixed(float value, int* pSign, int* pInt, int* pFrac);

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
