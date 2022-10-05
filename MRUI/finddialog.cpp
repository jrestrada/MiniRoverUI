#include <QtGui> // contains QtCore and QtGui modules
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent){
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckbox(tr("Match &case"));
    backwardCheckBox new QCheckbox(tr("Search &backward"));
}
