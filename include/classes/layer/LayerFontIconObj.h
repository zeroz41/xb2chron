#ifndef CLASSES_LAYER_LAYERFONTICONOBJ_H
#define CLASSES_LAYER_LAYERFONTICONOBJ_H

#include "layer/LayerBase.h"

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

// table 0x7100B80640
// A LayerBase: its table has LayerBase's shape (slot 0 destructor, slot 2 release), and the layer accessors hand
// their LayerBase* to its methods unadjusted (LayerAccFontObj::setMsg/setColorMap, LayerAccFontStyle).
// LayerFontManager::createFontIconObj (type 11) and createFontColMapObj (type 12) make it.
class LayerFontIconObj : public ::layer::LayerBase {
public:
    virtual ~LayerFontIconObj();  // slot 0
    virtual void release();  // slot 2
    virtual void setupResource();  // slot 3
    // the four UV values of icon code (the first record's past the table's end; 1, 1, 0, 0 without a table)
    void getFontUvOnlyParms(float* uv, unsigned short code) const;

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
    unsigned char pad_4C[0xC];
};
}  // namespace layer

#endif
