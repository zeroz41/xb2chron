#ifndef CLASSES_GF_GFASSETMANAGER_H
#define CLASSES_GF_GFASSETMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace gf {
// a base of gf::GfAssetManager no evidence names yet
class TUnk_B43558 {
public:
    virtual ~TUnk_B43558();
};
// table 0x7100B43558; base at 0x0 unknown (TUnk_B43558)
class GfAssetManager : public TUnk_B43558, public ::ml::IWorkEvent {
public:
    virtual ~GfAssetManager();  // slot 0
};
}  // namespace gf

#endif
