#ifndef ML_DRRESCHKLIST_H
#define ML_DRRESCHKLIST_H

namespace ml {
// One node of a DrMdoCtlNom pass check list (4 bytes; DrMdoCtlNom::m_chkPool holds them): the part it draws and the
// next node. The field names are not the original's.
class DrResChkList {
public:
    unsigned short m_idx;  // 0x0, into the top header's MdsMdlInfoHeader array
    unsigned short m_next;  // 0x2, 1 + the next node's index in m_chkPool; 0 ends the list
};
}  // namespace ml

#endif
