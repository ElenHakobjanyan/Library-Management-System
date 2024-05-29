#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

void addBook(QSqlQuery &q, const QString &title, int year, const QVariant &authorId,
             const QVariant &genreId/*, int rating*/)
{
    q.addBindValue(title);
    q.addBindValue(year);
    q.addBindValue(authorId);
    q.addBindValue(genreId);
    //q.addBindValue(rating);

    q.exec();
    QString log = q.executedQuery();
}

QVariant addGenre(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

QVariant addAuthor(QSqlQuery &q, const QString &name, QDate birthdate)
{
    q.addBindValue(name);
    q.addBindValue(birthdate);
    q.exec();
    return q.lastInsertId();
}

const auto BOOKS_SQL = QLatin1String(R"(
    create table books(id integer primary key, title varchar, author integer,
                       genre integer, year integer)
    )");//rating integer

const auto AUTHORS_SQL =  QLatin1String(R"(
    create table authors(id integer primary key, name varchar, birthdate date)
    )");

const auto GENRES_SQL = QLatin1String(R"(
    create table genres(id integer primary key, name varchar)
    )");

const auto INSERT_AUTHOR_SQL = QLatin1String(R"(
    insert into authors(name, birthdate) values(?, ?)
    )");

const auto INSERT_BOOK_SQL = QLatin1String(R"(
    insert into books(title, year, author, genre)
                      values(?, ?, ?, ?)
    )");//rating

const auto INSERT_GENRE_SQL = QLatin1String(R"(
    insert into genres(name) values(?)
    )");

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("books", Qt::CaseInsensitive)
        && tables.contains("authors", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(BOOKS_SQL))
        return q.lastError();
    if (!q.exec(AUTHORS_SQL))
        return q.lastError();
    if (!q.exec(GENRES_SQL))
        return q.lastError();

    if (!q.prepare(INSERT_AUTHOR_SQL))
        return q.lastError();
    QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"), QDate(1920, 2, 1));
    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"), QDate(1904, 10, 2));
    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"), QDate(1948, 4, 28));

    if (!q.prepare(INSERT_GENRE_SQL))
        return q.lastError();
    QVariant fiction = addGenre(q, QLatin1String("Fiction"));
    QVariant novel = addGenre(q, QLatin1String("Novel"));
    QVariant non_fiction = addGenre(q, QLatin1String("Non-Fiction"));
    QVariant mystery = addGenre(q, QLatin1String("Mystery"));
    QVariant hfiction = addGenre(q, QLatin1String("Historical Fiction"));
    QVariant narrative = addGenre(q, QLatin1String("Narrative"));
    QVariant sfiction = addGenre(q, QLatin1String("Science Fiction"));
    QVariant rnovel = addGenre(q, QLatin1String("Romance Novel"));
    QVariant history = addGenre(q, QLatin1String("History"));
    QVariant sstory = addGenre(q, QLatin1String("Short Story"));
    QVariant memoir = addGenre(q, QLatin1String("Memoir"));
    QVariant gnovel = addGenre(q, QLatin1String("Graphic Novel"));
    QVariant childrens = addGenre(q, QLatin1String("Children's Literature"));
    QVariant thriller = addGenre(q, QLatin1String("Thriller"));
    QVariant selfhelp = addGenre(q, QLatin1String("Self-Help Book"));
    QVariant essay = addGenre(q, QLatin1String("Essay"));
    QVariant fantasy = addGenre(q, QLatin1String("Fantasy"));
    QVariant science = addGenre(q, QLatin1String("Science"));
    QVariant crime = addGenre(q, QLatin1String("True Crime"));
    QVariant humor = addGenre(q, QLatin1String("Humor"));
    QVariant horror = addGenre(q, QLatin1String("Horror Fiction"));
    QVariant adventure = addGenre(q, QLatin1String("Adventure Fiction"));
    QVariant cookbook = addGenre(q, QLatin1String("Cookbook"));
    QVariant dystopian = addGenre(q, QLatin1String("Dystopian Fiction"));

    if (!q.prepare(INSERT_BOOK_SQL))
        return q.lastError();
    addBook(q, QLatin1String("Foundation"), 1951, asimovId, sfiction);
    addBook(q, QLatin1String("Foundation and Empire"), 1952, asimovId, sfiction);
    addBook(q, QLatin1String("Second Foundation"), 1953, asimovId, sfiction);
    addBook(q, QLatin1String("Foundation's Edge"), 1982, asimovId, sfiction);
    addBook(q, QLatin1String("Foundation and Earth"), 1986, asimovId, sfiction);
    addBook(q, QLatin1String("Prelude to Foundation"), 1988, asimovId, sfiction);
    addBook(q, QLatin1String("Forward the Foundation"), 1993, asimovId, sfiction);
    addBook(q, QLatin1String("The Power and the Glory"), 1940, greeneId, fiction);
    addBook(q, QLatin1String("The Third Man"), 1950, greeneId, fiction);
    addBook(q, QLatin1String("Our Man in Havana"), 1958, greeneId, fiction);
    addBook(q, QLatin1String("Guards! Guards!"), 1989, pratchettId, fantasy);
    addBook(q, QLatin1String("Night Watch"), 2002, pratchettId, fantasy);
    addBook(q, QLatin1String("Going Postal"), 2004, pratchettId, fantasy);

    return QSqlError();
}

#endif
