#include "ssd/Mutex.h"

namespace ssd {

// the lock the debug output stream takes (1.0.0's ssd::InitDebug/QuitDebug set it up and tear it down)
Mutex OutStreamLock;

}  // namespace ssd
