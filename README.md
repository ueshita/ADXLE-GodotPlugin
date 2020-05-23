# ADX2LE-GodotPlugin
A plugin of ADX2LE for GodotEngine


# How to Build

## Requiments

- python3
- Scons
- Visual Studio 2019

## Clone repos

```sh
git clone https://github.com/ueshita/ADX2LE-GodotPlugin.git
git submodule update --init --recursive
```

## Build godot-cpp libs

```sh
cd godot-cpp
scons platform=windows bits=32 generate_bindings=yes target=debug -j4
scons platform=windows bits=32 generate_bindings=yes target=release -j4
scons platform=windows bits=64 generate_bindings=yes target=debug -j4
scons platform=windows bits=64 generate_bindings=yes target=release -j4
```

## Make ADX2LE SDK

Download ADX2LE SDK package  
https://game.criware.jp/products/adx2-le/

Copy `cri` directory to repo root.

Setup ADX2LE SDK files

```sh
python make_sdk.py
```

`cri-godot` directory has made in repo root.

## Build VC Proj

Open `libadx2le_godot.sln` and build.

Output to `godot-proj/addons/adx2le/bin/win64/libadx2le_godot.64.dll`
