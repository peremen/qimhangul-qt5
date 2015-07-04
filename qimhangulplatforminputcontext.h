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

#ifndef QIMHANGULPLATFORMINPUTCONTEXT_H
#define QIMHANGULPLATFORMINPUTCONTEXT_H

#include <qpa/qplatforminputcontext.h>
#include <QtCore/QList>
#include <hangul.h>
#include <QKeyEvent>

class QHangulPlatformInputContext: public QPlatformInputContext {
    Q_OBJECT

public:
    QHangulPlatformInputContext();
    QHangulPlatformInputContext(const QString &keyboardType);
    ~QHangulPlatformInputContext();

    bool isValid() const;

    void reset();
    void update(Qt::InputMethodQueries);
    bool filterEvent(const QEvent *event);

    void setFocusObject(QObject *object);

private:
    typedef enum {
        MODE_NONE,
        MODE_DIRECT,
        MODE_HANGUL
    } InputMode;

    QString getPreeditString() const;
    QString getCommitString() const;
    void updatePreedit(const QString &str);

    void commitText(const QString &str);
    bool isTriggerKey(const QKeyEvent *event);
    bool isCandidateKey(const QKeyEvent *event);
    bool backspace();
    bool popupCandidateList();
    void setModeInfo(int mode);

    HangulInputContext *m_hic;
    InputMode m_mode;
    QObject *m_focusObject;
};

#endif
