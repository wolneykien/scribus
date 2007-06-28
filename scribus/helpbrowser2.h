/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
*   Copyright (C) 2004 by Craig Bradney                                   *
*   cbradney@zip.com.au                                                   *
*   Copyright (C) 2005 by Petr Vanek                                      *
*   petr@yarpen.cz                                                        *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#ifndef HELPBROWSER2_H
#define HELPBROWSER2_H

#include <QList>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QToolBar>
#include <QVariant>
#include <QWidget>

#include "ui_helpbrowser2.h"
#include "scribusapi.h"
#include "util.h"
#include "scconfig.h"
#include "scpaths.h"
#include "prefsmanager.h"
#include "prefsfile.h"
#include "schelptreemodel.h"

//! \brief A structure holding title/file url reference.
struct histd2 {
	QString url;
	QString title;
};

class SCRIBUS_API HelpBrowser2 : public QMainWindow, Ui::HelpBrowser2
{
    Q_OBJECT

public:
	HelpBrowser2(QWidget* parent);
	HelpBrowser2(QWidget* parent, const QString& caption, const QString& guiLangage="en", const QString& jumpToSection="", const QString& jumpToFile="");
	~HelpBrowser2();

	/*! \brief History menu. It's public because of history reader - separate class */
	QMenu* histMenu;
	/*! \brief Mapping the documents for history. */
	QMap<int, histd2> mHistory;
	/*! \brief Set text to the browser
	\param str a QString with text (html) */
	void setText(const QString& str);

protected:
	void setupLocalUI();
	/*! \brief Reads saved bookmarks from external file */
	void readBookmarks();

	/*! \brief Reads saved history of browsing. */
	void readHistory();

	QMenu* fileMenu;
	QMenu* editMenu;
	QMenu* bookMenu;
	QAction* filePrint;
	QAction* fileExit;
	QAction* editFind;
	QAction* editFindNext;
	QAction* editFindPrev;
	QAction* bookAdd;
	QAction* bookDel;
	QAction* bookDelAll;
	QAction* goHome;
	QAction* goBack;
	QAction* goFwd;

	//! \brief Selected language is here. If there is no docs for this language, "en" is used.
	QString language;
	/*! \brief Text to be found in document */
	QString findText;
	/** \brief Configuration structure */
	PrefsContext* prefs;
	TreeModel* menuModel;

protected slots:
	virtual void languageChange();
	void loadHelp(const QString& filename);
	void loadMenu();

	/*! \brief Performs searching in documentation.
	It walks through installed documentation and searching in all text files
	\author Petr Vanek <petr@yarpen.cz> */
	void searchingButton_clicked();

	/*! \brief Find text in one document.
	Classical ctrl+f searching.
	\author Petr Vanek <petr@yarpen.cz> */
	void find();

	/*! \brief Find next occurences of the text in one document.
	\author Petr Vanek <petr@yarpen.cz> */
	void findNext();

	/*! \brief Find previous occurences of the text in one document.
	\author Petr Vanek <petr@yarpen.cz> */
	void findPrevious();

	/*! \brief Print the documentation.
	Based on the Qt example.
	*/
	void print();

	/*! \brief Add document into bookmarks. */
	void bookmarkButton_clicked();

	/*! \brief Delete selected document from bookmarks. */
	void deleteBookmarkButton_clicked();

	/*! \brief Delete all bookmarks */
	void deleteAllBookmarkButton_clicked();

};

#endif // HELPBROWSER2_H

