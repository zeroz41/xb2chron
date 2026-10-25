#ifndef CLASSES_GF_SCOM_FADE_H
#define CLASSES_GF_SCOM_FADE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
#include "mm/Col4.h"

namespace gf {
// table 0x7100B6A920
class SCOM_FADE : public ::gf::SCOM {
public:
    explicit SCOM_FADE(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // fades the screen in slot (its s_fades entry) to color over frames frames; one request applies every slot's
    // pending fade (its handle stays in s_hCreatedReq until it runs), returns that handle
    static unsigned long create(unsigned int slot, unsigned int frames, const mm::Col4& color);

    // a slot's pending fade: create fills it, exec passes it to GfMenuFade::setFade and clears m_slot to -1
    // (the names are not the original's; the static initializer sets m_slot to -1 only)
    struct Fade {
        Fade() : m_slot(-1) {}
        unsigned int m_slot;
        unsigned int m_frames;
        mm::Col4 m_color;
    };
    static Fade s_fades[3];
    static unsigned long s_hCreatedReq;  // the queued request's handle, -1 for none
};
}  // namespace gf

#endif
