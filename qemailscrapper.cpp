/*
 * qemailscrapper.cpp
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

#include "qemailscrapper.h"
#include "src/mlfunctions.h"
#include "ui_qemailscrapper.h"
#include "aboutqemailscrapper.h"

QEmailScrapper::QEmailScrapper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QEmailScrapper)
{
    ui->setupUi(this);
    mui_statusbar = ui->statusBar;
    mui_toolbar = ui->mainToolBar;
    mui_bottombar = ui->toolBar;

    m_toolbar = ui->actionShowTopToolbar;
    m_bottombar = ui->actionShowBottomToolbar;

    m_unscrappedtext = ui->mui_unscrapped_text;
    m_scrappedtext = ui->mui_scrapped_text;
    __active = 0;
    g_text = m_unscrappedtext;

    g_filename = "";

    m_separator_one = "";
    m_separator_two = "\n";


    __minfontsize=1;
    setFontSize(11);




    connect(m_unscrappedtext,SIGNAL(textChanged()),this,SLOT(activated_unscrapped()));
    connect(m_scrappedtext,SIGNAL(textChanged()),this,SLOT(activated_scrapped()));

}

QEmailScrapper::~QEmailScrapper()
{
    delete ui;
    delete mui_statusbar;
    delete mui_toolbar;
    delete mui_bottombar;

    delete m_toolbar;
    delete m_bottombar;
}


void QEmailScrapper::on_actionFullScreen_triggered()
{
    fullscreen();
}

void QEmailScrapper::fullscreen()
{
    if ( isFullScreen() ) {
        showNormal();
        mui_statusbar->showMessage("Full screen disabled");
    } else {
        showFullScreen();
        mui_statusbar->showMessage("Full screen enabled");
    } // end if
}

void QEmailScrapper::setFontSize(const int &points)
{
    g_font = QFont("Arial");
    g_fontsize=points;
    g_font.setPointSize(g_fontsize);
    m_unscrappedtext->setFont(g_font);
    m_scrappedtext->setFont(g_font);
}

void QEmailScrapper::on_actionShowTopToolbar_triggered(bool checked)
{
    if (checked == true)
    {
        mui_toolbar->show();
        mui_statusbar->showMessage("Main toolbar visible");
    } else
    {
        mui_toolbar->hide();
        mui_statusbar->showMessage("Main toolbar hidden");
    } // end if
}

void QEmailScrapper::on_actionShowBottomToolbar_triggered(bool checked)
{
    if (checked == true)
    {
        mui_bottombar->show();
        mui_statusbar->showMessage("Bottom toolbar visible");
    } else
    {
        mui_bottombar->hide();
        mui_statusbar->showMessage("Bottom toolbar hidden");
    } // end if

}

void QEmailScrapper::on_actionCut_triggered()
{
    if (g_text) {
        m_scrappedtext->cut();
    } // end if
}

void QEmailScrapper::on_actionCopy_triggered()
{
    if (g_text) {
        m_scrappedtext->copy();
    } // end if
}

void QEmailScrapper::on_actionPaste_triggered()
{
    if (g_text) {
        m_scrappedtext->paste();
    } // end if
}

void QEmailScrapper::on_actionDelete_triggered()
{
    if (g_text) {
        g_text->textCursor().removeSelectedText();
    } // end if
}



void QEmailScrapper::on_actionUndo_triggered()
{
    if (g_text)
    {
        g_text->undo();
    } // end if
}

void QEmailScrapper::on_actionRedo_triggered()
{
    if (g_text)
    {
        g_text->redo();
    } // end if
}

void QEmailScrapper::on_actionOpenFile_triggered()
{
    /// Open file dialog
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Supported files (*.txt *.sql *.md *.sqlite *.pro *.ui *.cpp *.h *.cxx *.hxx *.hpp *.user *.conf *.po *.pot *.js *.html *.html *.css *.py *.java *.class *.rb)");
    g_filename = fileName;
    openFile(fileName);
}

void QEmailScrapper::openFile(const QString &filechosed)
{
    /// Open desired file
    QFile textfile( filechosed );
    if (textfile.open(QIODevice::ReadOnly))
    {
        // Declare pointers and variables
        QTextStream text_stream(&textfile);
        QFileInfo file_info(textfile);

        m_unscrappedtext->clear();
        m_unscrappedtext->appendPlainText(text_stream.readAll());

    } // end if
    textfile.close();
}

void QEmailScrapper::activated_unscrapped() {
    __active = 0;
    g_text = m_unscrappedtext;
}

void QEmailScrapper::activated_scrapped() {
    __active = 1;
    g_text = m_scrappedtext;
}

void QEmailScrapper::on_actionScrap_triggered()
{
    QString contentUncrapped = m_unscrappedtext->toPlainText();


    QRegExp rx("([-a-zA-Z0-9._]+@[-a-zA-Z0-9_]+.[a-zA-Z0-9_.]+)");
    QString contentScrapped = "";
    int position = 0;

    while ((position = rx.indexIn(contentUncrapped, position)) != -1) {
        g_emailList << rx.cap(1);
        position += rx.matchedLength();
    } // end while
    g_emailList.removeDuplicates();

    if ( !g_emailList.isEmpty() ) {
        for (QStringList::iterator it = g_emailList.begin(); it != g_emailList.end(); ++it) {
            QString iter = *it;
            contentScrapped += QString(iter+m_separator_one + m_separator_two);
        } // end for
    } // end if

    m_scrappedtext->clear();
    m_scrappedtext->appendPlainText(contentScrapped.trimmed());
    mui_statusbar->showMessage("Scrap done");
}

void QEmailScrapper::on_actionErase_triggered()
{
    m_scrappedtext->clear();
    mui_statusbar->showMessage("Erased scrapped text");
}

void QEmailScrapper::on_actionSelectAll_triggered()
{
    g_text->selectAll();
    mui_statusbar->showMessage("All selected");
}

void QEmailScrapper::on_actionSpaces_triggered(bool checked)
{
    if (checked == true) {
        m_separator_two = " ";
        ui->actionList->setChecked(false);
    }
    else {
        m_separator_two = "\n";
        ui->actionList->setChecked(true);
    }
    changeSeparation( m_separator_one, m_separator_two );
}

void QEmailScrapper::on_actionList_triggered(bool checked)
{
    if (checked == true) {
        m_separator_two = "\n";
        ui->actionSpaces->setChecked(false);
    }
    else {
        m_separator_two = " ";
        ui->actionSpaces->setChecked(true);
    }
    changeSeparation( m_separator_one, m_separator_two );

}


void QEmailScrapper::on_actionCommas_triggered(bool checked)
{
    if (checked == true) {
        m_separator_one = ",";
        ui->actionSemicolon->setChecked(false);
    }
    else {
        m_separator_one = "";
    }
    changeSeparation( m_separator_one, m_separator_two );
}

void QEmailScrapper::on_actionSemicolon_triggered(bool checked)
{
    if (checked == true) {
        m_separator_one = ";";
        ui->actionCommas->setChecked(false);
    }
    else {
        m_separator_one = "";
    }
    changeSeparation( m_separator_one, m_separator_two );
}

void QEmailScrapper::changeSeparation(const QString &separator_one, const QString &separator_two )
{
    QString contentScrapped = "";
    m_separator_one=separator_one;
    m_separator_two=separator_two;
    int iterador = 0;
    if ( !g_emailList.isEmpty() ) {
        for (QStringList::iterator it = g_emailList.begin(); it != g_emailList.end(); ++it) {
            iterador +=1;
            QString iteritem = *it;
            if ( iterador == g_emailList.count() ) {
                contentScrapped += QString(iteritem);
            }
            else {
                contentScrapped += QString(iteritem + m_separator_one + m_separator_two);

            }
        } // end for
    } // end if

    m_scrappedtext->clear();
    m_scrappedtext->appendPlainText(contentScrapped.trimmed());
}

void QEmailScrapper::on_actionZoomIn_triggered()
{
    g_fontsize+=1;
    setFontSize(g_fontsize);
}

void QEmailScrapper::on_actionZoomOut_triggered()
{
    if (g_fontsize != __minfontsize)
    {
        g_fontsize-=1;
    }
    setFontSize(g_fontsize);
}

void QEmailScrapper::on_actionZoomReset_triggered()
{
    setFontSize(11);
}

void QEmailScrapper::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog* dialog = new QPrintDialog(&printer, this);
    if (dialog->exec() == QDialog::Accepted)
    {
        m_scrappedtext->print(&printer);
    } // end if
}

void QEmailScrapper::on_actionAboutQEmailScrapper_triggered()
{
    AboutQEmailScrapper about;
    about.exec();
    about.show();
}

void QEmailScrapper::on_actionSave_triggered()
{
    QFileInfo filename(g_filename);
    QString finalname = filename.absolutePath() + QDir::separator() + filename.baseName() + ".scrapped.txt";
    QString contentfile = m_scrappedtext->toPlainText() + "\n";
    if ( !finalname.isNull()) {
        saveFile(finalname,contentfile);
    }

}

void QEmailScrapper::on_actionSaveScrappedFileAs_triggered()
{
    QString contentfile = m_scrappedtext->toPlainText() + "\n";
    QString filenamestring = QFileDialog::getSaveFileName(
                                 this,
                                 "Save file",
                                 mlGetHome(),
                                 "Text file (*.txt)");
    if( !filenamestring.isNull() )
    {

        QFileInfo filename(filenamestring);
        QString finalname = filename.absoluteFilePath();
        saveFile(finalname,contentfile);
    }
}

void QEmailScrapper::saveFile(const QString &desiredfile, QString &desiredcontent)
{
    QString chosedfile = desiredfile;
    QString chosedcontent = desiredcontent;
    QFile file(chosedfile);
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        QTextStream stream( &chosedfile );
        file.write(chosedcontent.toAscii());
        file.close();
    }
    else {
        mlMsgError("The file can't be saved");
    } // end if
}

void QEmailScrapper::on_actionGotoBlockStart_triggered()
{
    g_text->moveCursor(QTextCursor::Start);
}

void QEmailScrapper::on_actionGotoBlockEnd_triggered()
{
    g_text->moveCursor(QTextCursor::End);
}
