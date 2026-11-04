#include "gf/GfDataSave.h"

namespace gf {

void GfDataSave::getSaveDataPath(mm::mtl::FixStr<256>& out) {
    out = "save:/";
}

const char* GfDataSave::getSaveDataFileName() {
    return "bf2savefile";
}

const char* GfDataSave::getIraSaveDataFileName() {
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

void GfDataSave::getFileNameForIraLoad(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    if (slot == -1) {
        out.clear();
    } else if (slot == 0x16) {
        getSaveDataPath(out);
        out += getIraSaveDataFileName();
    } else if (slot < 10) {
        getSaveDataPath(out);
        out += getIraSaveDataFileName();
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

void GfDataSave::getFileNameForIraSave(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    if (slot == -1) {
        out.clear();
    } else if (slot == 0x16) {
        getSaveDataPath(out);
        out += getIraSaveDataFileName();
    } else if (slot < 10) {
        getSaveDataPath(out);
        out += getIraSaveDataFileName();
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

void GfDataSave::getFileNameForIraOption(mm::mtl::FixStr<256>& out) {
    getSaveDataPath(out);
    out += "iraoption";
}

void GfDataSave::getFileNameForSaveBin(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    getFileNameForSave(out, slot);
    out += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForIraSaveBin(mm::mtl::FixStr<256>& out, SAVESLOT slot) {
    getFileNameForIraSave(out, slot);
    out += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForOptionBin(mm::mtl::FixStr<256>& out) {
    getFileNameForOption(out);
    out += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForIraOptionBin(mm::mtl::FixStr<256>& out) {
    getFileNameForIraOption(out);
    out += getSaveDataExtNameForBin();
}

}  // namespace gf
