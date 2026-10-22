#ifndef CLASSES_UI_UIOBJBUILDDATA_H
#define CLASSES_UI_UIOBJBUILDDATA_H

#include "mm/mtl/Vector.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace ui {
// table 0x7100B74708; a layout's objects and their parameters as a "UIB " file holds them (UIBuildInfoUIO reads
// its objects through it). The field names are not the original's
class UIObjBuildData {
public:
    // the file's start (the names are not the original's: deserialize shows what each does)
    struct FileHeader {
        unsigned int m_magic;      // 'UIB '
        unsigned int m_version;    // 2
        unsigned int m_objectNum;
        unsigned int m_objectOffset;  // from the file's start: per object its parameter count, then its parameters
        unsigned int m_stringNum;
        unsigned int m_stringOffset;  // from the file's start: the strings one after another
    };
    // a parameter of an object (the names are not the original's: getObjectParam shows what each does)
    struct Parameter {
        unsigned short m_type;   // its name's index in the parameter names (getParamType's)
        unsigned short m_flags;  // 0: m_value is the value; bit 0: m_value is a string's index; bit 1: the value
        int m_value;
    };
    // an object's parameters
    struct ObjData {
        mm::mtl::Vector<Parameter> m_params;
        unsigned int m_name;  // its "name" parameter's value: its name's index in the strings
    };
    // a parameter's value: getObjectParam writes the number or the string (the names are not the original's)
    union Value {
        int m_int;
        float m_float;
        const char* m_str;
    };
    UIObjBuildData(mm::mtl::IAllocator* allocator);
    virtual ~UIObjBuildData();  // slot 0
    void clear();
    static void initialize();  // hashes the parameter names
    void deserialize(const void* data, unsigned int size);
    unsigned int getObjectNum() const;
    // the value of the parameter name of the object at index (false: no such object or parameter)
    bool getObjectParam(unsigned int index, const char* name, Value& value) const;
    // the parameter name's index in the parameter names, -1 for none (inline: 1.0.0 has it out of line at
    // 0x71006D3CD4, 3.0.1's getObjectParam holds it)
    short getParamType(const char* name) const;

    mm::mtl::Vector<ObjData> m_objects;
    mm::mtl::Vector<const char*> m_strings;  // the file's strings
    mm::mtl::IAllocator* m_allocator;        // the vectors'
};
}  // namespace ui

#endif
