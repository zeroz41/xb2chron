#include "classes/fw/ScriptManager.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ml/PathUtil.h"
#include "mtl/MemManager.h"
#include "plugin/PluginRegist.h"
#include "vm/yvm2.h"
#include <string.h>

namespace fw {

ScriptManager::ScriptManager(mm::mtl::IAllocator* allocator, unsigned long size) : m_scripts(allocator) {
    m_scripts.reserve(size);
}

ScriptManager::~ScriptManager() {
    finalize();
}

bool ScriptManager::initialize() {
    if (!isInitialized()) {
        pluginRegist();
    }
    return true;
}

bool ScriptManager::finalize() {
    if (!isFinalized()) {
        for (unsigned long i = 0; i < m_scripts.size(); i++) {
            // as destroyScript(i, true)
            int id = i;
            m_scripts[id].destroy();
            void* buffer = m_scripts[id].m_buffer;
            if (buffer != nullptr) {
                mm::mtl::IAllocator* allocator = m_scripts[id].m_allocator;
                if (allocator != nullptr) {
                    allocator->deallocate(buffer);
                } else {
                    mtl::MemManager::deallocate(buffer, 0, false);
                }
                m_scripts[id].m_buffer = nullptr;
            }
        }
    }
    return true;
}

void ScriptManager::makeFullPath(mm::mtl::FixStr<256>& path, const char* name) {
    mm::mtl::FixStr<256> noExt;
    mm::mtl::FixStr<256> file;
    ml::PathUtil::getNoExtName(noExt, name);
    file = ml::PathUtil::getNoPathExtName(noExt.m_str).m_str;
    if (file.findLast('.') == -1) {
        file += ".sb";
    }
    path.format("%s%s", m_rootPath.m_str, file.m_str);
    int len = path.m_nLen;
    int slash = path.findLast('/');
    if (slash == -1) {
        slash = path.findLast('\\');
    }
    int start = slash == -1 ? 0 : slash;
    if (start < len) {
        for (int i = start; i < len; i++) {
            if (static_cast<unsigned char>(path.m_str[i]) > 0x80) {
                return;
            }
        }
        for (int i = start; i < path.m_nLen; i++) {
            if (path.m_str[i] >= 'A' && path.m_str[i] <= 'Z') {
                path.m_str[i] += 'a' - 'A';
            }
        }
    }
}

}  // namespace fw

namespace ml {
// path without its extension: none when it has none or starts with it (defined here: 3.0.1 keeps this file's
// FixStr<256> instance, which gf::GfGameLoad calls out of line)
template <typename STR>
bool PathUtil::getNoExtName(STR& out, const char* path) {
    out = path;
    int dot = out.findLast('.');
    if (dot == -1 || dot == 0) {
        return false;
    }
    out = out.substr(0, dot);
    return true;
}
}  // namespace ml

namespace fw {

void ScriptManager::createScript(int id, mm::mtl::IAllocator* allocator, unsigned long size) {
    void* buffer = allocator->allocate(size, 0x1000);
    m_scripts[id].initialize(this, id, buffer, size);
    m_scripts[id].m_allocator = allocator;
}

void ScriptManager::destroyScript(int id, bool release) {
    m_scripts[id].destroy();
    if (release) {
        void* buffer = m_scripts[id].m_buffer;
        if (buffer != nullptr) {
            mm::mtl::IAllocator* allocator = m_scripts[id].m_allocator;
            if (allocator != nullptr) {
                allocator->deallocate(buffer);
            } else {
                mtl::MemManager::deallocate(buffer, 0, false);
            }
            m_scripts[id].m_buffer = nullptr;
        }
    }
}

bool ScriptManager::isScriptLoaded(int id) const {
    return m_scripts[id].isLoaded();
}

void ScriptManager::loadScript(int id, const char* name, ml::FILE_PRIO prio) {
    mm::mtl::FixStr<256> path;
    makeFullPath(path, name);
    m_scripts[id].load(path, prio);
}

void ScriptManager::update(const UpdateInfo&) {
    if (!isFinalized()) {
        vmExec();
        for (unsigned long i = 0; i < m_scripts.size(); i++) {
            m_scripts[i].execute();
        }
    }
}

void ScriptManager::notifyEvent(int id, ScriptEventParam::State state) {
    ScriptEventParam param = {id, state};
    for (unsigned long i = 0; i < m_events.size(); i++) {
        m_events[i]->scriptEvent(param);
    }
}

mm::mtl::FixStr<256> ScriptManager::m_rootPath("/script/jp/");

}  // namespace fw
