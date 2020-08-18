# OsDialog

cmake_minimum_required(VERSION 3.1)
project(OsDialog)

set(OSDIALOG_SRC
    osdialog/osdialog.c
)

# TODO: Support more platforms
if (UNIX) 
    SET(OSDIALOG_SRC ${OSDIALOG_SRC} osdialog/osdialog_gtk3.c)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
elseif(WIN32)
    SET(OSDIALOG_SRC ${OSDIALOG_SRC} osdialog/osdialog_win.c)
else ()
    message(FATAL_ERROR "Platform not supported")
endif ()


include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_library(osdialog ${OSDIALOG_SRC})
target_link_libraries(osdialog ${GTK3_LIBRARIES})
target_include_directories(osdialog PUBLIC .)