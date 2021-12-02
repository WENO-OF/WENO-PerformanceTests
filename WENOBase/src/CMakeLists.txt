# CMake File to Create the Library


add_executable(WENOBasePerformanceTest
    WENOBasePerformanceTest.cpp
)


target_include_directories(WENOBasePerformanceTest PRIVATE
    $ENV{FOAM_SRC}/finiteVolume/lnInclude  
    $ENV{FOAM_SRC}/dynamicMesh/lnInclude
    $ENV{FOAM_SRC}/meshTools/lnInclude
    $ENV{FOAM_SRC}/surfMesh/lnInclude
    $ENV{FOAM_SRC}/fileFormats/lnInclude
    $ENV{FOAM_SRC}/OpenFOAM/lnInclude
    $ENV{FOAM_SRC}/OSspecific/POSIX/lnInclude
)

target_link_libraries(WENOBasePerformanceTest PRIVATE
    WENOEXT::WENOEXT
    -L$ENV{FOAM_LIBBIN}
    -lfiniteVolume
    -lOpenFOAM
)

set_target_properties(WENOBasePerformanceTest PROPERTIES LINK_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})

install(
    TARGETS WENOBasePerformanceTest 
    DESTINATION ${CMAKE_SOURCE_DIR}/WENOBase/
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE
)
