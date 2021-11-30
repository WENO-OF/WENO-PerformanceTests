# CMake File to Create the Library


add_executable(geometryWENOPerformanceTest
    geometryWENOPerformanceTest.cpp
)


target_include_directories(geometryWENOPerformanceTest PRIVATE
    $ENV{FOAM_SRC}/finiteVolume/lnInclude  
    $ENV{FOAM_SRC}/OpenFOAM/lnInclude
    $ENV{FOAM_SRC}/meshTools/lnInclude
    $ENV{FOAM_SRC}/OSspecific/POSIX/lnInclude
    $ENV{FOAM_SRC}/dynamicMesh/lnInclude
    $ENV{FOAM_SRC}/surfMesh/lnInclude
)

target_link_libraries(geometryWENOPerformanceTest PRIVATE
    WENOEXT::WENOEXT
    -L$ENV{FOAM_LIBBIN}
    -lfiniteVolume
    -lOpenFOAM
)

set_target_properties(geometryWENOPerformanceTest PROPERTIES LINK_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})

install(
    TARGETS geometryWENOPerformanceTest 
    DESTINATION ${CMAKE_SOURCE_DIR}/geometryWENO/
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE
)
