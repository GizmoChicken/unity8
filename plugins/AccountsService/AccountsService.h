/*
 * Copyright (C) 2013, 2015 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UNITY_ACCOUNTSSERVICE_H
#define UNITY_ACCOUNTSSERVICE_H

#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

class AccountsServiceDBusAdaptor;
class QDBusInterface;

class AccountsService: public QObject
{
    Q_OBJECT
    Q_ENUMS(PasswordDisplayHint)
    Q_PROPERTY (QString user
                READ user
                WRITE setUser
                NOTIFY userChanged)
    Q_PROPERTY (bool demoEdges
                READ demoEdges
                WRITE setDemoEdges
                NOTIFY demoEdgesChanged)
    Q_PROPERTY (QStringList demoEdgesCompleted
                READ demoEdgesCompleted
                NOTIFY demoEdgesCompletedChanged)
    Q_PROPERTY (bool enableLauncherWhileLocked
                READ enableLauncherWhileLocked
                NOTIFY enableLauncherWhileLockedChanged)
    Q_PROPERTY (bool enableIndicatorsWhileLocked
                READ enableIndicatorsWhileLocked
                NOTIFY enableIndicatorsWhileLockedChanged)
    Q_PROPERTY (QString backgroundFile
                READ backgroundFile
                NOTIFY backgroundFileChanged)
    Q_PROPERTY (bool statsWelcomeScreen
                READ statsWelcomeScreen
                NOTIFY statsWelcomeScreenChanged)
    Q_PROPERTY (PasswordDisplayHint passwordDisplayHint
                READ passwordDisplayHint
                NOTIFY passwordDisplayHintChanged)
    Q_PROPERTY (uint failedLogins
                READ failedLogins
                WRITE setFailedLogins
                NOTIFY failedLoginsChanged)
    Q_PROPERTY(bool hereEnabled
               READ hereEnabled
               WRITE setHereEnabled
               NOTIFY hereEnabledChanged)
    Q_PROPERTY(QString hereLicensePath
               READ hereLicensePath
               NOTIFY hereLicensePathChanged)
    Q_PROPERTY(bool hereLicensePathValid // qml sees a null string as "", so we use proxy setting for that
               READ hereLicensePathValid
               NOTIFY hereLicensePathChanged)
    Q_PROPERTY(QString realName READ realName WRITE setRealName NOTIFY realNameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QStringList keymaps
               READ keymaps
               NOTIFY keymapsChanged)

public:
    enum PasswordDisplayHint {
        Keyboard,
        Numeric,
    };

    explicit AccountsService(QObject *parent = 0, const QString & user = QString());
    ~AccountsService() = default;

    QString user() const;
    void setUser(const QString &user);
    bool demoEdges() const;
    void setDemoEdges(bool demoEdges);
    QStringList demoEdgesCompleted() const;
    Q_INVOKABLE void markDemoEdgeCompleted(const QString &edge);
    bool enableLauncherWhileLocked() const;
    bool enableIndicatorsWhileLocked() const;
    QString backgroundFile() const;
    bool statsWelcomeScreen() const;
    PasswordDisplayHint passwordDisplayHint() const;
    uint failedLogins() const;
    void setFailedLogins(uint failedLogins);
    bool hereEnabled() const;
    void setHereEnabled(bool enabled);
    QString hereLicensePath() const;
    bool hereLicensePathValid() const;
    QString realName() const;
    void setRealName(const QString &realName);
    QString email() const;
    void setEmail(const QString &email);
    QStringList keymaps() const;

Q_SIGNALS:
    void userChanged();
    void demoEdgesChanged();
    void demoEdgesCompletedChanged();
    void enableLauncherWhileLockedChanged();
    void enableIndicatorsWhileLockedChanged();
    void backgroundFileChanged();
    void statsWelcomeScreenChanged();
    void passwordDisplayHintChanged();
    void failedLoginsChanged();
    void hereEnabledChanged();
    void hereLicensePathChanged();
    void realNameChanged();
    void emailChanged();
    void keymapsChanged();

private Q_SLOTS:
    void onPropertiesChanged(const QString &user, const QString &interface, const QStringList &changed);
    void onMaybeChanged(const QString &user);

private:
    typedef QVariant (*ProxyConverter)(const QVariant &);

    void refresh(bool async);
    void registerProperty(const QString &interface, const QString &property, const QString &signal);
    void registerProxy(const QString &interface, const QString &property, QDBusInterface *iface, const QString &method, ProxyConverter converter = nullptr);

    void updateAllProperties(const QString &interface, bool async);
    void updateProperty(const QString &interface, const QString &property);
    void updateCache(const QString &interface, const QString &property, const QVariant &value);

    void setProperty(const QString &interface, const QString &property, const QVariant &value);
    QVariant getProperty(const QString &interface, const QString &property) const;

    void emitChangedForProperty(const QString &interface, const QString &property);

    struct PropertyInfo {
        QVariant value{};
        QString signal{};
        QDBusInterface *proxyInterface{};
        QString proxyMethod{};
        ProxyConverter proxyConverter{};
    };
    typedef QHash< QString, QHash<QString, PropertyInfo> > PropertyHash;
    PropertyHash m_properties;
    AccountsServiceDBusAdaptor *m_service;
    QDBusInterface *m_unityInput;
    QString m_user;
};

#endif
