bout_add_integrated_test(test_laplace
  SOURCES test_laplace.cxx
  EXTRA_FILES test_laplace.grd.nc data/benchmark.0.nc
  USE_RUNTEST
  USE_DATA_BOUT_INP
  )
