#include "notebook.h"
#include <QtWidgets>

NoteBook::NoteBook(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	textEdit = new QPlainTextEdit;//创建一个简单的子部件
	setCentralWidget(textEdit);

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	readSettings();
	connect(textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));//链接当内容被更改时执行槽函数
	setCurrentFile("");
	setUnifiedTitleAndToolBarOnMac(true);
}

void NoteBook::closeEvent(QCloseEvent *event)
{
	if (maybeSave())
	{
		writeSettings();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void NoteBook::newFile()
{
	if (maybeSave())
	{
		textEdit->clear();
		setCurrentFile("");
	}
}

void NoteBook::open()
{
	if (maybeSave())
	{
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
			loadFile(fileName);
	}
}

bool NoteBook::save()
{
	if (curFile.isEmpty())
	{
		return saveAs();
	}
	else
	{
		return saveFile(curFile);
	}
}

bool NoteBook::saveAs()
{
	QFileDialog dialog(this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	QStringList files;
	if (dialog.exec())
	{
		files = dialog.selectedFiles();
	}
	else
	{
		return false;
	}
	return saveFile(files.at(0));
}

void NoteBook::about()
{
	QMessageBox::about(this, "About Application", "The <b>Application</b> example demonstrates how to write modern GUI application using Qt,"
		"with a menu bar, toolbars, and a status bar.");
}

void NoteBook::documentWasModified()
{
	setWindowModified(textEdit->document()->isModified());
}

void NoteBook::createActions()
{
	newAct = new QAction(QIcon("D:\\QtDemo\\记事本\\记事本\\记事本\\images\\new.png"),tr("&New"), this);
	newAct->setShortcut(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

	openAct = new QAction(QIcon("D:\\QtDemo\\记事本\\记事本\\记事本\\images\\open.png"), tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(QIcon("D:\\QtDemo\\记事本\\记事本\\记事本\\images\\save.png"), tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAct = new QAction("Save &As...", this);
	saveAsAct->setShortcut(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	aboutAct = new QAction(tr("About &Qt"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQtAct()));

	cutAct = new QAction(QIcon("D:\\QtDemo\\记事本\\记事本\\记事本\\images\\cut.png"),"&Cut",this);
	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setStatusTip(tr("Cus the current selection's contents to the clipboard"));
	connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

	copyAct = new QAction(QIcon("D:\\QtDemo\\记事本\\记事本\\记事本\\images\\copy.png"),"&Copy",this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
	connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

	pasteAct = new QAction(QIcon("D:\\QtDemo\\记事本\\记事本\\记事本\\images\\paste.png"), "&Paste",this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
	connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

	cutAct->setEnabled(false);
	copyAct->setEnabled(false);
	connect(textEdit, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));
	connect(textEdit, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));
}

/*创建菜单栏*/
void NoteBook::createMenus()
{
	//QMainWindow::menuBar()函数返回窗口的菜单工具栏部件
	
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);

	//QMenuBar::addSeparator()函数创建一个分隔符，分隔各工具栏
	/*menuBar()->addSeparator();*/

 	helpMenu = menuBar()->addMenu(tr("&Help"));
// 	helpMenu->addAction(aboutAct);
// 	helpMenu->addAction(aboutQtAct);
}

/*创建工具栏*/
void NoteBook::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(newAct);
	fileToolBar->addAction(openAct);
	fileToolBar->addAction(saveAct);

	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(cutAct);
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);
}

/*创建一个状态栏*/
void NoteBook::createStatusBar()
{
	//QMainWindow::statusBar()返回一个指向主窗口状态栏的指针
	statusBar()->showMessage(tr("Ready"));
}

/*构造函数中调用*/
void NoteBook::readSettings()
{
	//用QSettings的参数用来确认你的伙伴知道这个产品的名称，防止混淆
	//用QSettings::value()函数来提取settings的值，如果不存在，则使用默认值，表明第一次运行
	QSettings settings(tr("QtProject"), tr("Application Example"));
	QPoint pos = settings.value(tr("pos"), QPoint(200, 200)).toPoint();
	QSize size = settings.value(tr("size"), QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}

/*在关闭事件中被调用*/
void NoteBook::writeSettings()
{
	QSettings settings(tr("QtProject"), tr("Application Example"));
	settings.setValue(tr("pos"), pos());
	settings.setValue(tr("size"), size());
}

/*判断时候文件改变*/
bool NoteBook::maybeSave()
{
	if (textEdit->document()->isModified())
	{
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Application"), tr("The document has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if (ret == QMessageBox::Save)
			return save();
		else if (ret = QMessageBox::Cancel)
		{
			return false;
		}
	}
	return true;
}

void NoteBook::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Application"), tr("Can't read file %1:\n%2.").arg(fileName).arg(file.errorString()));
		return;
	}
	QTextStream in(&file);
#ifndef QT_NO_CURSOR
	//Since the call to QTextStream::readAll() might take some time,
	//we set the cursor to be Qt::WaitCursor for the entire application while it goes on
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
	setCurrentFile(fileName);
	//display the string "File loaded" in the status bar for 2 seconds(2000 milliseconds)
	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool NoteBook::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Application"), tr("Can't write file %1:\n%2.").arg(fileName).arg(file.errorString()));
		return false;
	}
	QTextStream out(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

/*用来重置一些变量的状态*/
void NoteBook::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	textEdit->document()->setModified(false);
	setWindowModified(false);
	QString shownName = curFile;
	if (curFile.isEmpty())
		shownName = "untitled.txt";
	setWindowFilePath(shownName);//设置文件路径
}

/*切断文件路径以文件名作为窗口标题*/
QString NoteBook::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

NoteBook::~NoteBook()
{

}
