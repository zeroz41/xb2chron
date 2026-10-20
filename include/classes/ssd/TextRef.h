#ifndef CLASSES_SSD_TEXTREF_H
#define CLASSES_SSD_TEXTREF_H

namespace ssd { class TextRef; }

namespace ssd {
// table 0x7100B82098
class TextRef {
public:
    virtual void Set(ssd::TextRef const&);  // slot 0
    virtual void Set(char const*);  // slot 1
    virtual void Set(char16_t const*);  // slot 2
};
}  // namespace ssd

#endif
