#ifndef ML_ML_MISC_H
#define ML_ML_MISC_H

// monolib's odds and ends (ml_misc.cpp)
#ifdef __cplusplus
extern "C" {
#endif

// logs a call stack: `pTrace`'s return addresses (up to 30, ending at a null one), or the caller's own when null
void mlStackTrace(unsigned long* pTrace);

#ifdef __cplusplus
}
#endif

#endif
