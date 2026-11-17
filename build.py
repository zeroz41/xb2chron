#!/usr/bin/env python3
"""Builds the Xenoblade Chronicles 2 decompilation. Needs Python 3.11 or newer.

    python build.py                   build (the first run sets everything up)
    python build.py --rom FOLDER      take the game from FOLDER instead of rom/
    python build.py --keys FILE       use this prod.keys
    python build.py --ghidra          also install what `zkit decompile` needs (Ghidra itself is separate)
    python build.py zkit ARGS...      run the build's zkit, e.g. `python build.py zkit progress` (no game needed)

Everything it sets up stays in build/: a Python environment with zkit and Ninja (build/env), then the compilers
and tools zkit downloads. Delete build/ to start over.
"""
import argparse
import os
import platform
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROJECT = ROOT / "xc2.project.json"
ENV = ROOT / "build" / "env"
EXECUTABLE = ROOT / "orig" / "XC2_301" / "main"
ROMS = ROOT / "rom"
GAME_FILES = (".nsp", ".xci", ".nsz", ".xcz")

# The build tooling, pinned: zkit at a commit, Ninja at a release.
ZKIT = "zkit @ https://github.com/zeroz41/zkit-gcnx/archive/bb04aaf2e8d0fa2cfe13b29839b16719eee72397.zip"
NINJA = "ninja==1.13.0"


def fail(message):
    sys.exit(f"\n{message}")


def scripts():
    return ENV / ("Scripts" if os.name == "nt" else "bin")


def env_python():
    return scripts() / ("python.exe" if os.name == "nt" else "python")


def with_extra(spec, extra):
    """The pip requirement for zkit from spec with its optional dependencies `extra`."""
    name, at, url = spec.partition(" @ ")
    if at:
        return f"{name.strip()}[{extra}] @ {url.strip()}"
    if "://" in spec:
        return f"zkit[{extra}] @ {spec}"
    return f"{spec}[{extra}]"  # a local checkout


def setup(spec, ghidra=False):
    """Make build/env with zkit and Ninja, once (again when the pins change). With ghidra, and on every run after
    that, also zkit's `decompile` dependencies."""
    stamp = ENV / "installed.txt"
    before = stamp.read_text(encoding="utf-8") if stamp.is_file() else ""
    ghidra = ghidra or "ghidra" in before.splitlines()
    wanted = "\n".join([spec, NINJA, *(["ghidra"] if ghidra else [])]) + "\n"
    if env_python().is_file() and before == wanted:
        return
    print(f"Setting up build/env (zkit{', pyghidra' if ghidra else ''} and Ninja)...", flush=True)
    if not env_python().is_file():
        made = subprocess.run([sys.executable, "-m", "venv", str(ENV)])
        if made.returncode != 0 or not env_python().is_file():
            shutil.rmtree(ENV, ignore_errors=True)
            fail("Could not make a Python environment. On Debian or Ubuntu, install python3-venv "
                 "(sudo apt install python3-venv) and run this again.")
    installed = subprocess.run([str(env_python()), "-m", "pip", "install", "--quiet", "--disable-pip-version-check",
                                "--upgrade", with_extra(spec, "ghidra") if ghidra else spec, NINJA])
    if installed.returncode != 0:
        fail("Installing zkit and Ninja failed (see above). Check the internet connection and run this again.")
    stamp.write_text(wanted, encoding="utf-8")


def check_host():
    """What the compilers need from this computer, beyond what the build downloads."""
    if os.name == "nt":
        return
    if not (os.environ.get("CXX") or shutil.which("c++") or shutil.which("g++") or shutil.which("clang++")):
        fail("The build needs a C++ compiler to build a small plugin for the game's clang. Install one:\n"
             "  Debian/Ubuntu: sudo apt install g++\n"
             "  Fedora:        sudo dnf install gcc-c++\n"
             "  Arch:          sudo pacman -S gcc\n"
             "  macOS:         xcode-select --install")
    if sys.platform == "darwin" and platform.machine() == "arm64" and \
            subprocess.run(["arch", "-x86_64", "/usr/bin/true"], capture_output=True).returncode != 0:
        fail("The game's clang is an Intel program, which an Arm Mac runs with Rosetta 2. Install it:\n"
             "  softwareupdate --install-rosetta --agree-to-license")


def has_game():
    """Whether the executable is out already, or there are game files in rom/ (or its subfolders)."""
    return EXECUTABLE.is_file() or any(path.suffix.lower() in GAME_FILES for path in ROMS.rglob("*"))


def zkit(*args):
    """Run the environment's zkit on this project; its exit code."""
    env = {**os.environ, "PATH": str(scripts()) + os.pathsep + os.environ.get("PATH", "")}
    return subprocess.run([str(env_python()), "-m", "zkit.cli", "--project", str(PROJECT), *args],
                          cwd=ROOT, env=env).returncode


def main():
    if sys.version_info < (3, 11):
        fail(f"This needs Python 3.11 or newer; this is {platform.python_version()}. Get it from "
             "https://www.python.org/downloads/ (on Windows, run it as `py build.py`).")
    if sys.argv[1:2] == ["zkit"]:
        if not env_python().is_file():
            setup(ZKIT)  # only when missing: never replaces a zkit installed with --zkit
        return zkit(*sys.argv[2:])
    parser = argparse.ArgumentParser(description="Build the Xenoblade Chronicles 2 decompilation.",
                                     epilog="`python build.py zkit ARGS...` runs the build's zkit.")
    parser.add_argument("--rom", type=Path, action="append", metavar="FOLDER",
                        help="a folder holding the game's .nsp or .xci files (searched with its subfolders)")
    parser.add_argument("--keys", type=Path, metavar="FILE", help="prod.keys, if no emulator here has it")
    parser.add_argument("--zkit", default=ZKIT, metavar="SPEC",
                        help="install this zkit instead of the pinned one (a pip requirement or a local checkout)")
    parser.add_argument("--ghidra", action="store_true",
                        help="also install pyghidra for `zkit decompile`, from now on (Ghidra 11.3+ is separate)")
    args = parser.parse_args()

    if not (args.rom or args.keys or has_game()):
        fail("The game is missing. Put your copy of Xenoblade Chronicles 2 in the rom/ folder: the files of the\n"
             "game and its 3.0.1 update (.nsp or .xci), and prod.keys unless an emulator on this computer has it.\n"
             "Or point the build at the folder they are in:\n"
             "  python build.py --rom <folder>")
    check_host()
    setup(args.zkit, args.ghidra)
    if args.rom or args.keys:
        found = zkit("extract", *[str(folder.expanduser().resolve()) for folder in args.rom or []],
                     *(["--keys", str(args.keys.expanduser().resolve())] if args.keys else []))
        if found != 0:
            return found
    return zkit("build", "--download-build-tools")


if __name__ == "__main__":
    sys.exit(main())
