#ifndef CLOUD_CLOUDMDLPARTS_H
#define CLOUD_CLOUDMDLPARTS_H

#include "cloud/CloudUniform.h"
#include "mm/Vec3.h"

namespace cloud {

class CloudMdlDataObj;

// one part of a cloud model (0xD0: CloudMdlDataObj::create allocates it), kept in a list (CloudMdlListMan). The
// field names are not the original's.
class CloudMdlParts {
public:
    // inline: CloudMdlDataObj::create builds it in place (the symbols name no out-of-line copy)
    CloudMdlParts() {
        m_pos.x = 0.0f;
        m_pos.y = 0.0f;
        m_pos.z = 0.0f;
        m_scroll.x = 0.0f;
        m_scroll.y = 0.0f;
        m_scroll.z = 0.0f;
        m_detailScroll.x = 0.0f;
        m_detailScroll.y = 0.0f;
        m_detailScroll.z = 0.0f;
        m_sortKey = 0;
        m_param = 0.0f;
        m_dispBit = 0;
        m_pNext = nullptr;
        m_pPrev = nullptr;
    }
    // inline: the lists delete the parts in place (the symbols name no out-of-line copy)
    ~CloudMdlParts() { m_uniform.releaseUniform(); }
    // 0 or 1, read as a 32-bit value (CloudObjMdl::counterRender tests the whole register: not a bool)
    int isDisp() const;
    void bindVertex();
    void render();
    // moves both scrolls along the direction (scaled by the part's speed) and fills the uniform
    void createUniform(const mm::Vec3& dir);

    mm::Vec3 m_pos;                // 0x0, CMLObjData's position
    mm::Vec3 m_scroll;             // 0x10
    mm::Vec3 m_detailScroll;       // 0x20, moves 10 times as fast as m_scroll
    CloudUniform m_uniform;        // 0x30, created as kind 10 (CLOUD_UNIFORM_10)
    CloudMdlDataObj* m_pData;      // 0x68
    unsigned short m_index;        // 0x70, the CMLObjData index in m_pData
    unsigned short m_sortKey;      // 0x72, calcZSort's key
    unsigned short m_dispBit;      // 0x74: when set, the bit of CloudMan's m_pReserved that hides the part
    unsigned char pad_76[0x2];
    float m_param;                 // 0x78, CMLObjData's m_param
    float m_params0[7];            // 0x7C, CMLObjData's m_params0 ([1] scales the scroll speed)
    float m_params1[7];            // 0x98, CMLObjData's m_params1 ([4], [5] scale the scroll's x/z and y)
    int m_scrollType;              // 0xB4: 1 or 2 (CMLObjData's flag bit + 1); 2 wraps the scroll at 256
    unsigned int m_type;           // 0xB8, CMLObjData's m_type
    unsigned char pad_BC[0x4];
    CloudMdlParts* m_pNext;  // 0xC0, CloudObjMdl::counterRender walks the parts through it
    CloudMdlParts* m_pPrev;  // 0xC8
};

}  // namespace cloud

#endif
