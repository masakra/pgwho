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

#include "WidgetConfig.h"

#include <QtGui>

WidgetConfig::WidgetConfig( QWidget * parent )
	: QWidget( parent )
{
	createWidgets();
}

void
WidgetConfig::createWidgets()
{
	editHost = new QLineEdit( this );
	connect( editHost, SIGNAL( textChanged( const QString & ) ), SIGNAL( textChanged() ) );

	editPort = new QLineEdit( this );
	editPort->setInputMask("D0000");
	connect( editPort, SIGNAL( textChanged( const QString & ) ), SIGNAL( textChanged() ) );

	editDatabase = new QLineEdit( this );

	editUser = new QLineEdit( this );

	editPass = new QLineEdit( this );

	QLabel * labelHost = new QLabel( tr("&Server"), this ),
		   * labelDatabase = new QLabel( tr("&Database"), this ),
		   * labelUser = new QLabel( tr("&User"), this ),
		   * labelPass = new QLabel( tr("&Password"), this );

	labelHost->setBuddy( editHost );
	labelDatabase->setBuddy( editDatabase );
	labelUser->setBuddy( editUser );
	labelPass->setBuddy( editPass );

	QGridLayout * layout = new QGridLayout( this );

	layout->addWidget( labelHost, 0, 0, Qt::AlignRight );
	layout->addWidget( editHost, 0, 1 );
	layout->addWidget( editPort, 0, 2 );

	layout->addWidget( labelDatabase, 1, 0, Qt::AlignRight );
	layout->addWidget( editDatabase, 1, 1, 1, 2 );

	layout->addWidget( labelUser, 2, 0, Qt::AlignRight );
	layout->addWidget( editUser, 2, 1, 1, 2 );

	layout->addWidget( labelPass, 3, 0, Qt::AlignRight );
	layout->addWidget( editPass, 3, 1, 1, 2 );
}

QString
WidgetConfig::host() const
{
	return editHost->text();
}

QString
WidgetConfig::port() const
{
	return editPort->text();
}

QString
WidgetConfig::database() const
{
	return editDatabase->text();
}

QString
WidgetConfig::user() const
{
	return editUser->text();
}

QString
WidgetConfig::password() const
{
	return editPass->text();
}

void
WidgetConfig::setHost( const QString & host )
{
	editHost->setText( host );
}

void
WidgetConfig::setPort( const QString & port )
{
	editPort->setText( port );
}

void
WidgetConfig::setDatabase( const QString & database )
{
	editDatabase->setText( database );
}

void
WidgetConfig::setUser( const QString & user )
{
	editUser->setText( user );
}

void
WidgetConfig::setPassword( const QString & password )
{
	editPass->setText( password );
}

