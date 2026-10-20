#ifndef CLASSES_SSD_STRING_H
#define CLASSES_SSD_STRING_H

namespace ssd { class TextRef; }

namespace ssd {
// table 0x7100B823C8
class String {
public:
    virtual void Set(ssd::TextRef const&);  // slot 0
    virtual void Set(char const*);  // slot 1
    virtual void Set(char16_t const*);  // slot 2
    virtual ~String();  // slot 3
};
}  // namespace ssd

#endif
