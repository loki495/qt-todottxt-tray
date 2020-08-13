#ifndef TRAYAPP_H
#define TRAYAPP_H

#include <QObject>
#include <QMenu>
#include <QSystemTrayIcon>

#include "listwidget.h"

class QIcon;

class TrayApp : public QMenu
{
    Q_OBJECT
public:
    TrayApp();

    void iconActivated(QSystemTrayIcon::ActivationReason );
private:
    QAction *alertAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QIcon m_icon;

    ListWidget *m_list_widget;
};

#endif // TRAYAPP_H
