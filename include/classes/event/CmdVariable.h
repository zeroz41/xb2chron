#ifndef CLASSES_EVENT_CMDVARIABLE_H
#define CLASSES_EVENT_CMDVARIABLE_H

namespace event {
// table 0x7100B3BF30
class CmdVariable {
public:
    // 1.0.0 has it out of line (0x71000935D0); 3.0.1 inlines it
    CmdVariable() : m_type(0) { m_value.intValue = 0; }
    virtual ~CmdVariable();  // slot 0
    // 1.0.0 0x710009362C; 3.0.1 inlines it
    void setF32(float value) {
        m_type = 2;
        m_value.floatValue = value;
    }
    // 1.0.0 has it out of line; 3.0.1 inlines it
    void setS32(int value) {
        m_type = 1;
        m_value.intValue = value;
    }
    // 1.0.0 0x710009365C; 3.0.1 inlines it
    void setBool(bool value) {
        m_type = 3;
        m_value.boolValue = value;
    }
    // 1.0.0 0x7100093678; 3.0.1 inlines it
    void setStr(const char* value) {
        m_type = 4;
        m_value.strValue = value;
    }
    // stores a pointer (type 5, what getUserdata returns; the name is not the original's)
    void setUserdata(void* value) {
        m_type = 5;
        m_value.userdata = value;
    }
    // the value converted when it holds the other number type (1.0.0 0x710009360C; 3.0.1 inlines it)
    int getS32() const { return m_type == 2 ? (int)m_value.floatValue : m_value.intValue; }
    // the stored pointer (1.0.0 0x71000936A0; 3.0.1 inlines it)
    void* getUserdata() const { return m_value.userdata; }
    // the stored flag (1.0.0 0x7100093670; 3.0.1 inlines it)
    bool getBool() const { return m_value.boolValue; }
    // the stored string (1.0.0 0x7100093688; 3.0.1 inlines it)
    const char* getStr() const { return m_value.strValue; }
    // what the value holds (the field names are not the original's; the layout is CmdParam's: 1.0.0
    // CmdParam::CmdParam zeroes +0x8 and +0x10 of each of its 0x18-byte values)
    int m_type;  // 0x8
    union {
        int intValue;
        float floatValue;
        bool boolValue;
        const char* strValue;
        void* userdata;
    } m_value;  // 0x10
};
}  // namespace event

#endif
