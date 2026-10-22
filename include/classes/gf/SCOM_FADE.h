#ifndef CLASSES_GF_SCOM_FADE_H
#define CLASSES_GF_SCOM_FADE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace mm { struct Col4; }

namespace gf {
// table 0x7100B6A920
class SCOM_FADE : public ::gf::SCOM {
public:
    virtual ~SCOM_FADE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
    // fades the screen in slot (its s_fades entry) to color over frames frames
    static void create(unsigned int slot, unsigned int frames, const mm::Col4& color);
};
}  // namespace gf

#endif
