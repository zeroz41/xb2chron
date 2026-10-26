#ifndef GF_PARAMOBJ_H
#define GF_PARAMOBJ_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// what a voice or a parameter is about: an object, or (with no object, m_handle == -1) a kind and an ID.
// DataParamAcc(ParamObj const&) calls setupObjHandle(m_handle) unless m_handle is -1, else setupObjId(m_type, m_id);
// SCOM_FIELD_VOICE's create functions build both forms in place. The member names are not the original's.
struct ParamObj {
    ParamObj(GF_OBJ_HANDLE* handle) : m_handle(handle), m_type(0), m_id(0) {}
    ParamObj(unsigned int type, unsigned int id)
        : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_type(type), m_id(id) {}
    // the same object, or with no object the same kind and ID (GfGameVoice::isPlayVoice and playVoice compare
    // their slots' objects so; the operator is inferred)
    bool operator==(const ParamObj& other) const {
        if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            return m_type == other.m_type && m_id == other.m_id;
        }
        return m_handle == other.m_handle;
    }

    GF_OBJ_HANDLE* m_handle;
    unsigned int m_type;
    unsigned int m_id;
};
}  // namespace gf

#endif
