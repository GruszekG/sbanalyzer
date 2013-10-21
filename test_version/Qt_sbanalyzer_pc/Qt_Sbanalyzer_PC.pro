QT       += core gui sql opengl img


OTHER_FILES += \
    skaters.txt

HEADERS += \
    visualizationwindow.h \
    ui_instantValuesWindow.h \
    ui_aboutproject.h \
    savemeasurementswindow.h \
    savegraphwindow.h \
    realtimeplotwindow.h \
    qtlogo.h \
    qskater.h \
    qextserialport_p.h \
    qextserialport_global.h \
    qextserialport.h \
    qcustomplot.h \
    measurementData.h \
    mainwindow.h \
    instvalueswindow.h \
    hled.h \
    glwidget.h \
    dialogwindow.h \
    aboutprojectwindow.h \
    command.h \
    LIS3DH.h \
    L3G4200D.h \
    measurementconfwindow.h

SOURCES += \
    visualizationwindow.cpp \
    savemeasurementswindow.cpp \
    savegraphwindow.cpp \
    realtimeplotwindow.cpp \
    qtlogo.cpp \
    qskater.cpp \
    qextserialport_win.cpp \
    qextserialport.cpp \
    qcustomplot.cpp \
    measurementData.cpp \
    mainwindow.cpp \
    main.cpp \
    instvalueswindow.cpp \
    hled.cpp \
    glwidget.cpp \
    dialogwindow.cpp \
    aboutprojectwindow.cpp \
    command.cpp \
    measurementconfwindow.cpp

FORMS += \
    visualizationwindow.ui \
    savemeasurementswindow.ui \
    savegraphwindow.ui \
    realtimeplotwindow.ui \
    mainwindow.ui \
    instvalueswindow.ui \
    dialogwindow.ui \
    aboutprojectwindow.ui \
    measurementconfwindow.ui

RESOURCES += \
    images.qrc \
    images.qrc

RC_FILE = icon.rc
