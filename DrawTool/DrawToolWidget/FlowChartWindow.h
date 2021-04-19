#ifndef FLOWCHARTWINDOW_H
#define FLOWCHARTWINDOW_H

#include <QMainWindow>
#include <QHash>

class CManagement;
class QHBoxLayout;
class CDragButton;
class PropertyWidget;
class CButtonGroup;
namespace Ui {
class MainWindow;
}

class FlowChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlowChartWindow(QWidget *parent = 0);
    ~FlowChartWindow();

private slots:
    void slot_Test();

    //新建
    void slot_NewItem(QString type);

    //编辑
    void slot_Edit();

    //结束编辑
    void slot_EditEnd();

    //画线
    void slot_EditFold();

    //插入点
    void slot_InsterPoint();

    //删除点
    void slot_DeletePoint();

    //顶置
    void slot_SetZValue();

    //删除
    void slot_Delete();

    //保存
    void slot_Save();

    //水平对齐
    void slot_HorizontalAlignment();

    //垂直对齐
    void slot_VerticalAlignment();

    void slot_AttrChanged(QString id, QString attr);

    void slot_Drag();

    void load(QString libName);

    void slot_CurrentChanged(QString oldId, QString currentId);

private:
    enum MenuType
    {
        Background,
        FlodLine,
        OtherItem
    };

    void createMenu();

    //操作折线
    void handFoldLine(int handle);

    void AlignmentType(QString type);

    Ui::MainWindow *            ui;
    CManagement*                m_Managment;
    QHBoxLayout*                m_MianLyout;
    CDragButton *               m_Button;
    PropertyWidget*             m_PropertyWidget;
    QHash<MenuType,QMenu*>      m_Menus;
    CButtonGroup *              m_NewBulidItemBtn;
    QString                     m_ToolFileName;
    QString                     m_ItemToolFileName;
    QAction*                    m_AlignmentAction;

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *);
};

#endif // FLOWCHARTWINDOW_H
