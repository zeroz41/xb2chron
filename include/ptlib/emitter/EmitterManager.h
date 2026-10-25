#ifndef PTLIB_EMITTER_EMITTERMANAGER_H
#define PTLIB_EMITTER_EMITTERMANAGER_H

namespace ptlib { namespace emitter {

// the emitters' manager: its per-category speeds (effect::SystemManager::setCategorySpd)
class EmitterManager {
public:
    static EmitterManager* get();
    static EmitterManager*& getPtr();

    unsigned char pad_0[0x1700];
    float m_categorySpeed[1];  // indexed by category; the count is not known yet
};
}}  // namespace ptlib::emitter

#endif
