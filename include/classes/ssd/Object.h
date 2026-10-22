#ifndef CLASSES_SSD_OBJECT_H
#define CLASSES_SSD_OBJECT_H

namespace ssd { class SoundCore; }

namespace ssd {

namespace ObjectType {
// what an object is (SoundActor's constructor passes 8)
enum Id {};
}  // namespace ObjectType

// table 0x7100B81C30
class Object {
public:
    Object(ObjectType::Id type);
    virtual ~Object() {}  // slot 0

    // the object's type and the library instance it was made under (SoundCore::instance_ when constructed); the
    // word between them is zeroed and nothing found reads it (the names are not the original's)
    ObjectType::Id type_;
    unsigned int pad_c;
    SoundCore* core_;
};
}  // namespace ssd

#endif
