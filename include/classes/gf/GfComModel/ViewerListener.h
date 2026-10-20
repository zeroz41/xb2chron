#ifndef CLASSES_GF_GFCOMMODEL_VIEWERLISTENER_H
#define CLASSES_GF_GFCOMMODEL_VIEWERLISTENER_H

#include "classes/gf/GfComModel.h"

namespace gf {
// table 0x7100B667F0
class GfComModel::ViewerListener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
