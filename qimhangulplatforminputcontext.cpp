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

#include "qimhangulplatforminputcontext.h"
#include <QCoreApplication>
#include <QString>
#include <QTextCodec>
#include <QEvent>
#include <QKeyEvent>
#include <QTextFormat>

#include <QDebug>

#include <hangul.h>

static inline QString ucsToQString(const ucschar *ucs);

static bool
onTransition(HangulInputContext* /* hic */,
	     ucschar /* c */, const ucschar *str, void* /* data */)
{
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString s = ucsToQString(str);
    return codec->canEncode(s);
}

static inline QString ucsToQString(const ucschar *ucs) {
    QString str;

    if (ucs != NULL) {
	while (*ucs != 0)
	    str += QChar(*ucs++);
    }
    return str;
}

QHangulPlatformInputContext::QHangulPlatformInputContext() {
    QHangulPlatformInputContext(QStringLiteral("2"));

}

bool QHangulPlatformInputContext::isValid() const {
    return true;
}

void QHangulPlatformInputContext::reset() {
    /*
    if (m_candidateList != NULL && m_candidateList->isVisible()) {
	m_candidateList->close();
    }
    */

    const ucschar *flushed = hangul_ic_flush(m_hic);

    // we do not send preedit update IMEvent
    // because commit() send InputMethodEnd event and it remove preedit string

    QString commitString = ucsToQString(flushed);
    if (!commitString.isEmpty()) {
	commitText(commitString);
    } else {
	updatePreedit("");
    }
}

void QHangulPlatformInputContext::update(Qt::InputMethodQueries q) {
    QPlatformInputContext::update(q);
}

QString QHangulPlatformInputContext::getPreeditString() const {
    return ucsToQString(hangul_ic_get_preedit_string(m_hic));
}

QString QHangulPlatformInputContext::getCommitString() const {
    return ucsToQString(hangul_ic_get_commit_string(m_hic));
}

void QHangulPlatformInputContext::updatePreedit(const QString &str) {
    QTextCharFormat fmt;
    fmt.setUnderlineStyle(QTextCharFormat::SingleUnderline);

    QList<QInputMethodEvent::Attribute> attrs;
    attrs << QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, 0,
		  str.length(), fmt);

    QInputMethodEvent e(str, attrs);
    if (m_focusObject) QCoreApplication::sendEvent(m_focusObject, &e);
}

void QHangulPlatformInputContext::commitText(const QString &str) {
    QInputMethodEvent e;
    e.setCommitString(str);
    if (m_focusObject) QCoreApplication::sendEvent(m_focusObject, &e);
}

bool QHangulPlatformInputContext::isTriggerKey(const QKeyEvent *event) {
    return (event->key() == Qt::Key_Space && (event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier) ||
	   (event->key() == Qt::Key_Hangul);
}

bool QHangulPlatformInputContext::isCandidateKey(const QKeyEvent *event) {
    return (event->key() == Qt::Key_Hangul_Hanja) ||
	   (event->key() == Qt::Key_F9);
}

bool QHangulPlatformInputContext::backspace() {
    bool ret = hangul_ic_backspace(m_hic);
    if (ret) {
	QString str = getPreeditString();
	updatePreedit(str);
    }
    return ret;
}

bool QHangulPlatformInputContext::popupCandidateList() {
    /*
    const ucschar *text = hangul_ic_get_preedit_string(m_hic);
    if (text != NULL && *text != 0) {
	QString str;
	str += QChar(text[0]);
	HanjaList *list = hanja_table_match_suffix(hanjaTable, str.toUtf8());

	if (m_candidateList == NULL)
	    m_candidateList = new CandidateList();

	QPoint p(0, 0);

	QWidget *focus = focusWidget();
	if (focus != NULL) {
	    QVariant v = focus->inputMethodQuery(Qt::ImMicroFocus);
	    QRect r = v.toRect();
	    p = focus->mapToGlobal(QPoint(r.right(), r.bottom()));
	}

	m_candidateList->open(list, p.x(), p.y());
    }
    */

    return false;
}


QHangulPlatformInputContext::QHangulPlatformInputContext(const QString &keyboardType) {
    qDebug() << "Selected keyboard type: " << keyboardType;

    int i, n;
    n = hangul_ic_get_n_keyboards();

    m_hic = NULL;
    for(i = 0; i < n; i++) {
        const char *s = hangul_ic_get_keyboard_id(i);
        if (keyboardType == s) {
            m_hic = hangul_ic_new(s);
            break;
        }
    }

    if (m_hic == NULL) {
        m_hic = hangul_ic_new("2");
    }
    hangul_ic_connect_callback(m_hic, "transition", (void*)onTransition, NULL);
}

QHangulPlatformInputContext::~QHangulPlatformInputContext() {
    if (m_hic != NULL) {
        hangul_ic_delete(m_hic);
    }
}

bool QHangulPlatformInputContext::filterEvent(const QEvent *event) {
    if (event->type() != QEvent::KeyPress)
	return false;

    const QKeyEvent *keyevent = static_cast<const QKeyEvent*>(event);
    /*
    if (m_candidateList != NULL && m_candidateList->isVisible()) {
	if (m_candidateList->filterEvent(keyevent)) {
	    if (m_candidateList->isSelected()) {
		hangul_ic_reset(m_hic);
		QString candidate(m_candidateList->getCandidate());
		commitText(candidate);
	    }
	    m_candidateList->close();
	}
	return true;
    }
    */

    if (keyevent->key() == Qt::Key_Shift)
	return false;

    if (keyevent->key() == Qt::Key_Backspace)
	return backspace();

    if (isTriggerKey(keyevent)) {
	if (m_mode == MODE_DIRECT) {
	    m_mode = MODE_HANGUL;
	} else {
	    reset();
	    m_mode = MODE_DIRECT;
	}
	setModeInfo(m_mode);

	return true;
    }

    /*
    if (isCandidateKey(keyevent)) {
	return popupCandidateList();
    }
    */

    if (keyevent->modifiers() & Qt::ControlModifier ||
	keyevent->modifiers() & Qt::AltModifier ||
	keyevent->modifiers() & Qt::MetaModifier) {
	reset();
	return false;
    }

    if (m_mode == MODE_HANGUL) {
	QString text = keyevent->text();
	if (keyevent->modifiers() & Qt::ShiftModifier)
	    text = text.toUpper();
	else
	    text = text.toLower();

	int ascii = 0;
	if (!text.isEmpty())
	    ascii = text[0].unicode();
	bool ret = hangul_ic_process(m_hic, ascii);

	QString commitString = getCommitString();
	if (!commitString.isEmpty())
	    commitText(commitString);

	QString preeditString = getPreeditString();
	if (!preeditString.isEmpty())
	    updatePreedit(preeditString);

	return ret;
    }

    return false;
}

void QHangulPlatformInputContext::setFocusObject(QObject *object) {
    m_focusObject = object;
}
