# Xenoblade Chronicles 2

A work-in-progress matching decompilation of Xenoblade Chronicles 2 for Nintendo Switch, version 1.0.0.

The goal is C++ source that compiles to the same code as the game's executable, function for function. This
repository contains no game code or assets; you need your own copy of the game.

## Progress

<!-- progress -->
| | Matched | Linked |
|:--|--:|--:|
| Code | 0.00% | 0.00% |
| Data | 0.00% | 0.00% |
| Functions | 0 of 49,907 | |
| Units | | 0 of 532 |
<!-- /progress -->

## Target

| | |
|---|---|
| Game | Xenoblade Chronicles 2, title `0100E95004038000`, version 1.0.0 (no update) |
| Executable | `main`, SHA-1 `87b95d0f9d58fd673f4ef6fb8560af6c4bd4bafe` |
| Compiler | clang 3.9.1 (NintendoSDK 3.5.0) |

## Building

You need your own dump of the game and Ninja.

1. Extract `main` from the game's ExeFS and place it at `orig/XC2_100/main`.
2. Install the build tooling, [zkit](https://github.com/zeroz41/gc-switch-tool-zkit), then run:

       zkit use xc2.project.json
       zkit build --download
       zkit build

The first build fetches the compiler and tools into `build/`. Each build writes the match report to
`build/XC2_100/report.json`; open the folder in [objdiff](https://github.com/encounter/objdiff) to compare
functions.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Source files go under `src/`, at the path of the original file they
recover; [docs/architecture.md](docs/architecture.md) describes how the executable is laid out.
