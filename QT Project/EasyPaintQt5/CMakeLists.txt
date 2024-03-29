cmake_minimum_required (VERSION 2.6)

# set project's name
set (PROJECT easypaint)

# you can uncomment/modify the command below if all of your teammates install same Qt in the same directory.
# set (CMAKE_PREFIX_PATH "C:/Qt/Qt5.9.1/5.9.1/msvc2017_64")

message(STATUS "System: " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

# add version define
set(EASYPAINT_VERSION 0.1.1)

#------- headers --------
set (HEADERS
    sources/mainwindow.h
    sources/easypaintenums.h
    sources/imagearea.h
    sources/datasingleton.h
    sources/additionaltools.h
    sources/effects/abstracteffect.h
    sources/effects/negativeeffect.h
    sources/effects/grayeffect.h
    sources/effects/binarizationeffect.h
    sources/effects/customeffect.h
    sources/effects/effectwithsettings.h
    sources/effects/gammaeffect.h
    sources/effects/gaussianblureffect.h
    sources/effects/sharpeneffect.h
    sources/undocommand.h
    sources/widgets/toolbar.h
    sources/widgets/colorchooser.h
    sources/widgets/palettebar.h
    sources/widgets/palettebutton.h
    sources/widgets/shortcutedit.h
    sources/widgets/abstracteffectsettings.h
    sources/widgets/customfiltersettings.h
    sources/widgets/sharpenfiltersettings.h
    sources/widgets/gaussianblurfiltersettings.h
    sources/widgets/imagepreview.h
    sources/dialogs/resizedialog.h
    sources/dialogs/settingsdialog.h
    sources/dialogs/textdialog.h
    sources/dialogs/effectsettingsdialog.h
    sources/instruments/abstractinstrument.h
    sources/instruments/abstractselection.h
    sources/instruments/selectioninstrument.h
    sources/instruments/pencilinstrument.h
    sources/instruments/lineinstrument.h
    sources/instruments/eraserinstrument.h
    sources/instruments/rectangleinstrument.h
    sources/instruments/ellipseinstrument.h
    sources/instruments/fillinstrument.h
    sources/instruments/sprayinstrument.h
    sources/instruments/magnifierinstrument.h
    sources/instruments/colorpickerinstrument.h
    sources/instruments/curvelineinstrument.h
    sources/instruments/textinstrument.h
	sources/instruments/dashlineinstrument.h
	sources/instruments/triangleinstrument.h 
	sources/instruments/signatureinstrument.h )

#------- sources --------
set (SOURCES
    sources/main.cpp
    sources/mainwindow.cpp
    sources/imagearea.cpp
    sources/datasingleton.cpp
    sources/additionaltools.cpp
    sources/effects/abstracteffect.cpp
    sources/effects/negativeeffect.cpp
    sources/effects/grayeffect.cpp
    sources/effects/binarizationeffect.cpp
    sources/effects/effectwithsettings.cpp
    sources/effects/gammaeffect.cpp
    sources/undocommand.cpp
    sources/widgets/toolbar.cpp
    sources/widgets/colorchooser.cpp
    sources/widgets/palettebar.cpp
    sources/widgets/palettebutton.cpp
    sources/widgets/shortcutedit.cpp
    sources/widgets/customfiltersettings.cpp
    sources/widgets/sharpenfiltersettings.cpp
    sources/widgets/gaussianblurfiltersettings.cpp
    sources/widgets/imagepreview.cpp
    sources/dialogs/resizedialog.cpp
    sources/dialogs/settingsdialog.cpp
    sources/dialogs/textdialog.cpp
    sources/dialogs/effectsettingsdialog.cpp
    sources/instruments/abstractinstrument.cpp
    sources/instruments/abstractselection.cpp
    sources/instruments/selectioninstrument.cpp
    sources/instruments/pencilinstrument.cpp
    sources/instruments/lineinstrument.cpp
    sources/instruments/eraserinstrument.cpp
    sources/instruments/rectangleinstrument.cpp
    sources/instruments/ellipseinstrument.cpp
    sources/instruments/fillinstrument.cpp
    sources/instruments/sprayinstrument.cpp
    sources/instruments/magnifierinstrument.cpp
    sources/instruments/colorpickerinstrument.cpp
    sources/instruments/curvelineinstrument.cpp
    sources/instruments/textinstrument.cpp
	sources/instruments/dashlineinstrument.cpp
	sources/instruments/triangleinstrument.cpp 
	sources/instruments/signatureinstrument.cpp)

#------- resources -------
set (RESOURCE_PATH
    sources)

set (RESOURCES
    ${RESOURCE_PATH}/resources.qrc)

project (${PROJECT})

include_directories (./)

find_package (Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
qt5_add_resources (QRC_SOURCES ${RESOURCES})
qt5_wrap_cpp (MOC_SOURCES ${HEADERS})

add_definitions (-Wall)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})
source_group ("Generated Files" FILES ${MOC_SOURCES})
source_group ("Resource Files" FILES ${QRC_SOURCES})

#-------  build executable from sources ----------
add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})

target_link_libraries (${PROJECT} ${Qt5PrintSupport_LIBRARIES})

#-------  installing ----------
if(UNIX AND NOT APPLE)
    # installing
    INSTALL(TARGETS easypaint RUNTIME DESTINATION bin)

    # install desktop files
    INSTALL(FILES "sources/media/easypaint.desktop" DESTINATION share/applications)

    # install pixmap
    INSTALL(FILES "sources/media/logo/easypaint_64.png" DESTINATION share/pixmaps)
endif(UNIX AND NOT APPLE)
