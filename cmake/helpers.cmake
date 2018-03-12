macro ( download_and_include SRC )
    get_filename_component ( download_and_include_FILE_NAME ${SRC} NAME )
    string ( CONCAT download_and_include_DEST ${CMAKE_CURRENT_BINARY_DIR}/downloaded-cmake-modules/ ${download_and_include_FILE_NAME} )
    if ( NOT EXISTS ${download_and_include_DEST} )
        message ( STATUS " Downloading cmake module from ${SRC}" )
        file ( DOWNLOAD "${SRC}" "${download_and_include_DEST}" )
    else ()
        message ( STATUS "Using cmake module downloaded from ${SRC}" )
    endif ()
    if ( NOT EXISTS ${download_and_include_DEST} )
        message ( FATAL_ERROR "File ${DEST} is missing" )
    endif ()
    include ( ${download_and_include_DEST} )
endmacro ()

macro ( start_hunter )
    download_and_include ( "https://raw.githubusercontent.com/hunter-packages/gate/master/cmake/HunterGate.cmake" )
    huntergate (
            URL "https://github.com/ruslo/hunter/archive/v0.20.14.tar.gz"
            SHA1 "18cdbf5c47abdda437c73bf5437b7c3c65afe47c "
    )
endmacro ()