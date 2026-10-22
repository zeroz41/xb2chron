#ifndef CLASSES_LAYER_LAYERTAGSTR_H
#define CLASSES_LAYER_LAYERTAGSTR_H

#include "classes/layer/LayerTag.h"

namespace layer {
// table 0x7100B7F910
class LayerTagStr : public ::layer::LayerTag {
public:
    LayerTagStr();
    virtual ~LayerTagStr();  // slot 0
    virtual void beginParseString();  // slot 2
    virtual void endParseString();  // slot 3
    virtual void parseNotTag(unsigned char const*, unsigned int&);  // slot 4
    virtual void parseNotTag(wchar_t const*, unsigned int&);  // slot 5
    virtual void callTagNoUse(unsigned char const*);  // slot 8
    void setStockTbl(char* tbl, int size);  // the buffer stockString fills and its size
    void stockString(const char* str);  // str appended to the buffer at m_stockCount
    // the names are not the original's (setStockTbl and stockString show what each does)
    char* m_stockTbl;
    int m_stockSize;
    int m_stockCount;  // the characters stockString has added
};
}  // namespace layer

#endif
