#ifndef MYHORIZONTALHEADER_H
#define MYHORIZONTALHEADER_H


#include <QHeaderView>
#include <QComboBox>
#include <QTableView>

class MyHorizontalHeader : public QHeaderView
{
Q_OBJECT

public:
    QComboBox *boxes[10];

    MyHorizontalHeader(QWidget *parent = 0);
    virtual ~MyHorizontalHeader();
    void showEvent(QShowEvent *e);

public slots:
    void handleSectionResized(int i);
    void handleSectionMoved(int logical, int oldVisualIndex, int newVisualIndex);

    void fixComboPositions();

}; // class MyHorizontalHeader

class MyQTableView : public QTableView
{

public:
    MyHorizontalHeader *horizHeader;

    MyQTableView(QWidget * parent = 0);
    void scrollContentsBy(int dx, int dy);
};

#endif // MYHORIZONTALHEADER_H
