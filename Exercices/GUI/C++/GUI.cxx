#include <QApplication>
#include "DaughterWindow.h" 

int main(int argc, char *argv[])
{
	QApplication app( argc , argv ) ;
	DaughterWindow fifille ; 
	fifille.show() ;
	return app.exec() ;
}
