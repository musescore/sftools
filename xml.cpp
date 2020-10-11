//=============================================================================
//  MuseScore sftools
//
//  Copyright (C) 2002-2011 Werner Schweer
//
//  This work is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Library General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  In addition, as a special exception, licensor gives permission to
//  link the code of this work with the OpenSSL Library (or with modified
//  versions of OpenSSL that use the same license as OpenSSL), and
//  distribute linked combinations including the two. You must obey the
//  GNU General Public License in all respects for all of the code used
//  other than OpenSSL. If you modify this file, you may extend this
//  exception to your version of the file, but you are not obligated to
//  do so. If you do not wish to do so, delete this exception statement
//  from your version. (This exception is necessary should this work be
//  included in a GPL-licenced work.)
//
//  See COPYING.LIB for the licence text and disclaimer of warranty.
//=============================================================================

#include "xml.h"

#include <QtCore/QStringList>

QString docName;

//---------------------------------------------------------
//   Xml
//---------------------------------------------------------

Xml::Xml()
      {
      stack.clear();
      }

Xml::Xml(QIODevice* device)
   : QTextStream(device)
      {
      setCodec("UTF-8");
      stack.clear();
      }

//---------------------------------------------------------
//   putLevel
//---------------------------------------------------------

void Xml::putLevel()
      {
      int level = stack.size();
      for (int i = 0; i < level * 2; ++i)
            *this << ' ';
      }

//---------------------------------------------------------
//   header
//---------------------------------------------------------

void Xml::header()
      {
      *this << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
      }

//---------------------------------------------------------
//   stag
//    <mops attribute="value">
//---------------------------------------------------------

void Xml::stag(const QString& s)
      {
      putLevel();
      *this << '<' << s << '>' << endl;
      stack.append(s.split(' ')[0]);
      }

//---------------------------------------------------------
//   etag
//    </mops>
//---------------------------------------------------------

void Xml::etag()
      {
      putLevel();
      *this << "</" << stack.takeLast() << '>' << endl;
      }

//---------------------------------------------------------
//   tagE
//    <mops attribute="value"/>
//---------------------------------------------------------

void Xml::tagE(const char* format, ...)
      {
      va_list args;
      va_start(args, format);
      putLevel();
      *this << '<';
      char buffer[BS];
      vsnprintf(buffer, BS, format, args);
      *this << buffer;
      va_end(args);
      *this << "/>" << endl;
      }

//---------------------------------------------------------
//   tagE
//---------------------------------------------------------

void Xml::tagE(const QString& s)
      {
      putLevel();
      *this << '<' << s << "/>\n";
      }

//---------------------------------------------------------
//   ntag
//    <mops> without newline
//---------------------------------------------------------

void Xml::ntag(const char* name)
      {
      putLevel();
      *this << "<" << name << ">";
      }

//---------------------------------------------------------
//   netag
//    </mops>     without indentation
//---------------------------------------------------------

void Xml::netag(const char* s)
      {
      *this << "</" << s << '>' << endl;
      }

void Xml::tag(const QString& name, QVariant data)
      {
      QString ename(name.split(' ')[0]);

      putLevel();
      switch(data.type()) {
            case QVariant::Bool:
            case QVariant::Char:
            case QVariant::Int:
            case QVariant::UInt:
                  *this << "<" << name << ">";
                  *this << data.toInt();
                  *this << "</" << ename << ">\n";
                  break;
            case QVariant::Double:
                  *this << "<" << name << ">";
                  *this << data.value<double>();
                  *this << "</" << ename << ">\n";
                  break;
            case QVariant::String:
                  *this << "<" << name << ">";
                  *this << xmlString(data.value<QString>());
                  *this << "</" << ename << ">\n";
                  break;
            default:
                  qDebug("Xml::tag: unsupported type %d\n", data.type());
                  // abort();
                  break;
            }
      }

//---------------------------------------------------------
//   xmlString
//---------------------------------------------------------

QString Xml::xmlString(const QString& ss)
      {
      QString s(ss);
      s.replace('&',  "&amp;");
      s.replace('<',  "&lt;");
      s.replace('>',  "&gt;");
      s.replace('\'', "&apos;");
      s.replace('"',  "&quot;");
      return s;
      }

 //---------------------------------------------------------
//   dump
//---------------------------------------------------------

void Xml::dump(int len, const unsigned char* p)
      {
      putLevel();
      int col = 0;
      setFieldWidth(5);
      setNumberFlags(numberFlags() | QTextStream::ShowBase);
      setIntegerBase(16);
      for (int i = 0; i < len; ++i, ++col) {
            if (col >= 16) {
                  setFieldWidth(0);
                  *this << endl;
                  col = 0;
                  putLevel();
                  setFieldWidth(5);
                  }
            *this << (p[i] & 0xff);
            }
      if (col)
            *this << endl << dec;
      setFieldWidth(0);
      setIntegerBase(10);
      }

//---------------------------------------------------------
//   printDomElementPath
//---------------------------------------------------------

static QString domElementPath(const QDomElement& e)
      {
      QString s;
      QDomNode dn(e);
      while (!dn.parentNode().isNull()) {
            dn = dn.parentNode();
            const QDomElement& e = dn.toElement();
            const QString k(e.tagName());
            if (!s.isEmpty())
                  s += ":";
            s += k;
            }
      return s;
      }

//---------------------------------------------------------
//   domError
//---------------------------------------------------------

void domError(const QDomElement& e)
      {
      QString m;
      QString s = domElementPath(e);
      if (!docName.isEmpty())
            m = QString("<%1>:").arg(docName);
      int ln = e.lineNumber();
      if (ln != -1)
            m += QString("line:%1 ").arg(ln);
      int col = e.columnNumber();
      if (col != -1)
            m += QString("col:%1 ").arg(col);
      m += QString("%1: Unknown Node <%2>, type %3").arg(s).arg(e.tagName()).arg(e.nodeType());
      if (e.isText())
            m += QString("  text node <%1>").arg(e.toText().data());
      qDebug("%s", qPrintable(m));
      }

//---------------------------------------------------------
//   domNotImplemented
//---------------------------------------------------------

void domNotImplemented(const QDomElement& e)
      {
      QString s = domElementPath(e);
      if (!docName.isEmpty())
            qDebug("<%s>:", qPrintable(docName));
      qDebug("%s: Node not implemented: <%s>, type %d\n",
         qPrintable(s), qPrintable(e.tagName()), e.nodeType());
      if (e.isText())
            qDebug("  text node <%s>\n", qPrintable(e.toText().data()));
      }

//---------------------------------------------------------
//   writeHtml
//---------------------------------------------------------

void Xml::writeHtml(const QString& s)
      {
      QStringList sl(s.split("\n"));
      //
      // remove first line from html (DOCTYPE...)
      //
      for (int i = 1; i < sl.size(); ++i)
            *this << sl[i] << "\n";
      }
