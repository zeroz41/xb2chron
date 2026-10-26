#ifndef CLASSES_LAYER_LAYERFONTRESOBJ_H
#define CLASSES_LAYER_LAYERFONTRESOBJ_H

#include "layer/LayerBase.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { class LayerFontManager; }

namespace layer {
// a font resource's header (the names are not the original's)
struct LayerFontResHead {
    unsigned char pad_0[0x24];
    unsigned int m_textureOffset;  // 0x24: its image, from the resource's start (setupResource)
    unsigned int m_textureSize;    // 0x28
};

// table 0x7100B80670
// A LayerBase: its table has LayerBase's shape (slot 0 destructor, slot 2 release), and the layer accessors hand
// their LayerBase* to its methods unadjusted (LayerAccFontObj::setMsg/setColorMap, LayerAccFontStyle).
class LayerFontResObj : public ::layer::LayerBase {
public:
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
    unsigned char pad_40[0x20];
    grlib::CGLibTextureBuffer* m_texture;  // 0x60: setupResource makes it
    unsigned char pad_68[0x10];
};
}  // namespace layer

#endif
