#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QObject>
#include <QDialog>
#include "ui_importdialog.h"

class ImportDialog : public QDialog, public Ui::ImportDialog
{
    Q_OBJECT
public:
    explicit ImportDialog(QDialog *parent = 0);
    ~ImportDialog();

protected:
    void loadTextFile(QString fileName);

signals:

public slots:
    void accept();
    void browseClicked();
};

#endif // IMPORTDIALOG_H
