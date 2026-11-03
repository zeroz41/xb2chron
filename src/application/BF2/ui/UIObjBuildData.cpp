#include "mm/mtl/Vector.h"
#include "classes/ui/UIObjBuildData.h"
#include <string.h>
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIObjBuildData.h"
#include "mm/mtl/Hash.h"
#include "mm/mtl/Vector.h"

namespace ui {

// the parameter names a Parameter's type indexes (the names of these two are not the original's)
static const char* s_paramNames[] = {
    "type",          "resource",      "name",          "parent",          "attach_layout",   "text_id",
    "text_align_h",  "text_align_v",  "text_property", "priority",        "def_undisp",      "offs_x",
    "offs_y",        "input_type",    "input_id",      "rot",             "alpha",           "col_name_mul",
    "col_name_add",  "screen_w",      "screen_h",      "border_weight",   "slope",           "input_disable",
    "screen_on_mem", "img_stream_list", "img_index",   "img_capture",     "img_capture_w",   "img_capture_h",
    "poly_v_num",    "scale_x",       "scale_y",       "img_hflip",       "img_vflip",       "localize",
    "text_face_ptn", "poly_shape_type", "poly_face_v_num", "poly_ring_div", "poly_ring_w",   "blend_type",
    "poly_particle_file", "save_def_col", "col_link_name", "ignore_sizing", "mask_link_name", "img_mask",
    "dlc",
};
static unsigned int s_paramHashes[sizeof(s_paramNames) / sizeof(s_paramNames[0])];  // initialize's

UIObjBuildData::UIObjBuildData(mm::mtl::IAllocator* allocator) : m_objects(), m_strings(), m_allocator(allocator) {
    if (m_allocator != nullptr) {
        m_objects.setAllocator(m_allocator);
        m_strings.setAllocator(m_allocator);
    }
}

UIObjBuildData::~UIObjBuildData() {
    clear();
}

void UIObjBuildData::clear() {
    for (unsigned int i = 0; i < m_objects.size(); i++) {
        if (m_objects[i].m_params.capacity() != 0) {
            m_objects[i].m_params.destroy();
        }
    }
    if (m_objects.capacity() != 0) {
        m_objects.destroy();
    }
    if (m_strings.capacity() != 0) {
        m_strings.destroy();
    }
}

void UIObjBuildData::initialize() {
    for (int i = 0; i < (int)(sizeof(s_paramNames) / sizeof(s_paramNames[0])); i++) {
        s_paramHashes[i] = mm::mtl::hashStrCrc(s_paramNames[i]);
    }
}

// deserialize (0x7100673EA4) is not here yet: the best candidate differs in register allocation and one spill

unsigned int UIObjBuildData::getObjectNum() const {
    return m_objects.size();
}

inline short UIObjBuildData::getParamType(const char* name) const {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (int i = 0; i < (int)(sizeof(s_paramHashes) / sizeof(s_paramHashes[0])); i++) {
        if (s_paramHashes[i] == hash) {
            return i;
        }
    }
    return -1;
}

bool UIObjBuildData::getObjectParam(unsigned int index, const char* name, Value& value) const {
    value.m_int = 0;
    if (index >= m_objects.size()) {
        return false;
    }
    short type = getParamType(name);
    if (type < 0) {
        return false;
    }
    const ObjData& object = m_objects[index];
    for (unsigned int i = 0; i < object.m_params.size(); i++) {
        if (object.m_params[i].m_type != type) {
            continue;
        }
        if (object.m_params[i].m_flags == 0) {
            value.m_int = object.m_params[i].m_value;
            return true;
        }
        if (object.m_params[i].m_flags & 1) {
            if (object.m_params[i].m_value < (int)m_strings.size()) {
                value.m_str = m_strings[object.m_params[i].m_value];
                return true;
            }
        } else if (object.m_params[i].m_flags & 2) {
            value.m_int = object.m_params[i].m_value;
            return true;
        }
    }
    return false;
}

}  // namespace ui

// the object and parameter vectors' growth (their users are not written yet)
template void mm::mtl::Vector<ui::UIObjBuildData::ObjData>::expand(size_t, size_t);
template void mm::mtl::Vector<ui::UIObjBuildData::Parameter>::assign(const mm::mtl::Vector<ui::UIObjBuildData::Parameter>&);
template void mm::mtl::Vector<ui::UIObjBuildData::Parameter>::expand(size_t, size_t);
template void mm::mtl::Vector<ui::UIObjBuildData::ObjData>::push_back(const ui::UIObjBuildData::ObjData&);
