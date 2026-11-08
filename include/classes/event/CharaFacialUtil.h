#ifndef CLASSES_EVENT_CHARAFACIALUTIL_H
#define CLASSES_EVENT_CHARAFACIALUTIL_H

namespace gf { class GfObj; }

namespace event {
// facial helpers (no table; the symbols name the class and its functions)
class CharaFacialUtil {
public:
    // out of line (0x71000D2048, not written yet); CharaObj::setTar and playAction pass a character's bdat id and
    // its object's kind (UpdatableObject::m_type) and test the result against 3
    static int transferGroup(int, unsigned int);
    // 0x71000D2430: the group of the first character table (CHR_Dr 3, CHR_Bl 4, RSC_NpcList 6) whose id range
    // holds the id, else the given group (transferGroup's fallback)
    static int transferGroupSub(int, unsigned int);
    // 0x71000D1F28: the object's facialSeat text in EVT_assetList (its row from its table's EventAsset column)
    static const char* getFacialBdat(gf::GfObj*);
};
}  // namespace event

#endif
