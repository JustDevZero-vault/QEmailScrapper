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
    m_vertical = ui->actionVertical;
    m_horizontal = ui->actionHorizontal;

    m_unscrappedtext = ui->mui_unscrapped_text;
    m_scrappedtext = ui->mui_scrapped_text;

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
    delete m_vertical;
    delete m_horizontal;
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

void QEmailScrapper::on_actionVertical_triggered(bool checked)
{
    if (checked == true)
    {
        m_horizontal->setChecked(false);
        mui_statusbar->showMessage("View in vertical layout");
    } else
    {
        m_horizontal->setChecked(true);
        mui_statusbar->showMessage("View in horizontal layout");
    } // end if
}

void QEmailScrapper::on_actionHorizontal_triggered(bool checked)
{
    if (checked == true)
    {
        m_vertical->setChecked(false);
        mui_statusbar->showMessage("View in horizontal layout");
    } else
    {
        m_vertical->setChecked(true);
        mui_statusbar->showMessage("View in vertical layout");
    } // end if
}


void QEmailScrapper::on_actionCut_triggered() {

    if (m_unscrappedtext) {
        m_unscrappedtext->cut();
    }
    if (m_scrappedtext) {
        m_scrappedtext->cut();
    }
}

void QEmailScrapper::on_actionCopy_triggered()
{
    if (m_unscrappedtext) {
        m_unscrappedtext->copy();
    }
    if (m_scrappedtext) {
        m_scrappedtext->copy();
    }
}

void QEmailScrapper::on_actionPaste_triggered()
{
    if (m_unscrappedtext) {
        m_unscrappedtext->paste();
    }
    if (m_scrappedtext) {
        m_scrappedtext->paste();
    }
}

void QEmailScrapper::on_actionDelete_triggered()
{
    /*QPlainTextEdit* p_text = dynamic_cast<QTextEdit*>(mui_tabs->currentWidget());
    if (p_text)
    {
         // it was a text, perform delete
        p_text->textCursor().removeSelectedText();
    } // end if*/

    if (m_unscrappedtext) {
        m_unscrappedtext->textCursor().removeSelectedText();
    }
    if (m_scrappedtext) {
        m_scrappedtext->textCursor().removeSelectedText();
    }
}

void QEmailScrapper::on_actionUndo_triggered()
{
    QPlainTextEdit *p_text;

    if (active_plaintextedit == 0) {
        p_text = m_unscrappedtext;
    }
    else if (active_plaintextedit == 1) {
        p_text = m_scrappedtext;
    }
    if (p_text)
    {
        p_text->undo();
    } // end if*/
}

void QEmailScrapper::on_actionRedo_triggered()
{
    QPlainTextEdit *p_text;

    if (active_plaintextedit == 0) {
        p_text = m_unscrappedtext;
    }
    else if (active_plaintextedit == 1) {
        p_text = m_scrappedtext;
    }
    if (p_text)
    {
        p_text->redo();
    } // end if*/
}

void QEmailScrapper::activated_unscrapped() {
    active_plaintextedit = 0;
}

void QEmailScrapper::activated_scrapped() {
    active_plaintextedit = 1;
}
