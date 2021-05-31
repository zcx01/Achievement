#include "MyWidget.h"
#include <QTableWidget>
#include <QBoxLayout>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    QBoxLayout *la = new QHBoxLayout();
    la->addWidget(new QTableWidget);
}
