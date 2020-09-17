#ifndef NAVITFAVOURITESMODEL_H
#define NAVITFAVOURITESMODEL_H

#include <QAbstractItemModel>
#include <QDebug>

#include <glib.h>
extern "C" {
#include "config.h"
#include "item.h" /* needs to be first, as attr.h depends on it */
#include "navit.h"

#include "coord.h"
#include "attr.h"
#include "xmlconfig.h" // for NAVIT_OBJECT
#include "layout.h"
#include "map.h"
#include "transform.h"

#include "mapset.h"
#include "search.h"
#include "bookmarks.h"

#include "proxy.h"
}

#include "navitinstance.h"
#include "navithelper.h"

class NavitFavouritesModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(NavitInstance * navit MEMBER m_navitInstance WRITE setNavit)
public:
    enum FavouriteModelRoles {
        LabelRole = Qt::UserRole + 1,
        CoordinatesRole
    };

    NavitFavouritesModel(QObject *parent = 0);

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void setNavit(NavitInstance * navit);

    Q_INVOKABLE void showFavourites();
    Q_INVOKABLE void setAsDestination(int index);
    Q_INVOKABLE void setAsPosition(int index);
    Q_INVOKABLE void addAsBookmark(int index);
    Q_INVOKABLE void addStop(int index,  int position);
private:
    QList<QVariantMap> m_favourites;
    NavitInstance *m_navitInstance = nullptr;
    void update();
};

#endif // NAVITFAVOURITESMODEL_H
