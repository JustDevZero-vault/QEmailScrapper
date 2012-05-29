/*
 * template.cpp
 * Translatorman: Utility for translating or just writing, manpages into other languages.
 * Copyright (C) 2012  Daniel Ripoll <info@danielripoll.es>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/* 
\ This is a template.cpp file
*/

#ifndef ABOUTQEMAILSCRAPPER_H
#define ABOUTQEMAILSCRAPPER_H

#include <QDialog>

namespace Ui {
    class AboutQEmailScrapper;
}

class AboutQEmailScrapper : public QDialog
{
    Q_OBJECT

public:
    explicit AboutQEmailScrapper(QWidget *parent = 0);
    ~AboutQEmailScrapper();

    /*private slots:
        void on_closeButton_clicked();*/

    private:
    Ui::AboutQEmailScrapper *ui;
};

#endif // ABOUTQEMAILSCRAPPER_H
