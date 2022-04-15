project(bezier)

cmake_minimum_required(VERSION 2.8.9)
cmake_policy(SET CMP0043 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

IF(WIN32)
    #get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
    #get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    set(_qt_bin_dir "${Qt5_DIR}/../bin")
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
    #find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
ENDIF()

find_package(Qt5 COMPONENTS OpenGL REQUIRED)

find_package(OpenGL REQUIRED)

add_definitions(-DGL_SILENCE_DEPRECATION -DGLM_FORCE_SILENT_WARNINGS)

FILE(GLOB_RECURSE
    folder_source
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

FILE(GLOB_RECURSE
    folder_header
    ${CMAKE_SOURCE_DIR}/src/*.h

)

FILE(GLOB_RECURSE
    folder_ui
    ${CMAKE_SOURCE_DIR}/src/*.ui
)

include_directories(
   ${CMAKE_SOURCE_DIR}/src
   ${CMAKE_SOURCE_DIR}/includes/
)

SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})
SOURCE_GROUP("Shader Files" FILES ${folder_shader})


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON )


add_executable(bezier
               ${folder_source}
               ${folder_header}
               ${folder_ui}
               )

IF (WIN32)
    add_custom_command(TARGET bezier POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
                "$<TARGET_FILE:bezier>"
        COMMENT "Running windeployqt..."
    )
ENDIF()

add_custom_command(TARGET bezier POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/Shaders/ ${CMAKE_SOURCE_DIR}/bin/
)

set(EXT_LIBS Qt5::OpenGL ${OPENGL_LIBRARIES})

target_link_libraries(bezier ${EXT_LIBS} )