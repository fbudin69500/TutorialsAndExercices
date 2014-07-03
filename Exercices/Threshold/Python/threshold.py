#!/usr/bin/env python

import sys
import SimpleITK

if len(sys.argv) != 4:
  print sys.argv[0]+" <inputImage> <outputImage> <thresholdValue>"
  sys.exit(1)
# Input Image
reader = SimpleITK.ImageFileReader(); 
reader.SetFileName(sys.argv[1]); 
image = reader.Execute();

# Threshold Filter 
thresholdFilter = SimpleITK.BinaryThresholdImageFilter();
thresholdFilter.SetLowerThreshold(int(sys.argv[3])); 
thresholdFilter.SetUpperThreshold(255); 
thresholdFilter.SetOutsideValue(0); 
thresholdFilter.SetInsideValue(255); 

# Output Image
output = thresholdFilter.Execute(image);
writer = SimpleITK.ImageFileWriter(); 
writer.SetFileName(sys.argv[2]); 
writer.Execute(output); 

