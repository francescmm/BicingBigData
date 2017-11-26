/****************************************************************************************
 ** Copyright (C) 2017  Francesc Martinez <es.linkedin.com/in/cescmm/en>
 **
 ** This file is part of BicingBigData.
 ** BicingBigData is an application to access, show and store data from Bicing service from Barcelona.
 **
 ** This application is free software; you can redistribute it and/or
 ** modify it under the terms of the GNU Lesser General Public
 ** License as published by the Free Software Foundation; either
 ** version 3 of the License, or (at your option) any later version.
 **
 ** This application is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 ** Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public
 ** License along with this library; if not, write to the Free Software
 ** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ***************************************************************************************/

#ifndef OPENDATAREQUESTOR_H
#define OPENDATAREQUESTOR_H

#include <QObject>
#include <QFile>

class QNetworkReply;
class QNetworkAccessManager;

class OpenDataRequestor : public QObject
{
      Q_OBJECT

   signals:
      void signalTaskDone();

   public:
      explicit OpenDataRequestor(QObject *parent = nullptr);
      ~OpenDataRequestor();

   public slots:
      void makeRequest();

   private:
      QNetworkAccessManager *manager = nullptr;

   private slots:
      void replyFinished(QNetworkReply *reply);
};

#endif // OPENDATAREQUESTOR_H
