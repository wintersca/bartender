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
        Rum,
        WhiteRum,
        LightRum,

        // Liquors
        GrandMarnier,
        SweetVermouth,
        Angustura,
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
        DryVermouth,
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
        CreamOfCoconut,
        GingerBeer,
        MintLeaf,
        Cherry,
        GreenOlive,
        Celery,
        Nutmeg,
        MintSprig,
        PineappleWedge,

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
        "Rum",
        "White Rum",
        "Light Rum",

        // Liquors
        "Grand Marnier",
        "Sweet Vermouth",
        "Angustura",
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
        "Dry Vermouth",
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
        "Cream Of Coconut",
        "Ginger Beer",
        "Mint Leaf",
        "Cherry",
        "Green Olive",
        "Celery",
        "Nutmeg",
        "Mint Sprig",
        "Pineapple Wedge",

        // Actions
        "Shake",
        "Stir",
        "Muddle"
    };
}

#endif // INGREDIENTS_H
