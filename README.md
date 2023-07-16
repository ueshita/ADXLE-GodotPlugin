# ADXLE-GodotPlugin
A plugin of ADXLE for GodotEngine


# How to Build (Windows)

## Requiments

- python3
- Scons
- Visual Studio 2023

## Clone repos

```sh
git clone https://github.com/ueshita/ADXLE-GodotPlugin.git
git submodule update --init --recursive
```

## Get ADXLE SDK

Download ADXLE Native SDK package  
https://game.criware.jp/products/adx-le/

Copy `cri` directory to this repos root.

## Build the plugin

```sh
python build.py platform=windows
```

Output to `godot-proj/addons/adxle/bin/windows/libadxle.win64.dll`
