#ifndef DRAWWIDGETFACTORY_H
#define DRAWWIDGETFACTORY_H

#include <QWidget>
class BaseDrawObject;

class DrawWidgetFactory : public QWidget
{
    Q_OBJECT

public:
    DrawWidgetFactory(QWidget *parent = 0);
    ~DrawWidgetFactory();

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:

    bool LoadConfig(QString onfigFilePath);

    void load(QString libName);

private:
    QHash<QString,BaseDrawObject*>   m_Objs;
};

#endif // DRAWWIDGETFACTORY_H
