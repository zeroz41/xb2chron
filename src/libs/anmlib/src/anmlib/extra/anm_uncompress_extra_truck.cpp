#include "anm/Array.h"
#include "anm/SerialiseArg.h"
#include "anm/ExtraBinding.h"
#include "classes/anm/UncompressExtraTruck.h"
#include "classes/anm/CubicExtraTruck.h"
#include <new>

namespace anm {

ExtraBinding::ExtraBinding(const SerialiseArg& arg) {
    if (m_pTruck != nullptr) {
        switch (m_pTruck->m_type) {
        case 0:
            new (m_pTruck) UncompressExtraTruck(arg);
            break;
        case 1:
            new (m_pTruck) CubicExtraTruck(arg);
            break;
        }
    }
}

// UncompressExtraTruck::sampleTrucks (0x7100884B4C) is not matched yet

}  // namespace anm
