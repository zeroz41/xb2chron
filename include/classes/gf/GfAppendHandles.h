#ifndef CLASSES_GF_GFAPPENDHANDLES_H
#define CLASSES_GF_GFAPPENDHANDLES_H

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B3FBE8
class GfAppendHandles {
public:
    virtual ~GfAppendHandles() {}  // slot 0
    // msg handed to the appended objects, from sender
    void sendMessage(fw::MessageObject* sender, fw::Message& msg) const;
};
}  // namespace gf

#endif
