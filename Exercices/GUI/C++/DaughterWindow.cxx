//Header File
#include "DaughterWindow.h"


//**********Constructor**********//
DaughterWindow::DaughterWindow() : Ui_MotherWindow()
{	
	setupUi(this);

	//Memory allocation  
	m_OutputWriter = WriterType::New(); 


	//Connections
	connect(inputButton, SIGNAL(clicked()), this, SLOT(SelectInputImage()));
	connect(threshold, SIGNAL(valueChanged(int)), this, SLOT(EnterThresholdValue(int)));
	connect(runButton, SIGNAL(clicked()), this, SLOT(Run()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(SaveOutput()));
}


//**********Destructor***********//
DaughterWindow::~DaughterWindow(){}


//**********Slot**********//
void DaughterWindow::SelectInputImage()
{
	//File selection
	m_InputFileWay = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "." ,"Images (*.png *.gif *.jpg *.jpeg)");
	//Input Image// 
	m_Reader = ReaderType::New() ;
	m_Reader->SetFileName(m_InputFileWay.toStdString());
  m_Reader->Update() ;
	//Display
	QVTKWidget *inputWidget = new QVTKWidget(this->inputArea);
	Display( m_Reader->GetOutput() , inputWidget ) ;
}

void DaughterWindow::EnterThresholdValue(int thresholdValue)
{
	m_Threshold=thresholdValue;
}

void DaughterWindow::Run()
{ 


	//Threshold Filtering//
  m_ThresholdFilter=FilterType::New(); 
	m_ThresholdFilter->SetInput(m_Reader->GetOutput());
	m_ThresholdFilter->SetLowerThreshold(m_Threshold);
	m_ThresholdFilter->SetUpperThreshold(255);
	m_ThresholdFilter->SetOutsideValue(0); 
	m_ThresholdFilter->SetInsideValue(255); 
	

	//Display
   QVTKWidget *outputWidget = new QVTKWidget(this->outputArea);
	Display(m_ThresholdFilter->GetOutput(), outputWidget);
}

void DaughterWindow::SaveOutput()
{
	// File Way Selection
	m_OutputFileWay = QFileDialog::getSaveFileName(this, "Save File", "." , "Images (*.png *.gif *.jpg *.jpeg)");		

	// Output Saving 
	m_OutputWriter->SetFileName( m_OutputFileWay.toStdString() ) ;
  m_OutputWriter->SetInput( m_ThresholdFilter->GetOutput() ) ;
	m_OutputWriter->Update();
}


//**********Other Functions**********//
void DaughterWindow::Display(ImageType::Pointer image, QVTKWidget* widget)
{
	//Widget
	widget->resize(221, 257);
	//ITK to VTK
	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
	ConnectorType::Pointer connector=ConnectorType::New();
	connector->SetInput(image);
	connector->Update();
  //deep copy connector's output to an image else connector will go out of scope
  //and vanish it will cause error while changing slice
  vtkImageData * vtkimage = vtkImageData::New();
  vtkimage->DeepCopy(connector->GetOutput());

  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
  actor->SetInput(vtkimage);
	//PNG Reader
	/*vtkSmartPointer<vtkPNGReader> pngReader = vtkSmartPointer<vtkPNGReader>::New();
	pngReader->SetFileName((file.toStdString()).c_str());*/

	//Viewer	
	vtkSmartPointer<vtkImageViewer> viewer = vtkSmartPointer<vtkImageViewer>::New();
	//viewer->SetInputConnection(connector->GetOutput());
  viewer->GetRenderer()->AddActor(actor);
	viewer->SetColorLevel(128);
	viewer->SetColorWindow(256);

	//Render window	
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow=viewer->GetRenderWindow();

	//Display
	widget->SetRenderWindow(renderWindow);
	renderWindow->Render();
	widget->show();
}

