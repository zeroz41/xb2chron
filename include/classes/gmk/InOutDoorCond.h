#ifndef CLASSES_GMK_INOUTDOORCOND_H
#define CLASSES_GMK_INOUTDOORCOND_H

namespace gmk {
// table 0x7100B6F1E8
// GmkEffect holds one (its gimmick data's bytes 0x1F and 0x20); its table is weak: Vector<GmkEffect>::resize builds it
class InOutDoorCond {
public:
    InOutDoorCond() : pad_8(true), pad_9(true) {}
    // GmkEffect::create assigns a temporary built from its data's bytes 0x1F and 0x20 (the copy's 2-byte store of
    // the two loaded bytes shows the temporary)
    InOutDoorCond(bool first, bool second) : pad_8(first), pad_9(second) {}
    virtual ~InOutDoorCond() {}  // slot 0
    bool pad_8;  // (the names of the flags are not known)
    bool pad_9;
};
}  // namespace gmk

#endif
