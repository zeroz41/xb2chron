#ifndef CLASSES_ML_SCNOBJ_H
#define CLASSES_ML_SCNOBJ_H

namespace ml { class DebDraw; }

namespace ml {
// table none (its derived classes')
class ScnObj {
public:
    virtual ~ScnObj() {}  // slot 0 (inline: its derived classes' destructors call none)
    virtual void update() {}  // slot 2
    virtual void renderDebug(ml::DebDraw*) {}  // slot 3
    virtual void apply() {}  // slot 4
    virtual void tail() {}  // slot 5
    virtual void getName() const = 0;  // slot 6
    virtual void setDelete();  // slot 7

    unsigned char pad_8[0xA];
    bool m_delete;  // setDelete sets it (the name is not the original's)
    unsigned char pad_13[1];
};
}  // namespace ml

#endif
