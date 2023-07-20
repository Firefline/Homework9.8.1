#ifndef DATABASE_H
#define DATABASE_H

#include <QTableWidget>
#include <QObject>
#include <QSqlDataBase>
#include <QSqlError>
//#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlTableModel>



#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

//Перечисление полей данных
enum fieldsForConnect{
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

//Типы запросов
enum requestType{

    requestAllFilms = 0,
    requestComedy   = 1,
    requestHorrors  = 2

};



class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB = "");
    void DisconnectFromDataBase(QString nameDb = "");
    void RequestToDB(QString request);
    QSqlError GetLastError(void);
    void ConnectToDataBase(QVector<QString> dataForConnect);
    void ReceiveType(int type);
    int typeOfRequest = 0;


signals:

   void sig_SendDataFromDB(QSqlQueryModel * model, QString typeR);
   void sig_SendDataFromDBAll(QSqlTableModel * model, QString typeR);
   void sig_SendStatusConnection(bool);



private:

    QSqlDatabase* dataBase;
    QSqlQueryModel* simpleQuery;
    QTableView* tableWinget;
    QSqlTableModel* notSimpleQuery;


};

#endif // DATABASE_H
