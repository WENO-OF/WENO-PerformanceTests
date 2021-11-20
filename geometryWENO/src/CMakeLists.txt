# CMake File to Create the Library


add_executable(geometryWENOPerformanceTest
    geometryWENOPerformanceTest.cpp
)


target_include_directories(geometryWENOPerformanceTest PRIVATE
    Blaze
    $ENV{FOAM_SRC}/finiteVolume/lnInclude  
    $ENV{FOAM_SRC}/dynamicMesh/lnInclude
    $ENV{FOAM_SRC}/meshTools/lnInclude
    $ENV{FOAM_SRC}/surfMesh/lnInclude
    $ENV{FOAM_SRC}/fileFormats/lnInclude
    $ENV{FOAM_SRC}/OpenFOAM/lnInclude
    $ENV{FOAM_SRC}/OSspecific/POSIX/lnInclude
    /home/jan/Solver/WENOEXT/libWENOEXT/WENOBase/geometryWENO
    /home/jan/Solver/WENOEXT/libWENOEXT/BlazeIO
)

target_link_libraries(geometryWENOPerformanceTest PRIVATE
    Blaze
    -L$ENV{FOAM_LIBBIN}
    -ldynamicMesh
    -lfiniteVolume
    -lmeshTools
    -lspecie
    -lsurfMesh
    -lfileFormats
    -lOpenFOAM
    -L$ENV{FOAM_USER_LIBBIN}
    -lWENOEXT
)

set_target_properties(geometryWENOPerformanceTest PROPERTIES LINK_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})

install(
    TARGETS geometryWENOPerformanceTest 
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE
)
