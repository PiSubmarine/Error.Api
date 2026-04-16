include("${PISUBMARINE_BUILD_SYSTEM}")

message("Adding library: ${PISUBMARINE_MODULE_NAME}")
add_library(${PISUBMARINE_MODULE_NAME} INTERFACE
        "../public/PiSubmarine/Error/Api/Error.h"
        "../public/PiSubmarine/Error/Api/ErrorCondition.h"
        "../public/PiSubmarine/Error/Api/MakeError.h"
        "../public/PiSubmarine/Error/Api/Result.h")
target_include_directories(${PISUBMARINE_MODULE_NAME} INTERFACE "../public")
PiSubmarineInitTarget(${PISUBMARINE_MODULE_NAME})
