#ifndef EVENT_AGELOGUTIL_H
#define EVENT_AGELOGUTIL_H

#include "mm/mtl/FixStr.h"

namespace event {

// the event log's output (1.0.0's event::AgelogUtil::setPath(char const*) and print(char const*, ...))
class AgelogUtil {
public:
    static void setPath(const char* path);
    static void print(const char* format, ...);
    static mm::mtl::FixStr<256> s_path;
};

}  // namespace event

#endif
