#ifndef USERS_MESSAGETESTAPPLET_H
#define USERS_MESSAGETESTAPPLET_H

#include "mm/mtl/RTTI.h"

// The message test applet's sample objects and components. 1.0.0 had their tables and getRTTI; 3.0.1 keeps only
// their types, which MessageTestApplet.cpp's initializer stores.
namespace users {
class Updatable1 {  // an fw::UpdatableObject
public:
    static mm::mtl::RTTI m_rtti;
};
class Updatable2 {  // a Updatable1
public:
    static mm::mtl::RTTI m_rtti;
};
class Updatable3 {  // an fw::UpdatableObject
public:
    static mm::mtl::RTTI m_rtti;
};
class Component1 {  // an fw::ComponentObject
public:
    static mm::mtl::RTTI m_rtti;
};
class Component2 {  // a Component1
public:
    static mm::mtl::RTTI m_rtti;
};
class Component3 {  // an fw::ComponentObject
public:
    static mm::mtl::RTTI m_rtti;
};
}  // namespace users

#endif
