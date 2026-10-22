#ifndef MS_MSWRAPPER_H
#define MS_MSWRAPPER_H

#include "lms/libms.h"
#include "mtl/AllocHandle.h"

namespace ms {

// the game's access to its LibMessageStudio project: one project, its memory from one monolib allocator
class MsWrapper {
public:
    // forgets the project and hands LMS the allocator's functions
    static void init(mtl::ALLOC_HANDLE handle);
    static void* myAlloc(unsigned long size);
    static void myFree(void* memory);
    static void regist(const char* data);
    static void unregist();
    static int getColorNum();
    // the color of an index: whether LMS_GetColor succeeded
    static bool getColor(unsigned int index, LMSColor* color);
    // the label of a color index, copied into buffer when it fits (false: the index has no color, or no label is
    // found)
    static bool getColorName(unsigned int index, char* buffer, unsigned int size);
    static unsigned short getTagNum(int group);
    static unsigned short getTagParamListItemNum(int group, int tag, int param);
    static const char* getTagName(int group, int tag);
    static const char* getTagParamListItemName(int group, int tag, int param, int item);

    static LMS_ProjectBinary* m_pProj;
    static mtl::ALLOC_HANDLE m_allocHandle;
};

}  // namespace ms

#endif
