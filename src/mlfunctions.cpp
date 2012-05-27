/*
 * mlfunctions.cpp
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

#include "mlfunctions.h"


void mlMsgInfo ( QString cad, QWidget *parent )
{
    /// Information Message
    
    QMessageBox msgBox;
    msgBox.information ( parent,
                         "Program Information" ,
                         cad,  "&Continue" ,
                         QString::null, 0 );
}


void mlMsgWarning ( QString cad, QWidget *parent )
{
    /// Warning Message
    QMessageBox msgBox;
    msgBox.warning ( parent,
                     "Program notice" ,
                     cad, "&Continue",
                     QString::null, 0 );
}


void mlMsgError ( QString cad, QWidget *parent )
{
    /// Error Message
    
    QMessageBox msgBox;
    msgBox.critical ( parent,
                      "Program Error",
                      cad, "&Continue",
                      QString::null, 0 );
}



void mlWebBrowser(const QString &uri, const QString &defbrowser) {

    QString browser = "";
    /*if (browser.isEmpty()) {
        browser = g_confpr->value(CONF_NAVEGADOR);
    } // end if
    */

    #ifndef Q_OS_WIN32
        QString commas = " ";
        QString inbackground = " &";
    #else
        QString commas= "\" ";
        QString inbackground = "";
    #endif

    if (defbrowser.isEmpty()) {
        QDesktopServices::openUrl(QUrl(uri, QUrl::TolerantMode));
    }

    else {
        browser = defbrowser;
        QString webcommand = commas + browser + commas + QUrl(uri, QUrl::TolerantMode).toString() + inbackground;
        system ( webcommand.toAscii().data() );
    } // end if

}




#ifdef Q_OS_WIN32
/// Converts QString to WCHAR (MS-Windows only function).
wchar_t* MlQStringToWCHAR (QString inString) {
    //sML_FUNC_DEBUG

	if (inString.isEmpty())
		return NULL;

	std::wstring str = inString.toStdWString ();

	wchar_t *outString = new wchar_t[inString.size () + 1];
    	unsigned int length = inString.toWCharArray (outString);

	outString[length] = '\0';

	return outString;
}
#endif

QString mlGetEnv( const char *varName ) {
    

/// In MS-Windows there are some problems with UTF-8
#ifdef Q_OS_WIN32
	DWORD length;
	length = GetEnvironmentVariableW(MlQStringToWCHAR(varName), NULL, 0);

	wchar_t *variable = new wchar_t[length];
	GetEnvironmentVariableW(MlQStringToWCHAR(varName), variable, length );

	return QString::fromWCharArray(variable);
#else
        return QString( qgetenv(varName).constData() );
#endif // Q_OS_WIN32
}


bool mlCopyFile( const QString &oldName, const QString &newName )
{
    /// Function to copy files between folders or partitions, with torelants urls.
    

    // If it's the same file, don't copy it.
    if(oldName.compare(newName) == 0)
    {
        return true;
    } // end if
    
    // Transform urls in tolerants, for make it work cross plataform.
    QString oldFile = QUrl(oldName, QUrl::TolerantMode).toString();
    QString newFile = QUrl(newName, QUrl::TolerantMode).toString();

    // Try to copy it with QFile::copy().
    if(!QFile::copy(oldFile, newFile))
    {
	QString command = "";


        // If something went wrong use to copy with system.

	#ifdef Q_OS_WIN32
	    command = "copy \"" + oldFile + "\" \"" + newFile + "\"";
	#else
	    command = "cp " + oldFile + " " + newFile;
        #endif // Q_OS_WIN32

	int result = system ( command.toAscii().data() );

        if (result == -1) {
            return false;
            }
    } // end if

    // Se ha copiado correctamente el archivo
    return true;
}

bool mlRemove(const QString &filetoremove )
{
    /// Function to remove files independent.
    

    QString removeFile = QUrl(filetoremove, QUrl::TolerantMode).toString();
    QDir rootDir;
    
    // Trues to close file and delete it.
    if(!QFile::remove(removeFile) )
    {
        // If something went wrong use QDir::remove()
        if(!rootDir.remove (removeFile))
        {
	QString command = "";

        // If something still going wrong, use the system.

	#ifdef Q_OS_WIN32
	    command = "del \"" + removeFile + "\"";
	#else
	    command = "rm " + removeFile;
        #endif // Q_OS_WIN32

        int result = system ( command.toAscii().data() );
        if (result == -1) {
            return false;
            } // end if

        } // end if
    } // end if

    // Deleted with exit.
    return true;
    
}

bool mlMoveFile( const QString &oldName, const QString &newName )
{
    /// Move files, between folders and partitions, using crossplataform urls.
    
    QDir rootDir;
    
    
    // Transform urls in tolerants, for make it work cross plataform.
    QString oldFile = QUrl(oldName, QUrl::TolerantMode).toString();
    QString newFile = QUrl(newName, QUrl::TolerantMode).toString();

    // Try to use QDir::rename()
    if(!rootDir.rename(oldName, newName) )
    {
        // If something went wrong use mlCopyFile()

        // Copy has failed, don't delete the original.
        if(!mlCopyFile(oldName, newName))
        return false;

        // Copy exit correctly, delete the original
        mlRemove(oldName);
    } // end if

    // It was moved, or copied and moved with exit.
    return true;
}

