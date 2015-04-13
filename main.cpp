#include <QtWidgets>
#define MAX_COLUMN_COUNT 30

#include "customtableheader.h"

class HeaderObject : public QWidget{

    QGridLayout *layout;
    QComboBox *comboBox;
    QCheckBox *checkBox;

public:
    HeaderObject(QWidget *parent = 0) : QWidget(parent){
        comboBox = new QComboBox(this);
        comboBox->addItem("test");
        comboBox->addItem("test2");
        comboBox->addItem("test3");
        comboBox->addItem("test4");

        checkBox = new QCheckBox(this);
        checkBox->setChecked(true);

        layout = new QGridLayout;
        layout->addWidget(comboBox);
        layout->addWidget(checkBox);

        setLayout(layout);
    }
};

class CustomHeader : public QHeaderView{
public:
    CustomHeader(QWidget *parent = 0):QHeaderView(Qt::Horizontal, parent){

        for(int i = 0; i < MAX_COLUMN_COUNT; i++){
            headerSections.insert(i,new HeaderObject(this));
            headerSections[i]->hide();
        }

        //setFont(QFont("Helvetica [Cronyx]", 32));
        //setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        setMinimumSectionSize(headerSections[0]->minimumSizeHint().width());
        setDefaultSectionSize(headerSections[0]->minimumSizeHint().width());
    }
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
    {
        if (!rect.isValid())
            return;
        //qDebug() << logicalIndex;
        //qDebug() << "QRect: " << rect << " AND OFFSET:" << offset();
        headerSections[logicalIndex]->setGeometry(rect);
        headerSections[logicalIndex]->show();
    }

    QSize sizeHint() const
    {
        QSize s = size();
        s.setHeight(headerSections[0]->minimumSizeHint().height());
        return s;
    }

private:
    mutable QVector< QPointer <HeaderObject> > headerSections;
};


class CustomModel : public QAbstractTableModel
{
public:
    CustomModel() : QAbstractTableModel(){
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        return 10;
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const
    {
        return 20;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (role == Qt::DisplayRole) return QVariant();
        return QVariant();
    }
};

class MyHorizontalHeader : public QHeaderView{

public:
    QComboBox *boxes[MAX_COLUMN_COUNT];

    MyHorizontalHeader(QWidget *parent = 0) : QHeaderView(Qt::Horizontal, parent)
    {
         connect(this, SIGNAL(sectionResized(int, int, int)), this,
                 SLOT(handleSectionResized(int)));
         connect(this, SIGNAL(sectionMoved(int, int, int)), this,
                 SLOT(handleSectionMoved(int, int, int)));
         setSectionsMovable(true);

         for (int i = 0; i < MAX_COLUMN_COUNT; i++)
         {
             boxes[i] = NULL;
         }
    }

    void showEvent(QShowEvent *e)
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

    void handleSectionResized(int i)
    {
        for (int j=visualIndex(i);j<count();j++) {
            int logical = logicalIndex(j);
            boxes[logical]->setGeometry(sectionViewportPosition(logical), 0,
                                           sectionSize(logical) - 5, height());
        }
    }
    void handleSectionMoved(int logical, int oldVisualIndex, int newVisualIndex)
    {
        for (int i=qMin(oldVisualIndex, newVisualIndex);i<count();i++){
            int logical = logicalIndex(i);
            boxes[logical]->setGeometry(sectionViewportPosition(logical), 0,
                                           sectionSize(logical) - 5, height());
        }
    }

    void fixComboPositions()
    {
        for (int i = 0; i<count();i++)
            boxes[i]->setGeometry(sectionViewportPosition(i), 0,
                                  sectionSize(i) - 5, height());
    }

}; // class MyHorizontalHeader

class MyQTableView : public QTableView {

public:
    MyHorizontalHeader *horizHeader;
    CustomHeader *cusHeader;
    CheckedHeader *checkHeader;

    MyQTableView(QWidget * parent = 0) : QTableView(parent)
    {
        horizHeader = new MyHorizontalHeader;
        setHorizontalHeader(horizHeader);

        //cusHeader = new CustomHeader(this);
        //setHorizontalHeader(cusHeader);

        //checkHeader = new CheckedHeader(Qt::Horizontal, this);
        //setHorizontalHeader(checkHeader);
    }

    void scrollContentsBy(int dx, int dy)
    {
       QTableView::scrollContentsBy(dx, dy);

       if (dx != 0)
          horizHeader->fixComboPositions();
    }
};

int main(int argc, char *argv[])
{
 QApplication a(argc, argv);

    CustomModel *model = new CustomModel;
    MyQTableView *view = new MyQTableView();
    view->setModel(model);
    //view->setHorizontalHeader(new CustomHeader(view));
    //view->setHorizontalHeader(new MyHorizontalHeader(view));
    view->setMinimumSize(400, 200);
    view->show();
    return a.exec();
}
