/*
 * mlfunctions.h
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

#ifndef MLFUNCTIONS_H
#define MLFUNCTIONS_H


#include <QDir>
#include <QFile>
#include <QUrl>
#include <QString>
#include <QString>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTextStream>

#include <stdio.h>

#ifdef Q_OS_WIN32
	#include <qt_windows.h>
#endif

#include "mldefs.h"

void ML_EXPORT mlMsgInfo ( QString cad, QWidget *parent = 0 );
void ML_EXPORT mlMsgWarning ( QString cad, QWidget *parent = 0 );
void ML_EXPORT mlMsgError ( QString cad, QWidget *parent = 0 );


void ML_EXPORT mlWebBrowser(const QString &uri, const QString &defbrowser="");

QString ML_EXPORT mlGetEnv( const char *varName );

#ifdef Q_OS_WIN32
wchar_t* ML_EXPORT MlQStringToWCHAR (QString inString);
#endif



/// Copies a file from one location to another
bool ML_EXPORT mlCopyFile(const QString &oldName, const QString &newName);

/// Moves a file from one location to another
bool ML_EXPORT mlMoveFile(const QString &oldName, const QString &newName);

/// Deletes a file
bool ML_EXPORT mlRemove(const QString &filetoremove);


#endif // MLFUNCTIONS_H
