QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bar_chart.cpp \
    cartesian_chart.cpp \
    chart.cpp \
    comparison_chart.cpp \
    dialog_entrance.cpp \
    dot_chart.cpp \
    main.cpp \
    pie_chart.cpp \
    polar_chart.cpp \
    segmented_bar_chart.cpp \
    simple_bar_chart.cpp \
    stacked_bar_chart.cpp \
    time_chart.cpp

HEADERS += \
    bar_chart.h \
    cartesian_chart.h \
    chart.h \
    comparison_chart.h \
    dialog_entrance.h \
    dot_chart.h \
    pie_chart.h \
    polar_chart.h \
    segmented_bar_chart.h \
    simple_bar_chart.h \
    stacked_bar_chart.h \
    time_chart.h

FORMS +=

TRANSLATIONS += \
    Project2021_it_IT.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    newchart.png \
    openchart.png

RESOURCES += \
    Resources.qrc
