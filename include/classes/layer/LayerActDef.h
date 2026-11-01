#ifndef CLASSES_LAYER_LAYERACTDEF_H
#define CLASSES_LAYER_LAYERACTDEF_H

#include "classes/layer/LayerObjWork.h"

namespace layer { class LyrActionData; }
namespace layer { class LayerVertexObj; }
namespace grlib { class CGLibTextureBuffer; }
namespace grlib { class CGLibVtxInstans; }
namespace grlib { class CGLibDblUniformBlock; }
namespace grlib { template <class T> class CGLibUniformArray; }
namespace layer { class LayerTextureObj; }

namespace layer {
// table none in 3.0.1 (its derived classes'). 1.0.0's LayerActDef() calls LayerObjWork's C2 constructor and its
// table (0x71011B7980) is LayerObjWork's but for slot 1 (its own destructor) and slot 10 (updatePartsAction).
class LayerActDef : public ::layer::LayerObjWork {
public:
    virtual ~LayerActDef() {}  // slot 0: inline (no table in 3.0.1; ~LayerObjTopDef inlines it)
    virtual void updatePartsAction(layer::LyrActionData const*);  // slot 10
    // the action commands s_pCallActCmd adds to LayerActBase's (each reads its command at cmd, steps cmd past it
    // and returns whether the action waits)
    bool actcmd_iconnum(const unsigned char*& cmd);
    bool actcmd_animicon(const unsigned char*& cmd);
    bool actcmd_animfrm(const unsigned char*& cmd);
    bool actcmd_animdef(const unsigned char*& cmd);

    // The field names follow LayerAccDefObj's accessors (its objects of type 1; not the original's). They are
    // LayerActDef's: actcmd_iconnum and actcmd_animicon write m_iconNum (LayerObjMesh and LayerObjTopDef add none).
    unsigned char pad_258[0x18];
    LayerVertexObj* m_vertexObj;  // 0x270: LayerObjTopDef::resourceInit creates it from the resource (the name is not the original's)
    LayerTextureObj* m_textureObj;  // 0x278: workIconCreate creates it from the resource (the name is not the original's)
    grlib::CGLibTextureBuffer** m_textures;  // 0x280: the LayerObjDraw texture draws index it (the name is not the original's)
    int m_textureNum;  // 0x288: m_textureObj's texture count (the name is not the original's)
    unsigned char pad_28C[0x4];
    void* m_work;  // 0x290: the block workIconCreate allocates; ~LayerObjTopDef frees it (the name is not the original's)
    // which of m_textures each draw uses (the type and field names are not the original's)
    struct TexRef {
        unsigned short pad_0;
        unsigned short m_texIdx;
        unsigned short pad_4;
    };
    // the animation m_texRefs plays: actcmd_animdef sets its end frame from m_frameNum, actcmd_animfrm steps it by
    // m_frameRate a second (the type and field names are not the original's)
    struct AnimInfo {
        unsigned char pad_0[0x18];
        unsigned int m_frameNum;  // 0x18
        float m_frameRate;  // 0x1C
    };
    // the per-instance vertices of a number draw (the type and field names are not the original's)
    struct NumberWork {
        grlib::CGLibVtxInstans* m_instans;  // 0x0
        unsigned int m_num;  // 0x8: the instances to draw
    };
    struct TexRefList {
        const AnimInfo* m_anim;  // 0x0
        const TexRef* m_refs;  // a LyrDrawData's m_texNum entries from its m_texIdx
        unsigned char pad_10[0x58];
        grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_uniforms;  // 0x68: ~LayerObjTopDef releases it
        unsigned char pad_70[0x8];
        NumberWork* m_number;  // 0x78: LayerObjDraw::draw_call_number draws its instances
        float m_frameEnd;  // 0x80: actcmd_animfrm runs while the frame is below it
        float m_frameStart;  // 0x84
    };
    // what m_frames points to: actcmd_animdef zeroes ResData::m_frameNum of them, actcmd_animfrm sets the first
    // one's m_frame (the type and names are not the original's)
    struct Frame {
        float m_frame;
        float pad_4;
    };
    // the head of its resource (m_resData; the type and field names are not the original's)
    struct ResData {
        unsigned char pad_0[0x10];
        unsigned int m_vertexOfs;  // 0x10: its vertex data, from the head (0: none); LayerObjTopDef::resourceInit
        unsigned char pad_14[0x14];
        int m_frameNum;  // 0x28: m_frames' count
        unsigned int m_iconOfs;  // 0x2C: its IconData, from the head
    };
    // the icons of a resource (LayerObjMesh::call_uniform_icon; the types and field names are not the original's)
    struct IconInfo {
        float m_pos[2];  // 0x0
        float m_uv[4];  // 0x8
        unsigned char pad_18[0x4];
    };
    struct IconData {
        unsigned char pad_0[0x18];
        unsigned int m_infoOfs;  // 0x18: its IconInfo table, from IconData
    };
    TexRefList* m_texRefs;  // 0x298 (the name is not the original's)
    float m_param;  // setParm
    unsigned short m_iconNum;  // setIconNum / getIconNum
    unsigned short m_iconMax;  // getIconMax
    unsigned short m_gauge;  // setGauge / getGauge (a LAYER_GAUGE)
    unsigned char pad_2AA[0x6];
    Frame* m_frames;  // 0x2B0 (the name is not the original's)
    float m_frameTime;  // 0x2B8: actcmd_animdef zeroes it (the name is not the original's)
    unsigned char pad_2BC[0x4];
};
}  // namespace layer

#endif
