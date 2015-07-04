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

#include <qpa/qplatforminputcontextplugin_p.h>
#include <QStringList>
#include "qimhangulplatforminputcontext.h"

class QHangulPlatformInputContextPlugin: public QPlatformInputContextPlugin {
    Q_OBJECT
public:
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "qimhangul-qt5.json")

    QHangulPlatformInputContextPlugin();
    ~QHangulPlatformInputContextPlugin();

//    QStringList keys() const;
    QHangulPlatformInputContext *create(const QString &system, const QStringList& paramList);
};
