# Xenoblade Chronicles 2

A work-in-progress matching decompilation of *Xenoblade Chronicles 2* for the Nintendo Switch, version 3.0.1:
C++ source that compiles to the same code as the game's executable, function for function, in its original
translation units.

Nothing from the game is included here. You need your own copy of the game to build it; see [Legal](#legal).

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

Measured on `main` from the 3.0.1 update, in the latest build of `master`. The [progress page] breaks it down by
unit and function, and the [treemap] shows every function and data section as a tile sized by its bytes. A
function is matched when it compiles to the original's exact bytes. Code, data and units are linked when the build
takes them from compiled source instead of the original. Data includes `.bss`.

## Target

| | |
|---|---|
| Game | Xenoblade Chronicles 2 (`0100E95004038000`), update 3.0.1 (`0100E95004038800`, `v1114112`) |
| Executable | `main` from the 3.0.1 update, SHA-1 `55a82580cd6826cfb9ffbbb2da5fe9a4c5a4b4c8` |
| Compiler | clang 3.9.1 (NintendoSDK 3.5.0); clang 4.0.1 for most of `ssd/` |

3.0.1 is the only version built. Versions 1.0.0 and 2.0.0 only supply the original names
([Names](docs/architecture.md#names)).

## Building

You need Python 3.11 or newer, your own dump of the game and its 3.0.1 update, and your Switch's `prod.keys`. On
Linux and macOS you also need a C++ compiler (`g++`, or `xcode-select --install` on macOS).

1. Put the base game and the 3.0.1 update (NSP or XCI) and `prod.keys` in `rom/`.
2. Run:

       python3 build.py

   On Windows, `py build.py`.

The first build downloads [zkit](https://github.com/zeroz41/zkit-gcnx), Ninja and the compilers into `build/`.
The build finds the 3.0.1 executable in your files by its SHA-1, whatever they are named. If they are somewhere
else, pass `--rom <folder>`; `--keys <file>` points it at a `prod.keys` that is not in `rom/` or an emulator's
folder.

The build rebuilds `main` as `build/XC2_301/link/main.nso` and checks it against the original's SHA-1. Code that is
not decompiled yet still comes from the original, so a passing build does not mean the decompilation is complete.

## Objdiff and the progress page

- **objdiff.** Download [objdiff](https://github.com/encounter/objdiff/releases) and open the repository folder
  in it. It reads the `objdiff.json` the build writes, rebuilds a unit when you save its source and shows each
  function next to the original.
- **Progress page.** Every build also writes `build/progress/index.html` and `build/progress/treemap.html`, the
  pages the [progress page] and [treemap] links show for `master`.

## Working on it

- **Check for regressions.** Run `python3 build.py zkit progress --save` before a change and
  `python3 build.py zkit ci check --base master` after it, the same check CI runs on every pull request. It
  rebuilds, compares the reports by original address, so renaming or moving functions never hides a lost match,
  and checks the added lines and files.

[CONTRIBUTING.md](CONTRIBUTING.md) covers what a change can do and the rules for it.
[docs/architecture.md](docs/architecture.md) describes how the executable and the source tree are laid out.

## Credits

Built with [zkit](https://github.com/zeroz41/zkit-gcnx), [objdiff](https://github.com/encounter/objdiff),
[LLVM](https://llvm.org/) and [Ninja](https://ninja-build.org/). The game links zlib, libc++, the Mersenne Twister
and dlmalloc; [third_party/](third_party/README.md) lists the source adapted from them.

## Legal

This repository contains no game assets, no game files and no assembly or code copied from the game. The source was
written for this project, or adapted from the open-source projects credited above, to compile into the same machine
code as the original; the tables and strings the code uses are written out in it, as matching requires. Everything
else the build needs comes from your own legally obtained copy of the game, on your machine, when you build.

*Xenoblade Chronicles* is a trademark of Nintendo. This project is not affiliated with or endorsed by Nintendo or
Monolith Soft.

## License

[MIT](LICENSE). Code adapted from other projects keeps its own licence; [third_party/](third_party/README.md) lists
them.
