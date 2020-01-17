## This file should be placed in the root directory of your project. 
## Then modify the CMakeLists.txt file in the root directory of your 
## project to incorporate the testing dashboard. 
## # The following are required to uses Dart and the Cdash dashboard 
##   ENABLE_TESTING() 
##   INCLUDE(CTest) 
set(CTEST_PROJECT_NAME "Optim++") 
#set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")  
#set(CTEST_DROP_METHOD "http") 
#if(NOT CTEST_DROP_SITE)
#  set(CTEST_DROP_SITE "eu-frlyo-ap-051:8080")
#endif()
#set(CTEST_DROP_LOCATION "/submit.php?project=3DReshaper") 
#set(CTEST_DROP_SITE_CDASH TRUE)

#set(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/ReshaperTools/memcheck.supp" CACHE FILEPATH
#  "File that contains suppressions for the memory checker" FORCE)

#set(VALGRIND_COMMAND_OPTIONS "--error-exitcode=1")

if(EXISTS "${CMAKE_SOURCE_DIR}/CTestCustom.cmake")
	configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR})
endif()