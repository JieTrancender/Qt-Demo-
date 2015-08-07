#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QMainWindow>
#include "ui_notebook.h"

class QPlainTextEdit;
class QAction;
class QMenu;
class QPlainTextEdit;

class NoteBook : public QMainWindow
{
	Q_OBJECT

public:
	NoteBook(QWidget *parent = 0);
	~NoteBook();

protected:
	void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void about();
	void documentWasModified();

private:
	Ui::NoteBookClass ui;
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool maybeSave();
	void loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);

	QPlainTextEdit *textEdit;
	QString curFile;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
};

#endif // NOTEBOOK_H
