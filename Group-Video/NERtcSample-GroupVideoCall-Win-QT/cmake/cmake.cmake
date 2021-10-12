#**Utils***************************************************************
include(cmake/Utils.cmake)

#**3rdparty************************************************************
include(cmake/3rdparty_lib.cmake)
include(cmake/3rdparty.cmake)

#**Enable Solution Folders*********************************************
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")