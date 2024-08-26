function(PreCommitInstallation)
    set(RET 0)
    set(SUCCESS 0)
    set(FAILED 1)
    execute_process(COMMAND
        pip install pre-commit
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE RET
    )

    if (${RET} EQUAL ${SUCCESS}) 
        message(STATUS "The pre-commit module has been already installed")
        execute_process(COMMAND
            pre-commit install
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    else() 
        message(FATAL_ERROR "Cannot install pre-commit module. Try to resolve it manually")
    endif()

endfunction(PreCommitInstallation)