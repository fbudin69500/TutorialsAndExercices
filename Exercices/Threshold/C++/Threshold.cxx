#include "itkImage.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "ThresholdCLP.h"

int main(int argc, char *argv[])
{	
	PARSE_ARGS;	

	//Seuil//
	int Threshold=atoi(argv[3]);
 
	//Image Type//
	typedef itk::Image<unsigned char, 3> ImageType;

	//Input Image//
	typedef itk::ImageFileReader<ImageType> ReaderType; 
	ReaderType::Pointer reader = ReaderType::New(); 
	reader->SetFileName(argv[1]); 

	//Threshold Filtering//
	typedef itk::BinaryThresholdImageFilter <ImageType, ImageType> FilterType;
	FilterType::Pointer thresholdFilter=FilterType::New(); 
	
	thresholdFilter->SetInput(reader->GetOutput());

	thresholdFilter->SetLowerThreshold(Threshold);
	thresholdFilter->SetUpperThreshold(255);

	thresholdFilter->SetOutsideValue(0); 
	thresholdFilter->SetInsideValue(255); 
	
	//Output Image
	typedef itk::ImageFileWriter<ImageType> WriterType;  
	WriterType::Pointer writer = WriterType::New(); 
	writer->SetInput(thresholdFilter->GetOutput()); 
	writer->SetFileName(argv[2]);
	writer->Update(); 
}
