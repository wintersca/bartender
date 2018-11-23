#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <QObject>
#include <QString>


namespace Ingredients {
    enum Ingredients {
        Vodka,
        Tequila,
        Salt,
        GrandMarnier,
        SimpleSyrup,
        Angustura,
        Bourbon,
        OrangeTwist,
        LimeJuice,
        MintLeaf,
        WhiteRum,
        SparklingWater,
        Gin,
        TonicWater,
        OrangeJuice,
        OrangeWedge,
        AngosturaBitters,
        SweetVermouth,
        LemonTwist,
        Cherry,
        DryVermouth,
        GreenOlive
    };

    const int TOTALINGREDIENTS = 22;
    static const QString All[] = {
        "Vodka",
        "Tequila",
        "Salt",
        "Grand Marnier",
        "Simple Syrup",
        "Angustura",
        "Bourbon",
        "Orange Twist",
        "Lime Juice",
        "Mint Leaf",
        "White Rum",
        "Sparkling Water",
        "Gin",
        "Tonic Water",
        "Orange Juice",
        "Orange Wedge",
        "Angostura Bitters",
        "Sweet Vermouth",
        "Lemon Twist",
        "Cherry",
        "Dry Vermouth",
        "Green Olive"
    };
}


#endif // INGREDIENTS_H
