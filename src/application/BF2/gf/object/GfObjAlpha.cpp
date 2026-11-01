#include "gf/GfObjAlpha.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfComponent.h"
#include "math.h"

namespace gf {

void GfObjAlpha::updateCamera(GF_OBJ_HANDLE* handle, float rate, bool force) {
    GfObjAcc acc(handle);
    {
        DataParamAcc param(handle);
        if (param.isNoCameraFade()) {
            acc.setAlphaCamera(1.0f);
            return;
        }
    }
    if (GfObjUtil::getParentObj(acc.getObj()) != nullptr) {
        acc.setAlphaCamera(1.0f);
        return;
    }
    float alpha = acc.getAlphaCamera();
    if (acc.isCameraFadeAllOK()) {
        float step = rate * 0.125f;
        bool near = isNearCamera(acc);
        if (force || !near || acc.isCameraFadeDisableForEvent() || acc.isCameraFadeDisableForBattle()) {
            if (alpha < 1.0f) {
                alpha = fminf(step + alpha, 1.0f);
            }
        } else {
            if (alpha > 0.0f) {
                alpha = fmaxf(alpha - step, 0.0f);
            }
        }
    } else if (alpha <= 1e-6f) {
        alpha = 1.0f;
    }
    acc.setAlphaCamera(alpha);
}

bool GfObjAlpha::isNearCamera(const GfObjAcc& acc) { return acc.isCollideModelClip(); }

mm::mtl::RTTI GfComponent::m_rtti("GfComponent", &fw::ComponentObject::m_rtti, nullptr);

}  // namespace gf
