#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62378
class GfMenuObjFieldSkill : public ::gf::GfMenuObject {
public:
    class BaseListener;
    class BladeListener;
    class InputListener;
    class MainListener;
    class ResultListener;
    class SkillInfoListener;
    class TotalListener;
    virtual ~GfMenuObjFieldSkill();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
