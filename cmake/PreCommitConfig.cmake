function(PreCommitInstallation)
  set(RET 0)
  set(DETECTION_RUN
      OFF
      CACHE BOOL "The dectection on pre-commit has been run")
  set(SUCCESS 0)
  set(FAILED 1)
  if(NOT ${DETECTION_RUN})
    set(DETECTION_RUN ON FORCE)
    message(STATUS "Check the pre-commit")
    execute_process(
      COMMAND pip install pre-commit
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE RET)
    if(${RET} EQUAL ${SUCCESS})
      message(STATUS "The pre-commit module has been already installed")
      execute_process(COMMAND pre-commit install
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    else()
      message(
        FATAL_ERROR
          "Cannot install pre-commit module. Try to resolve it manually")
    endif()
  else()
    message(STATUS "The existance of pre-commit has been detected")
  endif()
endfunction(PreCommitInstallation)
