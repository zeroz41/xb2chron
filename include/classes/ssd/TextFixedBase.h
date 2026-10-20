#ifndef CLASSES_SSD_TEXTFIXEDBASE_H
#define CLASSES_SSD_TEXTFIXEDBASE_H

namespace ssd { class TextRef; }

namespace ssd {
// table none (its derived classes')
class TextFixedBase {
public:
    virtual void Set(ssd::TextRef const&);  // slot 0
    virtual void Set(char const*);  // slot 1
    virtual void Set(char16_t const*);  // slot 2
};
}  // namespace ssd

#endif
