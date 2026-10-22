#ifndef FW_OBJECTEVENT_H
#define FW_OBJECTEVENT_H

namespace fw {
// what UpdatableObject::onEvent is given: GfObj::onEvent flushes its property for type 0 (the name is not the
// original's)
class ObjectEvent {
public:
    unsigned int m_type;
};
}  // namespace fw

#endif
