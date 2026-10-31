#include "classes/ui/UIMotionData.h"

#include <string.h>

namespace ui {

namespace {
// a motion file's header ('UIM ', version 1.0; the names are not the original's)
struct MotionFileHeader {
    unsigned int m_magic;
    unsigned int m_version;
    unsigned int m_motionCount;
    unsigned int m_motionOffset;  // from the file's start
    unsigned int m_nameCount;
    unsigned int m_nameOffset;    // from the file's start: m_nameCount strings one after the other
};
// a motion's entry in the file, its frames following (a count, then that many Parameters, each; the names are not
// the original's)
struct MotionFileEntry {
    unsigned int m_nameIndex;
    unsigned int m_frameCount;
};
}  // namespace

UIMotionData::UIMotionData(mm::mtl::IAllocator* allocator) : m_allocator(allocator) {
    if (allocator != nullptr) {
        m_motions.setAllocator(allocator);
        m_names.setAllocator(allocator);
    }
}

UIMotionData::~UIMotionData() {
    clear();
}

void UIMotionData::clear() {
    for (unsigned int i = 0; i < m_motions.size(); ++i) {
        if (m_motions[i].m_frames.size() != 0) {
            for (unsigned int j = 0; j < m_motions[i].m_frames.size(); ++j) {
                if (m_motions[i].m_frames[j].capacity() != 0) {
                    m_motions[i].m_frames[j].destroy();
                }
            }
            m_motions[i].m_frames.destroy();
        }
    }
    if (m_motions.capacity() != 0) {
        m_motions.destroy();
    }
    if (m_names.capacity() != 0) {
        m_names.destroy();
    }
}

void UIMotionData::deserialize(const void* data, unsigned int) {
    const MotionFileHeader* header = static_cast<const MotionFileHeader*>(data);
    if (header == nullptr || header->m_magic != 0x204D4955 || header->m_version != 0x10000) {
        return;
    }
    clear();
    const unsigned char* p = static_cast<const unsigned char*>(data) + header->m_motionOffset;
    m_motions.reserve(header->m_motionCount);
    for (unsigned int i = 0; i < header->m_motionCount; ++i) {
        const MotionFileEntry* entry = reinterpret_cast<const MotionFileEntry*>(p);
        m_motions.push_back(MotionData());
        m_motions[i].m_frames.setAllocator(m_allocator);
        m_motions[i].m_frames.reserve(entry->m_frameCount);
        m_motions[i].m_nameIndex = entry->m_nameIndex;
        p += sizeof(MotionFileEntry);
        for (unsigned int j = 0; j < entry->m_frameCount; ++j) {
            const unsigned int* count = reinterpret_cast<const unsigned int*>(p);
            m_motions[i].m_frames.push_back(mm::mtl::Vector<Parameter>());
            m_motions[i].m_frames[j].setAllocator(m_allocator);
            m_motions[i].m_frames[j].reserve(*count);
            p += sizeof(unsigned int);
            for (unsigned int k = 0; k < *count; ++k) {
                m_motions[i].m_frames[j].push_back(*reinterpret_cast<const Parameter*>(p));
                p += sizeof(Parameter);
            }
        }
    }
    const char* name = static_cast<const char*>(data) + header->m_nameOffset;
    m_names.reserve(header->m_nameCount);
    for (unsigned int i = 0; i < header->m_nameCount; ++i) {
        m_names.push_back(name);
        name += strlen(name) + 1;
    }
}

int UIMotionData::searchMotion(const char* name) const {
    for (unsigned int i = 0; i < m_motions.size(); ++i) {
        if (m_motions[i].m_nameIndex < static_cast<int>(m_names.size())) {
            if (strcmp(m_names[m_motions[i].m_nameIndex], name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

float UIMotionData::getMotionLength(unsigned int index) const {
    if (index < m_motions.size()) {
        return m_motions[index].m_frames.size() * (1.0f / 30.0f);
    }
    return 0.0f;
}

bool UIMotionData::getMotionParamDefault(unsigned int index, MotionParam& param) const {
    if (index < m_motions.size()) {
        unsigned int kind;
        return getMotionParamFrame(index, 0, kind, param) & (kind == 0);
    }
    return false;
}

bool UIMotionData::getMotionParamFrame(unsigned int index, unsigned int frame, unsigned int& kind,
                                       MotionParam& param) const {
    if (index < m_motions.size() && frame < m_motions[index].m_frames.size()) {
        const mm::mtl::Vector<Parameter>& params = m_motions[index].m_frames[frame];
        param = MotionParam();
        Parameter::Value value;
        for (unsigned int i = 0; i < params.size(); ++i) {
            if (params[i].m_flags == 0) {
                value = params[i].m_value;
            } else if (params[i].m_flags & 1) {
                if (params[i].m_value.i < static_cast<int>(m_names.size())) {
                    // the name entry's first four bytes
                    value = *reinterpret_cast<const Parameter::Value*>(&m_names[params[i].m_value.i]);
                }
            } else if (params[i].m_flags & 2) {
                value = params[i].m_value;
            }
            switch (params[i].m_type) {
            case 1:
                kind = value.u;
                break;
            case 2:
                param.m_flags |= 1;
                param.m_posX = value.f;
                break;
            case 3:
                param.m_flags |= 2;
                param.m_posY = value.f;
                break;
            case 4:
                param.m_flags |= 4;
                param.m_scaleX = value.f;
                break;
            case 5:
                param.m_flags |= 8;
                param.m_scaleY = value.f;
                break;
            case 6:
                param.m_flags |= 0x10;
                param.m_rot = value.f * 0.017453292f;
                break;
            case 7:
                param.m_flags |= 0x20;
                param.m_alpha = value.f / 100.0f;
                break;
            }
        }
        return true;
    }
    return false;
}

bool UIMotionData::getMotionParamDelta(unsigned int index, float time, float step, MotionParam& param) const {
    bool result = false;
    if (step != 0.0f && index < m_motions.size()) {
        MotionParam frameParam = MotionParam();
        param = MotionParam();
        int frame = static_cast<int>(time / (1.0f / 30.0f));
        float rest = time - frame * (1.0f / 30.0f);
        if (rest < 1e-06f) {
            rest = 0.0f;
        }
        if (step > 1e-06f) {
            if (rest + 1e-06f >= 1.0f / 30.0f) {
                rest = 0.0f;
                ++frame;
            }
            do {
                ++frame;
                float rate;
                float span;
                if (rest != 0.0f) {
                    if (step + rest > 1.0f / 30.0f) {
                        rate = 1.0f - rest / (1.0f / 30.0f);
                        span = 1.0f / 30.0f - rest;
                    } else {
                        rate = step / (1.0f / 30.0f);
                        span = step;
                    }
                    rest = 0.0f;
                } else if (step < 1.0f / 30.0f) {
                    rate = step / (1.0f / 30.0f);
                    span = step;
                } else {
                    rate = 1.0f;
                    span = 1.0f / 30.0f;
                }
                unsigned int kind;
                if (!getMotionParamFrame(index, frame, kind, frameParam)) {
                    return false;
                }
                if (kind == 1) {
                    param.m_posX += rate * frameParam.m_posX;
                    param.m_posY += rate * frameParam.m_posY;
                    param.m_scaleX += rate * frameParam.m_scaleX;
                    param.m_scaleY += rate * frameParam.m_scaleY;
                    param.m_rot += rate * frameParam.m_rot;
                    param.m_alpha += rate * frameParam.m_alpha;
                }
                step -= span;
                if (step < 1e-06f) {
                    step = 0.0f;
                }
            } while (step > 1e-06f);
        }
        result = true;
    }
    return result;
}

}  // namespace ui
