#include "classes/ui/UIBuildInfoUIO.h"

#include <string.h>

#include "classes/fw/CommonResource.h"
#include "classes/ui/UIObjBuildData.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/UIUtil.h"

namespace ui {

UIBuildInfoUIO::UIBuildInfoUIO(const char* name) : m_name(name), m_resource(nullptr) {
    mm::mtl::FixStr<128> path;
    UIUtil::makeMenuUIOFileName(path, name);
    fw::CommonResource* resource = fw::CommonResource::request(UIUtil::getResourceAllocator(), path.m_str, 10, false);
    if (resource != nullptr) {
        m_resource = resource;
    }
    m_objects.setAllocator(UIUtil::getProgAllocator());
}

UIBuildInfoUIO::~UIBuildInfoUIO() {
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
}

void UIBuildInfoUIO::update() {
    if (m_objects.size() != 0) {
        return;
    }
    if (m_resource == nullptr || !m_resource->valid()) {
        return;
    }
#line 61
    UIObjBuildData* buildData = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__)
        UIObjBuildData(UIUtil::getProgAllocator());
    buildData->deserialize(m_resource->getAssetData(), m_resource->getAssetSize());
    unsigned int num = buildData->getObjectNum();
    if (num != 0) {
        m_objects.reserve(num);
        for (unsigned int i = 0; i < num; i++) {
            getObjectDataUIO(buildData, i, m_objects[i]);
        }
        delete buildData;
    } else {
        delete buildData;
        if (m_resource != nullptr) {
            m_resource->release();
            m_resource = nullptr;
        }
    }
}

void UIBuildInfoUIO::getObjectDataUIO(UIObjBuildData* buildData, unsigned int index,
                                      ui::UIBuildInfo::ObjectData& data) const {
    if (!isReady()) {
        return;
    }
    data = ObjectData();
    UIObjBuildData::Value value;
    if (!buildData->getObjectParam(index, "type", value)) {
        return;
    }
    data.m_type = value.m_int;
    if (!buildData->getObjectParam(index, "name", value)) {
        return;
    }
    data.m_name = value.m_str;
    if (buildData->getObjectParam(index, "offs_x", value)) {
        data.m_offsX = value.m_int;
    }
    if (buildData->getObjectParam(index, "offs_y", value)) {
        data.m_offsY = value.m_int;
    }
    if (buildData->getObjectParam(index, "scale_x", value)) {
        data.m_scaleX = value.m_float;
    }
    if (buildData->getObjectParam(index, "scale_y", value)) {
        data.m_scaleY = value.m_float;
    }
    if (buildData->getObjectParam(index, "rot", value)) {
        data.m_attr = (short)value.m_int;
    }
    if (buildData->getObjectParam(index, "alpha", value)) {
        data.m_alpha = value.m_int / 100.0f;
    }
    if (buildData->getObjectParam(index, "priority", value)) {
        data.m_priority = value.m_int;
    }
    if (buildData->getObjectParam(index, "def_undisp", value)) {
        data.m_defUndisp = value.m_int != 0;
    }
    if (buildData->getObjectParam(index, "localize", value)) {
        data.m_resourceIsFile = value.m_int != 0;
    }
    if (buildData->getObjectParam(index, "dlc", value)) {
        data.m_flagB = value.m_int != 0;
    }
    if (buildData->getObjectParam(index, "save_def_col", value)) {
        data.m_saveDefCol = value.m_int != 0;
    }
    if (buildData->getObjectParam(index, "ignore_sizing", value)) {
        data.m_ignoreSizing = value.m_int != 0;
    }
    if (buildData->getObjectParam(index, "col_link_name", value)) {
        data.m_strA = value.m_str;
    }
    if (buildData->getObjectParam(index, "mask_link_name", value)) {
        data.m_strB = value.m_str;
    }
    if (buildData->getObjectParam(index, "parent", value)) {
        data.m_parent = value.m_str;
    }
    if (buildData->getObjectParam(index, "attach_layout", value)) {
        data.m_attachLayout = value.m_str;
    }
    if (buildData->getObjectParam(index, "col_name_mul", value)) {
        data.m_layoutFile = value.m_str;
    }
    if (buildData->getObjectParam(index, "col_name_add", value)) {
        data.m_layoutName = value.m_str;
    }
    if (buildData->getObjectParam(index, "blend_type", value)) {
        data.m_flagA = value.m_int;
    }
    if (buildData->getObjectParam(index, "resource", value)) {
        data.m_resourceFile = value.m_str;
    }
    if (buildData->getObjectParam(index, "img_stream_list", value)) {
        data.m_strC = value.m_str;
    }
    if (buildData->getObjectParam(index, "img_index", value)) {
        data.m_index = value.m_int;
    }
    if (buildData->getObjectParam(index, "img_capture", value)) {
        data.m_textFlag = value.m_int != 0;
    }
    if (buildData->getObjectParam(index, "img_capture_w", value)) {
        data.m_textA = value.m_int;
    }
    if (buildData->getObjectParam(index, "img_hflip", value)) {
        data.m_imgHFlip = value.m_int == 1;
    }
    if (buildData->getObjectParam(index, "img_vflip", value)) {
        data.m_imgVFlip = value.m_int == 1;
    }
    if (buildData->getObjectParam(index, "img_mask", value)) {
        data.m_textD = value.m_int == 1;
    }
    if (buildData->getObjectParam(index, "img_capture_h", value)) {
        data.m_textB = value.m_int;
    }
    if (buildData->getObjectParam(index, "screen_w", value)) {
        data.m_screenW = value.m_int;
    }
    if (buildData->getObjectParam(index, "screen_h", value)) {
        data.m_screenH = value.m_int;
    }
    if (buildData->getObjectParam(index, "screen_on_mem", value)) {
        data.m_extE = value.m_int != 0;
    }
    if (data.m_type == 5) {
        if (buildData->getObjectParam(index, "poly_shape_type", value)) {
            data.m_extF = value.m_int;
        }
        if (buildData->getObjectParam(index, "poly_face_v_num", value)) {
            data.m_polyFaceVNum = value.m_int;
        }
        if (buildData->getObjectParam(index, "poly_ring_div", value)) {
            data.m_polyRingDiv = value.m_int;
        }
        if (buildData->getObjectParam(index, "poly_ring_w", value)) {
            data.m_extH = value.m_int;
        }
        if (buildData->getObjectParam(index, "poly_particle_file", value)) {
            data.m_extI = value.m_str;
        }
    }
    mm::mtl::FixStr<64> textName;
    textName = m_name;
    textName += "_txt";
    if (Bdat::isExistFP(textName.m_str)) {
        unsigned char* fp = Bdat::getFP(textName.m_str);
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            if (strcmp((const char*)Bdat::getVal(fp, "obj_name", Bdat::getIdTop(fp) + i), data.m_name) == 0) {
                int textId = Bdat::getVal(fp, "text_id", Bdat::getIdTop(fp) + i);
                if (textId != 0) {
                    UIUtil::getBdatFP(5);
                    data.m_textId = textId;
                    if (buildData->getObjectParam(index, "text_align_h", value)) {
                        data.m_textAlignH = value.m_int;
                    }
                    if (buildData->getObjectParam(index, "text_align_v", value)) {
                        data.m_textAlignV = value.m_int;
                    }
                    if (buildData->getObjectParam(index, "border_weight", value)) {
                        data.m_borderWeight = value.m_int * 0.1f;
                    }
                    if (buildData->getObjectParam(index, "slope", value)) {
                        data.m_extB = value.m_int;
                    }
                    if (buildData->getObjectParam(index, "text_face_ptn", value)) {
                        data.m_extC = value.m_str;
                    }
                }
                break;
            }
        }
    }
    buildData->getObjectParam(index, "input_type", value);
    data.m_inputType = value.m_int;
    buildData->getObjectParam(index, "input_id", value);
    if (value.m_str != nullptr) {
        unsigned char* fp;
        if (data.m_inputType == 1) {
            fp = UIUtil::getBdatFP(7);
        } else if (data.m_inputType == 2) {
            fp = UIUtil::getBdatFP(8);
        } else if (data.m_inputType == 3) {
            fp = UIUtil::getBdatFP(9);
        } else {
            goto disable;
        }
        if (fp != nullptr) {
            int i;
            for (i = 0; i < Bdat::getIdCount(fp); i++) {
                int id = Bdat::getIdTop(fp) + i;
                if (strcmp(value.m_str, (const char*)Bdat::getVal(fp, "name", id)) == 0) {
                    data.m_inputId = id;
                    break;
                }
            }
            if (i >= Bdat::getIdCount(fp)) {
                // no such input: the original counts the rows once more here and does nothing (a report left
                // out of the build, likely)
            }
        }
    }
disable:
    if (buildData->getObjectParam(index, "input_disable", value)) {
        data.m_inputFlag = value.m_int != 0;
    }
}

bool UIBuildInfoUIO::isReady() const {
    return m_objects.size() != 0;
}

bool UIBuildInfoUIO::isValid() const {
    return m_resource != nullptr;
}

unsigned int UIBuildInfoUIO::getObjectNum() const {
    return isReady() ? m_objects.size() : 0;
}

void UIBuildInfoUIO::getObjectData(unsigned int index, ui::UIBuildInfo::ObjectData& data) const {
    if (isReady()) {
        data = m_objects[index];
    }
}

const char* UIBuildInfoUIO::getName() const {
    return m_name;
}

}  // namespace ui
