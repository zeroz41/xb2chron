#ifndef CLASSES_GF_SCOM_DESTROY_GAME_OBJ_H
#define CLASSES_GF_SCOM_DESTROY_GAME_OBJ_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B270
class SCOM_DESTROY_GAME_OBJ : public ::gf::SCOM {
public:
    virtual ~SCOM_DESTROY_GAME_OBJ();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
