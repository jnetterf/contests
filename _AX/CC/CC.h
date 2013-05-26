/***************************************************************************
 *                                                                         *
 *   copyright : (C) 2011 Joshua Netterfield                               *
 *                   joshua.netterfield@gmail.com                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CCLINEEDIT_H
#define CCLINEEDIT_H

#include <QLineEdit>
#include <QStringList>


/**
 * A category is a list of possible completions under a certain title.
 * For example, a Category could be a list of Vector names
 */
class Category : public QStringList {
    QString _title;
public:
    Category(QString title) : QStringList(), _title(title) { }
    Category(QString title, QString i) : QStringList(i), _title(title) { }
    Category(QString title, QStringList l) : QStringList(l), _title(title) { }
    const QString& title() { return _title; }
};

/**
 * A completion case applies to space-sperated words or [vector/scaler names in between square brackets] which begin with a certain prefix.
 * CompletionCases with longer prefixes are checked first. So, for example, if you want to create a list or CompletionCase for vectors and scalers,
 * but a phrase begining with \[ is not a vector, create an empty completion case with the prefix "\\[".
 */
class CompletionCase : public QList<Category> {
    QString _prefix;
public:
    CompletionCase(QString prefix) : QList<Category>(), _prefix(prefix) { }
    CompletionCase(QString prefix,QList<Category> l) : QList<Category>(l), _prefix(prefix) { }
    const QString& prefix() const { return _prefix; }
};

bool operator<(const CompletionCase&a,const CompletionCase&b);

class CategoricalCompleter;

class  CCLineEdit : public QLineEdit {
    Q_OBJECT
    CategoricalCompleter* _cc;
public:
    CCLineEdit(QWidget*p=0);
    CCLineEdit(const QString&s,QWidget*p=0);
    void init(QList<CompletionCase>* data);

public slots:
    void insert(const QString &i);
    void divide(QString x="\0");

protected:
    void keyPressEvent(QKeyEvent *);
signals:
    void newCurrentPrefix(QString);
};

#endif // ACLINEEDIT_H
