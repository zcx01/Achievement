#ifndef BASEDRAWOBJECT_H
#define BASEDRAWOBJECT_H

#include <QWidget>
#include <QMenu>
#include <QBoxLayout>
#include "./HfFrameReflect/cmyregister_hf.h"

class CZDrawManagement;

class BaseDrawObject : public QObject
{
    Q_OBJECT
public:
    explicit BaseDrawObject(QWidget *parent = nullptr);
    virtual ~BaseDrawObject();

    bool InitManagement(QString configDirPath,QLayout *layout);

    virtual void contextMenuEvent(QContextMenuEvent *event);

signals:

public slots:

protected:
    virtual bool loadConfigFile(QString configDirPath,CZDrawManagement* m);

    virtual void ConnectSig(const bool &state);

    bool CreateItem(const QString &id,const QString &className,const QVariantMap *selfAttr);

    static QMenu *createMenu(QList<QString> actionNames,QList<QString> sequences,
                      QList<const char *> funs,QObject *receive, QList<int> separators = QList<int>());

    void Save();

    QHash<QString,QMenu*>       m_Menu;             //菜单
    CZDrawManagement*           m_DrawObj;          //绘图
    QString                     m_ToolFileName;
    QString                     m_ItemToolFileName;
    QString                     m_ItemFileName;
};

#endif // BASEDRAWOBJECT_H
