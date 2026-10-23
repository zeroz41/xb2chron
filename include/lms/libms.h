#ifndef LMS_LIBMS_H
#define LMS_LIBMS_H

// NintendoWare LibMessageStudio (LMS), as the module links it: C functions (their names are C names). The
// structures' and fields' names are not the original's.
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// one block of a message binary, as LMSi_AnalyzeMessageBinary lists it
typedef struct LMSiBlock {
    const void* data;      // the block's contents (after its 0x10-byte header)
    char type[4];          // its magic ("CLR1", "TGG2", ...)
    unsigned int size;     // its size (the blocks follow each other 16-aligned)
    unsigned short reserved;  // the halfword after the size in its header (the name is not the original's)
} LMSiBlock;

// a message binary and its blocks
typedef struct LMSiBinary {
    const unsigned char* data;  // the file
    size_t fileSize;            // the header's word at 0x12
    unsigned char encoding;     // the header's byte at 0xC
    unsigned short numBlocks;   // the header's halfword at 0xE
    LMSiBlock* blocks;          // LMSi_Malloc's, numBlocks of them
} LMSiBinary;

// a project's color block ("CLR1"): a count, then that many colors, four bytes each
typedef struct LMSiColorBlock {
    int count;
    unsigned char colors[1][4];  // count of them
} LMSiColorBlock;

// a project binary ("MsgPrjBn"): the index of each block LMS_InitProject looks up, -1 for none
typedef struct LMS_ProjectBinary {
    LMSiBinary common;
    int clb1;  // color labels
    int clr1;  // colors
    int alb1;  // attribute labels
    int ati2;  // attribute infos
    int ali2;  // attribute lists
    int tgg2;  // tag groups
    int tag2;  // tags
    int tgp2;  // tag parameters
    int tgl2;  // tag list items
    int syl3;  // styles
    int slb1;  // style labels
    int cti1;  // content infos
} LMS_ProjectBinary;

// a color of the project's color block (ms::MsWrapper::getColor hands one to LMS_GetColor)
typedef struct LMSColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} LMSColor;

typedef void* (*LMS_MallocFunc)(size_t size);
typedef void (*LMS_FreeFunc)(void* memory);

void LMS_SetMemFuncs(LMS_MallocFunc mallocFunc, LMS_FreeFunc freeFunc);
void* LMSi_Malloc(size_t size);
void LMSi_Free(void* memory);
int LMSi_MemCmp(const void* a, const void* b, int count);
LMS_ProjectBinary* LMS_InitProject(const void* data);
void LMS_CloseProject(LMS_ProjectBinary* project);
int LMS_GetColorNum(LMS_ProjectBinary* project);
int LMS_GetColor(LMS_ProjectBinary* project, int index, LMSColor* color);
const char* LMS_GetTagName(LMS_ProjectBinary* project, unsigned short groupId, unsigned short tagIndex);
const char* LMS_GetTagListItemName(LMS_ProjectBinary* project, unsigned short groupId, unsigned short tagIndex,
                                   unsigned short paramIndex, unsigned short itemIndex);
int LMS_GetTagNum(LMS_ProjectBinary* project, unsigned short groupId);
int LMS_GetTagListItemNum(LMS_ProjectBinary* project, unsigned short groupId, unsigned short tagIndex,
                          unsigned short paramIndex);
void LMSi_AnalyzeMessageBinary(LMSiBinary* binary, const char* signature, int version);
int LMSi_SearchBlockByName(LMSiBinary* binary, const char* type);

#ifdef __cplusplus
}
#endif

#endif
