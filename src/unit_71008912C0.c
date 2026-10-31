// LibMessageStudio's project functions (C): a project binary ("MsgPrjBn") and the blocks it holds.
#include "lms/libms.h"

int LMSi_MemCmp(const void* a, const void* b, int count) {
    const char* p = (const char*)a;
    const char* q = (const char*)b;
    int i;
    for (i = 0; i < count; i++) {
        if (p[i] != q[i]) {
            return 0;
        }
    }
    return 1;
}

LMS_ProjectBinary* LMS_InitProject(const void* data) {
    LMS_ProjectBinary* project = (LMS_ProjectBinary*)LMSi_Malloc(sizeof(LMS_ProjectBinary));
    project->common.data = (const unsigned char*)data;
    LMSi_AnalyzeMessageBinary(&project->common, "MsgPrjBn", 4);
    project->clr1 = LMSi_SearchBlockByName(&project->common, "CLR1");
    project->clb1 = LMSi_SearchBlockByName(&project->common, "CLB1");
    project->ati2 = LMSi_SearchBlockByName(&project->common, "ATI2");
    project->alb1 = LMSi_SearchBlockByName(&project->common, "ALB1");
    project->ali2 = LMSi_SearchBlockByName(&project->common, "ALI2");
    project->tgg2 = LMSi_SearchBlockByName(&project->common, "TGG2");
    project->tag2 = LMSi_SearchBlockByName(&project->common, "TAG2");
    project->tgp2 = LMSi_SearchBlockByName(&project->common, "TGP2");
    project->tgl2 = LMSi_SearchBlockByName(&project->common, "TGL2");
    project->syl3 = LMSi_SearchBlockByName(&project->common, "SYL3");
    project->slb1 = LMSi_SearchBlockByName(&project->common, "SLB1");
    project->cti1 = LMSi_SearchBlockByName(&project->common, "CTI1");
    return project;
}

void LMS_CloseProject(LMS_ProjectBinary* project) {
    if (project->common.blocks != NULL) {
        LMSi_Free(project->common.blocks);
    }
    LMSi_Free(project);
}
