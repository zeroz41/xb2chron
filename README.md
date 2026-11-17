# Xenoblade Chronicles 2

A decompilation of *Xenoblade Chronicles 2* for Nintendo Switch, version 3.0.1: C++ source that compiles to
exactly the same code as the game, function for function. 3.0.1, the game's final update, is the only version it
targets. It is a work in progress, and help is welcome.

This repository contains no game files. To build it you need your own copy of the game (see [Legal](#legal)).

## Progress

[![Code matched]][progress page] [![Data matched]][progress page] [![Functions matched]][progress page]<br>
[![Code linked]][progress page] [![Data linked]][progress page] [![Units linked]][progress page]

[progress page]: https://zeroz41.github.io/xb2chron/
[treemap]: https://zeroz41.github.io/xb2chron/treemap.html
[Code matched]: https://img.shields.io/endpoint?url=https%3A%2F%2Fzeroz41.github.io%2Fxb2chron%2Fbadges%2Fcode.json
[Data matched]: https://img.shields.io/endpoint?url=https%3A%2F%2Fzeroz41.github.io%2Fxb2chron%2Fbadges%2Fdata.json
[Functions matched]: https://img.shields.io/endpoint?url=https%3A%2F%2Fzeroz41.github.io%2Fxb2chron%2Fbadges%2Ffunctions.json
[Code linked]: https://img.shields.io/endpoint?url=https%3A%2F%2Fzeroz41.github.io%2Fxb2chron%2Fbadges%2Fcode-linked.json
[Data linked]: https://img.shields.io/endpoint?url=https%3A%2F%2Fzeroz41.github.io%2Fxb2chron%2Fbadges%2Fdata-linked.json
[Units linked]: https://img.shields.io/endpoint?url=https%3A%2F%2Fzeroz41.github.io%2Fxb2chron%2Fbadges%2Funits-linked.json

Updated every time `master` changes. The [progress page] lists every folder, file and function, and the
[treemap] shows them all at once, each as a tile sized by its bytes.

- **Matched**: the source compiles to exactly the original's bytes.
- **Linked**: the build takes it from the compiled source instead of from the original game.

## Building

### What you need

**1. Python 3.11 or newer.**

- Windows: install it from [python.org](https://www.python.org/downloads/).
- macOS: install it from [python.org](https://www.python.org/downloads/). The `python3` that comes with macOS is
  too old.
- Linux: check with `python3 --version`. On Debian and Ubuntu, also run `sudo apt install python3-venv`.
  Ubuntu 22.04 has Python 3.10, which is too old: run `sudo apt install python3.11 python3.11-venv` and type
  `python3.11` wherever this page says `python3`.

**2. A C++ compiler** (macOS and Linux only; Windows needs nothing else).

- macOS: run `xcode-select --install`. On a Mac with an Apple chip (M1 or later), also run
  `softwareupdate --install-rosetta --agree-to-license`.
- Linux: Debian and Ubuntu `sudo apt install g++`, Fedora `sudo dnf install gcc-c++`, Arch `sudo pacman -S gcc`.

**3. The game's 3.0.1 update file, from your own Switch.** On the Switch, Xenoblade Chronicles 2 comes in two
parts: the game itself (about 14 GB) and an update (about 180 MB) that brings it to version 3.0.1, its final
version. The build needs only the update file, because the update holds the game's complete code. Dump it from your
Switch as an `.nsp` file with a homebrew tool such as [nxdumptool](https://github.com/DarkMatterCore/nxdumptool).
Its title ID is `0100E95004038800`; version 3.0.1 shows as `v1114112` in file names. An `.xci` that contains the
update works too. It has to be 3.0.1: the build does not work with any other version.

**4. Your Switch's keys file, `prod.keys`.** If you already play Switch games on an emulator (Ryujinx, yuzu,
suyu, sudachi, citron or eden), you have it, and the build finds it by itself.

**5. About 3 GB of free disk space.** The build downloads everything else it needs (zkit, Ninja and the compilers
the game was made with) into the `build/` folder.

### Steps

**1. Get this repository.** On GitHub, click **Code → Download ZIP** and unzip it, or clone it with git:

    git clone https://github.com/zeroz41/xb2chron

**2. Put the update file in the `rom/` folder**, and `prod.keys` with it unless an emulator has it:

    rom/
        Xenoblade Chronicles 2 [0100E95004038800][v1114112].nsp
        prod.keys

The file names do not matter: the build checks what is inside. Anything else in `rom/` (the base game, DLC, other
versions) is ignored. Compressed `.nsz` and `.xcz` files have to be decompressed first.

**3. Open a terminal in the repository's folder and run the build.**

| | Open a terminal there | Then run |
|---|---|---|
| Windows | in File Explorer, open the folder, type `cmd` in the address bar and press Enter | `py build.py` |
| macOS | open Terminal, type `cd ` (with the space), drag the folder into the window and press Enter | `python3 build.py` |
| Linux | in your file manager, right-click the folder and choose **Open in Terminal** (or `cd` into it) | `python3 build.py` |

The first build sets up its tools and downloads the compilers, which takes a while; later builds only rebuild
what changed. The build is done when it prints `build: ok`. That means every source file compiled with the
game's own compiler, and the game's executable rebuilt from them (`build/XC2_301/link/main.nso`) is identical to
yours. Code that is not decompiled yet still comes from your copy, so `build: ok` does not mean the decompilation
is finished.

If your game files are somewhere else, point the build at that folder instead of copying them:
`python3 build.py --rom <folder>` (on Windows, `py build.py --rom <folder>`). For a `prod.keys` somewhere else,
add `--keys <file>`.

### If something goes wrong

- The build stops with a message that says what is missing and how to fix it.
- To start over from scratch, delete the `build/` folder and run the build again.
- The build is tested on Linux. Windows and macOS (Intel and Apple chips) are supported but have not been tested
  on real machines yet. If the build fails for you, [open an issue](https://github.com/zeroz41/xb2chron/issues)
  and paste its whole output.

## Target

| | |
|---|---|
| Game | Xenoblade Chronicles 2 (`0100E95004038000`), update 3.0.1 (`0100E95004038800`, `v1114112`) |
| Executable | `main` of the 3.0.1 update, SHA-1 `55a82580cd6826cfb9ffbbb2da5fe9a4c5a4b4c8` |
| Compiler | clang 3.9.1 (NintendoSDK 3.5.0) |

3.0.1 is the only target. Versions 1.0.0 and 2.0.0 are used only for the original names they still contain
([Names](docs/architecture.md#names)); nothing is built for them.

## Seeing the progress

- **On your machine.** After a build, open `build/progress/index.html` in a browser for the same page as the
  [progress page], and `build/progress/treemap.html` for the treemap. They work offline.
- **Function by function.** Download [objdiff](https://github.com/encounter/objdiff/releases) and open this folder
  in it. It shows each function next to the original and rebuilds a file when you save it.

## Contributing

Help is welcome: matching functions, defining data so files link, naming things, and cleaning up matched code.
Start with [CONTRIBUTING.md](CONTRIBUTING.md): how to work on a function, the checks to run, and the rules.
[docs/architecture.md](docs/architecture.md) explains how the game's code is organised in this repository.
Questions and problems go in [issues](https://github.com/zeroz41/xb2chron/issues).

The build's tools come from [zkit](https://github.com/zeroz41/zkit-gcnx): `python3 build.py zkit <command>` runs
one (on Windows, `py build.py zkit <command>`).

## Credits

Built with [zkit](https://github.com/zeroz41/zkit-gcnx), [objdiff](https://github.com/encounter/objdiff),
[LLVM](https://llvm.org/) and [Ninja](https://ninja-build.org/). The game links zlib, libc++, the Mersenne Twister
and dlmalloc; the source that rebuilds them keeps their notices, listed in [third_party/](third_party/README.md).

## Legal

This repository contains no game files, no game assets and no assembly copied from the game. The source is written
for this project, or adapted from the open-source projects credited above, to compile into the same machine code as
the original; the tables and strings the code itself uses are written out in it, as matching requires. Everything
else the build needs comes from your own legally obtained copy of the game, on your machine, when you build.

*Xenoblade Chronicles* is a trademark of Nintendo. This project is not affiliated with or endorsed by Nintendo or
Monolith Soft.

## License

[MIT](LICENSE), for this project's own work. The files adapted from other projects keep their own licences, listed
in [third_party/](third_party/README.md). Xenoblade Chronicles 2 and its code and data belong to their owners and
are not part of this project.
