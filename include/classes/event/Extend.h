#ifndef CLASSES_EVENT_EXTEND_H
#define CLASSES_EVENT_EXTEND_H

#include "mm/mtl/FixStr.h"

namespace event {
// builds file paths: a name with an extension appended, a path's directory or file part
// table 0x7100B3FC68
class Extend {
public:
    // inline and empty: the table's slot 0 holds the identical-code-folded NoncopyableBase destructor, and
    // Singleton<Extend>::getPtr (evt_setup's evpa) registers no destructor (an empty one is dropped)
    virtual ~Extend() {}  // slot 0

    // the name with the extension the function is named after appended (".wav" appends ".nop")
    const char* mdo(const char* pszName);
    const char* arc(const char* pszName);
    const char* anm(const char* pszName);
    const char* eva(const char* pszName);
    // 1.0.0's Extend::effeva (0x71000901DC): the name with "_eff.eva" appended; 3.0.1 inlines it
    const char* effeva(const char* pszName);
    // 2.0.0's Extend::pack_efb: the name with "_pack.wiefb" appended; 3.0.1 inlines it (EffectRes's constructor)
    const char* pack_efb(const char* pszName);
    const char* lgt(const char* pszName);
    const char* wav(const char* pszName);
    const char* evpa(const char* pszName);
    const char* webm(const char* pszName);
    // the text before the last '\\' (else '/'), in a static buffer; the path itself when it has neither
    const char* dirname(const char* pszPath);
    // the text after the last '\\' (else '/'); the path itself when it has neither
    const char* filename(const char* pszPath);
    // 1.0.0's Extend::replaceString (0x7100090C30): the string with every occurrence of the second one replaced by
    // the third, in a static buffer; 3.0.1 inlines it (CharaPlayEvaEff::update, CamMotion::play)
    const char* replaceString(const char* str, const char* from, const char* to);

private:
    // the path the extension functions build and return; the name is not the original's
    mm::mtl::FixStr<256> m_path;  // 0x8
};
}  // namespace event

#endif
