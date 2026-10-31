// LibMessageStudio's project queries (C): the colors and the tags a project binary ("MsgPrjBn") lists.
#include "lms/libms.h"


// the entry at the index of a block that lists its entries by offset (the helper's name is not the original's)
static const void* LMSi_GetTableEntry(LMS_ProjectBinary* project, int block, unsigned short index) {
    const LMSiOffsetTable* table = (const LMSiOffsetTable*)project->common.blocks[block].data;
    return (const char*)table + table->offsets[index];
}

// the tag group with the id (the groups are sorted by id), NULL when there is none
// (the helper's name is not the original's)
static const LMSiTagGroup* LMSi_GetTagGroup(LMS_ProjectBinary* project, unsigned short groupId) {
    const LMSiOffsetTable* table;
    size_t i;
    if (project->tgg2 == -1) {
        return NULL;
    }
    table = (const LMSiOffsetTable*)project->common.blocks[project->tgg2].data;
    for (i = 0; i < table->count; i++) {
        const LMSiTagGroup* group = (const LMSiTagGroup*)((const char*)table + table->offsets[i]);
        if (group->id == groupId) {
            return group;
        }
        if (group->id > groupId) {
            return NULL;
        }
    }
    return NULL;
}

// the group's tag at the index (the helper's name is not the original's)
static const LMSiTag* LMSi_GetTag(LMS_ProjectBinary* project, const LMSiTagGroup* group, unsigned short tagIndex) {
    if (project->tag2 == -1) {
        return NULL;
    }
    if (tagIndex >= group->numTags) {
        return NULL;
    }
    return (const LMSiTag*)LMSi_GetTableEntry(project, project->tag2, group->tags[tagIndex]);
}

int LMS_GetColorNum(LMS_ProjectBinary* project) {
    if (project->clr1 != -1) {
        return ((const LMSiColorBlock*)project->common.blocks[project->clr1].data)->count;
    }
    return 0;
}

int LMS_GetColor(LMS_ProjectBinary* project, int index, LMSColor* color) {
    const LMSiColorBlock* block;
    if (project->clr1 == -1) {
        return -5;
    }
    block = (const LMSiColorBlock*)project->common.blocks[project->clr1].data;
    if (index < block->count) {
        color->r = block->colors[index][0];
        color->g = block->colors[index][1];
        color->b = block->colors[index][2];
        color->a = block->colors[index][3];
        return 0;
    }
    return -1;
}

const char* LMS_GetTagName(LMS_ProjectBinary* project, unsigned short groupId, unsigned short tagIndex) {
    const LMSiTagGroup* group = LMSi_GetTagGroup(project, groupId);
    const LMSiTag* tag;
    if (group == NULL) {
        return NULL;
    }
    tag = LMSi_GetTag(project, group, tagIndex);
    if (tag == NULL) {
        return NULL;
    }
    return (const char*)&tag->params[tag->numParams];
}

int LMS_GetTagNum(LMS_ProjectBinary* project, unsigned short groupId) {
    const LMSiTagGroup* group = LMSi_GetTagGroup(project, groupId);
    if (group == NULL) {
        return 0;
    }
    return group->numTags;
}
