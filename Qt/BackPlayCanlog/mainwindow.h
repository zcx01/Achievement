#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sig_ReadPy();

private slots:
    void on_canBtn_clicked();

    void on_startBtn_clicked();

    void pyReadProcess();

    void liReadProcess();

    void pyFinishedProcess();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void sendPyCmd(const QString &cmd);

    void sendliCmd(const QString &cmd);

    void ReadPy();

    void Out(QTextEdit *edit,const QString &str);

    void readConfigFile(QString jsonFile);

    void writeConfigFile(QString jsonFile,const QVariantMap &data);

    void analydbc();

    QString analyline(const QString &msg,int index=-1);

    QString pyPath;
    QString dbcPath;
    QString canlog;

    QProcess* pyPro;
    QProcess* liPro;

    QHash<QString,int> sigMessageIds;
};
#endif // MAINWINDOW_H
