// Performance test case for geometryWENO
//


#include "fvCFD.H"
#include "WENOCoeff.H"
#include <chrono>
#include <random>
#include <vector>

int main(int argc, char *argv[])
{
    // First generate OpenFOAM mesh
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"


    // Create scalar field
    volScalarField scalarF
    (
        IOobject
        (
            "F",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("a",dimless,1.0)
    );

    volVectorField vectorF
    (
        IOobject
        (
            "F",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("a",dimless,vector(1,1,1))
    );
    std::default_random_engine dev;
    std::uniform_real_distribution<double> randomFloats(0,1);

    // Add some random fluctuations to the field
    forAll(scalarF,cellI)
    {
        scalarF[cellI] = scalarF[cellI] + randomFloats(dev); 
    }

    forAll(vectorF,cellI)
    {
        scalar temp = randomFloats(dev);
        vectorF[cellI] = vectorF[cellI] + vector(temp,temp,temp); 
    }

    // -------------------------------------------------------------------------
    //                  Performance Test: scalar field
    // -------------------------------------------------------------------------
    {
        // Connstruct WENOCoeff
        WENOCoeff<scalar> coeffs(mesh,3);
        auto start = std::chrono::high_resolution_clock::now();
        // Call getWENOPol
        tmp<Field<Field<scalar>>> res = coeffs.getWENOPol(scalarF);

        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        Info << "\tWENOCoeff scalar: "<<duration.count()/1000.0 << "ms" << endl;
    }

    // -------------------------------------------------------------------------
    //                  Performance Test: vector field
    // -------------------------------------------------------------------------
    {
        // Connstruct WENOCoeff
        WENOCoeff<vector> coeffs(mesh,3);
        auto start = std::chrono::high_resolution_clock::now();
        // Call getWENOPol
        tmp<Field<Field<vector>>> res = coeffs.getWENOPol(vectorF);

        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        Info << "\tWENOCoeff vector: "<<duration.count()/1000.0 << "ms" << endl;
    }
    
    return 0;
}
