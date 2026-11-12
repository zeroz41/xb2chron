// LibMessageStudio's message binary functions (C): the file header and the list of its blocks.
#include <string.h>
#include "lms/libms.h"

void LMSi_AnalyzeMessageBinary(LMSiBinary* binary, const char* signature, int version) {
    const LMSiFileHeader* header = (const LMSiFileHeader*)binary->data;
    size_t offset;
    size_t pos;
    int i;
    binary->encoding = header->encoding;
    binary->numBlocks = header->numBlocks;
    if (binary->numBlocks == 0) {
        binary->blocks = NULL;
    } else {
        binary->blocks = (LMSiBlock*)LMSi_Malloc(binary->numBlocks * sizeof(LMSiBlock));
    }
    binary->fileSize = ((const LMSiFileHeader*)binary->data)->fileSize;
    offset = sizeof(LMSiFileHeader);
    for (i = 0; i < binary->numBlocks; i++) {
        // the block's header, read through a byte cursor (the file gives no alignment)
        LMSiBlock* block = &binary->blocks[i];
        block->data = &binary->data[offset + sizeof(LMSiBlockHeader)];
        pos = offset;
        block->type[0] = binary->data[pos];
        pos++;
        block->type[1] = binary->data[pos];
        pos++;
        block->type[2] = binary->data[pos];
        pos++;
        block->type[3] = binary->data[pos];
        pos++;
        memcpy(&block->size, &binary->data[pos], sizeof(block->size));
        pos += sizeof(block->size);
        memcpy(&block->reserved, &binary->data[pos], sizeof(block->reserved));
        offset = (offset + sizeof(LMSiBlockHeader) + block->size + 0xF) & ~(size_t)0xF;
    }
}

int LMSi_SearchBlockByName(LMSiBinary* binary, const char* type) {
    unsigned short i;
    for (i = 0; i < binary->numBlocks; i++) {
        if (LMSi_MemCmp(binary->blocks[i].type, type, 4)) {
            return i;
        }
    }
    return -1;
}
