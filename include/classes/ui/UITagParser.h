#ifndef CLASSES_UI_UITAGPARSER_H
#define CLASSES_UI_UITAGPARSER_H

#include "classes/layer/LayerTagStr.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace layer { class LayerTagTbl; }
namespace mm { namespace mtl { class IAllocator; }}
namespace ui { class UITagConv; }
namespace ui { class UITagParser; }

namespace ui {
// table 0x7100B754A0; its base at 0x18 is its PtrSingleton (the destructor installs that table, 0x7100B75518, and
// clears its s_instance). It parses a text's tags into its stock buffer, each tag through the converter of its name;
// the field names are not the original's
class UITagParser : public ::layer::LayerTagStr, public ::mm::mtl::PtrSingleton< ::ui::UITagParser> {
public:
    // what calcParseString's callTagStart does with a tag
    enum Mode {
        MODE_CONVERT,  // parse: through its converter
        MODE_PARAM,    // parseTagParam: m_result takes m_param's value of the tag m_tag
        MODE_TAG,      // parseTag: m_result takes the tag's name when it is m_tag
    };
    UITagParser(mm::mtl::IAllocator* allocator);
    virtual ~UITagParser();  // slot 0
    virtual bool callTagStart(char const*, layer::LayerTagTbl const*, unsigned int);  // slot 6
    virtual bool callTagEnd(char const*);  // slot 7
    void releaseConverter();  // deletes every converter
    void registConverter(UITagConv* conv);  // one more converter (none of a name it has, at most 16)
    void parse(const char* text);
    const char* getResult();  // the text parse made
    // the value of the parameter param of the tag in text (null: none)
    const char* parseTagParam(const char* text, const char* tag, const char* param);
    bool parseTag(const char* text, const char* tag);  // whether the text carries the tag

    mm::mtl::IAllocator* m_allocator;  // the stock buffer's
    char* m_buffer;                    // the stock buffer (0x400 bytes)
    mm::mtl::FixedVector<UITagConv*, 16> m_converters;
    // the owner id of the text it parses (UITextObject::setText gives it the text's UIStr::m_ownerId; the name is
    // not the original's)
    unsigned short m_ownerId;
    unsigned short m_mode;  // Mode
    const char* m_tag;
    const char* m_param;
    mm::mtl::FixStr<0x80> m_result;
};
}  // namespace ui

#endif
