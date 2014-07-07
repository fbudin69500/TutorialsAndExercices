#ifndef _DaughterWindow
#define _DaughterWindow

//General Libraries
#include <string.h>

//Qt Libraries
#include <QFileDialog>
#include <QMainWindow>
#include <QWidget>
#include "QVTKWidget.h"
#include "ui_MotherWindow.h"

//ITK Libraries
#include "itkImage.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include <itkImageFileWriter.h>

//ITK to VTK Libraries
#include <itkImageToVTKImageFilter.h>

//VTK Libraries
#include <vtkSmartPointer.h> 
#include <vtkImageViewer.h>
#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>
#include <vtkRenderWindow.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>

class DaughterWindow :public QMainWindow, public Ui_MotherWindow
{
  Q_OBJECT // Enable slots and signals 

  public:
   //Image Type//
   typedef itk::Image< unsigned char , 2 > ImageType ;
   typedef itk::ImageFileReader< ImageType > ReaderType ;
   typedef itk::ImageFileWriter< ImageType > WriterType ;
   typedef itk::BinaryThresholdImageFilter< ImageType , ImageType > FilterType ;

  DaughterWindow() ;
  ~DaughterWindow() ;
  void Display( ImageType::Pointer image , QVTKWidget* widget ) ;

  public slots:
  void SelectInputImage() ;
  void EnterThresholdValue( int threshold ) ;
  void Run() ;
  void SaveOutput() ;
  
  private:
  //Input
  QString m_InputFileWay ;
  ReaderType::Pointer m_Reader ;
  //Output
  QString m_OutputFileWay ;
  WriterType::Pointer m_OutputWriter ;
  FilterType::Pointer m_ThresholdFilter ;
  //Filter
  int m_Threshold ;
};

#endif 
