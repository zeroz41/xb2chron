#ifndef LAYER_LAYERANIMEOBJ_H
#define LAYER_LAYERANIMEOBJ_H

#include "mtl/AllocHandle.h"

namespace layer {

// the parameters an object's animation moves (calcParm blends each group toward a key's). The field names are not
// the original's; the groups follow the key flags (LayerAnimeInfo::FLAG_)
struct LayerResParmInfo {
    float m_pos[2];    // 0x0: FLAG_POS
    float m_rot;       // 0x8: FLAG_ROT
    float m_scale[2];  // 0xC: FLAG_SCALE
    float m_size[2];   // 0x14: FLAG_SIZE
    float m_color[4];  // 0x1C: FLAG_COLOR
    float m_parm[3];   // 0x2C: FLAG_PARM
};

// one key of an animation (0x40 bytes, LayerAnimeObj(int) allocates its count times 0x40): the frames it lasts and
// the parameters it reaches. The names are not the original's
struct LayerAnimeInfo {
    enum {
        FLAG_POS = 0x1,
        FLAG_ROT = 0x2,
        FLAG_SCALE = 0x4,
        FLAG_SIZE = 0x8,
        FLAG_PARM = 0x10,
        FLAG_COLOR = 0x20,
    };

    unsigned int m_flags;  // 0x0: FLAG_
    float m_frame;         // 0x4: the key's length in frames
    float m_pos[2];        // 0x8
    float m_rot;           // 0x10
    float m_scale[2];      // 0x14
    float m_size[2];       // 0x1C
    float m_color[4];      // 0x24
    float m_parm[3];       // 0x34
};

// an object's animation (LayerObj holds three; baseRelease deletes them): a list of keys played in turn. 1.0.0's
// LayerAnimeObj(int) shows the layout (0x38 bytes); the field names are not the original's
class LayerAnimeObj {
public:
    enum {
        FLAG_LOOP = 0x1,           // setAnimeLoop (1.0.0)
        FLAG_CORRECTION = 0x2,     // setAnimeCorrection (1.0.0): the blend rate is frame / length
        FLAG_SELECT_NUMBER = 0x4,  // setSelectNumber (1.0.0): plays the key setSelectIdx picks, then stops
        FLAG_STOP = 0x8,           // the picked key has been reached (the name is not the original's)
        FLAG_RELEASE = 0x8000,     // release (1.0.0)
    };

    ~LayerAnimeObj();
    // true when the animation has ended (or was released)
    bool update(LayerResParmInfo& info, float frame);
    void calcParm(LayerResParmInfo& info, const LayerAnimeInfo& anime, float frame);

    float m_frame;                     // 0x0: the current key's frame
    unsigned short m_index;            // 0x4: the current key
    unsigned short m_flags;            // 0x6: FLAG_
    unsigned short m_selectIdx[2];     // 0x8: setSelectIdx's key plus one, per LayerManager::s_nStkIdx
    unsigned char pad_0C[0x4];
    LayerAnimeInfo* m_infos;           // 0x10: m_capacity keys, from m_handle
    int m_num;                         // 0x18: the keys in use
    int m_capacity;                    // 0x1C
    mtl::ALLOC_HANDLE m_handle;        // 0x20
    unsigned char pad_24[0x4];
    unsigned char pad_28[0x8];         // 0x28: zeroed by the constructor (1.0.0)
    unsigned char pad_30[0x4];         // 0x30: zeroed by the constructor (1.0.0)
    unsigned char pad_34[0x4];
};
}  // namespace layer

#endif
