/*
 * AstadeView
 * Copyright (C) 2008 Stefan Eilers
 *
 * Astade is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License V2
 * as published by the Free Software Foundation.
 *
 * Astade  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St., Fifth Floor, Boston, MA 02110-1301, USA
 */
#include "SearchWidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>


SearchWidget::SearchWidget( QWidget* parent ): QWidget( parent ), m_pEditField( NULL )
{
    QHBoxLayout* h_layout = new QHBoxLayout( this );

    m_pEditField   = new QLineEdit( this );
    QPushButton* stop_button = new QPushButton( tr("Stop"), this );
    
    h_layout->addWidget( m_pEditField );
    h_layout->addWidget( stop_button );
    
    connect( m_pEditField, SIGNAL( textChanged( const QString& ) ),
             this, SIGNAL( signalTextChanged( const QString& ) ) );
    connect( stop_button, SIGNAL( clicked( bool ) ),
             this, SIGNAL( signalStopClicked() ) );
    connect( stop_button, SIGNAL( clicked( bool ) ),
            this, SLOT( slotStopPressed() ) );
}


void SearchWidget::slotStopPressed()
{
    m_pEditField->clear();
}



