project()


find_package()\
basic signature: //some properties \
search mode:\
    module mode: search for a file called Find<PackageName>.cmake\
        Find<PackageName>.cmake file is not typically provided by the package itself, rather by some external, such as operating system\
        CMAKE_MODILE_PATH\
config mode:\
    In this mode, CMake searches for a file called <lowercasePackageName>-config.cmake or <PackageName>Config.cmake. It will also look for <lowercasePackageName>-config-version.cmake or <PackageName>ConfigVersion.cmake


include_directory : 全局包含include头文件\
target_include_directory(target "xxx") : 目标相关include头文件

target_link_library : 声明目标间依赖关系