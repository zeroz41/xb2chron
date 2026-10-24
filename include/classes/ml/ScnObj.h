#ifndef CLASSES_ML_SCNOBJ_H
#define CLASSES_ML_SCNOBJ_H

namespace ml { class DebDraw; }
namespace ml { class Scn; }

namespace ml {
// table none (its derived classes')
class ScnObj {
public:
    // the scene that owns it and its kind (1 model, 4 light, 6 clip list and environment collision)
    ScnObj(Scn* scn, unsigned short type) : m_scn(scn), m_type(type), m_delete(false) {}
    virtual ~ScnObj() {}  // slot 0 (inline: its derived classes' destructors call none)
    virtual void update() {}  // slot 2
    virtual void renderDebug(ml::DebDraw*) {}  // slot 3
    virtual void apply() {}  // slot 4
    virtual void tail() {}  // slot 5
    virtual const char* getName() const = 0;  // slot 6
    virtual void setDelete();  // slot 7

    Scn* m_scn;  // 0x8 (the name is not the original's)
    unsigned short m_type;  // 0x10 (the name is not the original's)
    bool m_delete;  // setDelete sets it (the name is not the original's)
    unsigned char pad_13[1];
};
}  // namespace ml

#endif
