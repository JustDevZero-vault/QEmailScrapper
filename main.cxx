/*
 * main.cxx
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

//#include <QtGui/QApplication>
#include "src/mlapplication.h"
#include "src/mlfunctions.h"
#include "qemailscrapper.h"

int main(int argc, char **argv)
{
    bool valorSalida = 0;
    QEmailScrapper *memail;

    try {
        g_theApp = new MlApplication (argc, argv);
        memail = new QEmailScrapper();
        memail->show();

        valorSalida = g_theApp->exec();
    } catch ( ... ) {
       mlMsgInfo ( "Error inesperado en QEmailScrapper. El programa se cerrara." );
    } // end try

    // Free memory

    //delete memail;
    delete g_theApp;

    return valorSalida;


}
