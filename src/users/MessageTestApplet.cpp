#include "classes/fw/ComponentObject.h"
#include "users/MessageTestApplet.h"
#include "classes/fw/UpdatableObject.h"

namespace users {

mm::mtl::RTTI Updatable1::m_rtti("Updatable1", &fw::UpdatableObject::m_rtti, nullptr);
mm::mtl::RTTI Updatable2::m_rtti("Updatable2", &Updatable1::m_rtti, nullptr);
mm::mtl::RTTI Updatable3::m_rtti("Updatable3", &fw::UpdatableObject::m_rtti, nullptr);
mm::mtl::RTTI Component1::m_rtti("Component1", &fw::ComponentObject::m_rtti, nullptr);
mm::mtl::RTTI Component2::m_rtti("Component2", &Component1::m_rtti, nullptr);
mm::mtl::RTTI Component3::m_rtti("Component3", &fw::ComponentObject::m_rtti, nullptr);

}  // namespace users
