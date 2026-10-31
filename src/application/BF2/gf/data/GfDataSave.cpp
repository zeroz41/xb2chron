#include "gf/GfDataSave.h"

namespace gf {

void GfDataSave::getSaveDataPath(mm::mtl::FixStr<256>& out) {
    out = "save:/";
}

const char* GfDataSave::getSaveDataFileName() {
    return "bf2savefile";
}

const char* GfDataSave::fn_710022C0FC() {
    return "irasavefile";
}

const char* GfDataSave::getOptionSaveDataFileName() {
    return "bf2option";
}

const char* GfDataSave::getChapterSaveDataFileName() {
    return "bf2chapter";
}

const char* GfDataSave::getSaveDataExtNameForBin() {
    return ".sav";
}

const char* GfDataSave::getSaveDataExtNameForXml() {
    return ".xml";
}

void GfDataSave::getFileNameForLoad(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    if (slot == -1) {
        out.clear();
    } else if (slot == 0x16) {
        getSaveDataPath(out);
        out += getSaveDataFileName();
    } else if (slot < 10) {
        getSaveDataPath(out);
        out += getSaveDataFileName();
        mm::mtl::FixStr<16> num;
        num.format("%d", slot);
        out += num.m_str;
    } else {
        mm::mtl::FixStr<16> num;
        num.format("%d", slot - 8);
        out.format("/work/gf_select/%s%s", getChapterSaveDataFileName(), num.m_str);
    }
}

void GfDataSave::fn_710022C2B0(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    if (slot == -1) {
        out.clear();
    } else if (slot == 0x16) {
        getSaveDataPath(out);
        out += fn_710022C0FC();
    } else if (slot < 10) {
        getSaveDataPath(out);
        out += fn_710022C0FC();
        mm::mtl::FixStr<16> num;
        num.format("%d", slot);
        out += num.m_str;
    } else {
        mm::mtl::FixStr<16> num;
        num.format("%d", slot - 8);
        out.format("/work/gf_select/%s%s", "irachapter", num.m_str);
    }
}

void GfDataSave::getFileNameForSave(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    if (slot == -1) {
        out.clear();
    } else if (slot == 0x16) {
        getSaveDataPath(out);
        out += getSaveDataFileName();
    } else if (slot < 10) {
        getSaveDataPath(out);
        out += getSaveDataFileName();
        mm::mtl::FixStr<16> num;
        num.format("%d", slot);
        out += num.m_str;
    } else {
        getSaveDataPath(out);
        mm::mtl::FixStr<16> num;
        num.format("%d", slot - 8);
        out += getChapterSaveDataFileName();
        out += num.m_str;
    }
}

void GfDataSave::fn_710022C63C(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    if (slot == -1) {
        out.clear();
    } else if (slot == 0x16) {
        getSaveDataPath(out);
        out += fn_710022C0FC();
    } else if (slot < 10) {
        getSaveDataPath(out);
        out += fn_710022C0FC();
        mm::mtl::FixStr<16> num;
        num.format("%d", slot);
        out += num.m_str;
    } else {
        getSaveDataPath(out);
        mm::mtl::FixStr<16> num;
        num.format("%d", slot - 8);
        out += "irachapter";
        out += num.m_str;
    }
}

void GfDataSave::getFileNameForOption(mm::mtl::FixStr<256>& out) {
    getSaveDataPath(out);
    out += getOptionSaveDataFileName();
}

void GfDataSave::fn_710022C894(mm::mtl::FixStr<256>& out) {
    getSaveDataPath(out);
    out += "iraoption";
}

void GfDataSave::getFileNameForSaveBin(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    getFileNameForSave(out, slot);
    out += getSaveDataExtNameForBin();
}

void GfDataSave::fn_710022C96C(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    fn_710022C63C(out, slot);
    out += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForOptionBin(mm::mtl::FixStr<256>& out) {
    getFileNameForOption(out);
    out += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForOptionXml(mm::mtl::FixStr<256>& out) {
    fn_710022C894(out);
    out += getSaveDataExtNameForBin();
}

}  // namespace gf
