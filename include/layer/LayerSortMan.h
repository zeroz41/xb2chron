#ifndef LAYER_LAYERSORTMAN_H
#define LAYER_LAYERSORTMAN_H

#include "mm/Vec3.h"

namespace layer {
class LayerManager;
class LayerSortObj;

// sorts the layer objects to draw into 2D priority slots and 3D distance slots (each a list with head and tail
// tables and a bit per used slot, all in one allocation), then chains the used slots into one list (end). The
// field names are not the original's
class LayerSortMan {
public:
    LayerSortMan(LayerManager* manager, unsigned int num2D, unsigned int num3D);
    ~LayerSortMan();
    void begin(const mm::Vec3& pos);
    void set2DSpace(LayerSortObj* obj, unsigned int priority);
    void stock2DObj(LayerSortObj* obj, int index);
    void set3DSpace(LayerSortObj* obj, float distance);
    void stock3DObj(LayerSortObj* obj, int index);
    void end();
    void finalRender();

    LayerManager* m_manager;  // 0x0
    void* m_mem;              // 0x8
    LayerSortObj** m_2DHead;  // 0x10
    LayerSortObj** m_2DTail;  // 0x18
    LayerSortObj** m_3DHead;  // 0x20
    LayerSortObj** m_3DTail;  // 0x28
    unsigned int* m_2DBits;   // 0x30
    unsigned int* m_3DBits;   // 0x38
    LayerSortObj* m_top;      // 0x40: the list end built
    LayerSortObj* m_last;     // 0x48
    mm::Vec3 m_pos;           // 0x50: begin's
    float m_alphaMax;         // 0x60: 255 (what reads it is not known)
    float m_far;              // 0x64: 300, set3DSpace's distance for the last slot
    float m_power;            // 0x68: 0.8, set3DSpace's curve
    unsigned int m_2DNum;     // 0x6C
    unsigned int m_3DNum;     // 0x70
    unsigned int m_2DBitSize;  // 0x74
    unsigned int m_3DBitSize;  // 0x78
};
}  // namespace layer

#endif
