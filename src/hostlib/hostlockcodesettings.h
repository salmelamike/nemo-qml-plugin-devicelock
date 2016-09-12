/*
 * Copyright (C) 2016 Jolla Ltd
 * Contact: Andrew den Exter <andrew.den.exter@jolla.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef HOSTLOCKCODESETTINGS_H
#define HOSTLOCKCODESETTINGS_H

#include <QDBusAbstractAdaptor>
#include <QDBusObjectPath>

#include <hostobject.h>

class HostLockCodeSettings;
class HostLockCodeSettingsAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_PROPERTY(bool LockCodeSet READ isSet NOTIFY setChanged)
    Q_CLASSINFO("D-Bus Interface", "org.nemomobile.devicelock.LockCodeSettings")
public:
    explicit HostLockCodeSettingsAdaptor(HostLockCodeSettings *settings);

    bool isSet() const;

public slots:
    void Change(const QString &oldCode, const QString &newCode);
    void Clear(const QString &code);

signals:
    void setChanged();

private:
    HostLockCodeSettings * const m_settings;
};

class HostLockCodeSettings : public HostObject
{
    Q_OBJECT
public:
    explicit HostLockCodeSettings(QObject *parent = nullptr);
    ~HostLockCodeSettings();

protected:
    virtual bool isSet() const = 0;

    virtual void change(const QString &oldCode, const QString &newCode) = 0;
    virtual void clear(const QString &code) = 0;

    void setChanged();

private:
    friend class HostLockCodeSettingsAdaptor;

    HostLockCodeSettingsAdaptor m_adaptor;
};

#endif