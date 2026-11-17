#include "plugin/Bdat.h"
#include "plugin/Bdat.h"

#include <assert.h>
#include <string.h>

// The BDAT library: the files fw::BdatManager loads are registered in slots, their tables found by name, and a
// table's members (columns) read by name or index for a row id. A file is a count of tables, its size and the
// tables' offsets; a table starts with this header. The names of the header's fields are not the original's: what
// each one is comes from the code reading it.
// the original's name for a 32-bit unsigned integer (getFP's assertion spells "(u32)fileIdx < binCount")
typedef unsigned int u32;

#pragma pack(push, 2)
namespace {
struct BdatHeader {
    unsigned char magic[4];
    unsigned char flags;  // bit 1: the table is still scrambled
    unsigned char pad_5;
    unsigned short nameOfs;     // the table's name (and the end of the scrambled member names: hashOfs)
    unsigned short rowSize;     // bytes per row
    unsigned short hashOfs;     // the member hash table (u16 member offsets, chained)
    unsigned short hashSize;    // its slot count
    unsigned short rowOfs;      // the first row
    unsigned short rowCount;    // getIdCount
    unsigned short idTop;       // getIdTop: the first row's id
    unsigned short pad_14;
    unsigned short scrambleKey; // the scramble key, also the checksum calcCheckSum compares
    int stringOfs;              // the string table (scrambled)
    int stringSize;
    unsigned short memberOfs;   // the member table: 6 bytes per member
    unsigned short memberCount; // getMemberSize
};

#pragma pack(pop)
// a member (column): its info's offset, the next member in its hash chain and its name's offset
struct BdatMember {
    unsigned short infoOfs;
    unsigned short next;
    unsigned short nameOfs;
};

// a member's info, read byte-wise (the original reads it through byte pointers: no field load is widened): kind 1
// scalar, 2 array, 3 flag
#pragma pack(push, 1)
struct BdatVarInfo {
    unsigned char kind;
    unsigned char type;  // the value type
    unsigned short ofs;  // the offset in a row
    unsigned short count;  // an array's element count
};

// a flag member's info (kind 3): a bit field of its parent scalar member
struct BdatFlagInfo {
    unsigned char kind;
    unsigned char shift;
    unsigned int mask;
    unsigned short parent;  // the parent member's offset
};
#pragma pack(pop)

inline BdatHeader* getHeader(unsigned char* fp) {
    return reinterpret_cast<BdatHeader*>(fp);
}
inline unsigned char* getTable(unsigned char* bin, int idx) {
    return bin + *reinterpret_cast<unsigned int*>(bin + (idx << 2) + 8);
}
}  // namespace

namespace Bdat {
unsigned char* m_pBin[16];

#define BDAT_FILE_MAX 16

void regist(int idx, void* data) {
#line 34
    assert(idx < BDAT_FILE_MAX);
    m_pBin[idx] = static_cast<unsigned char*>(data);
    decodeScramble(data);
}

void unregist(int idx) {
#line 43
    assert(idx < BDAT_FILE_MAX);
    m_pBin[idx] = 0;
}

static bool calcCheckSumSub(unsigned char* fp) {
    BdatHeader* header = getHeader(fp);
    unsigned short sum = 0;
    unsigned int end = header->stringOfs + header->stringSize;
    for (unsigned int i = 0x20; i < end; i++) {
        sum += static_cast<unsigned char>(fp[i] << (i & 3));
    }
    return sum == header->scrambleKey;
}

bool calcCheckSum(int idx) {
#line 55
    assert(idx < BDAT_FILE_MAX);
    unsigned char* bin = m_pBin[idx];
    unsigned int count = *reinterpret_cast<unsigned int*>(bin);
    for (unsigned int i = 0; i < count; i++) {
        if (!calcCheckSumSub(bin + *reinterpret_cast<unsigned int*>(bin + (8 + i * 4)))) {
            return false;
        }
    }
    return true;
}

int getFileCount(int idx) {
#line 71
    assert(idx < BDAT_FILE_MAX);
    return *reinterpret_cast<unsigned int*>(m_pBin[idx]);
}

const char* getFileName(int idx, int fileIdx) {
#line 79
    assert(idx < BDAT_FILE_MAX);
    unsigned char* bin = m_pBin[idx];
    if (static_cast<unsigned int>(fileIdx) < *reinterpret_cast<unsigned int*>(bin)) {
        return getSheetName(getTable(bin, fileIdx));
    }
    return 0;
}

void errFile(const char* name);

static unsigned char* getFPSub(const char* name) {
    for (int i = 0; i < BDAT_FILE_MAX; i++) {
        unsigned char* bin = m_pBin[i];
        if (bin == 0) {
            continue;
        }
        int lo = 0;
        int hi = *reinterpret_cast<int*>(bin);
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            unsigned char* fp = getTable(bin, mid);
            int result = strcmp(getSheetName(fp), name);
            if (result < 0) {
                lo = mid + 1;
            } else if (result > 0) {
                hi = mid;
            } else {
                return fp;
            }
        }
    }
    return 0;
}

unsigned char* getFP(const char* name) {
    unsigned char* fp = getFPSub(name);
    if (fp != 0) {
        return fp;
    }
    errFile(name);
    return 0;
}

// a table that is not loaded (empty: the report is compiled out)
void errFile(const char* name) {
}

unsigned char* getFP(int fileIdx, int idx) {
#line 105
    assert(idx < BDAT_FILE_MAX);
    unsigned char* bin = m_pBin[idx];
    unsigned int binCount = *reinterpret_cast<unsigned int*>(bin);
#line 110
    assert((u32)fileIdx < binCount);
    return getTable(bin, fileIdx);
}

unsigned char* isExistFP(const char* name) {
    return getFPSub(name);
}

const char* getSheetName(unsigned char* fp) {
    return reinterpret_cast<const char*>(fp + getHeader(fp)->nameOfs);
}

static unsigned int calcHash(const char* name, int size) {
    int len = strlen(name);
    if (len > 8) {
        len = 8;
    }
    unsigned int hash = 0;
    for (int i = 0; i < len; i++) {
        hash = hash * 7 + static_cast<unsigned char>(name[i]);
    }
    return hash % size;
}

unsigned char* getMember(unsigned char* pBdat, const char* name) {
#line 136
    assert(pBdat != 0L);
    BdatHeader* header = getHeader(pBdat);
    unsigned short* hashTable = reinterpret_cast<unsigned short*>(pBdat + header->hashOfs);
    unsigned short ofs = hashTable[calcHash(name, header->hashSize)];
    while (ofs != 0) {
        BdatMember* member = reinterpret_cast<BdatMember*>(pBdat + ofs);
        if (strcmp(name, reinterpret_cast<const char*>(pBdat + member->nameOfs)) == 0) {
            return reinterpret_cast<unsigned char*>(member);
        }
        ofs = member->next;
    }
    return 0;
}

static unsigned char* getMember(unsigned char* fp, int member) {
#line 163
    assert(member < getMemberSize(fp));
    return fp + getHeader(fp)->memberOfs + member * 6;
}

unsigned short getMemberSize(unsigned char* fp) {
    return getHeader(fp)->memberCount;
}

unsigned long getVal(unsigned char* fp, const char* column, int id) {
    unsigned char* member = getMember(fp, column);
    if (member == 0) {
        return 0;
    }
    return getVal(fp, member, id);
}

static inline void clearVal(uVal* val) {
    val->str = 0;
}

static inline bool calcId(unsigned char* fp, int* id) {
    int idx = *id - getHeader(fp)->idTop;
    if (static_cast<unsigned int>(idx) < getHeader(fp)->rowCount) {
        *id = idx;
        return true;
    }
    return false;
}

static inline BdatVarInfo* getVarInfo(unsigned char* fp, unsigned char* member) {
    return reinterpret_cast<BdatVarInfo*>(fp + reinterpret_cast<BdatMember*>(member)->infoOfs);
}

static inline uVal getVarVal(unsigned char* fp, unsigned char* ptr, unsigned char type) {
    uVal val;
    clearVal(&val);
    switch (type) {
    case 1:
        val.ubyte = *ptr;
        break;
    case 2:
        val.ushort = *reinterpret_cast<unsigned short*>(ptr);
        break;
    case 3:
        val.uint = *reinterpret_cast<unsigned int*>(ptr);
        break;
    case 4:
        val.sbyte = *reinterpret_cast<signed char*>(ptr);
        break;
    case 5:
        val.sshort = *reinterpret_cast<short*>(ptr);
        break;
    case 6:
        val.sint = *reinterpret_cast<int*>(ptr);
        break;
    case 7:
        val.str = reinterpret_cast<char*>(fp + *reinterpret_cast<unsigned int*>(ptr));
        break;
    case 8:
        val.real = *reinterpret_cast<float*>(ptr);
        break;
    }
    return val;
}

static inline uVal getVar(unsigned char* fp, unsigned char* member, int idx) {
    BdatVarInfo* info = getVarInfo(fp, member);
    if (info->kind != 1) {
        uVal val;
        clearVal(&val);
        return val;
    }
    BdatHeader* header = getHeader(fp);
    unsigned char* row = fp + header->rowOfs + header->rowSize * idx;
    return getVarVal(fp, row + info->ofs, info->type);
}

unsigned long getVal(unsigned char* pBdat, unsigned char* pVarName, int id) {
#line 206
    assert(pVarName != 0L);
    uVal val;
    clearVal(&val);
#line 209
    assert(pBdat != 0L);
    if (!calcId(pBdat, &id)) {
        return val.ulong;
    }
    return getVar(pBdat, pVarName, id).ulong;
}

unsigned long getVal(unsigned char* fp, int member, int id) {
    return getVal(fp, getMember(fp, member), id);
}

unsigned long getArrayVal(unsigned char* fp, const char* column, int id, int index) {
    unsigned char* member = getMember(fp, column);
    if (member == 0) {
        return 0;
    }
    return getArrayVal(fp, member, id, index);
}

static inline unsigned char* getArray(unsigned char* fp, unsigned char* member, int idx, int index) {
    BdatVarInfo* info = getVarInfo(fp, member);
    BdatHeader* header = getHeader(fp);
    unsigned char* ptr = fp + header->rowOfs + header->rowSize * idx + info->ofs;
    switch (info->type) {
    case 1:
    case 4:
        ptr += index;
        break;
    case 2:
    case 5:
        ptr += index * 2;
        break;
    case 3:
    case 6:
    case 7:
    case 8:
        ptr += index * 4;
        break;
    }
    return ptr;
}

unsigned long getArrayVal(unsigned char* pBdat, unsigned char* pVarName, int id, int index) {
#line 243
    assert(pVarName != 0L);
    uVal val;
    clearVal(&val);
#line 246
    assert(pBdat != 0L);
    if (!calcId(pBdat, &id)) {
        return val.ulong;
    }
    BdatVarInfo* info = getVarInfo(pBdat, pVarName);
    if (info->kind != 2) {
        return val.ulong;
    }
    if (index >= info->count) {
        return val.ulong;
    }
    return getVarVal(pBdat, getArray(pBdat, pVarName, id, index), info->type).ulong;
}

static int getArrayCount(unsigned char* pBdat, unsigned char* member) {
#line 280
    assert(pBdat != 0L);
    BdatVarInfo* info = getVarInfo(pBdat, member);
    if (info->kind != 2) {
        return 0;
    }
    return info->count;
}

int getArrayCount(unsigned char* fp, const char* column) {
    unsigned char* member = getMember(fp, column);
    if (member == 0) {
        return 0;
    }
    return getArrayCount(fp, member);
}

int getIdCount(unsigned char* pBdat) {
#line 296
    assert(pBdat != 0L);
    return getHeader(pBdat)->rowCount;
}

int getIdTop(unsigned char* pBdat) {
#line 307
    assert(pBdat != 0L);
    return getHeader(pBdat)->idTop;
}

int getIdEnd(unsigned char* fp) {
    return getIdTop(fp) + getIdCount(fp) - 1;
}

static int getVarType(unsigned char* pBdat, unsigned char* pVarName) {
#line 334
    assert(pVarName != 0L);
#line 337
    assert(pBdat != 0L);
    return getVarInfo(pBdat, pVarName)->type;
}

int getVarType(unsigned char* fp, const char* column) {
    unsigned char* member = getMember(fp, column);
    if (member == 0) {
        return 0;
    }
    return getVarType(fp, member);
}

int getFlagVal(unsigned char* fp, const char* member, int id, const char* bitMember) {
    unsigned char* var = getMember(fp, member);
    if (var == 0) {
        return 0;
    }
    unsigned char* flag = getMember(fp, bitMember);
    if (flag == 0) {
        return 0;
    }
    return getFlagVal(fp, var, id, flag);
}

bool getShiftMask(unsigned char* pBdat, const char* varName, const char* flagName, int* shift, unsigned int* mask) {
#line 422
    assert(pBdat != 0L);
    unsigned char* var = getMember(pBdat, varName);
    if (var == 0) {
        return false;
    }
    unsigned char* flagMember = getMember(pBdat, flagName);
    if (flagMember == 0) {
        return false;
    }
    BdatFlagInfo* flag = reinterpret_cast<BdatFlagInfo*>(getVarInfo(pBdat, flagMember));
    if (flag->kind != 3) {
        return false;
    }
    if (flag->parent != static_cast<unsigned short>(var - pBdat)) {
        return false;
    }
    *shift = flag->shift;
    *mask = flag->mask;
    return true;
}

static inline bool getValCheckSub(unsigned char* fp, unsigned char* member, int type) {
    if (member == 0) {
        return false;
    }
    return getVarType(fp, member) == type;
}

// one case per destination type, each storing that type's own member: the separate (codegen-merged) case blocks put
// convertType's inline cost at 275, so getValCheck/getArrayValCheck call it out of line as the original does
void convertType(unsigned char* fp, unsigned char* member, int type, uVal* val) {
    int from = getVarType(fp, member);
    if (type == 7 || from == 7) {
        clearVal(val);
        return;
    }
    if (type == 8 || from == 8) {
        clearVal(val);
        return;
    }
    switch (from) {
    case 1:
        switch (type) {
        case 2:
            val->ushort = val->ubyte;
            break;
        case 3:
            val->uint = val->ubyte;
            break;
        case 4:
            val->sbyte = val->ubyte;
            break;
        case 5:
            val->sshort = val->ubyte;
            break;
        case 6:
            val->sint = val->ubyte;
            break;
        }
        break;
    case 2:
        switch (type) {
        case 1:
            val->ubyte = val->ushort;
            break;
        case 3:
            val->uint = val->ushort;
            break;
        case 4:
            val->sbyte = val->ushort;
            break;
        case 5:
            val->sshort = val->ushort;
            break;
        case 6:
            val->sint = val->ushort;
            break;
        }
        break;
    case 3:
        switch (type) {
        case 1:
            val->ubyte = val->uint;
            break;
        case 2:
            val->uint = val->ushort;
            break;
        case 4:
            val->sbyte = val->uint;
            break;
        case 5:
            val->sshort = val->uint;
            break;
        }
        break;
    case 4:
        switch (type) {
        case 2:
            val->ushort = val->sbyte;
            break;
        case 3:
            val->uint = val->sbyte;
            break;
        case 5:
            val->sshort = val->sbyte;
            break;
        case 6:
            val->sint = val->sbyte;
            break;
        }
        break;
    case 5:
        switch (type) {
        case 1:
            val->ubyte = val->sshort;
            break;
        case 2:
            val->ushort = val->sshort;
            break;
        case 3:
            val->uint = val->sshort;
            break;
        case 4:
            val->sbyte = val->sshort;
            break;
        case 6:
            val->sint = val->sshort;
            break;
        }
        break;
    case 6:
        switch (type) {
        case 1:
            val->ubyte = val->sint;
            break;
        case 2:
            val->ushort = val->sint;
            break;
        case 4:
            val->sbyte = val->sint;
            break;
        case 5:
            val->sshort = val->sint;
            break;
        }
        break;
    }
}

const char* getMSText(unsigned char* fp, int id) {
    return reinterpret_cast<const char*>(getVal(fp, "name", id));
}

int getMSStyle(unsigned char* fp, int id) {
    return static_cast<unsigned short>(getVal(fp, "style", id));
}

const char* getMSLabel(unsigned char* fp, int id) {
    return reinterpret_cast<const char*>(getVal(fp, "label", id));
}

// getValCheck x3 / getArrayValCheck x2 with the unsigned long getters: each differs only by convertType being
// inlined (the original calls it)

unsigned long getValCheck(unsigned char* fp, const char* column, int id, int type) {
    unsigned char* member = getMember(fp, column);
    uVal val;
    if (member == 0) {
        clearVal(&val);
        return val.ulong;
    }
    bool same = getValCheckSub(fp, member, type);
    unsigned long ret = getVal(fp, member, id);
    if (!same) {
        val.ulong = ret;
        convertType(fp, member, type, &val);
        return val.ulong;
    }
    return ret;
}

unsigned long getValCheck(unsigned char* fp, int member, int id, int type) {
    unsigned char* var = getMember(fp, member);
    uVal val;
    if (var == 0) {
        clearVal(&val);
        return val.ulong;
    }
    bool same = getValCheckSub(fp, var, type);
    unsigned long ret = getVal(fp, var, id);
    if (!same) {
        val.ulong = ret;
        convertType(fp, var, type, &val);
        return val.ulong;
    }
    return ret;
}

unsigned long getValCheck(unsigned char* fp, unsigned char* member, int id, int type) {
    uVal val;
    if (member == 0) {
        clearVal(&val);
        return val.ulong;
    }
    bool same = getValCheckSub(fp, member, type);
    unsigned long ret = getVal(fp, member, id);
    if (!same) {
        val.ulong = ret;
        convertType(fp, member, type, &val);
        return val.ulong;
    }
    return ret;
}

unsigned long getArrayValCheck(unsigned char* fp, const char* column, int id, int index, int type) {
    unsigned char* member = getMember(fp, column);
    uVal val;
    if (member == 0) {
        clearVal(&val);
        return val.ulong;
    }
    bool same = getValCheckSub(fp, member, type);
    unsigned long ret = getArrayVal(fp, member, id, index);
    if (!same) {
        val.ulong = ret;
        convertType(fp, member, type, &val);
        return val.ulong;
    }
    return ret;
}

unsigned long getArrayValCheck(unsigned char* fp, unsigned char* member, int id, int index, int type) {
    uVal val;
    if (member == 0) {
        clearVal(&val);
        return val.ulong;
    }
    bool same = getValCheckSub(fp, member, type);
    unsigned long ret = getArrayVal(fp, member, id, index);
    if (!same) {
        val.ulong = ret;
        convertType(fp, member, type, &val);
        return val.ulong;
    }
    return ret;
}


}  // namespace Bdat
