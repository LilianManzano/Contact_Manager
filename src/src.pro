QT -= gui

QT += sql \
    widgets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        CalendarDialog.cpp \
        Contact.cpp \
        DatabaseCRUD.cpp \
        DatabaseManagement.cpp \
        Date.cpp \
        DetailsContactDialog.cpp \
        EditContactDialog.cpp \
        EditTagDialog.cpp \
        Interaction.cpp \
        ListContact.cpp \
        ListInteraction.cpp \
        MainWidget.cpp \
        MainWindow.cpp \
        ModificationsWindow.cpp \
        Todo.cpp \
        ListTodo.cpp \
        YesNoDialog.cpp \
        main.cpp \
        MessageLabel.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CalendarDialog.h \
    Contact.h \
    DatabaseCRUD.h \
    DatabaseManagement.h \
    Date.h \
    DetailsContactDialog.h \
    EditContactDialog.h \
    EditTagDialog.h \
    Interaction.h \
    ListContact.h \
    ListInteraction.h \
    MainWidget.h \
    MainWindow.h \
    ModificationsWindow.h \
    Todo.h \
    ListTodo.h \
    YesNoDialog.h \
    MessageLabel.h

FORMS +=

RESOURCES += \
    resource.qrc
