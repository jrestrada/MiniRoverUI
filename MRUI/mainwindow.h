#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void resetValue();
    void quitApp();
private:
    QSpinBox *spinbox;
    QSlider *slider;
    QLabel *label;
    QPushButton *quitbutton;
    QPushButton *resetVal;
    QListWidget *customerList;
};
#endif // MAINWINDOW_H
