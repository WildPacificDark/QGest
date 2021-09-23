QT += core gui xml widgets


CONFIG += c++11

SOURCES += \
    gui/source/ContextButton.cpp \
    gui/source/MainWindow.cpp \
    gui/source/dialog/Form.cpp \
    gui/source/dialog/FormClienti.cpp \
    gui/source/dialog/FormContratti.cpp \
    gui/source/dialog/FormDipendenti.cpp \
    gui/source/dialog/FormPersone.cpp \
    gui/source/tab/Tab_Clienti.cpp \
    gui/source/tab/Tab_Contratti.cpp \
    gui/source/tab/Tab_Dipendenti.cpp \
    main.cpp \
    model/source/Contratto.cpp \
    model/source/Gestionale.cpp \
    model/source/UniqueID.cpp \
    model/source/cliente/Cliente.cpp \
    model/source/cliente/Cliente_Business.cpp \
    model/source/cliente/Cliente_Res.cpp \
    model/source/data/Data.cpp \
    model/source/data/Ora.cpp \
    model/source/dipendente/Agente.cpp \
    model/source/dipendente/Dipendente.cpp \
    model/source/dipendente/Manager.cpp \
    model/source/persona/Persona.cpp


HEADERS += \
    gui/header/ContextButton.h \
    gui/header/MainWindow.h \
    gui/header/dialog/Form.h \
    gui/header/dialog/FormClienti.h \
    gui/header/dialog/FormContratti.h \
    gui/header/dialog/FormDipendenti.h \
    gui/header/dialog/FormPersone.h \
    gui/header/tab/Tab_Clienti.h \
    gui/header/tab/Tab_Contratti.h \
    gui/header/tab/Tab_Dipendenti.h \
    model/header/Contratto.h \
    model/header/Exception.h \
    model/header/Gestionale.h \
    model/header/Queue.h \
    model/header/UniqueID.h \
    model/header/cliente/Cliente.h \
    model/header/cliente/Cliente_Business.h \
    model/header/cliente/Cliente_Res.h \
    model/header/data/Data.h \
    model/header/data/Ora.h \
    model/header/dipendente/Agente.h \
    model/header/dipendente/Dipendente.h \
    model/header/dipendente/Manager.h \
    model/header/persona/Persona.h

FORMS += \

RESOURCES = resources.qrc \
    resources.qrc \
    resources.qrc \
    resources.qrc \
    resources.qrc

DISTFILES += \
    img/cancel.png \
    img/diskette.png \
    img/editing.png \
    img/plus.png \
    img/redo.png \
    img/undo.png \
    xml/data.xml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
