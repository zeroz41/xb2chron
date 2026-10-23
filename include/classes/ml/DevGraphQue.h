#ifndef CLASSES_ML_DEVGRAPHQUE_H
#define CLASSES_ML_DEVGRAPHQUE_H

#include "mm/Rect.h"

namespace ml {
// ml::DevGraph's rectangle queue (DevGraph holds one at 0x330 and forwards pushRect/popRect to it)
class DevGraphQue {
public:
    DevGraphQue();
    void createQue(unsigned int size);
    void flushViewport();
    void pushRect(const mm::Rect<int>& a, const mm::Rect<int>& b, const mm::Rect<int>& c, bool flag);
    void popRect();
};
}  // namespace ml

#endif
