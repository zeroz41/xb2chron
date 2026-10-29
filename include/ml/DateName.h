#ifndef ML_DATENAME_H
#define ML_DATENAME_H

// monolib's C helper in ClockLap's unit (unmangled symbol): writes the current date as text into the buffer
// (it stores a 0 first); event::AgelogManager::OnEventProc passes a 0x40-byte buffer and its size. The parameter
// names are not the original's; the return value is unused by its only caller.
extern "C" void mlGetDateName(char* name, int size);

#endif
