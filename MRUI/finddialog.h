#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QObject>
#include <QCheckBox>

//Forward Declarations, possible since the private members are
// pointers which we dont access here

class QCheckbox;
class QLabel;
class QLineEdit;
class QPushbutton;

class FindDialog : public QDialog {
    Q_OBJECT
public:
    FindDialog(QWidget *parent = nullptr);
signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrev(const QString &str, Qt::CaseSensitivity cs);
private slots:
    void findClicked();
    void enableFindButton(const QString &text);
private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif // FINDDIALOG_H
