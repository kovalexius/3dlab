#ifndef __MY_DIALOG__H
#define __MY_DIALOG__H

#include <QtGui>

class MyDialog : public QDialog
{
	Q_OBJECT
public:
	MyDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~MyDialog();

private slots:
	void slotOk();
	void slotCancel();

private:
	QPushButton* m_ok;
	QPushButton* m_cancel;
	QGridLayout* m_grid;
};

#endif