#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QObject>

//Forward Declarations, possible since the private members are
// pointers which we dont access here

class QCheckbox;
class QLabel;
class QLineEdit;
class QPushbutton;

class FindDialog : QDialog {
    Q_OBJECT
public:
    FindDialog(QWidget *parent = nullptr);
signals:
    void findnext(const QString &str, Qt::CaseSensitivity cs);
    void findprev(const QString &str, Qt::CaseSensitivity cs);
private slots:
    void findclicked();
    void enableFindButton(const QString &text);
private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckbox *caseCheckBox;
    QCheckbox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif // FINDDIALOG_H
