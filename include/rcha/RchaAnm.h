#ifndef RCHA_RCHAANM_H
#define RCHA_RCHAANM_H

#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"

// one animated value of an Rcha node (1.0.0's RchaAnm::getValue(float) and getValueInt(float), which read it): a
// constant, or a track of per-frame words in the node's data (compressed when m_compressed), or a buffer of its own.
// It has no table and no out-of-line constructor, clear or destructor; RchaNode's inline them.
// The field, inline function and nested class names are not the original's: they are named from what getValue and
// RchaNode::setup do with them.
class RchaAnm {
public:
    // words getValue reads instead of the track while it holds any, freed through mtl::MemManager when its own
    // (a class of its own: RchaNode's constructor stores its fields in the order an inlined constructor of one
    // does)
    class Buffer {
    public:
        Buffer() : m_data(nullptr), m_size(0), m_capacity(0), m_owned(0), pad_18(0), pad_20(0) {}
        ~Buffer() { release(); }

        void release() {
            m_size = 0;
            if (m_owned != 0 && m_data != nullptr) {
                mtl::MemManager::deallocate(m_data, 0, false);
                m_data = nullptr;
            }
            m_data = nullptr;
            m_capacity = 0;
            m_owned = 0;
        }

        unsigned int* m_data;     // 0x00
        unsigned int m_size;      // 0x08
        unsigned int m_capacity;  // 0x0C
        unsigned int m_owned;     // 0x10
        unsigned long pad_18;     // 0x18 cleared by the constructor
        unsigned int pad_20;      // 0x20 cleared by the constructor
        unsigned char pad_24[4];  // 0x24
    };

    RchaAnm() : m_value(0), m_count(0), m_data(nullptr), m_compressed(false), m_id(0) {}

    float getValue(float frame) const;
    int getValueInt(float frame) const;

    void clear() {
        m_buffer.release();
        m_name.m_nLen = 0;
        m_name.m_str[0] = '\0';
        m_compressed = false;
        m_value = 0;
        m_count = 0;
        m_data = nullptr;
    }
    // a constant value
    void setValue(unsigned int value) {
        m_buffer.release();
        m_value = value;
    }
    // a track of `count` frames at `data`
    void setTrack(int count, unsigned int* data, bool compressed) {
        m_buffer.release();
        m_count = count;
        m_data = data;
        m_compressed = compressed;
    }

    mm::mtl::FixStr<64> m_name;  // 0x00
    Buffer m_buffer;             // 0x48
    unsigned int m_value;        // 0x70 the constant, when there is no track
    int m_count;                 // 0x74 the track's frame count
    unsigned int* m_data;        // 0x78 the track
    bool m_compressed;           // 0x80
    unsigned int m_id;           // 0x84 the track's id from the data
};

#endif
