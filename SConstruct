#!/usr/bin/env python
import os


def normalize_path(val, env):
    return val if os.path.isabs(val) else os.path.join(env.Dir("#").abspath, val)


def validate_parent_dir(key, val, env):
    if not os.path.isdir(normalize_path(os.path.dirname(val), env)):
        raise UserError("'%s' is not a directory: %s" % (key, os.path.dirname(val)))


libname = "adxle"
projectdir = "godot-proj"

localEnv = Environment(tools=["default"], PLATFORM="")

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Add(
    BoolVariable(
        key="compiledb",
        help="Generate compilation DB (`compile_commands.json`) for external tools",
        default=localEnv.get("compiledb", False),
    )
)
opts.Add(
    PathVariable(
        key="compiledb_file",
        help="Path to a custom `compile_commands.json` file",
        default=localEnv.get("compiledb_file", "compile_commands.json"),
        validator=validate_parent_dir,
    )
)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()
env["compiledb"] = False

env.Tool("compilation_db")
compilation_db = env.CompilationDatabase(
    normalize_path(localEnv["compiledb_file"], localEnv)
)
env.Alias("compiledb", compilation_db)

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs})

if env["platform"] == "windows":
    cri_headers_path = "cri/pc/include"
    cri_libs_path = "cri/pc/libs/x64"
    cri_libs_file = "cri_ware_pcx64_le_import.lib"
elif env["platform"] == "macos":
    cri_headers_path = "cri/macosx/include"
    cri_libs_path = "cri/macosx/libs"
    cri_libs_file = "libcri_ware_macosx_LE.a"
elif env["platform"] == "ios":
    cri_headers_path = "cri/ios/include"
    cri_libs_path = "cri/ios/libs"
    cri_libs_file = "libcri_ware_ios_LE.a"
elif env["platform"] == "android":
    android_arch_table = {"arm32": "armeabi-v7a", "arm64": "arm64-v8a", "x86_64": "x86_64"}
    cri_headers_path = "cri/android/include"
    cri_libs_path = "cri/android/libs/" + android_arch_table[env["arch"]]
    cri_libs_file = "libcri_ware_android_LE.so"

env.Append(CPPPATH=[cri_headers_path])
env.Append(LIBPATH=[cri_libs_path])
env.Append(LIBS=[cri_libs_file])

sources = Glob("src/*.cpp")

libfile = f"lib{libname}.{env['arch']}{env['SHLIBSUFFIX']}"

# if env["platform"] == "macos" or env["platform"] == "ios":
#     libfile = f"{libname}.framework/{env['platform']}/{libname}"

if env["platform"] == "ios":
    env.Append(LINKFLAGS=[
        "-framework", "Foundation",
        "-framework", "CoreServices",
        "-framework", "AVFoundation",
        "-framework", "AudioToolbox",
        "-framework", "UIKit",
    ])

library = env.SharedLibrary(
    f"bin/{env['platform']}/{libfile}",
    source=sources,
)

copy = env.InstallAs(
    f"{projectdir}/addons/{libname}/bin/{env['platform']}/{libfile}", 
    library
)

default_args = [library, copy]
if localEnv.get("compiledb", False):
    default_args += [compilation_db]
Default(*default_args)