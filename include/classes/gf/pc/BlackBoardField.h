#ifndef CLASSES_GF_PC_BLACKBOARDFIELD_H
#define CLASSES_GF_PC_BLACKBOARDFIELD_H

namespace gf { namespace pc {
// table 0x7100B67908
class BlackBoardField {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~BlackBoardField();  // slot 1
};
}}  // namespace gf::pc

#endif
