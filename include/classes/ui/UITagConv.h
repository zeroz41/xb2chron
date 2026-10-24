#ifndef CLASSES_UI_UITAGCONV_H
#define CLASSES_UI_UITAGCONV_H

namespace mm { namespace mtl { template <typename, typename> class MapPair; }}
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace ui {
// table none (its derived classes')
class UITagConv {
public:
    virtual ~UITagConv() {}  // slot 0
    // the tag's name (UITagParser::callTagStart and callTagEnd compare it with the tag's)
    virtual const char* getTagName() = 0;  // slot 2
    // the text the tag starts (null: none), from its parameters and the text's owner id
    virtual const char* convBegin(mm::mtl::FixedVector<mm::mtl::MapPair<char const*, char const*>, 8ul> const&, unsigned short) = 0;  // slot 3
    virtual const char* convEnd() { return nullptr; }  // slot 4: the text the tag ends with (null: none)
};
}  // namespace ui

#endif
