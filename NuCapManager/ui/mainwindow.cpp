#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <utils/Log.h>

#define LOG_TAG                         "MAIN_WINDOW"
#include "utils/Log.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    t = new QtTelnet;

    connect(t, SIGNAL(message(const QString &)),
            this, SLOT(telnetMessage(const QString &)));
    connect(t, SIGNAL(loginRequired()),
            this, SLOT(telnetLoginRequired()));
    connect(t, SIGNAL(loginFailed()),
            this, SLOT(telnetLoginFailed()));
    connect(t, SIGNAL(loggedOut()),
            this, SLOT(telnetLoggedOut()));
    connect(t, SIGNAL(loggedIn()),
            this, SLOT(telnetLoggedIn()));
    connect(t, SIGNAL(connectionError(QAbstractSocket::SocketError)),
            this, SLOT(telnetConnectionError(QAbstractSocket::SocketError)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

ServerRequest MainWindow::parseServerRequestMsg(const QString &msg)
{
    if (msg.contains("Username:"))
        return ServerRequest::REQ_RAISECOM_LOGIN_USERNAME;

    else if (msg.contains("Password:"))
        return ServerRequest::REQ_RAISECOM_LOGIN_PASSWORD;

    else if (msg.contains("nufront login:"))
        return ServerRequest::REQ_CAP_LOGIN_USERNAME;

    else
        return ServerRequest::REQ_UNKNOWN;
}

void
MainWindow::handleServerRequestMsg(const ServerRequest req)
{
    switch (req) {
    case ServerRequest::REQ_RAISECOM_LOGIN_USERNAME:
        t->sendData("admin");
        break;

    case ServerRequest::REQ_RAISECOM_LOGIN_PASSWORD:
        t->sendData("!iK9u5!!fUkjKou!9klIUf!23mjJD123r!87k!");
        break;

    case ServerRequest::REQ_CAP_LOGIN_USERNAME:
        t->sendData("root");
        break;

    default:
        break;
    }
}

void
MainWindow::telnetMessage(const QString &msg)
{
    ui->textEdit->append(stripCR(msg));
    handleServerRequestMsg(parseServerRequestMsg(stripCR(msg)));
    //QScrollBar *s = ui->textEdit->verticalScrollBar();
    //s->setValue(s->maximum());
}

void
MainWindow::telnetLoginRequired()
{
    ALOGDTRACE();
}

void
MainWindow::telnetLoginFailed()
{
    ALOGDTRACE();
}

void
MainWindow::telnetLoggedOut()
{
    ALOGDTRACE();
}

void
MainWindow::telnetLoggedIn()
{
    ALOGDTRACE();
}

void
MainWindow::telnetConnectionError(QAbstractSocket::SocketError error)
{
    ui->lineEdit_status->setText(QString("Connection error: %1").arg(error));
}

void
MainWindow::on_pushButton_connect_clicked()
{
    t->connectToHost("113.64.223.6", 2306);
}

QString
MainWindow::stripCR(const QString &msg)
{
    QString nmsg(msg);
    nmsg.remove('\r');
    nmsg.remove(QRegExp("\033\\[[0-9;]*[A-Za-z]")); // Also remove terminal control codes
    return nmsg;
}

void
MainWindow::on_pushButton_Send_clicked()
{
    QString aux;
    aux = ui->lineEdit_data->text();

    t->sendData(aux);

    ui->lineEdit_data->clear();
}
