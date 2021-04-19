#include "ObjectFactory.h"
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QToolButton>
#include <QAbstractSlider>
#include <QAbstractSpinBox>
#include <QCalendarWidget>
#include <QComboBox>
#include <QDesktopWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDockWidget>
#include <QFocusFrame>
#include <QFrame>
#include <QGroupBox>

#if QT_VERSION >= 0x050000
#include <QKeySequenceEdit>
#include <QOpenGLWidget>
#else
#endif

#include <QLineEdit>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QSplashScreen>
#include <QStatusBar>
#include <QTabBar>
#include <QTabWidget>
#include <QToolBar>
#include <QWizardPage>

//#include <QMacCocoaViewContainer>
//#include <QMacNativeWidget>
//#include <QRubberBand>
//#include <QSizeGrip>
//#include <QSplitterHandle>

ObjectFactory *ObjectFactory::getInstance()
{
    ObjectFactory m_Instance;
    return &m_Instance;
}

ObjectFactory::ObjectFactory()
{
    MYRESISCOPY(QWidget);
    MYRESISCOPY(QPushButton);
    MYRESISCOPY(QCheckBox);
    MYRESISCOPY(QRadioButton);
    MYRESISCOPY(QToolButton);
    MYRESISCOPY(QAbstractSlider);
    MYRESISCOPY(QAbstractSpinBox);
    MYRESISCOPY(QCalendarWidget);
    MYRESISCOPY(QComboBox);
    MYRESISCOPY(QDesktopWidget);
    MYRESISCOPY(QDialog);
    MYRESISCOPY(QDialogButtonBox);
    MYRESISCOPY(QDockWidget);
    MYRESISCOPY(QFocusFrame);
    MYRESISCOPY(QFrame);
    MYRESISCOPY(QGroupBox);
#if QT_VERSION >= 0x050000
    MYRESISCOPY(QKeySequenceEdit);
    MYRESISCOPY(QOpenGLWidget);
#endif
    MYRESISCOPY(QLineEdit);
    MYRESISCOPY(QMainWindow);
    MYRESISCOPY(QMdiSubWindow);
    MYRESISCOPY(QMenu);
    MYRESISCOPY(QMenuBar);

    MYRESISCOPY(QProgressBar);
    MYRESISCOPY(QSplashScreen);
    MYRESISCOPY(QStatusBar);
    MYRESISCOPY(QTabBar);
    MYRESISCOPY(QTabWidget);
    MYRESISCOPY(QToolBar);
    MYRESISCOPY(QWizardPage);

    //MYRESISCOPY(QMacCocoaViewContainer);
    //MYRESISCOPY(QMacNativeWidget);
    //MYRESISCOPY(QSplitterHandle);
    //MYRESISCOPY(QRubberBand);
    //MYRESISCOPY(QSizeGrip);
}

