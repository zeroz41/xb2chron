#ifndef LAYER_LAYEROBJPLACE_H
#define LAYER_LAYEROBJPLACE_H

#include "mm/Col3.h"
#include "mm/Col4.h"

namespace layer {

// A node's placement values that LayerObjPlace's reset and animation callbacks write. The field names follow the
// callbacks that write them (placeReset_Pos/Srt/Col, placeAnm_Pos/Scl/Rot/MulCol/AddCol/Blend; not the original's).
struct LayerResNode {
    float m_posX;
    float m_posY;
    float m_sclX;
    float m_sclY;
    float m_rotX;
    float m_rotY;
    mm::Col4 m_mulCol;
    mm::Col3 m_addCol;
    unsigned char pad_34[0x2];
    unsigned char m_flags;  // placeAnm_Blend sets 0x2
    unsigned char m_blend;  // placeAnm_Blend
};

class LayerObjPlace {
public:
    typedef void (*PlaceResetFunc)(LayerResNode*);
    typedef void (*PlaceFormatFunc)(LayerResNode*, int, const unsigned char*, const unsigned char*, unsigned int);
    typedef void (*PlaceAnimFunc)(LayerResNode*, const unsigned char*, unsigned int);

    void updateGblFrm();
    void calcNodePos(float frame);

    static void placeReset_Off(LayerResNode* node);
    static void placeReset_Pos(LayerResNode* node);
    static void placeReset_Srt(LayerResNode* node);
    static void placeReset_Pos_Srt(LayerResNode* node);
    static void placeReset_Col(LayerResNode* node);
    static void placeReset_Pos_Col(LayerResNode* node);
    static void placeReset_Srt_Col(LayerResNode* node);
    static void placeReset_Pos_Srt_Col(LayerResNode* node);
    static void placeFormat_u8(LayerResNode* node, int anim, const unsigned char* data, const unsigned char* frames, unsigned int frame);
    static void placeFormat_u16(LayerResNode* node, int anim, const unsigned char* data, const unsigned char* frames, unsigned int frame);
    static void placeFormat_u32(LayerResNode* node, int anim, const unsigned char* data, const unsigned char* frames, unsigned int frame);
    static void placeAnm_Pos(LayerResNode* node, const unsigned char* data, unsigned int key);
    static void placeAnm_Scl(LayerResNode* node, const unsigned char* data, unsigned int key);
    static void placeAnm_Rot(LayerResNode* node, const unsigned char* data, unsigned int key);
    static void placeAnm_Srt(LayerResNode* node, const unsigned char* data, unsigned int key);
    static void placeAnm_AddCol(LayerResNode* node, const unsigned char* data, unsigned int key);
    static void placeAnm_MulCol(LayerResNode* node, const unsigned char* data, unsigned int key);
    static void placeAnm_AllCol(LayerResNode* node, const unsigned char* data, unsigned int key);
    static void placeAnm_Blend(LayerResNode* node, const unsigned char* data, unsigned int key);

    static PlaceResetFunc s_resCallPlaceReset[8];
    static PlaceFormatFunc s_resCallPlaceFormat[3];
    static PlaceAnimFunc s_resCallPlaceAnim[8];
};

}  // namespace layer

#endif
