/***************************************************************************
 *   Copyright (C) 2013 by Sergey N Chursanov                              *
 *                                                                         *
 *   email: masakra@mail.ru                                                *
 *   jabber: masakra@jabber.ru                                             *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/

 /** \class WidgetConfig
  *
  * \brief 
  */

#ifndef WIDGETCONFIG_H
#define WIDGETCONFIG_H

#include <QWidget>

class QLineEdit;

class WidgetConfig : public QWidget
{
	Q_OBJECT

	private:
		void createWidgets();

		QLineEdit * editHost,
				  * editPort,
				  * editDatabase,
				  * editUser,
				  * editPass;
	public:
		WidgetConfig( QWidget * parent = 0 );

		QString host() const;
		QString port() const;
		QString database() const;
		QString user() const;
		QString password() const;

		void setHost( const QString & host );
		void setPort( const QString & port );
		void setDatabase( const QString & database );
		void setUser( const QString & user );
		void setPassword( const QString & password );

	Q_SIGNALS:
		void textChanged();


};

#endif


