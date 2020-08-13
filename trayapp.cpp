#include "trayapp.h"

#include <QCoreApplication>
#include <QDebug>

TrayApp::TrayApp()
    :  m_icon("/home/andres/dev/qt/projects/todo-tray/todo.png")
{
    alertAction = new QAction(tr("&Show message"), this);
    connect(alertAction, &QAction::triggered, [&] () {
        trayIcon->showMessage("title","message");
    });

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(alertAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayApp::iconActivated);

    trayIcon->setIcon(m_icon);

    trayIcon->show();

    m_list_widget = new ListWidget();
}

void TrayApp::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if (m_list_widget->isVisible()) {
            m_list_widget->hide();
        } else {
            m_list_widget->show();
        }
        break;
    case QSystemTrayIcon::DoubleClick:
        QCoreApplication::quit();
        break;
    default:
        ;
    }
}
