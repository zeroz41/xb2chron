#include "classes/fw/EffectResData.h"
#include <string.h>
#include "anm/AsmAnnotetion.h"
#include "classes/anm/ResASM.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

namespace {
// the frame the state of the name ends at, 30 a second: its last clip's length, 3000 without the state or a clip,
// rounded, less 0.1 (the name is not the original's)
inline float getStateEndFrame(const anm::ResASM* asmRes, const char* name) {
    float frame = 3000.0f;
    const anm::ResStateData* state = asmRes->findResStateData(name);
    if (state != nullptr) {
        for (unsigned int i = 0; i < state->m_clips.size(); ++i) {
            frame = state->m_clips[i].m_end * 30.0f;
        }
    }
    return static_cast<float>(static_cast<int>(frame + (frame > 0.0f ? 0.5f : -0.5f))) - 0.1f;
}

// whether sub is in str (the last occurrence is searched for; the name is not the original's)
inline bool hasSuffix(const char* str, const char* sub) {
    const char* found = strstr(str, sub);
    if (found == nullptr) {
        return false;
    }
    while (*found != '\0') {
        found = strstr(found + 1, sub);
        if (found == nullptr) {
            break;
        }
    }
    return true;
}
}  // namespace

EffectResData* EffectResData::createEffectResData(const SetupInfo& info) {
#line 63
    EffectResData* data = new (info.m_allocator, 16, __FILE__, __LINE__) EffectResData(info.m_allocator);
    if (data != nullptr) {
        data->init(info);
        data->addRef();
    }
    return data;
}

void EffectResData::init(const SetupInfo& info) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < info.m_tables.size(); ++i) {
        unsigned int num = info.m_tables[i].m_size / sizeof(EffectAnnotationTbl);
        if (info.m_tables[i].m_data == nullptr) {
            num = 0;
        }
        count += num;
    }
    m_annotations.reserve(count);
    for (unsigned int i = 0; i < info.m_tables.size(); ++i) {
        unsigned int num = info.m_tables[i].m_size / sizeof(EffectAnnotationTbl);
        if (info.m_tables[i].m_data != nullptr) {
            initSub(num, info.m_tables[i].m_data);
        }
    }
}

void EffectResData::registerAsmAnnotation(anm::ResASM* asmRes, unsigned int kind, const char* name) {
    for (EffectAnnotationData* it = m_annotations.begin(); it != m_annotations.end(); ++it) {
        anm::AsmAnnotetion annotation;
        annotation.m_name = name;
        annotation.m_type = 3;
        annotation.m_data = it;
        float startFrame = getStateEndFrame(asmRes, it->m_stateName.m_str);
        float endFrame = getStateEndFrame(asmRes, it->m_endStateName.m_str);
        switch (it->m_type) {
        case 1:
            if (it->m_startFrame == -1.0f) {
                asmRes->setEnterAnnotation(kind, it->m_stateName.m_str, annotation);
            } else {
                if (startFrame < it->m_startFrame) {
                    it->m_startFrame = startFrame;
                }
                it->m_atStart = true;
                it->m_atEnd = false;
                asmRes->setFrameAnnotation(kind, it->m_stateName.m_str, it->m_startFrame, annotation);
            }
            break;
        case 5:
            asmRes->setEnterAnnotation(kind, it->m_stateName.m_str, annotation);
            if (it->m_baseName.length() > 0 && strcmp(it->m_baseName.m_str, it->m_stateName.m_str) != 0) {
                mm::mtl::FixStr<64> leaveName;
                for (int i = 0; i < 3; ++i) {
                    leaveName.format("%s_%02d", it->m_baseName.m_str, i);
                    asmRes->setLeaveAnnotation(kind, leaveName.m_str, annotation);
                }
            } else {
                asmRes->setLeaveAnnotation(kind, it->m_stateName.m_str, annotation);
            }
            break;
        case 6:
            if (startFrame < it->m_startFrame) {
                it->m_startFrame = startFrame;
            }
            it->m_atStart = true;
            it->m_atEnd = false;
            asmRes->setFrameAnnotation(kind, it->m_stateName.m_str, it->m_startFrame, annotation);
            if (endFrame < it->m_endFrame) {
                it->m_endFrame = endFrame;
            }
            it->m_atStart = false;
            it->m_atEnd = true;
            if (strcmp(it->m_stateName.m_str, it->m_endStateName.m_str) != 0 || it->m_endFrame > 0.0f) {
                asmRes->setFrameAnnotation(kind, it->m_endStateName.m_str, it->m_endFrame, annotation);
            } else {
                it->m_type = 1;
            }
            break;
        case 7:
            if (startFrame < it->m_startFrame) {
                it->m_startFrame = startFrame;
            }
            it->m_atStart = true;
            it->m_atEnd = false;
            asmRes->setFrameAnnotation(kind, it->m_stateName.m_str, it->m_startFrame, annotation);
            if (endFrame < it->m_endFrame) {
                it->m_endFrame = endFrame;
            }
            it->m_atStart = false;
            it->m_atEnd = true;
            if (strcmp(it->m_stateName.m_str, it->m_endStateName.m_str) != 0 || it->m_endFrame > 0.0f) {
                asmRes->setFrameAnnotation(kind, it->m_endStateName.m_str, it->m_endFrame, annotation);
            } else {
                it->m_type = 1;
            }
            asmRes->setLeaveAnnotation(kind, it->m_stateName.m_str, annotation);
            break;
        }
    }
    asmRes->sortAnnotation(kind);
}

EffectResData::~EffectResData() {}

void EffectResData::initSub(unsigned int count, EffectAnnotationTbl* table) {
    EffectAnnotationData data;
    for (unsigned int i = 0; i < count; ++i) {
        data.m_stateName = table[i].m_stateName;
        data.m_startFrame = table[i].m_startFrame;
        data.m_endStateName = table[i].m_endStateName;
        data.m_endFrame = table[i].m_endFrame;
        data.pad_50 = table[i].pad_f8;
        data.pad_54 = table[i].pad_80;
        data.pad_78 = table[i].pad_c0;
        data.m_position = mm::Vec3(table[i].m_position[0], table[i].m_position[1], table[i].m_position[2]);
        data.m_rotation = mm::Vec3(table[i].m_rotation[0] * 0.017453292f, table[i].m_rotation[1] * 0.017453292f,
                                   table[i].m_rotation[2] * 0.017453292f);
        data.pad_f9 = table[i].pad_bd;
        data.pad_fa = table[i].pad_be;
        data.pad_fb = table[i].pad_bf;
        data.pad_f5 = table[i].pad_f7;
        data.pad_f4 = table[i].pad_f6;
        data.pad_f6 = table[i].pad_114;
        data.pad_c4 = table[i].pad_108;
        data.pad_f7 = table[i].pad_115;
        data.pad_100 = table[i].pad_10c;
        data.pad_f0 = table[i].pad_116;
        data.pad_114 = table[i].pad_110;
        data.pad_f8 = table[i].pad_117;
        data.pad_108 = table[i].pad_fc;
        data.pad_10a = table[i].pad_f4;
        if (data.m_stateName.length() != 0 && data.m_endStateName.length() == 0) {
            data.m_endStateName = data.m_stateName;
        }
        if (hasSuffix(data.m_stateName.m_str, "_00") || hasSuffix(data.m_stateName.m_str, "_01") ||
            hasSuffix(data.m_stateName.m_str, "_02")) {
            data.m_baseName = data.m_stateName;
            int length = data.m_baseName.m_nLen - 3;
            data.m_baseName.m_str[length] = '\0';
            data.m_baseName.m_nLen = length;
        } else {
            data.m_baseName = "";
        }
        if (strstr(data.m_stateName.m_str, "<SETUP>") != nullptr) {
            data.m_type = 0;
        } else if (strstr(data.m_stateName.m_str, "<COMBAT>") != nullptr) {
            data.m_type = 2;
        } else if (strstr(data.m_stateName.m_str, "<WPN_CHANGE>") != nullptr) {
            data.m_type = 3;
        } else if (strstr(data.m_stateName.m_str, "<FOOTSTEP>") != nullptr) {
            data.m_type = 4;
        } else if (strstr(data.m_stateName.m_str, "<PROG_HIT>") != nullptr) {
            data.m_type = 8;
        } else if (strstr(data.m_stateName.m_str, "<PROG_BUFF>") != nullptr) {
            data.m_type = 9;
        } else if (data.m_stateName.length() != 0 && data.m_endFrame == -1.0f) {
            data.m_type = 5;
        } else if (strstr(data.m_endStateName.m_str, "<END>") != nullptr) {
            data.m_type = 7;
            data.m_endStateName = data.m_stateName;
        } else {
            data.m_type = 6;
        }
        m_annotations.push_back(data);
    }
}

}  // namespace fw
