#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainInterface; }
QT_END_NAMESPACE

class MainInterface : public QMainWindow
{
    Q_OBJECT

public:
    MainInterface(QWidget *parent = nullptr);
    ~MainInterface();

private:
    Ui::MainInterface *ui;
};
#endif // MAININTERFACE_H
