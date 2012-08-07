/*
 * aboutqemailscrapper.cpp
 * QEmailScrapper: Utility for scrapping a file in search of emails
 * Copyright (C) 2012  Daniel Ripoll <info@danielripoll.es>
 * http://danielripoll.es
 *

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

#include "aboutqemailscrapper.h"
#include "ui_aboutqemailscrapper.h"


AboutQEmailScrapper::AboutQEmailScrapper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutQEmailScrapper)
{
    ui->setupUi(this);
    ui->mui_texbrowser->viewport()->setAutoFillBackground(false);
    ui->mui_texbrowser->setFrameShape(QTextBrowser::NoFrame);
    ui->mui_texbrowser->setFrameShadow(QTextBrowser::Plain);
    ui->mui_logo->viewport()->setAutoFillBackground(false);
    ui->mui_logo->setFrameShape(QTextBrowser::NoFrame);
    ui->mui_logo->setFrameShadow(QTextBrowser::Plain);

    QString qtversion_string = ui->mui_version->text();
    qtversion_string.replace("__QTVERSION__",QT_VERSION_STR);
    qtversion_string.replace("__ARCH__",mlGetArch());
    ui->mui_version->setText(qtversion_string);

    QString version_string = ui->mui_title->text();
    version_string.replace("__VERSION__",mlGetVersion());
    ui->mui_title->setText(version_string);
}

AboutQEmailScrapper::~AboutQEmailScrapper()
{
    delete ui;
}
