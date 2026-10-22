#ifndef CLASSES_UI_UITAGPARSER_H
#define CLASSES_UI_UITAGPARSER_H

#include "classes/layer/LayerTagStr.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace layer { class LayerTagTbl; }
namespace ui { class UITagParser; }

namespace ui {
// table 0x7100B754A0; its base at 0x18 is its PtrSingleton (the destructor installs that table, 0x7100B75518, and
// clears its s_instance)
class UITagParser : public ::layer::LayerTagStr, public ::mm::mtl::PtrSingleton< ::ui::UITagParser> {
public:
    virtual ~UITagParser();  // slot 0
    virtual void callTagStart(char const*, layer::LayerTagTbl const*, unsigned int);  // slot 6
    virtual void callTagEnd(char const*);  // slot 7
    bool parseTag(const char* text, const char* tag);  // whether the text carries the tag
};
}  // namespace ui

#endif
