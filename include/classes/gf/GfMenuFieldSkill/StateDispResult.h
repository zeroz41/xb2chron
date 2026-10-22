#ifndef CLASSES_GF_GFMENUFIELDSKILL_STATEDISPRESULT_H
#define CLASSES_GF_GFMENUFIELDSKILL_STATEDISPRESULT_H

#include "classes/ai/State.h"
#include "classes/gf/GfMenuFieldSkill.h"

namespace ai { class State; }

namespace gf {
// table 0x7100B5E6E8
class GfMenuFieldSkill::StateDispResult : public ::ai::State {
public:
    virtual ~StateDispResult();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
