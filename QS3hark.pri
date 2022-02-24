
    INCLUDEPATH += $$PWD/ \
           $$PWD/Include \
           $$PWD/FEM \
           $$PWD/SiteResponse \
           $$PWD/UI

    SOURCES += $$PWD/UI/RockOutcrop.cpp \
        $$PWD/UI/BonzaTableView.cpp \
        $$PWD/UI/InsertWindow.cpp \
        $$PWD/UI/BonzaTableModel.cpp \
        $$PWD/UI/SiteResponse.cpp \
        $$PWD/UI/TabManager.cpp \
        $$PWD/UI/JsonManager.cpp \
        $$PWD/UI/ElementModel.cpp \
        $$PWD/FEM/TaggedObject.cpp \
        $$PWD/FEM/TimeSeries.cpp \
        $$PWD/FEM/TimeSeriesIntegrator.cpp \
        $$PWD/FEM/TrapezoidalTimeSeriesIntegrator.cpp \
        $$PWD/FEM/Vector.cpp \
        $$PWD/FEM/GroundMotion.cpp \
        $$PWD/FEM/PathTimeSeries.cpp \
        $$PWD/FEM/ID.cpp \
        $$PWD/FEM/PathSeries.cpp \
        $$PWD/SiteResponse/EffectiveFEModel.cpp \
        $$PWD/SiteResponse/Mesher.cpp \
        $$PWD/SiteResponse/soillayer.cpp \
        $$PWD/SiteResponse/siteLayering.cpp \
        $$PWD/SiteResponse/outcropMotion.cpp \
        $$PWD/UI/PostProcessor.cpp \
        $$PWD/UI/SSSharkThread.cpp


    HEADERS  += $$PWD/UI/RockOutcrop.h \
        $$PWD/GlobalConstances.h \
        $$PWD/UI/BonzaTableView.h \
        $$PWD/UI/InsertWindow.h \
        $$PWD/UI/BonzaTableModel.h \
        $$PWD/UI/SiteResponse.h \
        $$PWD/UI/TabManager.h \
        $$PWD/UI/JsonManager.h \
        $$PWD/UI/ElementModel.h \
        $$PWD/FEM/TaggedObject.h \
        $$PWD/FEM/TimeSeries.h \
        $$PWD/FEM/TimeSeriesIntegrator.h \
        $$PWD/FEM/TrapezoidalTimeSeriesIntegrator.h \
        $$PWD/FEM/Vector.h \
        $$PWD/FEM/GroundMotion.h \
        $$PWD/FEM/PathTimeSeries.h \
        $$PWD/FEM/ID.h \
        $$PWD/FEM/PathSeries.h \
        $$PWD/SiteResponse/Mesher.h \
        $$PWD/SiteResponse/EffectiveFEModel.h \
        $$PWD/SiteResponse/soillayer.h \
        $$PWD/SiteResponse/outcropMotion.h \
        $$PWD/SiteResponse/siteLayering.h \
        $$PWD/UI/PostProcessor.h \
        $$PWD/UI/SSSharkThread.h


FORMS    += $$PWD/UI/MainWindow.ui \
    $$PWD/UI/RockOutcrop.ui \
    $$PWD/UI/InsertWindow.ui \
    $$PWD/UI/PM4Sand.ui \
    $$PWD/UI/PM4Sand_random.ui \
    $$PWD/UI/PM4Silt.ui \
    $$PWD/UI/DefaultMatTab.ui \
    $$PWD/UI/GroundMotion.ui \
    $$PWD/UI/FEM.ui \
    $$PWD/UI/PIMY.ui \
    $$PWD/UI/PDMY.ui \
    $$PWD/UI/PDMY02.ui \
    $$PWD/UI/PDMY03.ui \
    $$PWD/UI/PDMY03_random.ui \
    $$PWD/UI/ManzariDafalias.ui \
    $$PWD/UI/J2Bounding.ui \
    $$PWD/UI/ElasticIsotropic.ui \
    $$PWD/UI/ElasticIsotropic_random.ui \

RESOURCES += \
    $$PWD/resources.qrc

