#include "notebook.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setOrganizationName("QtProject");
	a.setApplicationName("Application Example");
	NoteBook w;
	w.show();
	return a.exec();
}
