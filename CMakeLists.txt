cmake_minimum_required(VERSION 3.8)

project(elisa
    VERSION 0.4.80
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(REQUIRED_QT_VERSION "5.11.0")
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Network Qml Quick Test Sql Multimedia Svg Gui Widgets QuickTest Concurrent QuickControls2)

find_package(Qt5Core ${REQUIRED_QT_VERSION} CONFIG REQUIRED Private)

set(REQUIRED_KF5_VERSION "5.60.0")
find_package(ECM ${REQUIRED_KF5_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(FeatureSummary)
include(ECMAddAppIcon)
include(ECMAddTests)
include(ECMQtDeclareLoggingCategory)

if (NOT WIN32)
    find_package(Qt5DBus ${REQUIRED_QT_VERSION} CONFIG QUIET)
    set_package_properties(Qt5DBus PROPERTIES
        DESCRIPTION "Qt5 DBus is needed to provide MPris2 interface to allow remote control by the desktop workspace."
        TYPE OPTIONAL)
endif()

find_package(Qt5QuickWidgets ${REQUIRED_QT_VERSION} CONFIG QUIET)
set_package_properties(Qt5QuickWidgets PROPERTIES
    DESCRIPTION "Qt5 Quick Widgets is needed at runtime to provide the interface."
    TYPE RUNTIME)

find_package(Qt5QuickControls2 ${REQUIRED_QT_VERSION} CONFIG QUIET)
set_package_properties(Qt5QuickControls2 PROPERTIES
    DESCRIPTION "Qt5 Quick Controls version 2 is needed at runtime to provide the interface."
    TYPE RUNTIME)

if (ANDROID)
    find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG QUIET OPTIONAL_COMPONENTS AndroidExtras)
    set_package_properties(Qt5AndroidExtras PROPERTIES
        DESCRIPTION "Qt5 AndroidExtras is needed to provide the Android integration."
        TYPE REQUIRED)
endif()

find_package(KF5Kirigami2 ${REQUIRED_KF5_VERSION} CONFIG QUIET)

set_package_properties(KF5Kirigami2 PROPERTIES
    DESCRIPTION "KF5 Kirigami 2 is needed to provide the mobile UI components."
    TYPE REQUIRED)

find_package(KF5I18n ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5I18n PROPERTIES
    DESCRIPTION "KF5 text internationalization library."
    TYPE REQUIRED)

find_package(KF5Declarative ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5Declarative PROPERTIES
    DESCRIPTION "Integration of QML and KDE work spaces."
    TYPE RECOMMENDED)

find_package(KF5CoreAddons ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5CoreAddons PROPERTIES
    DESCRIPTION "Qt addon library with a collection of non-GUI utilities."
    TYPE REQUIRED)

if (NOT WIN32)
find_package(KF5Baloo ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5Baloo PROPERTIES
    DESCRIPTION "Baloo provides file searching and indexing."
    TYPE RECOMMENDED)
endif()

find_package(KF5FileMetaData ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5FileMetaData PROPERTIES
    DESCRIPTION "Provides a simple library for extracting metadata."
    TYPE RECOMMENDED)

find_package(KF5DocTools ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5DocTools PROPERTIES
    DESCRIPTION "Create documentation from DocBook library."
    TYPE OPTIONAL)

find_package(KF5XmlGui ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5XmlGui PROPERTIES
    DESCRIPTION "Framework for managing menu and toolbar actions."
    TYPE RECOMMENDED)

find_package(KF5Config ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5Config PROPERTIES
    DESCRIPTION "Persistent platform-independent application settings."
    TYPE REQUIRED)

find_package(KF5ConfigWidgets ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5ConfigWidgets PROPERTIES
    DESCRIPTION "Widgets for configuration dialogs."
    TYPE RECOMMENDED)

find_package(KF5Crash ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5Crash PROPERTIES
    DESCRIPTION "Graceful handling of application crashes."
    TYPE OPTIONAL)

if (NOT WIN32)
    find_package(KF5DBusAddons ${REQUIRED_KF5_VERSION} CONFIG QUIET)
    set_package_properties(KF5DBusAddons PROPERTIES
        DESCRIPTION "Convenience classes for D-Bus."
        TYPE OPTIONAL)
endif()

find_package(KF5KCMUtils ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5KCMUtils PROPERTIES
    DESCRIPTION "KF5 Utilities for KDE System Settings modules library."
    TYPE RECOMMENDED)

find_package(KF5Package ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5Package PROPERTIES
    DESCRIPTION "KF5 package management library needed to get the configuration dialogs."
    TYPE RECOMMENDED)

find_package(KF5KIO ${REQUIRED_KF5_VERSION} CONFIG QUIET)
set_package_properties(KF5KIO PROPERTIES
    DESCRIPTION "File management libraries used for file browsing."
    TYPE RECOMMENDED)

find_package(UPNPQT CONFIG QUIET)
set_package_properties(UPNPQT PROPERTIES
    DESCRIPTION "UPNP layer build with Qt 5. UPnP support is currently broken. You should probably avoid this dependency."
    URL "https://gitlab.com/homeautomationqt/upnp-player-qt"
    TYPE OPTIONAL)

if (UPNPQT_FOUND)
    message(WARNING "UPnP support is experimental and may not work.")
endif()

find_package(LIBVLC QUIET)
set_package_properties(LIBVLC PROPERTIES
    DESCRIPTION "libvlc allows to play music in Elisa (otherwise it will use QtMultimedia)"
    URL "https://www.videolan.org/vlc/libvlc.html"
    TYPE RECOMMENDED)

include(FeatureSummary)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)

if (CMAKE_SYSTEM_NAME STREQUAL Android)
    set(QT_QMAKE_EXECUTABLE "$ENV{Qt5_android}/bin/qmake")
endif()

configure_file(config-upnp-qt.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-upnp-qt.h )

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX ELISA
    VERSION_HEADER elisa-version.h)

add_subdirectory(src)
add_subdirectory(icons)
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
add_subdirectory(doc)

install(
    PROGRAMS org.kde.elisa.desktop
    DESTINATION ${XDG_APPS_INSTALL_DIR}
)

install(
    FILES org.kde.elisa.appdata.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)

if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/po")
    ki18n_install(po)
endif()

if (${ECM_VERSION} STRGREATER "5.58.0")
    install(FILES elisa.categories DESTINATION  ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
else()
    install(FILES elisa.categories DESTINATION ${KDE_INSTALL_CONFDIR})
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

