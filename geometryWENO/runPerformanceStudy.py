#!/usr/bin/env python3
# =========================================================
#               Run Performance Study
# =========================================================
# Description:
#   Run the geometryWENO performance test multiple times
#   to gather some statistics and plot the results 
#
# Author: Jan Gärtner <jan.gaertner@outlook.de>


import subprocess
import re
import numpy as np

# Lists to store the execution times
gaussQuad = []
transformPoint = []
jacobiInverse = []


# loop several times over the process to gather statistics
for i  in range(1,100):
    result = subprocess.run("./geometryWENOPerformanceTest",stdout=subprocess.PIPE,universal_newlines=True)

    # Parse the result
    for line in result.stdout.split('\n'):
        match = re.search('\tGauss quad: ([0-9]*[.][0-9]+)',line)
        if match:
            gaussQuad.append(float(match.group(1)))
        
        match = re.search('\tTransform point: ([0-9]*[.][0-9]+)',line)
        if match:
            transformPoint.append(float(match.group(1)))
        
        match = re.search('\tCalculate Jacobi inverse: ([0-9]*[.][0-9]+)',line)
        if match:
            jacobiInverse.append(float(match.group(1)))

# Convert into numpy array for post processing

gaussQuad = np.array(gaussQuad)
transformPoint = np.array(transformPoint)
jacobiInverse = np.array(jacobiInverse)

# Get mean and std deviation of samples
print(f"Mean: {np.mean(gaussQuad)} \tStd. dev: {np.std(gaussQuad)}")
print(f"Mean: {np.mean(transformPoint)} \tStd. dev: {np.std(transformPoint)}")
print(f"Mean: {np.mean(jacobiInverse)} \tStd. dev: {np.std(jacobiInverse)}")




