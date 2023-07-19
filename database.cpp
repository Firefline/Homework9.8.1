#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    simpleQuery = new QSqlQueryModel();
    notSimpleQuery = new QSqlTableModel();
    tableWinget = new QTableView();


}

DataBase::~DataBase()
{
    delete dataBase;
    delete simpleQuery;
    delete tableWinget;
    delete notSimpleQuery;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());


    ///Тут должен быть код ДЗ


    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::ReceiveType(int type)
{
    if (type == 0)
    {
        typeOfRequest = 0;
    }
    if (type == 1)
    {
        typeOfRequest = 1;
    }
    if (type == 2)
    {
        typeOfRequest = 2;
    }
}
void DataBase::RequestToDB(QString request)
{

    ///Тут должен быть код ДЗ

    if (typeOfRequest == 0)
    {
        notSimpleQuery->setTable("film");
        notSimpleQuery->setEditStrategy(QSqlTableModel::OnManualSubmit);
        notSimpleQuery->select();
        notSimpleQuery->setHeaderData(0, Qt::Horizontal, tr("title"));
        notSimpleQuery->setHeaderData(1, Qt::Horizontal, tr("description"));

        emit sig_SendDataFromDBAll(notSimpleQuery, request);
    }
    if (typeOfRequest == 1 || typeOfRequest == 2)
    {
        simpleQuery->setQuery (request, *dataBase);
        if (simpleQuery->lastError().isValid())
        {
            qDebug() << simpleQuery->lastError();
        }
        simpleQuery->setHeaderData(0, Qt::Horizontal, tr("Title"));
        simpleQuery->setHeaderData(1, Qt::Horizontal, tr("Description"));

        emit sig_SendDataFromDB(simpleQuery, request);
    }

}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
