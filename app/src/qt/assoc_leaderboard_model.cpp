/*
 assoc_leaderboard_model.cpp     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "assoc_leaderboard_model.h"

namespace m8r {

AssocLeaderboardModel::AssocLeaderboardModel(QObject* parent)
    : QStandardItemModel(parent)
{
    setColumnCount(2);
    setRowCount(0);
}

AssocLeaderboardModel::~AssocLeaderboardModel()
{
}

void AssocLeaderboardModel::removeAllRows()
{
    QStandardItemModel::clear();

    QStringList tableHeader;
    tableHeader
        << tr("Associated Note")
        << tr("%");
    // IMPROVE set tooltips: items w/ tooltips instead of just strings
    setHorizontalHeaderLabels(tableHeader);
}

void AssocLeaderboardModel::addRow(Note* note, float similarity)
{
    QList<QStandardItem*> items;
    QStandardItem* item;

    QString html, tooltip;
    html = QString(note->getName().c_str());
    html += " (";
    html.append(QString::fromStdString(note->getOutline()->getName()));
    html += ")";
    tooltip = html;

    // item
    item = new QStandardItem(html);
    item->setToolTip(tooltip);
    // TODO under which ROLE this is > I should declare CUSTOM role (user+1 as constant)
    item->setData(QVariant::fromValue(note));
    items.append(item);

    QString s{};
    s += QString::number(similarity*100.);
    s += "%";
    items.append(new QStandardItem(s));

    appendRow(items);
}

} // m8r namespace
