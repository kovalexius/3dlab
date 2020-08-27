#include "my_dialog.h"

MyDialog::MyDialog(QWidget* _parent, Qt::WFlags _flags) : 
												QDialog(_parent, _flags)
{
	m_grid = new QGridLayout(this);
	m_grid->setMargin(0);

	m_ok = new QPushButton("ok", this);
	m_cancel = new QPushButton("cancel", this);

	m_grid->addWidget(m_ok, 1, 1);
	m_grid->addWidget(m_cancel, 1, 2);

	QObject::connect(m_ok, SIGNAL(clicked()), this, SLOT(slotOk()));
	QObject::connect(m_cancel, SIGNAL(clicked()), this, SLOT(slotCancel()));
}

MyDialog::~MyDialog()
{}

void MyDialog::slotOk()
{
	done(QDialog::Accepted);
}

void MyDialog::slotCancel()
{
	done(QDialog::Rejected);
}