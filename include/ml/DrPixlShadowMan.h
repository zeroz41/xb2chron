#ifndef ML_DRPIXLSHADOWMAN_H
#define ML_DRPIXLSHADOWMAN_H

namespace ml { class DrPixlShadowObj; }

namespace ml {
// DrPixlObjTbl::m_shadowMan. Only what the light objects call is declared.
class DrPixlShadowMan {
public:
    void releaseShadow(DrPixlShadowObj* obj);
};
}  // namespace ml

#endif
