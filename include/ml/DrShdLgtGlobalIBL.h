#ifndef ML_DRSHDLGTGLOBALIBL_H
#define ML_DRSHDLGTGLOBALIBL_H

#include "classes/mm/mtl/List.h"
#include "mm/Mat44.h"
#include "mm/mtl/FixedVector.h"

namespace grlib { class CGLibDblUniformBlock; }
namespace mm { class Vec3; }
namespace mm { class Vec4; }

namespace ml {
class DrLightObjGlobalIBL;
class DrMan;
class DrShdLgtMan;
class DrShdLgtObj;

namespace _dr_shd_lgt_glb_ibl {
// orders lights by DrLightObjGlobalIBL::getPriority, the higher first
bool CompareByPriority(const DrLightObjGlobalIBL* a, const DrLightObjGlobalIBL* b);
}  // namespace _dr_shd_lgt_glb_ibl

// The global IBL light (DrShdLgtMan::m_pGlobalIBL): one ViewInfo per view (the field names are not the original\x27s).
class DrShdLgtGlobalIBL {
public:
    struct SlotCandidate;

    // one of a view\x27s 32 IBL slots (0x18 bytes; the type and field names are not the original\x27s)
    struct Slot {
        int m_index;  // 0x0, the constructor numbers the slots 0..31
        // 0x4, three request states (DrRequetIBL::m_pState: requestIBL sets 1, cancelIBL 3), by m_frame
        unsigned char m_state[3];
        unsigned char pad_7[0x1];
        unsigned int m_frame;  // 0x8, removeObj reads m_state[(m_frame + 2) % 3]
        unsigned char pad_c[0x4];
        DrLightObjGlobalIBL* m_obj;  // 0x10, the light the slot holds

        Slot() : m_state(), m_frame(0), m_obj(nullptr) {}
    };
    // a view\x27s state, 0x2060 bytes (delViewInfo names it; the type and field names are not the original\x27s)
    struct ViewInfo {
        mm::mtl::List<DrLightObjGlobalIBL*> m_objList;  // 0x0, addObj/removeObj
        Slot m_slot[32];  // 0x40
        // 0x340, the constructor zeroes them; updateUniformBlockImpl transposes them into the uniform buffer
        mm::Mat44 m_mtx[0x60];
        // 0x1B40, the lights renderIndexTable gives a slot each (findSlotByPosition searches them)
        mm::mtl::FixedVector<DrLightObjGlobalIBL*, 128> m_lights;
        int m_indexTable[64];  // 0x1F48, by m_lights index: the slot renderIndexTable picks (-1 none)
        grlib::CGLibDblUniformBlock* m_uniformBlock;  // 0x2048, the constructor makes it
        bool m_resetColorBuff;  // 0x2050, resetColorBuff sets it
        unsigned char pad_2051[0xF];
    };

    DrShdLgtGlobalIBL(DrMan* drMan);
    ~DrShdLgtGlobalIBL();
    void update(int viewIdx);
    void updateView(int viewIdx);
    void addObj(DrLightObjGlobalIBL* obj, int viewIdx);
    void removeObj(DrLightObjGlobalIBL* obj, int viewIdx);
    void render(DrShdLgtMan* lgtMan);
    void renderIndexTable();
    // the return type is not proven (no caller or body read yet)
    bool findSlotByPosition(const mm::Vec3& pos, unsigned int& slot, float* weight, mm::Mat44& mtx, mm::Vec3& ofs) const;
    bool isEnable() const;
    void delViewInfo(int viewIdx);
    void resetColorBuff(int viewIdx);
    void renderLinkList(DrShdLgtMan* lgtMan);
    void renderByLinkList(DrShdLgtMan* lgtMan);
    void setShaderGlobalIBLListFadeParameter(DrShdLgtObj* obj, unsigned int index, const mm::Mat44& mtx,
                                             const mm::Vec4& a, const mm::Vec4& b,
                                             grlib::CGLibDblUniformBlock& block, unsigned int offset);
    void updateUniformBlockImpl(int viewIdx);
    void updateUniformBlock(int viewIdx);

    DrMan* m_drMan;  // 0x0
    unsigned char pad_8[0x8];
    ViewInfo m_view[4];  // 0x10
};
}  // namespace ml

#endif
