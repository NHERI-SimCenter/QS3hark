# QS3hark.cmake
# Usage:
#   include(path/to/QS3hark.cmake)
#   simcenter_add_shark(<target>)

set(SHARK_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}")

function(simcenter_add_shark target)

  set(dir "${SHARK_MODULE_DIR}")

  target_include_directories(${target} PRIVATE
    "${dir}"
    "${dir}/Include"
    "${dir}/FEM"
    "${dir}/SiteResponse"
    "${dir}/UI"
  )

  set(SOURCES
    "${dir}/UI/RockOutcrop.cpp"
    "${dir}/UI/BonzaTableView.cpp"
    "${dir}/UI/InsertWindow.cpp"
    "${dir}/UI/BonzaTableModel.cpp"
    "${dir}/UI/SiteResponse.cpp"
    "${dir}/UI/TabManager.cpp"
    "${dir}/UI/JsonManager.cpp"
    "${dir}/UI/ElementModel.cpp"
    "${dir}/FEM/TaggedObject.cpp"
    "${dir}/FEM/TimeSeries.cpp"
    "${dir}/FEM/TimeSeriesIntegrator.cpp"
    "${dir}/FEM/TrapezoidalTimeSeriesIntegrator.cpp"
    "${dir}/FEM/Vector.cpp"
    "${dir}/FEM/GroundMotion.cpp"
    "${dir}/FEM/PathTimeSeries.cpp"
    "${dir}/FEM/ID.cpp"
    "${dir}/FEM/PathSeries.cpp"
    "${dir}/SiteResponse/EffectiveFEModel.cpp"
    "${dir}/SiteResponse/Mesher.cpp"
    "${dir}/SiteResponse/soillayer.cpp"
    "${dir}/SiteResponse/siteLayering.cpp"
    "${dir}/SiteResponse/outcropMotion.cpp"
    "${dir}/UI/PostProcessor.cpp"
    "${dir}/UI/SSSharkThread.cpp"
  )

  set(HEADERS
    "${dir}/UI/RockOutcrop.h"
    "${dir}/GlobalConstances.h"
    "${dir}/UI/BonzaTableView.h"
    "${dir}/UI/InsertWindow.h"
    "${dir}/UI/BonzaTableModel.h"
    "${dir}/UI/SiteResponse.h"
    "${dir}/UI/TabManager.h"
    "${dir}/UI/JsonManager.h"
    "${dir}/UI/ElementModel.h"
    "${dir}/FEM/TaggedObject.h"
    "${dir}/FEM/TimeSeries.h"
    "${dir}/FEM/TimeSeriesIntegrator.h"
    "${dir}/FEM/TrapezoidalTimeSeriesIntegrator.h"
    "${dir}/FEM/Vector.h"
    "${dir}/FEM/GroundMotion.h"
    "${dir}/FEM/PathTimeSeries.h"
    "${dir}/FEM/ID.h"
    "${dir}/FEM/PathSeries.h"
    "${dir}/SiteResponse/Mesher.h"
    "${dir}/SiteResponse/EffectiveFEModel.h"
    "${dir}/SiteResponse/soillayer.h"
    "${dir}/SiteResponse/outcropMotion.h"
    "${dir}/SiteResponse/siteLayering.h"
    "${dir}/UI/PostProcessor.h"
    "${dir}/UI/SSSharkThread.h"
  )

  set(FORMS
    "${dir}/UI/MainWindow.ui"
    "${dir}/UI/RockOutcrop.ui"
    "${dir}/UI/InsertWindow.ui"
    "${dir}/UI/PM4Sand.ui"
    "${dir}/UI/PM4Sand_random.ui"
    "${dir}/UI/PM4Silt.ui"
    "${dir}/UI/DefaultMatTab.ui"
    "${dir}/UI/GroundMotion.ui"
    "${dir}/UI/FEM.ui"
    "${dir}/UI/PIMY.ui"
    "${dir}/UI/PDMY.ui"
    "${dir}/UI/PDMY02.ui"
    "${dir}/UI/PDMY03.ui"
    "${dir}/UI/PDMY03_random.ui"
    "${dir}/UI/ManzariDafalias.ui"
    "${dir}/UI/J2Bounding.ui"
    "${dir}/UI/ElasticIsotropic.ui"
    "${dir}/UI/ElasticIsotropic_random.ui"
  )

  set(RESOURCES "${dir}/resources.qrc")

  target_sources(${target} PRIVATE ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
  
endfunction()

