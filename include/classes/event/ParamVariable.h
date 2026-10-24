#ifndef CLASSES_EVENT_PARAMVARIABLE_H
#define CLASSES_EVENT_PARAMVARIABLE_H

#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3C018
class ParamVariable {
public:
    ParamVariable() : m_type(0) {
        m_value.intValue = 0;
    }
    virtual ~ParamVariable();  // slot 0

    void setS32(int value);
    void setF32(float value);
    void setBool(bool value);
    void setStr(const char* value);
    void setUserdata(void* value);
    // the value as text ("%d", "%f", "true"/"false", the string, "%lld"); empty for nothing
    void createString(mm::mtl::FixStr<256>& str);

    // what the value holds: setS32 makes it 1, setF32 2, setBool 3, setStr 4, setUserdata 5 (0 for nothing, clear())
    int m_type;
    union {
        int intValue;
        float floatValue;
        bool boolValue;
        const char* strValue;
        void* userdata;
    } m_value;
};
}  // namespace event

#endif
