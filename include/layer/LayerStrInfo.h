#ifndef LAYER_LAYERSTRINFO_H
#define LAYER_LAYERSTRINFO_H

#include "mm/Col4.h"
#include "mm/mtl/FixStr.h"

namespace layer {
// a named value of a font style (its colours and icons: UIFontManager::importMSBP fills them from the MessageStudio
// project); 0x24 bytes, the value before the name (Vector<LayerStrInfo>'s copies)
class LayerStrInfo {
public:
    LayerStrInfo();
    void setCol4(const char* name, const mm::Col4& col);
    void setS32(const char* name, int value);
    union {
        mm::Col4 m_col4;  // setCol4's
        int m_s32;        // setS32's
    };
    mm::mtl::FixStr<16> m_name;
};
}  // namespace layer

#endif
