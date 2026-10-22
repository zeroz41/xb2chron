#ifndef CLASSES_UI_UICOLORLIBRARY_H
#define CLASSES_UI_UICOLORLIBRARY_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Col4.h"
#include "mm/mtl/Vector.h"

namespace ui { class UIColorLibrary; }

namespace ui {
// table 0x7100B755F8; the colours the UI names, found by the CRC of their name
class UIColorLibrary : public ::mm::mtl::PtrSingleton< ::ui::UIColorLibrary> {
public:
    // one named colour (Vector<ColorInfo>::expand's element)
    struct ColorInfo {
        unsigned int m_hash;  // mm::mtl::hashStrCrc of the name add was given
        mm::Col4 m_color;
    };

    UIColorLibrary();
    virtual ~UIColorLibrary();  // slot 0
    // 1.0.0's UIColorLibrary::reset(): 3.0.1 keeps only the copy the destructor inlines
    void reset() {
        m_colors.clear();
        if (m_colors.capacity() != 0) {
            m_colors.destroy();
        }
    }
    bool add(const char* name, const mm::Col4& color);  // replaces the colour of a name it has
    bool find(const char* name, mm::Col4& color);  // the colour the library names; false (and white) when it has none

    mm::mtl::Vector<ColorInfo> m_colors;
};
}  // namespace ui

#endif
