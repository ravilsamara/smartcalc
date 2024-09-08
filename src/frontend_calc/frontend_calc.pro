QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../backend_calc/s21_calculation.c \
    ../backend_calc/s21_rpn.c \
    ../backend_calc/s21_str_parser.c \
    ../backend_calc/s21_str_validation.c \
    addremitemwidget.cpp \
    creditcalc.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../backend_calc/s21_smartcalc.h \
    addremitemwidget.h \
    creditcalc.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    addremitemwidget.ui \
    creditcalc.ui \
    graph.ui \
    mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
