#ifndef ML_DRPIXLSHADOWMAN_H
#define ML_DRPIXLSHADOWMAN_H

#include "grlib/CGLibRenderTarget.h"

namespace mm { class Vec3; }
namespace ml { class DrMan; }
namespace ml { class DrPixlShadowObj; }
namespace ml { class DrPixlShadowObjDir; }

namespace ml {
// DrPixlObjTbl::m_shadowMan. Only what the light objects call is declared.
class DrPixlShadowMan {
public:
    // one of the 16 pooled shadow depth targets (DrPixlShadowObj::m_depthTarget); the type and field names are not
    // the original's (releaseTexWork releases each one in use)
    struct TexWork : public grlib::CGLibDepthTarget {
        float m_size;  // 0x800, createSptShadow reuses a spot work of the same size
        int m_useCount;  // 0x804, releaseShadow releases the target when it drops to 0
        short m_type;  // 0x808, createSptShadow sets 2
        short m_index;  // 0x80A, createSptShadow's int argument
        unsigned char pad_80C[0x4];
    };

    ~DrPixlShadowMan();
    void releaseTexWork();
    void releaseShadow(DrPixlShadowObj* obj);
    void shadowRender();
    bool setAddObjPos(mm::Vec3 const& pos, float radius);
    // forwards to every active object's setSptCalcPos; true when any of them returned true
    bool setSptCalcPos(mm::Vec3 const& pos, float radius);
    // false without a directional shadow; else (unless skipView) the sphere's line along the shadow direction must
    // cross the view, then the shadow's type clip and its plane must hold the sphere
    bool clipDirShadowChk(mm::Vec3 const& pos, float radius, bool skipView);

    DrPixlShadowObj* m_objs[0x100];  // 0x0 (the name is not the original's)
    TexWork m_texWork[16];  // 0x800
    int m_objNum;  // 0x8900 (the name is not the original's)
    unsigned char pad_8904[0x4];
    DrMan* m_drMan;  // 0x8908 (the name is not the original's)
    unsigned char pad_8910[0x8];
    // 0x8918: setAddObjPos forwards to it when the post parameters allow (the name is not the original's)
    DrPixlShadowObjDir* m_dirShadow;
};
}  // namespace ml

#endif
