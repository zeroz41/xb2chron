// The bdat script class (a monolib VM OC plugin): its methods, constructor function, class table and Regist
// function. The methods are static and nothing names them: they keep placeholder fn_ names.
#include "vm/yvm2.h"
#include "plugin/Bdat.h"
#include <string.h>

// bdat(name): the bdat file of that name
static int fn_7100656894(VMThread* th, void* unused, unsigned long ocId) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(th, 1));
    VMData ret;
    ret.type = VMDATA_OC;
    ret.hi = ocId;
    ret.v.obj = Bdat::getFP(name);
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getVal(column, id)
static int fn_71006568F4(VMThread* th, unsigned char* fp) {
    const char* column = vmArgStringGet(1, vmArgPtrGet(th, 1));
    int id = vmArgIntGet(2, vmArgPtrGet(th, 2));
    char* value = Bdat::getVal(fp, column, id);
    int type = Bdat::getVarType(fp, column);
    VMData ret;
    int v = 0;
    switch (type) {
    case 1:
        v = (unsigned char)(unsigned long)value;
        break;
    case 2:
        v = (unsigned short)(unsigned long)value;
        break;
    case 3:
        v = (unsigned int)(unsigned long)value;
        break;
    case 4:
        v = (signed char)(unsigned long)value;
        break;
    case 5:
        v = (short)(unsigned long)value;
        break;
    case 6:
        v = (int)(unsigned long)value;
        break;
    case 7:
        ret.type = VMDATA_STRING;
        ret.hi = strlen(value);
        ret.v.str = value;
        break;
    case 8:
        ret.type = VMDATA_FIXED;
        ret.v.i = (int)(unsigned long)value;
        break;
    }
    if (type != 7 && type != 8) {
        ret.type = VMDATA_INT;
        ret.v.i = v;
    }
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getArrayVal(column, id, index)
static int fn_7100656A04(VMThread* th, unsigned char* fp) {
    const char* column = vmArgStringGet(1, vmArgPtrGet(th, 1));
    int id = vmArgIntGet(2, vmArgPtrGet(th, 2));
    int index = vmArgIntGet(3, vmArgPtrGet(th, 3));
    char* value = Bdat::getArrayVal(fp, column, id, index);
    int type = Bdat::getVarType(fp, column);
    VMData ret;
    int v = 0;
    switch (type) {
    case 1:
        v = (unsigned char)(unsigned long)value;
        break;
    case 2:
        v = (unsigned short)(unsigned long)value;
        break;
    case 3:
        v = (unsigned int)(unsigned long)value;
        break;
    case 4:
        v = (signed char)(unsigned long)value;
        break;
    case 5:
        v = (short)(unsigned long)value;
        break;
    case 6:
        v = (int)(unsigned long)value;
        break;
    case 7:
        ret.type = VMDATA_STRING;
        ret.hi = strlen(value);
        ret.v.str = value;
        break;
    case 8:
        ret.type = VMDATA_FIXED;
        ret.v.i = (int)(unsigned long)value;
        break;
    }
    if (type != 7 && type != 8) {
        ret.type = VMDATA_INT;
        ret.v.i = v;
    }
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getArrayCount(column)
static int fn_7100656B34(VMThread* th, unsigned char* fp) {
    const char* column = vmArgStringGet(1, vmArgPtrGet(th, 1));
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = Bdat::getArrayCount(fp, column);
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getVarType(column)
static int fn_7100656B98(VMThread* th, unsigned char* fp) {
    const char* column = vmArgStringGet(1, vmArgPtrGet(th, 1));
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = Bdat::getVarType(fp, column);
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getIdCount()
static int fn_7100656BFC(VMThread* th, unsigned char* fp) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = Bdat::getIdCount(fp);
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getIdTop()
static int fn_7100656C44(VMThread* th, unsigned char* fp) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = Bdat::getIdTop(fp);
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getIdEnd()
static int fn_7100656C8C(VMThread* th, unsigned char* fp) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = Bdat::getIdEnd(fp);
    vmRetValSet(th, &ret);
    return 1;
}

// bdat.getFlagVal(column, id, flag)
static int fn_7100656CD4(VMThread* th, unsigned char* fp) {
    const char* column = vmArgStringGet(1, vmArgPtrGet(th, 1));
    int id = vmArgIntGet(2, vmArgPtrGet(th, 2));
    const char* flag = vmArgStringGet(3, vmArgPtrGet(th, 3));
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = Bdat::getFlagVal(fp, column, id, flag);
    vmRetValSet(th, &ret);
    return 1;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B72988).
static VMOCMethod s_bdatMethods[] = {
    {"getVal", reinterpret_cast<void*>(&fn_71006568F4), 0},
    {"getArrayVal", reinterpret_cast<void*>(&fn_7100656A04), 0},
    {"getArrayCount", reinterpret_cast<void*>(&fn_7100656B34), 0},
    {"getVarType", reinterpret_cast<void*>(&fn_7100656B98), 0},
    {"getIdCount", reinterpret_cast<void*>(&fn_7100656BFC), 0},
    {"getIdTop", reinterpret_cast<void*>(&fn_7100656C44), 0},
    {"getIdEnd", reinterpret_cast<void*>(&fn_7100656C8C), 0},
    {"getFlagVal", reinterpret_cast<void*>(&fn_7100656CD4), 0},
    {nullptr, nullptr, 0},
};

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B72968).
static VMOC s_bdat = {"bdat", reinterpret_cast<void*>(&fn_7100656894), nullptr, s_bdatMethods};

void ocBdatRegist() {
    vmOCRegist(&s_bdat);
}
