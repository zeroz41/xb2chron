// LibMessageStudio's message binary functions (C): the file header and the list of its blocks.
#include "lms/libms.h"

int LMSi_SearchBlockByName(LMSiBinary* binary, const char* type) {
    unsigned short i;
    for (i = 0; i < binary->numBlocks; i++) {
        if (LMSi_MemCmp(binary->blocks[i].type, type, 4)) {
            return i;
        }
    }
    return -1;
}
