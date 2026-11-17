#ifndef CLASSES_GF_SCOM_CREATE_PARTY_OBJ_H
#define CLASSES_GF_SCOM_CREATE_PARTY_OBJ_H

#include "classes/gf/SCOM.h"
#include "gf/GfReqParam.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B2A0
class SCOM_CREATE_PARTY_OBJ : public ::gf::SCOM {
public:
    // slot 0: implicit (the table's slot 0 is SCOM's destructor; exec is the key function and brings the D0)
    explicit SCOM_CREATE_PARTY_OBJ(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // each queues a type-22 request creating the party's objects and returns its handle. The map is the current map
    // jump's; the float goes to m_info.pad_C (GfGameUnit::createParty's PartyLeaderInfo::pad_0)
    static unsigned long create(float value);
    // the members at their saved positions (m_info.m_flags.m_fromSaveData)
    static unsigned long createSavePos(float value);
    // the members at posInfo's positions
    static unsigned long createPos(const GfPartyPosInfo& posInfo, float value);
    // for a map jump (a copy of info)
    static unsigned long create(const GfMapjumpInfo& info);

    // the name is not the original's
    GfMapjumpInfo m_info;
};
}  // namespace gf

#endif
