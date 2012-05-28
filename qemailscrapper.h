/*
 * qemailscrapper.h
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


#ifndef QEMAILSCRAPPER_H
#define QEMAILSCRAPPER_H

#include <QMainWindow>
#include <QAction>
#include <QStatusBar>
#include <QToolBar>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFile>

namespace Ui {
    class QEmailScrapper;
}

class QEmailScrapper : public QMainWindow
{
    Q_OBJECT

public:
    explicit QEmailScrapper(QWidget *parent = 0);
        int active_plaintextedit;
        QPlainTextEdit *g_text;
        QStringList g_emailList;
        QString g_separator;
        QString g_filename;
    ~QEmailScrapper();

   private slots:

        void fullscreen();
        void activated_unscrapped();
        void activated_scrapped();
        void openFile(const QString &filechosed);
        void changeSeparation(const QString &separator);

        void on_actionFullScreen_triggered();

        void on_actionShowTopToolbar_triggered(bool checked);

        void on_actionShowBottomToolbar_triggered(bool checked);

        void on_actionCut_triggered();

        void on_actionCopy_triggered();

        void on_actionPaste_triggered();

        void on_actionDelete_triggered();

        void on_actionUndo_triggered();

        void on_actionRedo_triggered();

        void on_actionOpenFile_triggered();

        void on_actionScrap_triggered();

        void on_actionErase_triggered();

        void on_actionSelectAll_triggered();

        void on_actionSpaces_triggered();

        void on_actionList_triggered();

        void on_actionCommas_triggered();

        void on_actionSemicolon_triggered();

    private:
        Ui::QEmailScrapper *ui;

        QAction *m_toolbar;
        QAction *m_bottombar;

        QPlainTextEdit *m_unscrappedtext;
        QPlainTextEdit *m_scrappedtext;

        QStatusBar *mui_statusbar;
        QToolBar *mui_toolbar;
        QToolBar *mui_bottombar;
};

#endif // QEMAILSCRAPPER_H
