#ifndef CLASSES_GF_SCOM_OBJ_ALPHA_H
#define CLASSES_GF_SCOM_OBJ_ALPHA_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B6A950
class SCOM_OBJ_ALPHA : public ::gf::SCOM {
public:
    // 1.0.0 has it out of line as SCOM_OBJ_ALPHA(GF_SCOM_HANDLE*, GF_OBJ_HANDLE*, float, float); 3.0.1 inlines it
    SCOM_OBJ_ALPHA(unsigned long handle, GF_OBJ_HANDLE* obj, float time, float alpha)
        : SCOM(SCOM_TYPE(40), handle), m_obj(obj), m_time(time), m_elapsed(0.0f), m_alpha(alpha), m_startAlpha(-1.0f),
          m_isPauseStop(false) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // requests an alpha change of the object behind handle over time to alpha
    static unsigned long create(gf::GF_OBJ_HANDLE* handle, float time, float alpha);
    // the same for each object mounted on handle (GfMountManager::getAppendHandles, attach 0)
    static void createWeapon(gf::GF_OBJ_HANDLE* handle, float time, float alpha);
    // 2.0.0's symbols name it. What it does: create's request with m_isPauseStop set (the request waits while
    // GfPause::isPause(0x80)).
    static unsigned long createEventPause(gf::GF_OBJ_HANDLE* handle, float time, float alpha);

    // the names below are not the original's
    GF_OBJ_HANDLE* m_obj;
    float m_time;        // the fade's length
    float m_elapsed;
    float m_alpha;       // the alpha to reach
    float m_startAlpha;  // the object's alpha when the fade starts (read on the first exec while negative)
    bool m_isPauseStop;  // the request waits while GfPause::isPause(0x80)
};
}  // namespace gf

#endif
