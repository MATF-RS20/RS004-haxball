#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);

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
    hide();
}
