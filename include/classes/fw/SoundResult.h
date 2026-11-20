#ifndef CLASSES_FW_SOUNDRESULT_H
#define CLASSES_FW_SOUNDRESULT_H

namespace fw {
// a class with no table: what ISoundDriver::playSeEx hands back (the field names are not the original's)
class SoundResult {
public:
    unsigned int handle;  // 0x00 (0 when nothing played)
    int status;  // 0x04 (3 when nothing played, else 0)
};
}  // namespace fw

#endif
