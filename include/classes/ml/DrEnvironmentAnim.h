#ifndef CLASSES_ML_DRENVIRONMENTANIM_H
#define CLASSES_ML_DRENVIRONMENTANIM_H

namespace ml { class LgtAnimInf; }

namespace ml {
// table none (its derived classes')
class DrEnvironmentAnim {
public:
    virtual ~DrEnvironmentAnim();  // slot 0
    virtual void envlgt_amb_color_R(ml::LgtAnimInf const*, float);  // slot 2
};
}  // namespace ml

#endif
