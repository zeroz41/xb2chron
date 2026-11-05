#ifndef CLASSES_EVENT_CHARAFACIALUTIL_H
#define CLASSES_EVENT_CHARAFACIALUTIL_H

namespace event {
// facial helpers (no table; the symbols name the class and its functions)
class CharaFacialUtil {
public:
    // out of line (0x71000D2048, not written yet); CharaObj::setTar and playAction pass a character's bdat id and
    // its object's kind (UpdatableObject::m_type) and test the result against 3
    static int transferGroup(int, unsigned int);
};
}  // namespace event

#endif
