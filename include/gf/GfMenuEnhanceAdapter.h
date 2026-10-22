#ifndef GF_GFMENUENHANCEADAPTER_H
#define GF_GFMENUENHANCEADAPTER_H

namespace ui {
class UIStr;
}

namespace gf {

// the menus' enhancement texts (application/BF2/gf/menu/adapter/gf_menu_enhance_adapter.cpp); 1.0.0's adapter class
// with its converters and table is gone from 3.0.1, which keeps only this function
class GfMenuEnhanceAdapter {
public:
    // the enhancement's caption (its Caption2 when menu layer 3 is usable and the table has a non-zero one), with
    // the enhancement's id as the text's owner; false when the enhancement or the text is not valid
    static bool getEnhanceCaption(unsigned int enhance, ui::UIStr& text);
};

}  // namespace gf

#endif
