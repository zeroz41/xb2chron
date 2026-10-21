#ifndef CLASSES_UI_UITAGCONV_H
#define CLASSES_UI_UITAGCONV_H

namespace mm { namespace mtl { template <typename, typename> class MapPair; }}
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace ui {
// table none (its derived classes')
class UITagConv {
public:
    virtual ~UITagConv() {}  // slot 0
    virtual void getTagName() = 0;  // slot 2
    virtual void convBegin(mm::mtl::FixedVector<mm::mtl::MapPair<char const*, char const*>, 8ul> const&, unsigned short) = 0;  // slot 3
    virtual void convEnd();  // slot 4
};
}  // namespace ui

#endif
