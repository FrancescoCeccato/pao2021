QT       += core gui charts xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bar_chart.cpp \
    cartesian_chart.cpp \
    chart.cpp \
    charts_cartesianchart_addpoints.cpp \
    charts_chartcreation.cpp \
    charts_comparisonchart_editor.cpp \
    charts_exception.cpp \
    charts_main_window.cpp \
    comparison_chart.cpp \
    dialog_entrance.cpp \
    dot_chart.cpp \
    main.cpp \
    model.cpp \
    pie_chart.cpp \
    polar_chart.cpp \
    presenter_chart_view.cpp \
    simple_bar_chart.cpp \
    stacked_bar_chart.cpp \
    time_chart.cpp \
    xml_management.cpp

HEADERS += \
    bar_chart.h \
    cartesian_chart.h \
    chart.h \
    charts_cartesianchart_addpoints.h \
    charts_chartcreation.h \
    charts_comparisonchart_editor.h \
    charts_exception.h \
    charts_main_window.h \
    comparison_chart.h \
    dialog_entrance.h \
    dot_chart.h \
    model.h \
    pie_chart.h \
    polar_chart.h \
    presenter_chart_view.h \
    simple_bar_chart.h \
    stacked_bar_chart.h \
    time_chart.h \
    xml_management.h

FORMS += \
    test.ui

TRANSLATIONS += \
    Project2021_it_IT.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    openchart.png

RESOURCES += \
    Resources.qrc
