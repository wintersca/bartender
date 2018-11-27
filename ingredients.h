#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <QObject>
#include <QString>


namespace Ingredients {
    enum Ingredients {
        // Core boozes
        Vodka,
        Tequila,
        Bourbon,
        Gin,
        DarkRum,
        WhiteRum,
        LightRum,

        // Liquors
        GrandMarnier,
        SweetVermouth,
        DryVermouth,
        TrippleSec,
        Kahlua,
        Jagermeister,
        Campari,
        GreenCremeDeMenthe,
        CremeDeCacao,
        PeachSchnapps,

        // Kitchen basics
        Salt,
        Pepper,
        Ice,

        // Non alcoholic liquids
        SimpleSyrup,
        TonicWater,
        SparklingWater,
        AngosturaBitters,
        Cola,
        ClubSoda,
        Cream,
        WorcestershireSauce,

        // Fruit juices.
        OrangeJuice,
        LimeJuice,
        LemonJuice,
        PineappleJuice,
        TomatoJuice,
        CranberryJuice,

        // Fruits and Vegetables.
        OrangeWedge,
        OrangeTwist,
        LimeWedge,
        LimeTwist,
        LemonTwist,
        PineappleWedge,
        CreamOfCoconut,
        GingerBeer,
        MintLeaf,
        MintSprig,
        Cherry,
        GreenOlive,
        Celery,
        Nutmeg,

        // Actions
        Shake,
        Stir,
        Muddle

    };

    const int TOTALINGREDIENTS = 52;
    static const QString All[] = {
        // Core boozes
        "Vodka",
        "Tequila",
        "Bourbon",
        "Gin",
        "Dark Rum",
        "White Rum",
        "Light Rum",

        // Liquors
        "Grand Marnier",
        "Sweet Vermouth",
        "Dry Vermouth",
        "Tripple Sec",
        "Kahlua",
        "Jagermeister",
        "Campari",
        "Green Creme de Menthe",
        "Creme de Cacao",
        "Peach Schnapps",

        // Kitchen basics
        "Salt",
        "Pepper",
        "Ice",

        // Non alcoholic liquids
        "Simple Syrup",
        "Tonic Water",
        "Sparkling Water",
        "Angostura Bitters",
        "Cola",
        "Club Soda",
        "Cream",
        "Worcestershire Sauce",

        // Fruit juices.
        "Orange Juice",
        "Lime Juice",
        "Lemon Juice",
        "Pineapple Juice",
        "Tomato Juice",
        "Cranberry Juice",

        // Fruits and Vegetables.
        "Orange Wedge",
        "Orange Twist",
        "Lime Wedge",
        "Lime Twist",
        "Lemon Twist",
        "Pineapple Wedge",
        "Cream Of Coconut",
        "Ginger Beer",
        "Mint Leaf",
        "Mint Sprig",
        "Cherry",
        "Green Olive",
        "Celery",
        "Nutmeg",

        // Actions
        "Shake",
        "Stir",
        "Muddle"
    };
}

#endif // INGREDIENTS_H
