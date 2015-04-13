#include "MyHorizontalHeader.h"
#include <QVariant>

#include "importgpsmodel.h"

MyHorizontalHeader::MyHorizontalHeader(QWidget *parent)
                  : QHeaderView(Qt::Horizontal, parent)
{
	 connect(this, SIGNAL(sectionResized(int, int, int)), this,
			 SLOT(handleSectionResized(int)));
	 connect(this, SIGNAL(sectionMoved(int, int, int)), this,
			 SLOT(handleSectionMoved(int, int, int)));
	 setSectionsMovable(true);

	 for (int i = 0; i < 10; i++)
	 {
		 boxes[i] = NULL;
	 }
}

MyHorizontalHeader::~MyHorizontalHeader()
{
}

void MyHorizontalHeader::showEvent(QShowEvent *e)
{
	for (int i=0;i<count();i++) {
	   if (!boxes[i]) {
		  QComboBox *box = new QComboBox(this);
		  box->addItem("test 1");
		  box->addItem("test 2");
		  boxes[i] = box;
	   }
	   boxes[i]->setGeometry(sectionViewportPosition(i), 0,
								sectionSize(i) - 5, height());
	   boxes[i]->show();
	}
	QHeaderView::showEvent(e);
}

void MyHorizontalHeader::handleSectionResized(int i)
{
	for (int j=visualIndex(i);j<count();j++) {
		int logical = logicalIndex(j);
		boxes[logical]->setGeometry(sectionViewportPosition(logical), 0,
									   sectionSize(logical) - 5, height());
	}
}
void MyHorizontalHeader::handleSectionMoved(int logical, int oldVisualIndex, int newVisualIndex)
{
	for (int i=qMin(oldVisualIndex, newVisualIndex);i<count();i++){
		int logical = logicalIndex(i);
		boxes[logical]->setGeometry(sectionViewportPosition(logical), 0,
									   sectionSize(logical) - 5, height());
	}
}

void MyHorizontalHeader::fixComboPositions()
{
	for (int i = 0; i<count();i++)
		boxes[i]->setGeometry(sectionViewportPosition(i), 0,
							  sectionSize(i) - 5, height());
}

MyQTableView::MyQTableView(QWidget * parent) : QTableView(parent)
{
	horizHeader = new MyHorizontalHeader;
	setHorizontalHeader(horizHeader);
}

void MyQTableView::scrollContentsBy(int dx, int dy)
{
   QTableView::scrollContentsBy(dx, dy);

   if (dx != 0)
	  horizHeader->fixComboPositions();
}

