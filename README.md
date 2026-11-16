# Xenoblade Chronicles 2

A work-in-progress matching decompilation of Xenoblade Chronicles 2 for Nintendo Switch, version 3.0.1: the
final update, whose executable holds the code of the whole game and every DLC.

The goal is C++ source that compiles to the same code as the game's executable, function for function. This
repository contains no game code or assets; you need your own copy of the game.

## Progress

<!-- progress -->
| | Matched | Linked |
|:--|--:|--:|
| Code | 56.85% | 16.16% |
| Data | 24.90% | 13.59% |
| Functions | 31,759 of 35,531 | |
| Units | | 496 of 868 |
<!-- /progress -->

## Target

| | |
|---|---|
| Game | Xenoblade Chronicles 2, title `0100E95004038000`, with update `0100E95004038800` version 3.0.1 |
| Executable | `main` of the 3.0.1 update, SHA-1 `55a82580cd6826cfb9ffbbb2da5fe9a4c5a4b4c8` |
| Compiler | clang 3.9.1 (NintendoSDK 3.5.0) |

## Building

You need:

- **Python 3.11 or newer** ([python.org](https://www.python.org/downloads/); on Windows, type `py` where this says
  `python`).
- **A C++ compiler** on Linux (`g++`) or macOS (`xcode-select --install`). An Arm Mac also needs Rosetta 2
  (`softwareupdate --install-rosetta`). Windows needs nothing else.
- **Your own copy of the game**, dumped from your Switch: Xenoblade Chronicles 2 with the 3.0.1 update, as `.nsp`
  or `.xci` files, and your console's `prod.keys`.

Everything else (zkit, Ninja, the compilers the game was built with) the build downloads into `build/`.

### 1. Put the game in `rom/`

Copy your game files into the `rom/` folder, subfolders too: the game, its updates and DLC, as many as you have.
The build finds the 3.0.1 update among them and takes the executable out of it; the rest is ignored.

    rom/
        Xenoblade Chronicles 2 [0100E95004038000][v0].nsp
        Xenoblade Chronicles 2 [0100E95004038800][v1114112].nsp     <- the 3.0.1 update
        prod.keys

If you play on Ryujinx or yuzu (or suyu, sudachi, citron, eden), the build finds your keys by itself and
`prod.keys` can stay where it is. Compressed `.nsz` and `.xcz` files need decompressing first.

Already keep your games somewhere else? Point the build there instead: `python build.py --rom <folder>`.

### 2. Build

    python build.py

The first run sets up its tools and downloads the compilers (a few hundred MB, about 2 GB once unpacked into
`build/`) and takes a few minutes; later runs only rebuild what changed. The build compiles every source file with the game's own compiler (clang 3.9.1), compares each function
with the original, and then rebuilds the game's executable, `build/XC2_301/link/main.nso`, from the matching code,
checking it is identical to yours. Code that is not decompiled yet still comes from your copy, so a passing build
does not mean the decompilation is complete.

Three source files need a small plugin for the game's clang. The Windows build of clang 3.9.1 cannot load
plugins, so on Windows the build patches a copy of it the same way (`clang++-bare_return_atexit.exe`, beside it
in `build/compilers`) and compiles those files with that.

## Seeing the progress

- **Progress page.** Open `build/progress/index.html` in a browser: what is matched and linked, for the whole
  game, each folder and each file, down to every function, with search and filters. It works offline.
- **objdiff.** Download [objdiff](https://github.com/encounter/objdiff/releases) and open this folder in it. It
  shows each function next to the original and rebuilds a file when you save it.

The build runs on [zkit](https://github.com/zeroz41/zkit-gcnx); `python build.py zkit <command>` runs it, for
example `python build.py zkit progress`.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Source files go under `src/`, at the path of the original file they
recover; [docs/architecture.md](docs/architecture.md) describes how the executable is laid out.

## License

The source in this repository is released under the [MIT License](LICENSE). It covers this project's own work
only: Xenoblade Chronicles 2 and its code and data belong to their owners and are not part of it.
