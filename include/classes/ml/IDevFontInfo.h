#ifndef CLASSES_ML_IDEVFONTINFO_H
#define CLASSES_ML_IDEVFONTINFO_H

namespace ml {
// an entry of DevFont's list (the class name is the original's, from reslist<IDevFontInfo*>'s symbols). The module
// has no table and no override of it, so no slot has a name: DevFont::wkUpdate calls slot 7 on each entry, then
// deletes (slot 1) the first whose slot 10 answers true; the other slots are only placeholders keeping the order
class IDevFontInfo {
public:
    virtual ~IDevFontInfo() {}  // slot 0
    virtual void fn_slot2() = 0;  // slot 2
    virtual void fn_slot3() = 0;  // slot 3
    virtual void fn_slot4() = 0;  // slot 4
    virtual void fn_slot5() = 0;  // slot 5
    virtual void fn_slot6() = 0;  // slot 6
    virtual void fn_slot7() = 0;  // slot 7 DevFont::wkUpdate calls it on every entry (an update, inferred)
    virtual void fn_slot8() = 0;  // slot 8
    virtual void fn_slot9() = 0;  // slot 9
    virtual bool fn_slot10() = 0;  // slot 10 true: DevFont::wkUpdate deletes the entry (a finished test, inferred)
};
}  // namespace ml

#endif
