cmake_minimum_required(VERSION 3.16)

project(Procesamiento_Imagenes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

if(WIN32)
    # Windows: buscar OpenCV en ubicaciones comunes
    set(OpenCV_DIR "C:/opencv/build" CACHE PATH "Directorio de OpenCV")
    find_package(OpenCV REQUIRED)
    
    if(OpenCV_FOUND)
        message(STATUS "OpenCV encontrado: ${OpenCV_VERSION}")
        message(STATUS "OpenCV librerías: ${OpenCV_LIBS}")
    else()
        message(FATAL_ERROR "OpenCV no encontrado. Instálalo o establece OpenCV_DIR")
    endif()
    
elseif(UNIX AND NOT APPLE)
    # Linux (Debian/Ubuntu): usar pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(OpenCV REQUIRED opencv4)
    
    # Convertir pkg-config a variables CMake
    set(OpenCV_LIBS ${OpenCV_LDFLAGS})
    set(OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS})
    set(OpenCV_FOUND ${OpenCV_FOUND})
    
elseif(APPLE)
    # macOS: usar Homebrew o MacPorts
    find_package(OpenCV REQUIRED)
endif()

set(TS_FILES Procesamiento_Imagenes_es_MX.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Image.h
    Image.cpp
    Pixel.h
    Pixel.cpp
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Procesamiento_Imagenes
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Pixel.h Pixel.cpp
        Image.h Image.cpp
        dialog.h dialog.cpp dialog.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Procesamiento_Imagenes APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Procesamiento_Imagenes SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Procesamiento_Imagenes
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_include_directories(Procesamiento_Imagenes PRIVATE
    src/
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(Procesamiento_Imagenes PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    ${OpenCV_LDFLAGS}
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Procesamiento_Imagenes)
endif()
set_target_properties(Procesamiento_Imagenes PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Procesamiento_Imagenes
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Procesamiento_Imagenes)
endif()

if(WIN32)
    # Copiar DLLs de OpenCV automáticamente
    if(OpenCV_FOUND)
        add_custom_command(TARGET Procesamiento_Imagenes POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Procesamiento_Imagenes>/opencv_dlls
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${OpenCV_DIR}/bin/opencv_core${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${CMAKE_SHARED_LIBRARY_SUFFIX}"
                $<TARGET_FILE_DIR:Procesamiento_Imagenes>/opencv_dlls/
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${OpenCV_DIR}/bin/opencv_imgproc${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${CMAKE_SHARED_LIBRARY_SUFFIX}"
                $<TARGET_FILE_DIR:Procesamiento_Imagenes>/opencv_dlls/
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${OpenCV_DIR}/bin/opencv_imgcodecs${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${CMAKE_SHARED_LIBRARY_SUFFIX}"
                $<TARGET_FILE_DIR:Procesamiento_Imagenes>/opencv_dlls/
            COMMAND ${CMAKE_COMMAND} -E echo "OpenCV DLLs copiadas a $<TARGET_FILE_DIR:Procesamiento_Imagenes>/opencv_dlls/"
        )
    endif()
endif()

# Propiedades del objetivo
set_target_properties(Procesamiento_Imagenes PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE FALSE
)

# Finalización para Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Procesamiento_Imagenes)
endif()
