#!/usr/bin/env python3
# =========================================================
#               Run Performance Study
# =========================================================
# Description:
#   Run the WENOCoeffPerformanceTest multiple times
#   to gather some statistics and plot the results 
#
# Author: Jan Gärtner <jan.gaertner@outlook.de>


import subprocess
import re
import numpy as np





# Lists to store the execution times
WENOCoeffScalar = []
WENOCoeffVector = []


# loop several times over the process to gather statistics
for i  in range(1,20):
    result = subprocess.run("../WENOCoeffPerformanceTest",stdout=subprocess.PIPE,universal_newlines=True)
    
    # Parse the result
    for line in result.stdout.split('\n'):
        match = re.search('\\tWENOCoeff scalar: ([0-9]*[.][0-9]+)ms',line)
        if match:
            WENOCoeffScalar.append(float(match.group(1)))
        
        match = re.search('\\tWENOCoeff vector: ([0-9]*[.][0-9]+)ms',line)
        if match:
            WENOCoeffVector.append(float(match.group(1)))

# Convert into numpy array for post processing

WENOCoeffScalar= np.array(WENOCoeffScalar)
WENOCoeffVector= np.array(WENOCoeffVector)

# Get mean and std deviation of samples
print(f"Mean: {np.mean(WENOCoeffScalar)} \tStd. dev: {np.std(WENOCoeffScalar)}")
print(f"Mean: {np.mean(WENOCoeffVector)} \tStd. dev: {np.std(WENOCoeffVector)}")




