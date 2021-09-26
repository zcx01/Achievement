#ifndef MAINNAVIGATIONWIDGET_H
#define MAINNAVIGATIONWIDGET_H

#include <QWidget>

class QPushButton;
class QTreeWidgetItem;
namespace Ui {
class MainNavigationWidget;
}

class MainNavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainNavigationWidget(QWidget *parent = 0);
    ~MainNavigationWidget();

    QTreeWidgetItem *AddWidget(QWindow *w,const QString &name,QTreeWidgetItem *parentItem=NULL,const int &index = -1);

private slots:
    void on_pushButton_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    void initWidget();

    Ui::MainNavigationWidget *ui;

    QHash<QString,QWidget *>  m_AllWidgets;
};

#endif // MAINNAVIGATIONWIDGET_H
