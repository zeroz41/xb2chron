#ifndef ML_DRPIXLSHADOWMAN_H
#define ML_DRPIXLSHADOWMAN_H

namespace mm { class Vec3; }
namespace ml { class DrMan; }
namespace ml { class DrPixlShadowObj; }
namespace ml { class DrPixlShadowObjDir; }

namespace ml {
// DrPixlObjTbl::m_shadowMan. Only what the light objects call is declared.
class DrPixlShadowMan {
public:
    void releaseShadow(DrPixlShadowObj* obj);
    bool setAddObjPos(mm::Vec3 const& pos, float radius);
    // forwards to every active object's setSptCalcPos; true when any of them returned true
    bool setSptCalcPos(mm::Vec3 const& pos, float radius);
    // false without a directional shadow; else (unless skipView) the sphere's line along the shadow direction must
    // cross the view, then the shadow's type clip and its plane must hold the sphere
    bool clipDirShadowChk(mm::Vec3 const& pos, float radius, bool skipView);

    DrPixlShadowObj* m_objs[0x1120];  // 0x0 (the name is not the original's)
    int m_objNum;  // 0x8900 (the name is not the original's)
    unsigned char pad_8904[0x4];
    DrMan* m_drMan;  // 0x8908 (the name is not the original's)
    unsigned char pad_8910[0x8];
    // 0x8918: setAddObjPos forwards to it when the post parameters allow (the name is not the original's)
    DrPixlShadowObjDir* m_dirShadow;
};
}  // namespace ml

#endif
