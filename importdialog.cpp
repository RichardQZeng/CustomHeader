// file head

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "importdialog.h"
#include "importgpsmodel.h"

ImportDialog::ImportDialog(QDialog *parent)
             : QDialog(parent)
{
    setupUi(this);
}

ImportDialog::~ImportDialog()
{
}

void ImportDialog::accept()
{
    QDialog::accept();
}

void ImportDialog::browseClicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,
                                                    tr("Open File"), "/home/zeng/Temp",
                                                    tr("Files (*.txt)"),
                                                    0,
                                                    QFileDialog::DontUseNativeDialog);

    //QString fileName("/home/zeng/Temp/gps-new.txt");
    if(!fileName.isEmpty())
    {
        loadTextFile(fileName);
    }
}

// load text file containing gps infomation
void ImportDialog::loadTextFile(QString fileName)
{
    QList< QStringList > lists;
    QFile inputFile(fileName);

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       QRegExp rx("(\\ |\\t)");

       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList tokens = line.split(rx);
          lists << tokens;
       }

       inputFile.close();
    }

    QMessageBox::information(this, tr("Infomation"),
                             "Text file loaded");
}
