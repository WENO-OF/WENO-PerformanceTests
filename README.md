# WENO Performance Testing

This project contains a few tests to perform quick, single core
performance testing for some of the WENOExt library functions 

## Usage

Clone the repository from Github into the same directory that you have cloned 
WENOExt. The directory structure can look then something like:
```
-<baseDir>:
    - WENOEXT
    - WENOEXT-PerformanceTests
```
If `WENOEXT-PerformanceTests` is cloned into a different path the `WENOEXT_PATH` 
variable in CMakeLists.txt has to be adjusted.

Install the test cases with the provided `install.sh` script.

In the directories WENOBase, WENOCoeff, and geometryWENO test cases are found for 
the different WENO classes or functions. For some a python script to generate some
performance statistics is included.


## License 

This OpenFOAM library is under the GNU General Public License.

## Authors
 * Jan Wilhelm Gärtner <jan.gaertner@outlook.de>

