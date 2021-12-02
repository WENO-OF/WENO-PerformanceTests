// Performance test case for WENOBase 
//


#include "fvCFD.H"
#include "WENOBase.H"
#include <chrono>
#include <random>
#include <vector>

int main(int argc, char *argv[])
{
    // First generate OpenFOAM mesh
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"


    // -------------------------------------------------------------------------
    //                  Performance Test: WENOBase
    // -------------------------------------------------------------------------
    {
        auto start = std::chrono::high_resolution_clock::now();

        const WENOBase& base = WENOBase::instance(mesh,3);

        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        Info << "\tWENOBase: "<<duration.count()/1000.0 << "ms" << endl;
    }
    return 0;
}
