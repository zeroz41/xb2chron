#ifndef CLASSES_LAYER_LAYERFONTRESOBJ_H
#define CLASSES_LAYER_LAYERFONTRESOBJ_H

#include "layer/LayerBase.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { class LayerFontManager; }

namespace layer {
// a font resource's header (the names are not the original's)
struct LayerFontResHead {
    unsigned char pad_0[0xC];
    unsigned int m_fontInfoOffset;   // 0xC: LayerFontResObj::m_fontInfo, from the resource's start (setFontData)
    unsigned int m_codeIndexOffset;  // 0x10: m_codeIndex, the same
    unsigned char pad_14[0x4];
    unsigned int m_hashTblOffset;    // 0x18: m_hashTbl, the same
    unsigned char pad_1C[0x4];
    unsigned int m_hashMask;       // 0x20: a character code's bits that pick its hash bucket (getFontInfo)
    unsigned int m_textureOffset;  // 0x24: its image, from the resource's start (setupResource)
    unsigned int m_textureSize;    // 0x28
    unsigned int m_texInfoOffset;  // 0x2C: m_texInfo, from the resource's start
    unsigned int m_border;         // 0x30: m_border's pixels
};

// table 0x7100B80670
// A LayerBase: its table has LayerBase's shape (slot 0 destructor, slot 2 release), and the layer accessors hand
// their LayerBase* to its methods unadjusted (LayerAccFontObj::setMsg/setColorMap, LayerAccFontStyle).
class LayerFontResObj : public ::layer::LayerBase {
public:
    // 1.0.0/2.0.0's constructor (out of line there, inline in LayerFontManager::createFontResObj in 3.0.1)
    LayerFontResObj(LayerFontManager* manager) {
        m_prev = nullptr;
        m_next = nullptr;
        m_manager = manager;
        m_state = 0xCC;
        m_objType = 10;
        m_releaseFlags = 0;
        m_data = nullptr;
        m_texture = nullptr;
        m_cellUvWidth = 1.0f;
        m_cellUvHeight = 1.0f;
        m_border = 0.0f;
        m_borderWidth = 0.0f;
    }
    virtual ~LayerFontResObj();  // slot 0
    virtual void release();  // slot 2
    virtual void setupResource();  // slot 3

    // The field names are not the original's.
    unsigned char m_state;  // 0x1C: 0xCC when made, 0x22 once released
    unsigned char pad_1D[0x3];
    LayerFontManager* m_manager;  // 0x20
    unsigned int m_releaseFlags;  // 0x28: release sets bit LayerManager::s_nStkIdx (LayerFontManager::update)
    unsigned char pad_2C[0x4];
    const unsigned char* m_data;  // 0x30: the resource
    const LayerFontResHead* m_head;  // 0x38: the same
    // a character's record (4 bytes)
    struct FontInfo {
        unsigned short m_code;
        unsigned char m_left;   // its first column in its cell
        unsigned char m_width;  // its width in pixels
    };
    // a hash bucket: its run of m_codeIndex, sorted by code
    struct HashEntry {
        unsigned short m_start;
        unsigned short m_num;
    };
    // the font image's grid (the cells are 1 pixel apart)
    struct TexInfo {
        unsigned int m_texWidth;
        unsigned int m_texHeight;
        unsigned int m_cellWidth;
        unsigned int m_cellHeight;
        unsigned int m_cellNumX;  // cells per row
    };
    // code's record and its index (1.0.0 has it out of line; the first record and 0 when the font lacks it)
    const FontInfo* getFontInfo(unsigned short& index, unsigned short code) const {
        index = 0;
        const HashEntry& entry = m_hashTbl[code & m_head->m_hashMask];
        if (entry.m_num != 0) {
            const unsigned short* codes = m_codeIndex + entry.m_start;
            int hi = entry.m_num;
            int lo = 0;
            do {
                int mid = (hi + lo) >> 1;
                const FontInfo* info = &m_fontInfo[codes[mid]];
                if (info->m_code == code) {
                    index = codes[mid];
                    return info;
                }
                if (info->m_code < code) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            } while (lo <= hi);
        }
        return m_fontInfo;
    }
    // 2.0.0's (inline in 3.0.1): data is the font resource
    void setFontData(const void* data) {
        m_data = static_cast<const unsigned char*>(data);
        m_head = static_cast<const LayerFontResHead*>(data);
        m_fontInfo = reinterpret_cast<const FontInfo*>(m_data + m_head->m_fontInfoOffset);
        m_codeIndex = reinterpret_cast<const unsigned short*>(m_data + m_head->m_codeIndexOffset);
        m_hashTbl = reinterpret_cast<const HashEntry*>(m_data + m_head->m_hashTblOffset);
        m_texInfo = reinterpret_cast<const TexInfo*>(m_data + m_head->m_texInfoOffset);
        m_border = (float)m_head->m_border;
        m_borderWidth = m_border + m_border;
        m_cellUvWidth = (float)m_texInfo->m_cellWidth / (float)m_texInfo->m_texWidth;
        m_cellUvHeight = (float)m_texInfo->m_cellHeight / (float)m_texInfo->m_texHeight;
        m_releaseFlags |= 4;
    }
    const HashEntry* m_hashTbl;      // 0x40: in the resource (LayerFontManager::createFontResObj)
    const unsigned short* m_codeIndex;  // 0x48: the same
    const FontInfo* m_fontInfo;      // 0x50: the same
    const TexInfo* m_texInfo;        // 0x58: the same
    grlib::CGLibTextureBuffer* m_texture;  // 0x60: setupResource makes it
    float m_cellUvWidth;   // 0x68: a cell's width over the image's
    float m_cellUvHeight;  // 0x6C: the same for its height
    float m_border;        // 0x70: from the resource's header
    float m_borderWidth;   // 0x74: twice m_border
};
}  // namespace layer

#endif
