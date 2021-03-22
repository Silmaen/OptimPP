

# minimum version of compilers
SET(OPP_CLANG_MINIMAL 10.0)
SET(OPP_GCC_MINIMAL 10.0)
SET(OPP_MSVC_MINIMAL 1914)

# system includes
include(c++-standards)

# Set the common compiler flags
include("OptimsCXXFlags")
include("OptimDefinitions")
