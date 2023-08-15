#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QJsonObject>
#include <QApplication>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->startBtn->setEnabled(false);
//    QtConcurrent::run(this,&MainWindow::ReadPy);
//    connect(this,&MainWindow::sig_ReadPy,this,&MainWindow::pyReadProcess);
    pyPro = new QProcess(this);
    connect(pyPro, SIGNAL(readyReadStandardOutput()), this, SLOT(pyReadProcess()));
    connect(pyPro, SIGNAL(finished(int)), this, SLOT(pyFinishedProcess()));
    connect(pyPro,&QProcess::errorOccurred,this,[=](QProcess::ProcessError err){qDebug()<<"error"<<err;});
    connect(pyPro,&QProcess::stateChanged,this,[=](QProcess::ProcessState err){qDebug()<<"state"<<err;});

    pyPro->start("bash");
    pyPro->waitForStarted();
    Out(ui->pyTextEdit,"sudo ip link add dev vcan0 type vcan");
    Out(ui->pyTextEdit,"sudo ip link set up vcan0");

    liPro = new QProcess(this);
    connect(liPro, SIGNAL(readyReadStandardOutput()), this, SLOT(liReadProcess()));
    liPro->start("bash");
    liPro->waitForStarted();

    QString jsonFile="./config.json";
    readConfigFile(jsonFile);
    if(dbcPath.isEmpty())
    {
        QVariantMap configData;
        configData["dbcPath"]="";
        configData["pyPath"]="";
        writeConfigFile(jsonFile,configData);
        QString openFileCmd;
#ifdef linux
        openFileCmd = "xdg-open";
#else
        openFileCmd="explorer";
#endif
        sendPyCmd(QString("%1 %2").arg(openFileCmd).arg(jsonFile));
        QApplication::exit(0);
    }
    analydbc();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_canBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();
    if(fileName.isEmpty())
    {
        QMessageBox::warning(this,"warn","文件名不能为空");
        return;
    }
    ui->canline->setText(fileName);
    canlog = fileName;
    ui->startBtn->setEnabled(true);
}


void MainWindow::on_startBtn_clicked()
{
//    sendPyCmd("python3 /home/chengxiongzhu/Works/Repos/back_play/mega_cantools_lib/blf_editor.py --replay can_log_20210927164452.blf");
//    sendliCmd("candump vcan0 | cantools decode /home/chengxiongzhu/Works/Repos/changan_c385/src/ic_service/parser/vendor/dbc_files/CAN0_C385EV-E_V2.1.0_20210713.dbc");
    if(ui->filterline->text().isEmpty())
    {
        sendPyCmd(QString("python3 %1 --replay %2").arg(pyPath).arg(canlog));
        sendliCmd(QString("candump vcan0 | cantools decode %1").arg(dbcPath));
    }
    else
    {
        auto sigName = ui->filterline->text().split("|");
        QString messageIds;
        for(auto sig : sigName)
        {
            int messgaId = sigMessageIds.value(sig,-1);
            if(messgaId == -1)
            {
                QMessageBox::warning(this,"warn",QString("信号不存在%1").arg(sig));
                return;
            }
            messageIds+= QString::number(messgaId)+",";
        }
        messageIds.chop(1);
        sendPyCmd(QString("python3 %1 --replay %2 --filter %3").arg(pyPath).arg(canlog).arg(messageIds));
        sendliCmd(QString("candump vcan0 | cantools decode %1 | grep -E \"%3\"").arg(dbcPath).arg(ui->filterline->text()));
    }
}

void MainWindow::pyReadProcess()
{
    Out(ui->pyTextEdit,pyPro->readAllStandardOutput());
}

void MainWindow::liReadProcess()
{
     Out(ui->liTextEdit,liPro->readAllStandardOutput());
}

void MainWindow::pyFinishedProcess()
{

}

void MainWindow::sendPyCmd(const QString &cmd)
{
    Out(ui->pyTextEdit,cmd);
    pyPro->write(cmd.toLocal8Bit()+"\n");
}

void MainWindow::sendliCmd(const QString &cmd)
{
    Out(ui->liTextEdit,cmd);
    liPro->write(cmd.toLocal8Bit()+"\n");
}

void MainWindow::ReadPy()
{
    while(1)
    {
        while (pyPro->bytesAvailable()) {
             emit sig_ReadPy();
        }
//        QThread::msleep(10);
    }
}

void MainWindow::Out(QTextEdit *edit, const QString &str)
{
    QTextCursor cursor = edit->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(str+"\n");
    edit->setTextCursor(cursor);
}

void MainWindow::readConfigFile(QString jsonFile)
{
    QFile loadFile(jsonFile);
    if(!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "could't open config file: " << jsonFile;
        return;
    }

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(allData, &jsonError));
    if(jsonError.error != QJsonParseError::NoError) {
        qWarning() << "json error: " << jsonError.errorString();
        return;
    }
    if(jsonDocument.isObject()){
        QVariantMap configData = jsonDocument.object().toVariantMap();
        dbcPath = configData.value("dbcPath").toString();
        pyPath = configData.value("pyPath").toString();
    }
}

void MainWindow::writeConfigFile(QString jsonFile, const QVariantMap &data)
{
    QJsonDocument jsonDocument(QJsonDocument::fromVariant(data));
    QFile loadFile(jsonFile);
    if(!loadFile.open(QIODevice::WriteOnly)) {
        qWarning() << "could't open config file: " << jsonFile;
        return;
    }
    loadFile.write(jsonDocument.toJson());
    loadFile.close();
}

void MainWindow::analydbc()
{
    QFile loadFile(dbcPath);
    if(!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "could't open config file: " << dbcPath;
        return;
    }
    int messageId;
    QTextStream stream(&loadFile);
    while (!stream.atEnd()) {
        QString text = stream.readLine();
        text=text.trimmed();
        if(text.startsWith("BO_"))
        {
            messageId = analyline(text,1).toInt();
            qDebug()<<messageId;
        }
        else if(text.startsWith("SG_"))
        {
            QString sigName = analyline(text);
            qDebug()<<sigName<<messageId;
            sigMessageIds.insert(sigName,messageId);
        }
    }

}

QString MainWindow::analyline(const QString &msg,int index)
{
    QString content =  msg.split(":").value(0);
    QStringList temp = content.trimmed().split(" ");
    QStringList contents;
    for (auto t : temp )
    {
        if(!t.isEmpty()&& t != "")
        {
            contents.append(t);
        }
    }
    if(index==-1)
    {
        index = contents.size()-1;
    }
    return contents.value(index);
}


void MainWindow::on_pushButton_clicked()
{
    ui->liTextEdit->clear();
    ui->pyTextEdit->clear();
}

