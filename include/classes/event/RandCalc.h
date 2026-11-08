#ifndef CLASSES_EVENT_RANDCALC_H
#define CLASSES_EVENT_RANDCALC_H

#include "mm/mtl/FixedVector.h"

namespace event {
// picks the random talk (FLD_randomTalk row) RandManager::play plays (no table; 1.0.0's symbols name the class)
class RandCalc {
public:
    // a random row of the type whose talkers are all present, or -1
    static int calc(int type);
    // 1.0.0's RandCalc::listup and listupType (out of line there; 3.0.1 inlines them into calc)
    static void listup(mm::mtl::FixedVector<int, 1024>& list);
    static void listupType(mm::mtl::FixedVector<int, 1024>& out, mm::mtl::FixedVector<int, 1024>& in, int type);
    // 1.0.0's RandCalc::listupRand (inline in 3.0.1): out holds one row of in, picked at random
    static void listupRand(mm::mtl::FixedVector<int, 1024>& out, mm::mtl::FixedVector<int, 1024>& in);
    // the rows of in whose talk0/talk1 characters are present
    static void listupParty(mm::mtl::FixedVector<int, 1024>& out, mm::mtl::FixedVector<int, 1024>& in);
};
}  // namespace event

#endif
