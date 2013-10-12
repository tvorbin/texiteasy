#ifndef WIDGETSTATUSBAR_H
#define WIDGETSTATUSBAR_H

#include <QStatusBar>
#include <QLabel>
#include <QDebug>

namespace Ui {
class WidgetStatusBar;
}
class QToolButton;
class QSplitter;
class QPixmap;
class QAction;

class WidgetStatusBarButton : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetStatusBarButton(QWidget * parent) :
        QWidget(parent),
        _action(0),
        _checked(false),
        _defaultPixmap(0),
        _hoverPixmap(0),
        _label(new QLabel(this))
    {
        this->setCursor(Qt::PointingHandCursor);
        this->setMinimumSize(20,20);
    }
    void      setAction(QAction * action);
    QAction * action() { return _action; }

    void setPixmaps(QPixmap * defaultPixmap, QPixmap * hoverPixmap)
    {
        _defaultPixmap = defaultPixmap;
        _hoverPixmap   = hoverPixmap;
        if(_defaultPixmap)
        {
            _label->setPixmap(*_defaultPixmap);
        }
    }

    void setCheckable(bool checkable) { _checkable = checkable; }
    bool isCheckable() { return _checkable; }
    bool isChecked() { return _checked; }

public slots:
    void toggleChecked();
    void setChecked(bool checked) { if(_checked != checked) this->toggleCheckedWithoutTriggeringAction(); }
private slots:
    void toggleCheckedWithoutTriggeringAction();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);


QAction * _action;

QPixmap * _defaultPixmap;
QPixmap * _hoverPixmap;
QLabel  * _label;

bool _checkable;
bool _checked;

};

class WidgetStatusBar : public QStatusBar
{
    Q_OBJECT

public:
    explicit WidgetStatusBar(QWidget *parent);
    ~WidgetStatusBar();
    void initTheme();

public slots:
    void toggleConsole();
    void toggleErrorTable();
    void closeConsole();
    void closeErrorTable();
    void setPosition(int,int);
    void setEncoding(QString encoding);

    void updateButtons();
    void setLinkSyncAction(QAction * action) { _labelLinkSync->setAction(action); }
    
private:
    Ui::WidgetStatusBar *ui;
    QToolButton * _pushButtonConsole;
    QToolButton * _pushButtonErreurs;
    QLabel * _positionLabel;
    QLabel * _encodingLabel;
    WidgetStatusBarButton * _labelLinkSync;

    QLabel * _labelConsole;
    QLabel * _labelErrorTable;
    bool _errorTableOpen, _consoleOpen;
};

#endif // WIDGETSTATUSBAR_H
