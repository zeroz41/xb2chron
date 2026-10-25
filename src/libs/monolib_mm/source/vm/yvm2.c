// monolib's script virtual machine (C). Struct, field and global names are inferred from the original's assertion
// texts (VMData, sSbHeader, pThread->reg.pc/sp, pThread->stackSize, pThread->pSb) or from what the code does; the
// inferred ones are not the original's.
#include <string.h>
#include <assert.h>
#include "vm/yvm2.h"


typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

#pragma pack(push, 2)
// One script value (12 bytes, 2-byte aligned: a string pointer sits at +4).
typedef struct VMData {
    u8 type;
    u8 pad_1;
    u16 hi;
    union {
        s32 i;
        f32 f;
        const char* str;
        u16 lo;
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
};

// A script binary's header: offsets (from the header) of its sections. codeOfs is the original's name (an assertion
// in vmCodeExecSub spells it); the pool names follow the original's pool functions (vmIdPoolGet, vmIntPoolGet, ...);
// dataOfs is inferred.
typedef struct sSbHeader {
    u8 pad_0[0x8];
    s32 codeOfs;    // 0x08
    s32 idOfs;      // 0x0C
    s32 intOfs;     // 0x10
    s32 fixedOfs;   // 0x14
    s32 strOfs;     // 0x18
    s32 funcOfs;    // 0x1C
    u8 pad_20[0xC];
    s32 dataOfs;    // 0x2C
    u8 pad_30[0x4];
    s32 sysAtrOfs;  // 0x34
} sSbHeader;

// A pool section: the offset (from the pool) of its entries and their count.
typedef struct sSbPool {
    s32 ofs;
    s32 num;
} sSbPool;

typedef struct sSbFunc {
    u8 pad_0[0xC];
    s32 pc;
    u8 pad_10[0x4];
} sSbFunc;

typedef struct VMReg {
    s32 pc;
    s32 sp;
    s32 pad_8;
    s32 pad_C;
    s32 pad_10;
    u8 pad_14[0x2C - 0x14];
} VMReg;

typedef struct VMThread {
    VMReg reg;      // 0x00
    s16 linkNo;     // 0x2C
    u8 pad_2E[2];
    s32 funcNo;     // 0x30
    s16 linkNo2;    // 0x34
    u8 pad_36[2];
    sSbHeader* pSb; // 0x38
    u8* pCode;      // 0x40
    void* pPool;    // 0x48
    VMData* stack;  // 0x50
    s32 stackSize;  // 0x58
    s32 id;         // 0x5C
    s32 flags;      // 0x60
    s16 waitMode;   // 0x64
    s16 wkIdx;      // 0x66
    void* wk[3];    // 0x68
    s16 pad_80;
    u8 pad_82[6];
} VMThread;

typedef struct VMLink {
    sSbHeader* pSb;
    void* pad_8;
} VMLink;

typedef struct VMPlugin {
    const char* name;
    void* pPlugin;
} VMPlugin;

typedef struct VMOCMethod {
    const char* name;
    void* func;
    s32 nameLen;
    u8 pad_14[4];
} VMOCMethod;

typedef struct VMOC {
    const char* name;
    u8 pad_8[0x10];
    VMOCMethod* methods;
} VMOC;

typedef struct VMWork {
    VMLink link[32];            // 0x0000
    VMThread* pCurThread;       // 0x0200
    s32 threadId;               // 0x0208
    VMThread* execList[32];     // 0x0210
    VMThread thread[32];        // 0x0310
    VMData stack[32][0x80];     // 0x1410
    VMPlugin plugin[48];        // 0xD410
    VMOC* oc[48];               // 0xD710
    VMOC* pBuiltinOC;           // 0xD890
} VMWork;

extern "C" {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71015DA308)
static VMWork s_vmWork;

#line 1 "D:/Monolithsoft/BF2/prog/libs/monolib_mm/source/vm/yvm2.c"

s32 vmThreadEnd(s32 id);

static VMLink* vmLinkSearch(void* pSb) {
    s32 i;
    for (i = 0; i < 32; i++) {
        if (s_vmWork.link[i].pSb == pSb) {
            return &s_vmWork.link[i];
        }
    }
    return NULL;
}

static s32 vmLinkIdxGet(void* pSb) {
    s32 i;
    for (i = 0; i < 32; i++) {
        if (s_vmWork.link[i].pSb == pSb) {
            return i;
        }
    }
    return -1;
}

#line 1702
static void vmPush(VMThread* pThread, VMData* pData) {
    assert(pThread->reg.sp < pThread->stackSize);
    pThread->stack[pThread->reg.sp++] = *pData;
}

#line 4064
static void vmArgAssert(s32 cond) {
    if (!cond) {
        vmMlAssert("[VM] INFINITY_LOOP", __FILE__, __LINE__);
    }
}


// The name is 1.0.0's (vmInit, the one of vmInit/vmDestory with a caller); 3.0.1's symbols spell it fn_71006ED39C.
void vmInit(void) {
    memset(&s_vmWork, 0, sizeof(s_vmWork));
}

int vmArgBoolGet(VMThread* pThread, VMData* pData) {
    u8 type = pData->type;
    if (type != VMDATA_TRUE && type != VMDATA_FALSE) {
        vmArgErr();
    }
    return type != VMDATA_FALSE;
}

s32 vmArgIntGet(VMThread* pThread, VMData* pData) {
    if (pData->type != VMDATA_INT) {
        if (pData->type == VMDATA_FIXED) {
            return (s32)pData->v.f;
        }
        vmArgErr();
    }
    return pData->v.i;
}

f32 vmArgFixedGet(VMThread* pThread, VMData* pData) {
    if (pData->type != VMDATA_FIXED) {
        if (pData->type == VMDATA_INT) {
            return (f32)pData->v.i;
        }
        vmArgErr();
    }
    return pData->v.f;
}

const char* vmArgStringGet(VMThread* pThread, VMData* pData) {
    if (pData->type != VMDATA_STRING) {
        vmArgErr();
    }
    return pData->v.str;
}

s32 vmArgFunctionGet(VMThread* pThread, VMData* pData) {
    if (pData->type != VMDATA_FUNCTION) {
        vmArgErr();
    }
    return (pData->hi << 16) | pData->v.lo;
}

s32 vmUnlink(void* pSb) {
    VMLink* pLink = vmLinkSearch(pSb);
    s32 idx;
    s32 i;
    if (pLink == NULL) {
        return 0;
    }
    idx = vmLinkIdxGet(pSb);
    for (i = 0; i < 32; i++) {
        if (s_vmWork.thread[i].linkNo == idx) {
            s_vmWork.thread[i].pSb = NULL;
        }
    }
    pLink->pSb = NULL;
    return 1;
}

#line 1547
static sSbFunc* vmFunctionPoolGet(sSbHeader* pSb, s32 no) {
    sSbPool* pFunc = (sSbPool*)((u8*)pSb + pSb->funcOfs);
    assert(pFunc->num > no);
    return (sSbFunc*)((u8*)pFunc + pFunc->ofs) + no;
}

VMThread* vmThreadCreate(sSbHeader* pSb, s32 no) {
    s32 i;
    for (i = 0; i < 32; i++) {
        VMThread* pNew = &s_vmWork.thread[i];
        if (pNew->pSb == NULL) {
            s32 j;
            s32 idx;
            s32* pOfs;
            u32* pDataOfs;
            for (j = 0; j < 32; j++) {
                if (s_vmWork.execList[j] == NULL) {
                    s_vmWork.execList[j] = pNew;
                    break;
                }
            }
            pNew->reg.pc = vmFunctionPoolGet(pSb, no)->pc;
            pNew->reg.sp = 0;
            pNew->reg.pad_8 = 0;
            pNew->reg.pad_C = 0;
            pNew->reg.pad_10 = 0;
            idx = vmLinkIdxGet(pSb);
            pNew->linkNo = idx;
            pNew->funcNo = no;
            pNew->linkNo2 = idx;
            pNew->pSb = pSb;
            pOfs = (s32*)((u8*)pSb + pSb->codeOfs);
            pNew->pCode = (u8*)pOfs + *pOfs;
            pDataOfs = (u32*)((u8*)pSb + pSb->dataOfs);
            pNew->pPool = (u8*)pDataOfs + *pDataOfs;
            pNew->stack = s_vmWork.stack[i];
            pNew->stackSize = 0x80;
            if (s_vmWork.threadId == -1) {
                s_vmWork.threadId = 0;
            }
            pNew->id = s_vmWork.threadId++;
            pNew->flags = 0;
            pNew->waitMode = 0;
            pNew->wkIdx = 0;
            pNew->wk[0] = NULL;
            pNew->wk[1] = NULL;
            pNew->wk[2] = NULL;
            pNew->pad_80 = 0;
            return pNew;
        }
    }
    return NULL;
}

VMData* vmArgPtrGet(VMThread* pThread, s32 no) {
    vmArgAssert(no <= (u8)pThread->stack[pThread->reg.sp - 1].v.i && no != 0);
    return &pThread->stack[pThread->reg.sp + ~no];
}

s32 vmArgOmitChk(VMThread* pThread, s32 no) {
    u8 argc = pThread->stack[pThread->reg.sp - 1].v.i;
    vmArgAssert(no != 0);
    if (argc < no) {
        return 1;
    }
    return pThread->stack[pThread->reg.sp + ~no].type == VMDATA_NIL;
}

void vmRetValSet(VMThread* pThread, VMData* pData) {
    if (pThread->waitMode == 0) {
        vmPush(pThread, pData);
    }
}

void vmWaitModeSet(VMThread* pThread) {
    pThread->waitMode = 1;
}

s32 vmWkIdxGet(VMThread* pThread) {
    return pThread->wkIdx;
}

void vmWkIdxSet(VMThread* pThread, s16 idx) {
    pThread->wkIdx = idx;
}

#line 597
void** vmWkGet(VMThread* pThread, s32 idx) {
    assert(idx >= 0 && idx < 3);
    return &pThread->wk[idx];
}

void vmBuiltinOCRegist(VMOC* pOC) {
    VMOCMethod* pMethod = pOC->methods;
    if (pMethod != NULL) {
        for (; pMethod->name != NULL; pMethod++) {
            pMethod->nameLen = strlen(pMethod->name);
        }
    }
    s_vmWork.pBuiltinOC = pOC;
}

s32 vmThreadIsFinish(void* pSb) {
    s32 i;
    for (i = 0; i < 32; i++) {
        if (s_vmWork.thread[i].pSb == pSb) {
            return 0;
        }
    }
    return 1;
}

s32 vmThreadGetOC(VMThread* pThread, s32 func, s32* pId) {
    s32 linkNo = func >> 16;
    s32 no = func & 0xFFFF;
    VMThread* pNew = vmThreadCreate(s_vmWork.link[linkNo].pSb, no);
    if (pNew == NULL) {
        return 0;
    }
    pNew->flags |= 0x80000000;
    *pId = pNew->id;
    return 1;
}

static VMThread* vmThreadSearch(s32 id) {
    s32 i;
    for (i = 0; i < 32; i++) {
        if (s_vmWork.thread[i].pSb != NULL && s_vmWork.thread[i].id == id) {
            return &s_vmWork.thread[i];
        }
    }
    return NULL;
}

s32 vmThreadEnd(s32 id) {
    VMThread* pThread = vmThreadSearch(id);
    if (pThread == NULL) {
        return 0;
    }
    pThread->pSb = NULL;
    return 1;
}

s32 vmThreadIsAlive(s32 id) {
    return vmThreadSearch(id) != NULL;
}

s32 vmThreadSleep(s32 id) {
    VMThread* pThread = vmThreadSearch(id);
    if (pThread == NULL) {
        return 0;
    }
    pThread->flags |= 0x80000000;
    return 1;
}

s32 vmThreadWakeup(s32 id) {
    VMThread* pThread = vmThreadSearch(id);
    if (pThread == NULL) {
        return 0;
    }
    pThread->flags &= 0x7FFFFFFF;
    return 1;
}

void splitFixed(f32 value, s32* pSign, s32* pInt, s32* pFrac) {
    *pSign = value < 0.0f ? -1 : 0;
    *pInt = (s32)value;
    *pFrac = (s32)((value - (f32)(s32)value) * 1000.0f);
}

}
