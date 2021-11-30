// Performance test case for geometryWENO
//


#include "fvCFD.H"
#include "geometryWENO.H"
#include <chrono>
#include <random>
#include <vector>

int main(int argc, char *argv[])
{
    // First construct all input variables 
    
    // Random function
    std::default_random_engine dev;
    std::uniform_int_distribution<int> exponentDistribution(0,5);
    
    std::uniform_real_distribution<double> randomFloats(0,10);
    
    // create vectors for n,m,l
    const size_t maxIter = 100000;
    std::vector<int> n,m,l;
    n.reserve(maxIter);
    m.reserve(maxIter);
    l.reserve(maxIter);
    
    for (size_t i=0; i < maxIter; i++)
    {
        n.push_back(exponentDistribution(dev));
        m.push_back(exponentDistribution(dev));
        l.push_back(exponentDistribution(dev));
    }
    
    // create vectors for vector inputs
    std::vector<vector> v0, v1, v2;
    v0.reserve(maxIter);
    v1.reserve(maxIter);
    v2.reserve(maxIter);
    
    const point p1(1,2,3);
    
    for (size_t i=0; i < maxIter; i++)
    {
        v0.push_back(
            vector(
                randomFloats(dev),
                randomFloats(dev),
                randomFloats(dev)
            )
        );
        v1.push_back(
            vector(
                randomFloats(dev),
                randomFloats(dev),
                randomFloats(dev)
            )
        );
        v2.push_back(
            vector(
                randomFloats(dev),
                randomFloats(dev),
                randomFloats(dev)
            )
        );
    }
    
    // -------------------------------------------------------------------------
    //                  Performance Test: gaussQuad
    // -------------------------------------------------------------------------
    {
        auto start = std::chrono::high_resolution_clock::now();
        double test = 0;
        for (size_t i=0; i < maxIter; i++)
        {
            test += geometryWENO::gaussQuad
            (
                n[i],
                m[i],
                l[i],
                p1,
                v0[i],
                v1[i],
                v2[i]
            );
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        Info << "\tGauss quad: "<<duration.count()/1000.0 << "ms" << endl;
    }
    
    // -------------------------------------------------------------------------
    //                  Performance Test: transformPoint
    // -------------------------------------------------------------------------
    {
        // Create the Jacobi matrix
        auto J = geometryWENO::jacobi
        (
            0, 0, 0,
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        );
        
        auto start = std::chrono::high_resolution_clock::now();
        point test(0,0,0);
        for (size_t i=0; i < maxIter; i++)
        {
            test += geometryWENO::transformPoint
            (
                J,
                v0[i],
                v1[i]
            );
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        Info << "\tTransform point: "<<duration.count()/1000.0 << "ms" << endl;
    }
    
    return 0;
}
