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

 /** \class PgWho
  *
  * \brief Plasmoid for display postresql connections
  */

#ifndef PGWHO_H
#define PGWHO_H

#define HOST "host"
#define PORT "port"
#define DB "database"
#define USER "username"
#define PASS "password"

#include <plasma/applet.h>
#include <QTimer>

class KConfigDialog;
class WidgetConfig;

class PgWho : public Plasma::Applet
{
	Q_OBJECT

	private:
		QStringList listConn;

		QString strErr;

		QTimer timer;

		WidgetConfig * wc;

	private Q_SLOTS:
		void refresh();

		void saveSettings();

	public:
		PgWho( QObject * parent, const QVariantList & args );
		~PgWho();

		void paintInterface( QPainter * painter, const QStyleOptionGraphicsItem * option,
				const QRect & contentsRect );

		void init();

		void createConfigurationInterface( KConfigDialog * parent );
};

#endif


