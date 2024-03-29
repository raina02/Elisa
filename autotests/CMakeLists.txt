enable_testing()

configure_file(mediaplaylisttestconfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/mediaplaylisttestconfig.h @ONLY)

include_directories(${elisa_CURRENT_BINARY_DIR})
include_directories(${elisa_BINARY_DIR})
include_directories(${elisa_BINARY_DIR}/src)

set(viewManagerTest_SOURCES
    viewmanagertest.cpp
    ../src/elisautils.cpp
)

ecm_add_test(${viewManagerTest_SOURCES}
    TEST_NAME "viewManagerTest"
    LINK_LIBRARIES
        Qt5::Test elisaLib)

target_include_directories(viewManagerTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(databaseInterfaceTest_SOURCES
    databaseinterfacetest.cpp
    databasetestdata.h
)

ecm_add_test(${databaseInterfaceTest_SOURCES}
    TEST_NAME "databaseInterfaceTest"
    LINK_LIBRARIES
        Qt5::Test elisaLib)

target_include_directories(databaseInterfaceTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(managemediaplayercontrolTest_SOURCES
    managemediaplayercontroltest.cpp
    ../src/elisautils.cpp
)

ecm_add_test(${managemediaplayercontrolTest_SOURCES}
    TEST_NAME "managemediaplayercontrolTest"
    LINK_LIBRARIES
        Qt5::Test elisaLib
)

set(manageheaderbarTest_SOURCES
    manageheaderbartest.cpp
    ../src/elisautils.cpp
)

ecm_add_test(${manageheaderbarTest_SOURCES}
    TEST_NAME "manageheaderbarTest"
    LINK_LIBRARIES
        Qt5::Test elisaLib
)

target_include_directories(manageheaderbarTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(manageaudioplayerTest_SOURCES
    manageaudioplayertest.cpp
)

ecm_add_test(${manageaudioplayerTest_SOURCES}
    TEST_NAME "manageaudioplayerTest"
    LINK_LIBRARIES Qt5::Test elisaLib
)

target_include_directories(manageaudioplayerTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(mediaplaylistTest_SOURCES
    mediaplaylisttest.cpp
    ../src/elisautils.cpp
)

ecm_qt_declare_logging_category(mediaplaylistTest_SOURCES HEADER elisa_debug.h IDENTIFIER lcModelTest CATEGORY_NAME qt.modeltest)

ecm_add_test(${mediaplaylistTest_SOURCES}
    TEST_NAME "mediaplaylistTest"
    LINK_LIBRARIES
        Qt5::Test elisaLib Qt5::CorePrivate
)

target_include_directories(mediaplaylistTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(trackslistenertest_SOURCES
    trackslistenertest.cpp
    ../src/elisautils.cpp
)

ecm_add_test(${trackslistenertest_SOURCES}
    TEST_NAME "trackslistenertest"
    LINK_LIBRARIES
        Qt5::Test elisaLib
)

target_include_directories(trackslistenertest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(datamodeltest_SOURCES
    datamodeltest.cpp
)

ecm_qt_declare_logging_category(datamodeltest_SOURCES HEADER elisa_debug.h IDENTIFIER lcModelTest CATEGORY_NAME qt.modeltest)

ecm_add_test(${datamodeltest_SOURCES}
    TEST_NAME "datamodeltest"
    LINK_LIBRARIES
        Qt5::Test elisaLib Qt5::CorePrivate
)

target_include_directories(datamodeltest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(trackmetadatamodeltest_SOURCES
    trackmetadatamodeltest.cpp
)

ecm_qt_declare_logging_category(trackmetadatamodeltest_SOURCES HEADER elisa_debug.h IDENTIFIER lcModelTest CATEGORY_NAME qt.modeltest)

ecm_add_test(${trackmetadatamodeltest_SOURCES}
    TEST_NAME "trackmetadatamodeltest"
    LINK_LIBRARIES
        Qt5::Test elisaLib Qt5::CorePrivate
)

target_include_directories(trackmetadatamodeltest PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(alltracksproxymodeltest_SOURCES
    alltracksproxymodeltest.cpp
)

ecm_qt_declare_logging_category(alltracksproxymodeltest_SOURCES HEADER elisa_debug.h IDENTIFIER lcModelTest CATEGORY_NAME qt.modeltest)

ecm_add_test(${alltracksproxymodeltest_SOURCES}
    TEST_NAME "alltracksproxymodeltest"
    LINK_LIBRARIES
        Qt5::Test elisaLib Qt5::CorePrivate
)

target_include_directories(alltracksproxymodeltest PRIVATE ${CMAKE_SOURCE_DIR}/src)

if (KF5FileMetaData_FOUND)
    set(localfilelistingtest_SOURCES
        localfilelistingtest.cpp
    )

    ecm_add_test(${localfilelistingtest_SOURCES}
        TEST_NAME "localfilelistingtest"
        LINK_LIBRARIES
            Qt5::Test elisaLib
    )

    target_include_directories(localfilelistingtest PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()

if (KF5XmlGui_FOUND AND KF5KCMUtils_FOUND)
    set(elisaapplicationtest_SOURCES
        elisaapplicationtest.cpp
        ../src/elisautils.cpp
    )

    ecm_add_test(${elisaapplicationtest_SOURCES}
        TEST_NAME "elisaapplicationtest"
        LINK_LIBRARIES
            Qt5::Test elisaLib
    )

    target_include_directories(elisaapplicationtest PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()

if (Qt5Quick_FOUND AND Qt5Widgets_FOUND AND NOT WIN32)
    set(elisaqmltests_SOURCES
        elisaqmltests.cpp
        qmltests/tst_GridBrowserDelegate.qml
        qmltests/tst_NavigationActionBar.qml
        qmltests/tst_PlayListEntry.qml
    )

    ecm_add_test(${elisaqmltests_SOURCES}
        TEST_NAME "elisaqmltests"
        LINK_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Test Qt5::QuickTest
        GUI)

    target_compile_definitions(elisaqmltests PRIVATE QUICK_TEST_SOURCE_DIR="${CMAKE_SOURCE_DIR}/autotests/qmltests")

    target_include_directories(elisaqmltests PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()

set(filescannerTest_SOURCES
    filescannertest.cpp
)

ecm_add_test(${filescannerTest_SOURCES}
    TEST_NAME "filescannerTest"
    LINK_LIBRARIES Qt5::Test elisaLib
)
