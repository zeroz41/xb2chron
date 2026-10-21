#ifndef CLASSES_ML_SCNOBJ_H
#define CLASSES_ML_SCNOBJ_H

namespace ml { class DebDraw; }

namespace ml {
// table none (its derived classes')
class ScnObj {
public:
    virtual ~ScnObj();  // slot 0
    virtual void update() {}  // slot 2
    virtual void renderDebug(ml::DebDraw*) {}  // slot 3
    virtual void apply() {}  // slot 4
    virtual void tail() {}  // slot 5
    virtual void getName() const = 0;  // slot 6
    virtual void setDelete();  // slot 7
};
}  // namespace ml

#endif
