#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T11:33:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = reader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = build
SOURCES += main.cpp


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

CONFIG( debug, debug|release ): DEPLOY_TARGET = $$shell_quote($$shell_path($${DESTDIR}/$${TARGET}$${TARGET_CUSTOM_EXT}))
else: DEPLOY_TARGET = $$shell_quote($$shell_path($${DESTDIR}/$${TARGET}$${TARGET_CUSTOM_EXT}))

QMAKE_POST_LINK += $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
