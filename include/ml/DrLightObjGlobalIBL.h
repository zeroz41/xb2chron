#ifndef ML_DRLIGHTOBJGLOBALIBL_H
#define ML_DRLIGHTOBJGLOBALIBL_H

#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibPixlCounter.h"
#include "grlib/CGLibTextureBuffer.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxVertex.h"
#include "mm/mtl/Vector.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"

namespace ml {
class DrResUseQueryObj;

// A global IBL light (DrGlobalIBLPack::resourceInit makes them). Only what DrRequetIBL's getters read is declared;
// the field names follow those getters (DrRequetIBL::getVersion, getTextureNum, getTexture, getAdditionalAmbient,
// getSkyIntensity, getDirLightIntensity, getSHMatrix) and are not the original's.
class DrLightObjGlobalIBL {
public:
    // One mesh of the light (0x1E0 bytes; the copy constructor's member copies give the layout). The field names are
    // not the original's.
    struct MeshData {
        grlib::CGLibVtxVertex m_vertex;  // 0x0, bindVertex binds it
        grlib::CGLibVtxIndex m_index;  // 0x28, drawVertex draws it
        unsigned char pad_50[0xC0];
        DrResUseQueryObj* m_query;  // 0x110, begin/endOccQuery
        unsigned char pad_118[0x38];
        grlib::CGLibDblUniformBlock m_uniform[2];  // 0x150
        grlib::CGLibPixlCounter m_pixlCounter;  // 0x1C0
        unsigned char pad_1d8[0x8];
    };

    DrLightObjGlobalIBL();
    ~DrLightObjGlobalIBL();
    unsigned int getPriority() const;
    bool isInRange(const mm::Vec3& pos) const;
    float calcSimilarity(const DrLightObjGlobalIBL& other) const;
    // binds mesh index's vertices (the mesh drawVertex and the occlusion query use)
    void bindVertex(unsigned int index);
    void drawVertex();
    void beginOccQuery();
    void endOccQuery();

    void* pad_0;
    unsigned int m_version;  // 0x8
    unsigned int m_priority;  // 0xC, getPriority (the name follows it)
    unsigned int pad_10;
    unsigned int m_textureNum;  // 0x14
    unsigned int pad_18;
    unsigned char pad_1c[0x4];
    mm::mtl::Vector<MeshData> m_meshes;  // 0x20 (the name is not the original's)
    unsigned int pad_48;
    unsigned char pad_4c[0x4];
    mm::Vec3 pad_50;
    mm::Vec3 pad_60;
    unsigned int m_bindIndex;  // 0x70, bindVertex's mesh (the name is not the original's)
    unsigned char pad_74[0x4];
    grlib::CGLibTextureBuffer m_texture[7];  // 0x78, the constructor builds seven
    unsigned char pad_388[0x8];
    mm::Vec3 m_position;  // 0x390, DrShdLgtGlobalIBL::updateUniformBlockImpl stores it with w = 1 (name inferred)
    mm::Vec3 m_additionalAmbient;  // 0x3A0
    float m_skyIntensity;  // 0x3B0
    float m_dirLightIntensity;  // 0x3B4
    unsigned long pad_3b8;
    unsigned int pad_3c0;
    bool pad_3c4;
    unsigned char pad_3c5[0xB];
    mm::Mat44 m_mtx;  // 0x3D0, DrShdLgtGlobalIBL::updateUniformBlockImpl transposes it per slot (name inferred)
    mm::Vec4 pad_410[4];
    unsigned char pad_450[0x3F0];
    mm::Mat44 m_shMatrix[4];  // 0x840, by index * 4 + term (getSHMatrix); the bound is not proven
};
}  // namespace ml

#endif
