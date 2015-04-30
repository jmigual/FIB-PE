#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T12:31:45
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = PE

CONFIG   += console c++14
CONFIG   -= app_bundle

TEMPLATE = app

Release {
    DESTDIR = release
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
}

Debug {
    DESTDIR = debug
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
}



#---------
# FILES
#---------


SOURCES += main.cpp \
    mainclass.cpp

HEADERS += \
    mainclass.h


# To copy files
win32 {
Release {
    OTHER_FILES += \
        Libraries/OpenSSl/libeay32.dll \
        Libraries/OpenSSl/libssl32.dll \
        Libraries/OpenSSL/ssleay32.dll
}
Debug {
    OTHER_FILES += \
        Libraries/OpenSSL/libeay32.dll \
        Libraries/OpenSSL/libssl32.dll \
        Libraries/OpenSSL/ssleay32.dll
}
}

win32 {
    DESTDIR_WIN = $${DESTDIR}
    DESTDIR_WIN ~= s,/,\\,g
    PWD_WIN = $${PWD}
    PWD_WIN ~= s,/,\\,g
    for(FILE, OTHER_FILES){
        FILE ~= s,/,\\,g
        QMAKE_POST_LINK += $$quote(cmd /c copy /y $${PWD_WIN}\\$${FILE} $${DESTDIR_WIN}$$escape_expand(\\n\\t))
    }
}
unix {
    for(FILE, OTHER_FILES){
        QMAKE_POST_LINK += $$quote(cp $${PWD}/$${FILE} $${DESTDIR}$$escape_expand(\\n\\t))
    }
}


#----------------------
# DEPLOY CONFIGURATION
#----------------------

isEmpty(TARGET_EXT) {
    win32: TARGET_CUSTOM_EXT = .exe
    macx: TARGET_CUSTOM_EXT = .app
} 
else: TARGET_CUSTOM_EXT = $${TARGET_EXT}

win32: DEPLOY_COMMAND = windeployqt
macx: DEPLOY_COMMAND = macdeployqt

CONFIG( debug, debug|release ): DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
else: DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))

QMAKE_POST_LINK += $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
