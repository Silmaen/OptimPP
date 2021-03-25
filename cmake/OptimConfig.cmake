

# minimum version of compilers
SET(OPP_CLANG_MINIMAL 10.0)
SET(OPP_GCC_MINIMAL 8.0)
SET(OPP_MSVC_MINIMAL 1914)

# Set the common compiler flags
include("OptimsCXXFlags")


include("OptimDefinitions")
include("OptimTools")
include("OptimDocumentation")
