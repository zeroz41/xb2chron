#ifndef CLASSES_SSD_IOSTREAMBASE_H
#define CLASSES_SSD_IOSTREAMBASE_H

namespace ssd { class TextRef; }

namespace ssd {
// table none (its derived classes')
class IoStreamBase {
public:
    class OpenMode;
    class SeekMode;
    virtual ~IoStreamBase();  // slot 0
    virtual void IsOpen() const = 0;  // slot 2
    virtual void Open(ssd::TextRef const&, ssd::IoStreamBase::OpenMode);  // slot 3
    virtual void Open(void*, unsigned long, ssd::IoStreamBase::OpenMode);  // slot 4
};
}  // namespace ssd

#endif
