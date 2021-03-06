/*
 * Copyright (C) 2016 Canonical, Ltd.
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


#include <unity/shell/launcher/AppDrawerModelInterface.h>

#include "launcheritem.h"

class UalWrapper;

class AppDrawerModel: public AppDrawerModelInterface
{
    Q_OBJECT
public:
    AppDrawerModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private Q_SLOTS:
    void appAdded(const QString &appId);
    void appRemoved(const QString &appId);
    void appInfoChanged(const QString &appId);

private:
    QList<LauncherItem*> m_list;
    UalWrapper *m_ual;
};
