/*
 * mlapplication.h
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

#include <QWidget>
#include "mlapplication.h"
#include "mlfunctions.h"


/// Definimos la variable global g_theApp.
MlApplication *g_theApp = NULL;


///
/**
\param argc
\param argv
**/
MlApplication::MlApplication ( int &argc, char **argv ) : QApplication ( argc, argv )
{
  //~ ML_FUNC_DEBUG
}


///
/**
**/
MlApplication::~MlApplication()
{
  //~ ML_FUNC_DEBUG
}


#if CONFIG_DEBUG == TRUE
///
/**
\param object
\param event
\return
**/
bool MlApplication::notify ( QObject *object, QEvent *event )
{
    ///   Esta funcion es llamada continuamente y por eso no la depuramos (ML_FUNC_DEBUG).

    try {
        return QApplication::notify ( object, event );
    } catch ( ... ) {
        fprintf(stderr, _("Error inesperado en el sistema de notificaciones.\n").toAscii());
        return FALSE;
    } // end try

}
#endif
