#ifndef CLASSES_GF_SCOM_H
#define CLASSES_GF_SCOM_H

#include "classes/gf/GfReqSmallCom.h"

namespace fw { class UpdateInfo; }

namespace gf {
// what a request is: GfReqSmallCom::isExistCommand(SCOM_TYPE) compares it with m_type; the values are the ones
// the create functions pass
enum SCOM_TYPE : int {};

// table 0x7100B6A8E8
class SCOM {
public:
    // inline: every create function builds its request in place (the handle comes from GfReqSmallCom's counter)
    explicit SCOM(SCOM_TYPE type, unsigned long handle = GfReqSmallCom::sys()->newHandle())
        : m_handle(handle), m_state(1), m_count(0), m_type(type) {}
    virtual ~SCOM() { m_handle = -1; }  // slot 0
    // true once the request is done
    virtual bool exec(fw::UpdateInfo const&) = 0;  // slot 2
    virtual unsigned long getObjHandle() const { return -1; }  // slot 3

    unsigned long m_handle;  // the request's ID: the create functions return it
    // the names below are not the original's: the constructor sets them, isValid/isExistCommand read 0x12
    unsigned short m_state;
    unsigned char pad_12[0x2];
    int m_count;
    SCOM_TYPE m_type;
};

// inline: the create functions queue their request in place, then return its handle
inline unsigned long GfReqSmallCom::addRequest(SCOM* request) {
    sys()->m_list.push_back(request);
    return request->m_handle;
}
}  // namespace gf

#endif
