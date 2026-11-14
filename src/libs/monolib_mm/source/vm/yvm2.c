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



// A script binary's header: offsets (from the header) of its sections. codeOfs is the original's name (an assertion
// in vmCodeExecSub spells it); the pool names follow the original's pool functions (vmIdPoolGet, vmIntPoolGet, ...);
// dataOfs is inferred.
typedef struct sSbHeader {
    char magic[4];  // 0x00: "SB  " (vmLink checks it)
    u8 version;     // 0x04: at least 2
    u8 pad_5;
    u8 flags;       // 0x06: 1 = refused by vmLink, 2 = string texts to scramble (inferred)
    u8 linkFlags;   // 0x07: 1 once linked (inferred)
    s32 codeOfs;    // 0x08
    s32 idOfs;      // 0x0C
    s32 intOfs;     // 0x10
    s32 fixedOfs;   // 0x14
    s32 strOfs;     // 0x18
    s32 funcOfs;    // 0x1C
    s32 pluginOfs;  // 0x20: plugin functions the program calls, {plugin, function} names, linked to their indices
    s32 ocOfs;      // 0x24: script classes it uses, by name, linked to their indices
    s32 farFuncOfs; // 0x28: the pool of other links' functions, {link, function} (inferred)
    s32 dataOfs;    // 0x2C
    s32 localOfs;   // 0x30: the local pools (vmLocalPoolGet)
    u32 sysAtrOfs;  // 0x34
} sSbHeader;

// A pool section: the offset (from the pool) of its entries, their count and (id and string pools) the size of an
// entry: 2 or 4 bytes holding a string's offset.
typedef struct sSbPool {
    s32 ofs;
    s32 num;
    s32 size;
} sSbPool;

// The data section and the local pools (vmLocalPoolGet): unsigned offset and count (the assertion casts num).
typedef struct sSbDataPool {
    u32 ofs;
    u32 num;
    u32 size;
} sSbDataPool;

// An entry of the far-function and plugin pools: the value's high and low halves (inferred).
typedef struct sSbLinkData {
    u16 hi;
    u16 lo;
} sSbLinkData;

typedef struct sSbFunc {
    u16 id;         // 0x00: the function's name in the id pool
    u8 pad_2[0xA];
    s32 pc;
    u8 pad_10[0x4];
} sSbFunc;

typedef struct VMReg {
    s32 pc;
    s32 sp;
    s32 pad_8;
    s32 excCode;    // 0x0C: the kind of exception thrown (inferred)
    s32 excPc;      // 0x10: where it was thrown (inferred)
    VMData exc[2];  // 0x14: the values it reports (inferred)
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
    const char* name;  // what vmFuncFarSearch finds the link by
} VMLink;

typedef struct VMPlugin {
    const char* name;
    VMPluginFunc* pPlugin;  // vmPluginRegist's table
} VMPlugin;

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

// One instruction of the script code: its mnemonic and the size of its operand (the name and the second field are
// inferred; the table is unnamed, lbl_7100B795A8).
#pragma pack(push, 4)
typedef struct VMOpcode {
    const char* name;
    s16 size;
    s16 pad_A;
} VMOpcode;
#pragma pack(pop)

static VMOpcode s_vmOpcode[96] = {
    {"NOP", 0, 0},
    {"CONST_0", 0, 1},
    {"CONST_1", 0, 1},
    {"CONST_2", 0, 1},
    {"CONST_3", 0, 1},
    {"CONST_4", 0, 1},
    {"CONST_I", 1, 1},
    {"CONST_I_W", 2, 1},
    {"POOL_INT", 1, 1},
    {"POOL_INT_W", 2, 1},
    {"POOL_FIXED", 1, 1},
    {"POOL_FIXED_W", 2, 1},
    {"POOL_STR", 1, 1},
    {"POOL_STR_W", 2, 1},
    {"LD", 1, 1},
    {"ST", 1, -1},
    {"LD_ARG", 1, 1},
    {"ST_ARG", 1, -1},
    {"ST_ARG_OMIT", 1, -1},
    {"LD_0", 0, 1},
    {"LD_1", 0, 1},
    {"LD_2", 0, 1},
    {"LD_3", 0, 1},
    {"ST_0", 0, -1},
    {"ST_1", 0, -1},
    {"ST_2", 0, -1},
    {"ST_3", 0, -1},
    {"LD_ARG_0", 0, 1},
    {"LD_ARG_1", 0, 1},
    {"LD_ARG_2", 0, 1},
    {"LD_ARG_3", 0, 1},
    {"ST_ARG_0", 0, -1},
    {"ST_ARG_1", 0, -1},
    {"ST_ARG_2", 0, -1},
    {"ST_ARG_3", 0, -1},
    {"LD_STATIC", 1, 1},
    {"LD_STATIC_W", 2, 1},
    {"ST_STATIC", 1, -1},
    {"ST_STATIC_W", 2, -1},
    {"LD_AR", 0, -1},
    {"ST_AR", 0, -3},
    {"LD_NIL", 0, 1},
    {"LD_TRUE", 0, 1},
    {"LD_FALSE", 0, 1},
    {"LD_FUNC", 1, 1},
    {"LD_FUNC_W", 2, 1},
    {"LD_PLUGIN", 1, 1},
    {"LD_PLUGIN_W", 2, 1},
    {"LD_FUNC_FAR", 1, 1},
    {"LD_FUNC_FAR_W", 2, 1},
    {"MINUS", 0, 0},
    {"NOT", 0, -1},
    {"L_NOT", 0, -1},
    {"ADD", 0, -1},
    {"SUB", 0, -1},
    {"MUL", 0, -1},
    {"DIV", 0, -1},
    {"MOD", 0, -1},
    {"OR", 0, -1},
    {"AND", 0, -1},
    {"R_SHIFT", 0, -1},
    {"L_SHIFT", 0, -1},
    {"EQ", 0, -1},
    {"NE", 0, -1},
    {"GT", 0, -1},
    {"LT", 0, -1},
    {"GE", 0, -1},
    {"LE", 0, -1},
    {"L_OR", 0, -1},
    {"L_AND", 0, -1},
    {"JMP", 2, 0},
    {"JPF", 2, -1},
    {"CALL", 1, 0},
    {"CALL_W", 2, 0},
    {"CALL_IND", 0, 0},
    {"RET", 0, 0},
    {"NEXT", 0, 0},
    {"PLUGIN", 1, 0},
    {"PLUGIN_W", 2, 0},
    {"CALL_FAR", 1, 0},
    {"CALL_FAR_W", 2, 0},
    {"GET_OC", 1, 0},
    {"GET_OC_W", 2, 0},
    {"GETTER", 1, 0},
    {"GETTER_W", 2, 0},
    {"SETTER", 1, -1},
    {"SETTER_W", 2, -1},
    {"SEND", 1, 0},
    {"SEND_W", 2, 0},
    {"TYPEOF", 0, 0},
    {"SIZEOF", 0, 0},
    {"SWITCH", 1, 0},
    {"INC", 0, 0},
    {"DEC", 0, 0},
    {"EXIT", 0, 0},
    {"BP", 0, 0},
};

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


// The name is 1.0.0's (vmInit, the one of vmInit/vmDestory with a caller).
void vmInit(void) {
    memset(&s_vmWork, 0, sizeof(s_vmWork));
}

int vmArgBoolGet(s32 no, VMData* pData) {
    u8 type = pData->type;
    if (type != VMDATA_TRUE && type != VMDATA_FALSE) {
        vmArgErr();
    }
    return type != VMDATA_FALSE;
}

s32 vmArgIntGet(s32 no, VMData* pData) {
    if (pData->type != VMDATA_INT) {
        if (pData->type == VMDATA_FIXED) {
            return (s32)pData->v.f;
        }
        vmArgErr();
    }
    return pData->v.i;
}

f32 vmArgFixedGet(s32 no, VMData* pData) {
    if (pData->type != VMDATA_FIXED) {
        if (pData->type == VMDATA_INT) {
            return (f32)pData->v.i;
        }
        vmArgErr();
    }
    return pData->v.f;
}

const char* vmArgStringGet(s32 no, VMData* pData) {
    if (pData->type != VMDATA_STRING) {
        vmArgErr();
    }
    return pData->v.str;
}

s32 vmArgFunctionGet(s32 no, VMData* pData) {
    if (pData->type != VMDATA_FUNCTION) {
        vmArgErr();
    }
    return (pData->hi << 16) | pData->v.lo;
}

#line 1493
static const char* vmIdPoolGet(sSbHeader* pSb, s32 no) {
    sSbPool* pId = (sSbPool*)((u8*)pSb + pSb->idOfs);
    assert(pId->num > no);
    u8* pData = (u8*)pId + pId->ofs;
    s32 ofs;
    if (pId->size == 2) {
        ofs = *(u16*)(pData + pId->size * no);
    } else {
        ofs = *(s32*)(pData + pId->size * no);
    }
    return (const char*)pData + ofs;
}

#line 1531
static const char* vmStringPoolGet(sSbHeader* pSb, s32 no) {
    sSbPool* pStr = (sSbPool*)((u8*)pSb + pSb->strOfs);
    assert(pStr->num > no);
    u8* pData = (u8*)pStr + pStr->ofs;
    s32 ofs;
    if (pStr->size == 2) {
        ofs = *(u16*)(pData + pStr->size * no);
    } else {
        ofs = *(s32*)(pData + pStr->size * no);
    }
    return (const char*)pData + ofs;
}


s32 vmFuncFarSearch(const char* linkName, const char* funcName) {
    s32 i;
    for (i = 0; i < 32; i++) {
        if (s_vmWork.link[i].name != NULL && strcmp(s_vmWork.link[i].name, linkName) == 0) {
            sSbHeader* pSb = s_vmWork.link[i].pSb;
            sSbPool* pFunc = (sSbPool*)((u8*)pSb + pSb->funcOfs);
            sSbFunc* p = (sSbFunc*)((u8*)pFunc + pFunc->ofs);
            s32 j;
            for (j = 0; j < pFunc->num; p++, j++) {
                if (strcmp(vmIdPoolGet(pSb, p->id), funcName) == 0) {
                    return (i << 16) | j;
                }
            }
            return -1;
        }
    }
    return -1;
}

// Resolves a value of the script's data section: a string's offset, a function of another link, a type-8 value.
void vmInitDataLink(sSbHeader* pSb, VMData* pData) {
    sSbPool* pPool;
    sSbLinkData* pLink;
    switch (pData->type) {
    case VMDATA_STRING:
        pData->v.str = vmStringPoolGet(pSb, pData->v.i);
        return;
    case VMDATA_FUNCTION:
        if (pData->hi == 0) {
            pData->hi = vmLinkIdxGet(pSb);
            return;
        }
        pPool = (sSbPool*)((u8*)pSb + pSb->farFuncOfs);
        pLink = (sSbLinkData*)((u8*)pPool + pPool->ofs) + pData->v.i;
        pData->hi = pLink->hi;
        pData->v.i = pLink->lo;
        return;
    case VMDATA_PLUGIN:
        pPool = (sSbPool*)((u8*)pSb + pSb->pluginOfs);
        pLink = (sSbLinkData*)((u8*)pPool + pPool->ofs) + pData->v.i;
        pData->hi = pLink->hi;
        pData->v.i = pLink->lo;
        return;
    }
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
            pNew->reg.excCode = 0;
            pNew->reg.excPc = 0;
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

#line 1576
static u16 vmSysAtrPoolGet(sSbHeader* pSb, s32 no) {
    sSbPool* pAtr = (sSbPool*)((u8*)pSb + pSb->sysAtrOfs);
    assert(pAtr->num > no);
    return *(u16*)((u8*)pAtr + pAtr->ofs + pAtr->size * no);
}

// Starts the program's main function (the code section names it after its offset).
void vmStart(void* program) {
    sSbHeader* pSb = (sSbHeader*)program;
    s32* pCode = (s32*)((u8*)pSb + pSb->codeOfs);
    u16 id;
    vmThreadCreate(pSb, pCode[1]);
    id = vmSysAtrPoolGet(pSb, 0);
    if (id != 0xFFFF) {
        // the program's name: only its check is left in this build
        const char* pName = vmIdPoolGet(pSb, id);
        (void)pName;
    }
}


// The original is C: NULL is ((void*)0) in its assertion texts.
#line 400
s32 vmPluginRegist(const char* mName, VMPluginFunc* pPlugin) {
    s32 i;
    assert(mName != ((void*)0) && pPlugin != ((void*)0));
    for (i = 0; i < 48; i++) {
        if (s_vmWork.plugin[i].name != NULL && strcmp(s_vmWork.plugin[i].name, mName) == 0) {
            return 1;
        }
    }
    for (i = 0; i < 48; i++) {
        if (s_vmWork.plugin[i].name == NULL) {
            s_vmWork.plugin[i].name = mName;
            s_vmWork.plugin[i].pPlugin = pPlugin;
            return 1;
        }
    }
    return 0;
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

// Raises a script exception of that kind on the thread at its current instruction, reporting the values the caller
// left in reg.exc (the name is inferred).
static void vmExceptionJump(VMThread* pThread) {
    vmDataGet(pThread, pThread->reg.excPc + 1, s_vmOpcode[pThread->pCode[pThread->reg.excPc]].size);
    pThread->reg.pc = pThread->reg.excPc;
    vmArgAssert(0);
}

static void vmExceptionThrow(VMThread* pThread, s32 code) {
    pThread->reg.excCode = code;
    pThread->reg.excPc = pThread->reg.pc;
    vmExceptionJump(pThread);
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

static s32 vmOCSearch(const char* name) {
    s32 i;
    for (i = 0; i < 48; i++) {
        if (s_vmWork.oc[i] != NULL && strcmp(s_vmWork.oc[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

#line 635
s32 vmOCRegist(VMOC* pOC) {
    s32 i;
    assert(pOC != ((void*)0));
    if (vmOCSearch(pOC->name) != -1) {
        return 1;
    }
    for (i = 0; i < 48; i++) {
        if (s_vmWork.oc[i] == NULL) {
            VMOCProperty* pProperty;
            VMOCMethod* pMethod;
            s_vmWork.oc[i] = pOC;
            pProperty = pOC->properties;
            if (pProperty != NULL) {
                for (; pProperty->name != NULL; pProperty++) {
                    pProperty->nameLen = strlen(pProperty->name);
                }
            }
            pMethod = pOC->methods;
            if (pMethod != NULL) {
                for (; pMethod->name != NULL; pMethod++) {
                    pMethod->nameLen = strlen(pMethod->name);
                }
            }
            return 1;
        }
    }
    return 0;
}

void vmOCExceptionThrow(VMThread* pThread) {
    pThread->reg.exc[0] = pThread->stack[pThread->reg.sp];
    vmExceptionThrow(pThread, 2);
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

#line 781
void vmThreadStart(VMThread* pThread, s32 id) {
    VMThread* pNew = vmThreadSearch(id);
    u8 argc;
    s32 num;
    assert(pNew);
    // the running call's arguments and their count go on the new thread's stack
    argc = pThread->stack[pThread->reg.sp - 1].v.i;
    num = argc + 1;
    memcpy(&pNew->stack[pNew->reg.sp], &pThread->stack[pThread->reg.sp - num], num * sizeof(VMData));
    pNew->reg.sp += num;
    pNew->stack[pNew->reg.sp - 1].v.i = argc;
    fn_71006EE9A0(pNew, pNew->funcNo, pNew->linkNo2, 0);
    pNew->flags &= 0x7FFFFFFF;
#line 799
    assert(pNew->reg.sp < pNew->stackSize && pNew->reg.sp >= 0);
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

s32 vmPropertySearch(VMOC* pOC, const char* name) {
    s32 len = strlen(name);
    VMOCProperty* pProperty = pOC->properties;
    s32 i;
    if (pProperty != NULL) {
        for (i = 0; pProperty->name != NULL; pProperty++, i++) {
            if (len == pProperty->nameLen && strcmp(name, pProperty->name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

s32 vmSelectorSearch(VMOC* pOC, const char* name) {
    s32 len = strlen(name);
    VMOCMethod* pMethod = pOC->methods;
    s32 i;
    if (pMethod != NULL) {
        for (i = 0; pMethod->name != NULL; pMethod++, i++) {
            if (len == pMethod->nameLen && strcmp(name, pMethod->name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

// Calls function func of plugin pluginNo on the thread (whose stack holds the call's argument count and expected
// return count) and drops the arguments; pc continues at nextPc unless the plugin threw or waits. 1 when the plugin
// set the thread waiting. The name is the one its assertion reports (__func__, lbl_71009AAB75); `used` keeps it
// until vmCodeExecSub, its one caller, is written.
#line 2966
__attribute__((used)) static s32 vmc_plugin_sub(VMThread* pThread, s32 pluginNo, s32 func, s32 nextPc) {
    s32 info = pThread->stack[pThread->reg.sp - 1].v.i;
    s32 ret;
    s32 sp;
    u8 argc;
    u8 retc;
    pThread->waitMode = 0;
    ret = s_vmWork.plugin[pluginNo].pPlugin[func].func(pThread);
    if (pThread->reg.excCode != 0) {
        return 0;
    }
    if (pThread->waitMode != 0) {
        return 1;
    }
    argc = info;
    retc = info >> 8;
    if (ret > 1 || retc > ret) {
        vmExceptionThrow(pThread, 8);
        return 0;
    }
    sp = pThread->reg.sp;
    pThread->reg.sp = sp + (-1 - argc - ret);
    if (retc != 0) {
        vmPush(pThread, &pThread->stack[sp - 1]);
    }
    assert(pThread->reg.sp < pThread->stackSize && pThread->reg.sp >= 0);
    pThread->reg.pc = nextPc;
    return 0;
}

void vmArgErr(void) {
    VMThread* pThread = s_vmWork.pCurThread;
    u8 op = pThread->pCode[pThread->reg.pc];
    if (op == 0x4D || op == 0x4E) {
        vmExceptionThrow(pThread, 1);
    } else {
        vmOCExceptionThrow(pThread);
    }
    vmExceptionJump(pThread);
}

}
