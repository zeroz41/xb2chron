#ifndef CLASSES_LAYER_LAYERFONTICONOBJ_H
#define CLASSES_LAYER_LAYERFONTICONOBJ_H

#include "layer/LayerBase.h"
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerShdManager.h"
#include "layer/LayerTextureMan.h"

namespace layer { class LayerFontManager; }
namespace layer { class LayerTextureObj; }

namespace layer {
// an icon font's UV table: a count, then at m_dataOffset its 0x1C-byte records (the names are not the original's)
struct LayerFontIconUvHead {
    unsigned short m_num;
    unsigned char pad_2[0x16];
    unsigned int m_dataOffset;  // 0x18
};
struct LayerFontIconUvData {
    unsigned char pad_0[0x8];
    float m_uv[4];  // 0x8: getFontUvOnlyParms copies them
    unsigned char pad_18[0x4];
};

// an icon font resource's header (the names are not the original's)
struct LayerFontIconResHead {
    unsigned char pad_0[0x8];
    unsigned char m_flags;  // 0x8: bit 1: it has a UV table (createIconRes)
    unsigned char pad_9[0x3];
    unsigned int m_infoOffset;  // 0xC: its LayerFontIconInfo, from the resource's start
    unsigned char pad_10[0x14];
    unsigned int m_textureOffset;  // 0x24: its image (0: none)
    unsigned char pad_28[0x4];
    unsigned int m_uvOffset;  // 0x2C: its LayerFontIconUvHead
};
// the icon image's sizes (laid out like LayerFontResObj::TexInfo; the names are not the original's)
struct LayerFontIconInfo {
    unsigned int m_texWidth;
    unsigned int m_texHeight;
    unsigned int m_cellWidth;
    unsigned int m_cellHeight;
};

// table 0x7100B80640
// A LayerBase: its table has LayerBase's shape (slot 0 destructor, slot 2 release), and the layer accessors hand
// their LayerBase* to its methods unadjusted (LayerAccFontObj::setMsg/setColorMap, LayerAccFontStyle).
// LayerFontManager::createFontIconObj (type 11) and createFontColMapObj (type 12) make it.
class LayerFontIconObj : public ::layer::LayerBase {
public:
    // 1.0.0/2.0.0's constructor (out of line there, inline in LayerFontManager::createFontIconObj and
    // createFontColMapObj in 3.0.1)
    LayerFontIconObj(LayerFontManager* manager, const void* data, LAYER_TYPE type) {
        m_prev = nullptr;
        m_next = nullptr;
        m_manager = manager;
        m_releaseFlags = 0;
        m_state = 0xCC;
        m_objType = type;
        m_data = static_cast<const unsigned char*>(data);
        m_texture = nullptr;
        m_texHeight = 0.0f;
        m_uvNum = 0;
        m_cellHeight = 0.0f;
        createIconRes();
    }
    virtual ~LayerFontIconObj();  // slot 0
    virtual void release();  // slot 2
    virtual void setupResource();  // slot 3
    // the four UV values of icon code (the first record's past the table's end; 1, 1, 0, 0 without a table)
    void getFontUvOnlyParms(float* uv, unsigned short code) const;
    // 2.0.0's (inline in 3.0.1): reads m_data's sizes, texture and UV table
    void createIconRes() {
        const LayerFontIconResHead* head = reinterpret_cast<const LayerFontIconResHead*>(m_data);
        const LayerFontIconInfo* info = reinterpret_cast<const LayerFontIconInfo*>(m_data + head->m_infoOffset);
        m_texHeight = (float)info->m_texHeight;
        m_cellHeight = (float)info->m_cellHeight;
        if (head->m_textureOffset != 0) {
            m_texture = mm::mtl::PtrSingleton<LayerManager>::get()->m_shdManager->m_textureMan->createTextureObj(
                m_data + head->m_textureOffset);
        }
        if (head->m_flags & 2) {
            m_uvHead = reinterpret_cast<const LayerFontIconUvHead*>(m_data + head->m_uvOffset);
            m_uvNum = m_uvHead->m_num;
        } else {
            m_uvHead = nullptr;
            m_uvNum = 0;
        }
    }

    // The field names are not the original's.
    unsigned char m_state;  // 0x1C: 0xCC when made, 0x22 once released
    unsigned char pad_1D[0x3];
    LayerFontManager* m_manager;  // 0x20
    unsigned int m_releaseFlags;  // 0x28: release sets bit LayerManager::s_nStkIdx (LayerFontManager::update)
    unsigned char pad_2C[0x4];
    const unsigned char* m_data;  // 0x30: the resource
    const LayerFontIconUvHead* m_uvHead;  // 0x38: in m_data, when it has one
    LayerTextureObj* m_texture;  // 0x40
    unsigned int m_uvNum;  // 0x48: m_uvHead's m_num
    float m_cellHeight;  // 0x4C: LayerFontIconInfo's (createIconRes; the name is not the original's)
    float m_texHeight;   // 0x50: the same
    unsigned char pad_54[0x4];
};
}  // namespace layer

#endif
