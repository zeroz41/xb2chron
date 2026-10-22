#ifndef LAYER_LAYERACCLAYOUTBINARY_H
#define LAYER_LAYERACCLAYOUTBINARY_H

namespace layer { class LayerObj; }

namespace layer {
// access to a layout binary's named positions (UILayoutData reads its layout through one)
class LayerAccLayoutBinary {
public:
    LayerAccLayoutBinary(const void* binary);
    int getPosIdx(const char* name) const;  // -1 when the binary has no position of that name
    void setLayoutPosData(float& x, float& y, float& width, float& height, unsigned int index);
    void setLayoutPosData(float& x, float& y, float& width, float& height, const char* name);
    void setLayoutObj(LayerObj* obj, const char* name, bool apply);

    const void* m_binary;          // the constructor's
    unsigned char pad_08[0x20];    // the tables the constructor finds in it
};
}  // namespace layer

#endif
