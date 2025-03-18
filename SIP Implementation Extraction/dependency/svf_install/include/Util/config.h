#ifndef CONFIG_H_IN
#define CONFIG_H_IN

// Directory structure of SVF build
#define SVF_ROOT "/home/dyd/software/SVF"
#define SVF_BUILD_DIR "/home/dyd/software/SVF/build"
#define SVF_INSTALL_DIR "/home/dyd/software/SVF/install"
#define SVF_BIN_DIR "/home/dyd/software/SVF/install/bin"
#define SVF_LIB_DIR "/home/dyd/software/SVF/install/lib"
#define SVF_INCLUDE_DIR "/home/dyd/software/SVF/install/include"
#define SVF_EXTAPI_DIR "/home/dyd/software/SVF/install/lib"
#define SVF_EXTAPI_BC "/home/dyd/software/SVF/install/lib/extapi.bc"

// Build mode used to build SVF
#define SVF_BUILD_TYPE ""

// Sanitiser mode used for building SVF
/* #undef SVF_SANITIZE */

// Build options used when building SVF
/* #undef SVF_COVERAGE */
#define SVF_WARN_AS_ERROR
/* #undef SVF_EXPORT_DYNAMIC */
/* #undef SVF_ENABLE_ASSERTIONS */

#endif // CONFIG_H_IN
