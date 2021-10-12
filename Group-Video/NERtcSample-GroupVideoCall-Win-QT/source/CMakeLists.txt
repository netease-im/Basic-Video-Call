#
set(AppName 1vn)

#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#definitions
#add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES -DGOOGLE_GLOG_DLL_DECL=)

# Qt
find_package(Qt5Widgets)
if(NOT Qt5Widgets_FOUND)
    return()
endif()

find_package(Qt5Core)
if(NOT Qt5Core_FOUND)
    return()
endif()

find_package(Qt5Gui)
if(NOT Qt5Gui_FOUND)
    return()
endif()

find_package(Qt5OpenGL)
if(NOT Qt5OpenGL_FOUND)
    return()
endif()

find_package(Qt5Network)
if(NOT Qt5Network_FOUND)
    return()
endif()
#
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
#
include_directories(${NERTC_INCLUDE_DIR})
link_directories(${NERTC_LIBRARY_DIRS})
#
include_directories(${JSONCPP_INCLUDE_DIR})
link_directories(${JSONCPP_LIBRARY_DIRS})
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# source code
#
file(GLOB_RECURSE demo_srcs "*.cpp" "*.c")
file(GLOB_RECURSE demo_hdrs "*.hpp" "*.h")
set(qrcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/resource/image.qrc)

#
source_group_by_dir(demo_srcs)
source_group_by_dir(demo_hdrs)

# execute
add_executable(${AppName} ${demo_srcs} ${demo_hdrs} ${qrcs})

# link
set(dependend_LIB
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
	${Qt5Gui_LIBRARIES}
	${Qt5OpenGL_LIBRARIES}
	${Qt5Network_LIBRARIES}
    nertc_sdk
	jsoncpp
)
target_link_libraries(${AppName} ${dependend_LIB})