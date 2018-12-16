#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "globals.h"
#include "mainwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Вход");
    LoginWindow::setFixedSize(250, 80);
    LoginWindow::layout()->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout->setSpacing(6);
    ui->widget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout->setSpacing(0);
    ui->horizontalLayout_2->setContentsMargins(6, 0, 6, 0);
    ui->horizontalLayout_4->setContentsMargins(6, 0, 6, 0);

    db = QSqlDatabase::addDatabase(db_Type);
    db.setHostName(db_HostName);
    db.setDatabaseName(db_DatabaseName);
    db.setUserName(db_UserName);
    db.setPassword(db_Password);

    if (!db.open() || !db.isValid()) { qDebug() << "Error (Connecting database): " << db.lastError().text(); return; }
    else qDebug() << "Connection success " << QSqlDatabase::database().connectionNames();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool login(QString name, QString pass)
{
    QSqlQuery q;
    q.exec("SELECT * FROM `users`");
    //q.next();
    q.first();

    for (int i = 0; i<=q.size(); i++)
    {
        if (name == q.value(0).toString() && pass == q.value(1).toString())
        {
            user = q.value(2).toString();
            username = q.value(3).toString();
            return true;
        }
        q.next();
    }
    return false;
}

void LoginWindow::on_pushButton_Login_clicked()
{
    QString name = ui->lineEdit_Login->text(), pass = ui->lineEdit_Pass->text();

    if (!login(name, pass) || name == "" || pass == "") QMessageBox::warning(this, tr("Ошибка"), tr("Неправильный логин и/или пароль"));
    else
    {
        /*if (user == "Заказчик")
        {
            //CustomerWindow *cw = new CustomerWindow;
            //cw->show();

            MainWindow w;
            w.showc();

            //this->hide();
        }
        else
        {*/


        QSqlQuery q;
        q.exec("SELECT * FROM `cloths`");
        q.first();

        for (int i = 0; i<q.size(); i++)
        {
            BDItemClothsData data;
            data.ID = q.value(0).toString();
            data.Name = q.value(1).toString();
            data.Color = q.value(2).toString();
            data.Pattern = q.value(3).toString();
            data.Composition = q.value(4).toString();
            data.Width = q.value(5).toString();
            data.Length = q.value(6).toString();
            data.Price = q.value(7).toString();
            clothsData.push_back(data);
            q.next();
        }

        QSqlQuery q2;
        q2.exec("SELECT * FROM `furniture`");
        q2.first();

        for (int i = 0; i<q.size(); i++)
        {
            BDItemFurnitureData data;
            data.ID = q2.value(0).toString();
            data.Name = q2.value(1).toString();
            data.Width = q2.value(2).toString();
            data.Length = q2.value(3).toString();
            data.Type = q2.value(4).toString();
            data.Price = q2.value(5).toString();
            furnitureData.push_back(data);
            q2.next();
        }


        QSqlQuery q3;
        q3.exec("SELECT * FROM `products`");
        q3.first();

        for (int i = 0; i<q.size(); i++)
        {
            BDItemProductData data;
            data.ID = q3.value(0).toString();
            data.Name = q3.value(1).toString();
            data.Width = q3.value(2).toString();
            data.Length = q3.value(3).toString();
            data.Price = q3.value(4).toString();
            productData.push_back(data);
            q3.next();
        }

            MainWindow *w = new MainWindow(NULL, clothsData, furnitureData, productData);
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->show();
            w->activateWindow();

            this->close();

            //w->clothsData = clothsData;

            //db.close();
        //}

    }

}

/*bool loadDB()
{
    QSqlQuery q;
    q.exec("SELECT * FROM `cloths`");
    q.first();

    for (int i = 0; i<q.size(); i++)
    {
        BDItemClothsData data;
        data.ID = q.value(0).toString();
        data.Name = q.value(1).toString();
        data.Color = q.value(2).toString();
        data.Pattern = q.value(3).toString();
        data.Composition = q.value(4).toString();
        data.Width = q.value(5).toString();
        data.Length = q.value(6).toString();
        data.Price = q.value(7).toString();
        //clothsData = {};s
    }
}
*/
