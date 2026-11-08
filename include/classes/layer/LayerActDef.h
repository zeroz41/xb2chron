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
// what LayerObjMesh::updateMeshUniformBlock and its s_pCallUniform callbacks read and write (the field names are
// not the original's)
struct LayerArgMdlRenInf {
    // one mesh's entry of LayerObjTopDef's mesh table (0x38 bytes; the type and names are not the original's)
    struct Node {
        LayerResMatrix m_matrix;  // updatePosMatrixUniformBlock's first matrix
        LayerResColor m_color;  // updateMeshUniformBlock combines it with m_color
        unsigned char pad_34[0x2];
        unsigned char m_flags;  // bit 0: the mesh is hidden (updateMeshUniformBlock clears the draw bit)
        unsigned char pad_37[0x1];
    };

    unsigned int* m_dispFlags;  // bit 0 set when the mesh draws
    grlib::CGLibDblUniformBlock* m_uniformBlock;  // m_buff starts at its getBuff()
    const Node* m_node;
    const LayerResMatrix* m_viewMatrix;  // its second
    const LayerResColor* m_color;
    const unsigned char* m_meshInfo;  // [3]: the s_pCallUniform index
    float* m_buff;  // the uniform data being written; each callback steps it past what it writes
};

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
    // updatePartsAction runs each command through it (by the command's first u16)
    static bool (LayerActDef::*s_pCallActCmd[14])(const unsigned char*& cmd);

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
        unsigned char pad_10[0x8];
        // the mesh records LayerObjMesh::updateMeshUniformBlock reads through LayerArgMdlRenInf::m_meshInfo
        // (0x1C bytes each; LayerObjTopDef::updateParams; the type and names are not the original's)
        struct MeshInfo {
            unsigned char m_data[0x1C];
        };
        const MeshInfo* m_meshInfos;  // 0x18
        unsigned char pad_20[0x28];
        // one mesh draw: its m_meshInfos and m_nodes entries (LayerObjTopDef::updateParams; the type and names are
        // not the original's)
        struct Draw {
            unsigned short m_meshIdx;
            unsigned short m_nodeIdx;
        };
        const Draw* m_draws;  // 0x48
        int m_drawNum;  // 0x50
        unsigned char pad_54[0x4];
        const void* m_viewData;  // 0x58: LayerObjTopDef::updateParams copies the LayerRenderView's
        unsigned int* m_dispFlags;  // 0x60: one per draw (LayerArgMdlRenInf::m_dispFlags)
        grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_uniforms;  // 0x68: ~LayerObjTopDef releases it
        const LayerArgMdlRenInf::Node* m_nodes;  // 0x70: one per m_draws node index
        NumberWork* m_number;  // 0x78: LayerObjDraw::draw_call_number draws its instances
        float m_frameEnd;  // 0x80: actcmd_animfrm runs while the frame is below it
        float m_frameStart;  // 0x84
    };
    // what m_frames points to: actcmd_animdef zeroes ResData::m_frameNum of them, actcmd_animfrm sets the first
    // one's m_frame (the type and names are not the original's)
    struct Frame {
        float m_frame;
        int m_frameIdx;  // LayerObjPlace::updateGblFrm: m_frame truncated (the name is not the original's)
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
