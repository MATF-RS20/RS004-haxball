#include "settings.h"
#include "ui_settings.h"
#include "mainwindow.hpp"
#include "clientsocket.hpp"
#include <QHostAddress>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    //setWindowFlag(Qt::FramelessWindowHint);

    ui->hostTextEdit->setText("127.0.0.1");
    ui->portTextEdit->setText("3334");

}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_cancelPushButton_clicked()
{
    hide();
}

void Settings::on_savePushButton_clicked()
{
    auto host = QHostAddress(ui->hostTextEdit->toPlainText().trimmed());
    quint16 port = static_cast<quint16>(ui->portTextEdit->toPlainText().trimmed().toUInt());

    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow != nullptr) {

        auto clientSocket = mainWindow->getClientSocket();
        clientSocket->disconnected();
        clientSocket->setHost(host);
        clientSocket->setPort(port);
        clientSocket->connectToServer(host, port);
    }

    hide();
}

void Settings::on_testButton_clicked()
{
    auto host = QHostAddress(ui->hostTextEdit->toPlainText().trimmed());
    quint16 port = static_cast<quint16>(ui->portTextEdit->toPlainText().trimmed().toUInt());

    ClientSocket clientSocketTest(host, port);
    bool connectResult = clientSocketTest.connectToServer(host, port);

    if(connectResult){
        ui->checkConnLabel->setText("Connection successful");
    }
    else{
        ui->checkConnLabel->setText("Connection refused");
    }

}
