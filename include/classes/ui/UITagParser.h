#ifndef CLASSES_UI_UITAGPARSER_H
#define CLASSES_UI_UITAGPARSER_H

#include "classes/layer/LayerTagStr.h"

namespace layer { class LayerTagTbl; }

namespace ui {
// a base of ui::UITagParser no evidence names yet
class TUnk_B754F8 {
public:
    virtual ~TUnk_B754F8();
};
// table 0x7100B754A0; base at 0x18 unknown (TUnk_B754F8)
class UITagParser : public ::layer::LayerTagStr, public TUnk_B754F8 {
public:
    virtual ~UITagParser();  // slot 0
    virtual void callTagStart(char const*, layer::LayerTagTbl const*, unsigned int);  // slot 6
    virtual void callTagEnd(char const*);  // slot 7
};
}  // namespace ui

#endif
