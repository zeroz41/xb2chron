#ifndef CLASSES_GF_TUNK_B5A648_ICONVERTER_H
#define CLASSES_GF_TUNK_B5A648_ICONVERTER_H

#include "classes/gf/GfMenuBtlchAdapter.h"

namespace gf {
// table none (its derived classes'): where a GfMenuBtlchAdapter's update takes its id from. The name follows the other
// adapters' IConverter (1.0.0's symbols); this file's own is not known.
class GfMenuBtlchAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    // Placeholder name: new in 3.0.1 (the derived classes' slot 2 at 0x7100334D68 and 0x7100334FD8); the id.
    virtual unsigned int fn_7100334D68() = 0;  // slot 2
};
}  // namespace gf

#endif
