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

#include "PgWho.h"

#include <QtSql>
#include <QPainter>

#include <KConfigDialog>

#include "WidgetConfig.h"

K_EXPORT_PLASMA_APPLET( pgwho, PgWho )

PgWho::PgWho( QObject * parent, const QVariantList & args )
	: Plasma::Applet( parent, args ),
	  strErr("initial"),
	  timer( this ),
	  wc( 0 )

{
	setAspectRatioMode( Plasma::IgnoreAspectRatio );
	setBackgroundHints( DefaultBackground );
	resize( 340, 210 );

	setHasConfigurationInterface( true );

	connect( &timer, SIGNAL( timeout() ), SLOT( refresh() ) );
}

PgWho::~PgWho()
{
}

void
PgWho::paintInterface( QPainter * painter, const QStyleOptionGraphicsItem * option,
		const QRect & contentsRect )
{
	Q_UNUSED( option )

	painter->setRenderHint( QPainter::SmoothPixmapTransform );
	painter->setRenderHint( QPainter::Antialiasing );

	painter->save();

	painter->setPen( Qt::white );

	if ( strErr.isEmpty() )
		painter->drawText( contentsRect, Qt::AlignLeft | Qt::AlignTop, listConn.join("\n") );
	else
		painter->drawText( contentsRect, Qt::AlignCenter, strErr );

	//for ( register int i = 0; i < listConn.size(); ++i ) {
		//painter->drawText( contentsRect, Qt::AlignLeft | Qt::AlignVCenter, "text" );
		//painter->drawText( 
	//}

	painter->restore();
}

void
PgWho::init()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

	KConfigGroup g = config();

	db.setHostName( g.readEntry( HOST ) );
	db.setPort( g.readEntry( PORT ).toInt() );
	db.setDatabaseName( g.readEntry( DB ) );
	db.setUserName( g.readEntry( USER ) );
	db.setPassword( g.readEntry( PASS ) );
	db.setConnectOptions( QString("application_name=%1").arg( pluginName() ) );

	if ( ! db.open() ) {
		strErr = db.lastError().text();

	} else {
		strErr.clear();

		timer.start( 30000 );	// 30 seconds
		refresh();
	}
}

void
PgWho::refresh()
{
	QSqlDatabase db = QSqlDatabase::database();

	if ( ! db.isOpen() )
		return;

	QSqlQuery q;

	q.prepare("SELECT "
				"usename || ' ' || client_addr || ' ' || application_name "
			"FROM "
				"\"pg_stat_activity\" "
			"WHERE "
				"application_name != :pName "
			"ORDER BY "
				"1 ");

	q.bindValue(":pName", pluginName() );

	if ( q.exec() ) {

		listConn.clear();
		strErr.clear();

		while( q.next() ) {
			listConn << q.value( 0 ).toString();
		}

		update();

	} else {
		strErr = q.lastError().text();
	}
}

void
PgWho::createConfigurationInterface( KConfigDialog * parent )
{
	wc = new WidgetConfig();

	KConfigGroup g = config();

	wc->setHost( g.readEntry( HOST, "localhost" ) );
	wc->setPort( g.readEntry( PORT, "5432" ) );
	wc->setDatabase( g.readEntry( DB ) );
	wc->setUser( g.readEntry( USER ) );
	wc->setPassword( g.readEntry( PASS ) );

	connect( wc, SIGNAL( textChanged() ), parent, SLOT( settingsModified() ) );

	// don't worry about wc's parent. It will be reparented.
	// http://api.kde.org/4.x-api/kdelibs-apidocs/kdeui/html/classKConfigDialog.html#a1ead7205c9c5b114f1c9729372d648e1

	parent->addPage( wc, "PostgreSQL", "network-server" );

	connect( parent, SIGNAL( applyClicked() ), SLOT( saveSettings() ) );
	connect( parent, SIGNAL( okClicked() ), SLOT( saveSettings() ) );
}

void
PgWho::saveSettings()
{
	if ( ! wc )
		return;

	KConfigGroup g = config();

	g.writeEntry( HOST, wc->host() );
	g.writeEntry( PORT, wc->port() );
	g.writeEntry( DB, wc->database() );
	g.writeEntry( USER, wc->user() );
	g.writeEntry( PASS, wc->password() );

	QSqlDatabase db = QSqlDatabase::database();

	if ( db.isOpen() )
		db.close();

	init();
}

