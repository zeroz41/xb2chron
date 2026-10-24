// skdlib's sphere detection jobs and LibMessageStudio's memory functions, as the split places them. Both cite
// skdlib's include paths (SKD_LIB_PROJECT), which a unit outside libs/skdlib does not get from its command.
#define MM_LIB_FROM_LIBS
#define SKD_LIB_PROJECT
#include "anm/Array.h"
#include "anm/JobQueue.h"
#include "skd/CalcUtil.h"
#include "skd/CollisionObj.h"
#include "skd/DetectInfo.h"
#include "skd/DetectJob.h"
#include "skd/ResSolver.h"
#include "skd/NodeArray.h"
#include "lms/libms.h"

// the functions LMSi_Malloc and LMSi_Free hand on to (the name is not the original's: the symbols leave it unnamed)
static struct {
    LMS_MallocFunc mallocFunc;
    LMS_FreeFunc freeFunc;
} s_memFuncs;
extern "C" {

void LMS_SetMemFuncs(LMS_MallocFunc mallocFunc, LMS_FreeFunc freeFunc) {
    s_memFuncs.mallocFunc = mallocFunc;
    s_memFuncs.freeFunc = freeFunc;
}

void* LMSi_Malloc(size_t size) {
    return s_memFuncs.mallocFunc(size);
}

void LMSi_Free(void* memory) {
    s_memFuncs.freeFunc(memory);
}

}  // extern "C"
