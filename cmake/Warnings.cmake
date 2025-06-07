function(target_set_warnings TARGET ENABLE ENABLED_AS_ERRORS)
    if(NOT ${ENABLED})
        message(STATUS "Warnings disabled for: ${TARGET}")
        return()
    endif()

    set(MSVC_WARNINGS
        /W4
        /permissive-)
        
    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic)

    set(GCC_WARNINGS ${CLANG_WARNINGS})

    if(${ENABLED_AS_ERRORS})
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror)
        set(GCC_WARNINGS ${GCC_WARNINGS} /Werror)
    endif()
    
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(WARNINGS ${GNU_WARNINGS})
    endif()
    
    target_compile_options(${TARGET} PRIVATE ${WARNINGS})
    message(STATUS "Using compiler: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "Warnings: ${WARNINGS}")

endfunction()
