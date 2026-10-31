#include "lms/libms.h"
#include "ms/MsWrapper.h"
#include "ml/EdianUtil.h"
#include "rcha/RchaAnm.h"
#include <math.h>
#include "mtl/MemManager.h"
#include <string.h>

namespace ms {

LMS_ProjectBinary* MsWrapper::m_pProj;
mtl::ALLOC_HANDLE MsWrapper::m_allocHandle;

void MsWrapper::init(mtl::ALLOC_HANDLE handle) {
    m_pProj = nullptr;
    m_allocHandle = handle;
    LMS_SetMemFuncs(myAlloc, myFree);
}

void* MsWrapper::myAlloc(unsigned long size) {
    return mtl::MemManager::allocate(m_allocHandle, size, 4, false, "no name", 0);
}

void MsWrapper::myFree(void* memory) {
    mtl::MemManager::deallocate(memory, 0, false);
}

void MsWrapper::regist(const char* data) {
    m_pProj = LMS_InitProject(data);
}

void MsWrapper::unregist() {
    LMS_CloseProject(m_pProj);
    m_pProj = nullptr;
}

int MsWrapper::getColorNum() {
    return LMS_GetColorNum(m_pProj);
}

bool MsWrapper::getColor(unsigned int index, LMSColor* color) {
    return LMS_GetColor(m_pProj, index, color) == 0;
}

bool MsWrapper::getColorName(unsigned int index, char* buffer, unsigned int size) {
    LMS_ProjectBinary* project = m_pProj;
    if (project->clr1 == -1) {
        return true;
    }
    const LMSiColorBlock* colors = static_cast<const LMSiColorBlock*>(project->common.blocks[project->clr1].data);
    if (colors->count <= static_cast<int>(index) || project->clb1 == -1) {
        return false;
    }
    const unsigned char* labels = static_cast<const unsigned char*>(project->common.blocks[project->clb1].data);
    const unsigned int* slots = reinterpret_cast<const unsigned int*>(labels);
    for (unsigned int i = 0; i < slots[0]; i++) {
        unsigned long offset = slots[static_cast<int>(i * 2 + 2)];
        unsigned char length = labels[offset];
        if (*reinterpret_cast<const unsigned int*>(labels + (offset + 1 + length)) == index) {
            if (length + 1 < static_cast<int>(size)) {
                memcpy(buffer, labels + (offset + 1), length);
                buffer[length] = '\0';
            }
            return true;
        }
    }
    return false;
}

int MsWrapper::getTagNum(int group) {
    return LMS_GetTagNum(m_pProj, group);
}

int MsWrapper::getTagParamListItemNum(int group, int tag, int param) {
    return LMS_GetTagListItemNum(m_pProj, group, tag, param);
}

const char* MsWrapper::getTagName(int group, int tag) {
    return LMS_GetTagName(m_pProj, group, tag);
}

const char* MsWrapper::getTagParamListItemName(int group, int tag, int param, int item) {
    return LMS_GetTagListItemName(m_pProj, group, tag, param, item);
}

}  // namespace ms

// `value`, or 0 when it is not finite or is the fill pattern 0xCCCCCCCC (the helper's name is not the original's)
static inline float validValue(float value) {
    unsigned int bits = *reinterpret_cast<unsigned int*>(&value);
    return (bits & 0x7F800000) != 0x7F800000 && bits != 0xCCCCCCCC ? value : 0.0f;
}

// the value at `frame` rounded to the nearest integer
int RchaAnm::getValueInt(float frame) const {
    float value = getValue(frame);
    int whole = (int)value;
    return whole + (value - (float)whole > 0.5f);
}

// the value at `frame`, interpolated between the frames around it. A compressed track is a run of blocks, each a
// big-endian head word (bits 28..31 the kind, bits 0..27 the frames it covers) and its data: kind 2 one base word and
// a short difference per further frame (padded to a word unless bit 0), kind 1 one word for every frame, else one word
// per frame. Interpolated and track values go through validValue.
float RchaAnm::getValue(float frame) const {
    const unsigned int* data = m_buffer.m_size != 0 ? m_buffer.m_data : m_data;
    if (data == nullptr) {
        return *reinterpret_cast<const float*>(&m_value);
    }
    frame = frame < 0.0f ? 0.0f : frame;
    float lo = floorf(frame);
    float hi = ceilf(frame);
    if (!m_compressed) {
        if (hi >= (float)m_count) {
            return reinterpret_cast<const float*>(data)[m_count - 1];
        }
        float first = reinterpret_cast<const float*>(data)[(unsigned int)lo];
        if (lo == hi) {
            return first;
        }
        float second = reinterpret_cast<const float*>(data)[(unsigned int)hi];
        return validValue(first + (second - first) * (frame - lo));
    } else {
        unsigned int loFrame = (unsigned int)lo;
        unsigned int hiFrame = (unsigned int)hi;
        float first = 0.0f;
        unsigned int second;
        unsigned int start = 0;
        const unsigned int* block = data;
        for (;;) {
            const unsigned int* body = block + 1;
            unsigned int head = ml::EdianUtil::read(*block);
            unsigned int kind = head & 0xF0000000;
            unsigned int count = head & 0x0FFFFFFF;
            if (kind == 0x10000000) {
                unsigned int end = start + count;
                if (loFrame >= start && end > loFrame) {
                    unsigned int word = ml::EdianUtil::read(*body);
                    first = *reinterpret_cast<float*>(&word);
                }
                if (hiFrame >= start && end > hiFrame) {
                    second = ml::EdianUtil::read(*body);
                    break;
                }
                block += 2;
                start = end;
            } else if (kind == 0x20000000) {
                const short* diffs = reinterpret_cast<const short*>(block + 2);
                unsigned int end = start + count;
                if (loFrame >= start && end > loFrame) {
                    unsigned int word = ml::EdianUtil::read(*body);
                    if (loFrame > start) {
                        word -= ml::EdianUtil::read(diffs[loFrame - 1 - start]);
                    }
                    first = *reinterpret_cast<float*>(&word);
                }
                if (hiFrame >= start && end > hiFrame) {
                    second = ml::EdianUtil::read(*body);
                    if (hiFrame > start) {
                        second -= ml::EdianUtil::read(diffs[hiFrame - 1 - start]);
                    }
                    break;
                }
                const short* next = diffs + (count - 1);
                if ((head & 1) == 0) {
                    next++;
                }
                block = reinterpret_cast<const unsigned int*>(next);
                start = end;
            } else {
                unsigned int end = start + count;
                if (loFrame >= start && end > loFrame) {
                    unsigned int word = ml::EdianUtil::read(body[loFrame - start]);
                    first = *reinterpret_cast<float*>(&word);
                }
                if (hiFrame >= start && end > hiFrame) {
                    second = ml::EdianUtil::read(body[hiFrame - start]);
                    break;
                }
                block = body + count;
                start = end;
            }
        }
        float last = *reinterpret_cast<float*>(&second);
        float value;
        if (lo == hi || hi >= (float)m_count) {
            value = last;
        } else {
            value = first + (last - first) * (frame - lo);
        }
        return validValue(value);
    }
}
