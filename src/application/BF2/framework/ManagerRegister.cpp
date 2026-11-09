#include "mm/mtl/FixedVector.h"
#include "classes/fw/ManagerObject.h"
#include "classes/fw/ManagerRegister.h"

namespace fw {

ManagerRegister::ManagerRegister() {}

ManagerRegister::~ManagerRegister() {}

void ManagerRegister::regist(ManagerObject* object) {
    if (object == nullptr) {
        return;
    }
    mm::mtl::FixedVector<ManagerObject*, 256>::iterator it = m_objects.begin();
    for (; it != m_objects.end(); ++it) {
        if (*it == object) {
            break;
        }
    }
    if (it != m_objects.end()) {
        return;
    }
    m_objects.push_back(object);
}

void ManagerRegister::remove(ManagerObject* object) {
    if (object == nullptr) {
        return;
    }
    mm::mtl::FixedVector<ManagerObject*, 256>::iterator it = m_objects.begin();
    for (; it != m_objects.end(); ++it) {
        if (*it == object) {
            break;
        }
    }
    if (it != m_objects.end()) {
        m_objects.erase(it);
    }
}

bool ManagerRegister::initialize() {
    bool result = true;
    for (mm::mtl::FixedVector<ManagerObject*, 256>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
        ManagerObject* object = *it;
        if (!object->isInitialized()) {
            bool initialized = object->initialize();
            result = false;
            if (initialized) {
                object->m_flags |= 1;
            }
        }
    }
    return result;
}

bool ManagerRegister::finalize() {
    if (m_objects.empty()) {
        return true;
    }
    unsigned char result = true;
    for (int i = m_objects.size(); i > 0; i--) {
        ManagerObject* object = m_objects[i - 1];
        if (!object->isFinalized()) {
            bool finalized = object->finalize();
            result = false;
            if (finalized) {
                object->m_flags |= 2;
            }
        }
    }
    return result;
}

void ManagerRegister::enterFinalizeApplet() {
    for (mm::mtl::FixedVector<ManagerObject*, 256>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
        (*it)->enterFinalizeApplet();
    }
}

}  // namespace fw
