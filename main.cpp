/* qimhangul-qt5 - Qt input context plugin for Hangul
 * Based on qimhangul
 * Copyright (C) 2004 Choe Hwanjin
 * Copyright (C) 2015 Shinjo Park
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include "main.h"

QHangulPlatformInputContextPlugin::QHangulPlatformInputContextPlugin() {
    if (QHangulPlatformInputContext::hanjaTable)
	hanja_table_delete(QHangulPlatformInputContext::hanjaTable);
    QHangulPlatformInputContext::hanjaTable = hanja_table_load(NULL);
}

QHangulPlatformInputContextPlugin::~QHangulPlatformInputContextPlugin() {
    if (QHangulPlatformInputContext::hanjaTable)
	hanja_table_delete(QHangulPlatformInputContext::hanjaTable);
}

// If QT_IM_MODULE contains colon, the values after colon will be passed into
// paramList.
// Example: QT_IM_MODULE=hangul:2 -> system=hangul, paramList=[ "2" ]

/*
QStringList QHangulPlatformInputContextPlugin::keys() const {
    return QStringList(QStringLiteral("hangul"));
}
*/

QHangulPlatformInputContext *QHangulPlatformInputContextPlugin::create(const QString &system, const QStringList &paramList) {
    if (system.compare(system, QStringLiteral("hangul"), Qt::CaseInsensitive) == 0) {
        if (paramList.size() == 0) {
            return new QHangulPlatformInputContext();
        } else {
            return new QHangulPlatformInputContext(paramList[0]);
        }
    }
    return 0;
}

