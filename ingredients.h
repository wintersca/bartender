#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QMap>

namespace Ingredients {

    enum Ingredients : unsigned int {

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
        MargaritaSalt,
        Pepper,
        Nutmeg,
        Ice,
        MargaritaSalt,

        // Non alcoholic liquids
        TonicWater,
        SparklingWater,
        ClubSoda,
        Cola,
        SimpleSyrup,
        Cream,
        AngosturaBitters,
        WorcestershireSauce,
        CreamOfCoconut,
        GingerBeer,

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
        MintLeaf,
        MintSprig,
        Cherry,
        GreenOlive,
        Celery,

        // Actions
        Shake,
        Stir,
        Muddle

    };

    enum Action : unsigned int {

        PourAction,
        ShakeAction,
        StirAction,
        MuddleAction,
        AddAction

    };

    struct IngredientData {

      QColor color;
      QString unit;
      QString imageFilename;
      QString displayString;
      Action action;

    };

    const int TOTALINGREDIENTS = 52;

    //You index into this by ingredientData[Ingredient::Ingredient].
    // ingredientData[Ingredient::Ingredient].displayString, etc.
    static const IngredientData ingredientData[]
    {
        // Core boozes
        // Vodka
        {
            QColor(246, 246, 246),
            "oz",
            "Vodka.png",
            "Vodka",
            Action::PourAction
        },

        // Tequila
        {
            QColor(238, 151, 9),
            "oz",
            "Tequila.png",
            "Tequila",
            Action::PourAction
        },

        // Bourbon
        {
            QColor(247, 139, 31),
            "oz",
            "Bourbon.png",
            "Bourbon",
            Action::PourAction
        },
        // Gin
        {
            QColor(241, 241, 241),
            "oz",
            "Gin.png",
            "Gin",
            Action::PourAction
        },
        // Dark Rum
        {
            QColor(83, 12, 18),
            "oz",
            "DarkRum.png",
            "Dark Rum",
            Action::PourAction
        },
        // White Rum
        {
            QColor(232, 232, 232),
            "oz",
            "WhiteRum.png",
            "White Rum",
            Action::PourAction
        },
        // Light Rum
        {
            QColor(241, 232, 217),
            "oz",
            "LightRum.png",
            "Light Rum",
            Action::PourAction
        },
        // Liquors
        // Grand Marnier
        {
            QColor(134, 23, 3),
            "oz",
            "GrandMarnier.png",
            "Grand Marnier",
            Action::PourAction
        },
        // Sweet Vermouth
        {
            QColor(14, 12, 13),
            "oz",
            "SweetVermouth.png",
            "Sweet Vermouth",
            Action::PourAction
        },
        // Dry Vermouth
        {
            QColor(117, 177, 63),
            "oz",
            "DryVermouth.png",
            "Dry Vermouth",
            Action::PourAction
        },
        // Tripple Sec
        {
            QColor(237, 239, 247),
            "oz",
            "TrippleSec.png",
            "Tripple Sec",
            Action::PourAction
        },
        // Kahlua
        {
            QColor(35, 26, 21),
            "oz",
            "Kahlua.png",
            "Kahlua",
            Action::PourAction
        },
        // Jagermeister
        {
            QColor(7, 7, 5),
            "oz",
            "Jagermeister.png",
            "Jagermeister",
            Action::PourAction
        },
        // Campari
        {
            QColor(181, 26, 22),
            "oz",
            "Campari.png",
            "Campari",
            Action::PourAction
        },
        // Green Creme de Menthe
        {
            QColor(26, 29, 22),
            "oz",
            "GreenCremeDeMenthe.png",
            "Green Creme de Menthe",
            Action::PourAction
        },
        // Creme de Cacao
        {
            QColor(13, 13, 11),
            "oz",
            "CremeDeCacao.png",
            "Creme de Cacao",
            Action::PourAction
        },
        // Peach Schnapps
        {
            QColor(248, 244, 241),
            "oz",
            "PeachSchnapps.png",
            "Peach Schnapps",
            Action::PourAction
        },

        // Kitchen basics
        // Salt
        {
            QColor(243, 243, 245),
            "dash",
            "Salt.png",
            "Salt",
            Action::PourAction
        },
        // Margarita Salt
        {
            QColor(237, 237, 237),
            "rim",
            "MargaritaSalt.png",
            "Margarita Salt",
            Action::AddAction
        },
        // Pepper
        {
            QColor(132, 113, 99),
            "dash",
            "Pepper.png",
            "Pepper",
            Action::PourAction
        },
        // Nutmeg
        {
            QColor(154, 103, 70),
            "dash",
            "Nutmeg.png",
            "Nutmeg",
            Action::PourAction
        },
        // Ice
        {
            QColor(236, 240, 243),
            "oz",
            "Ice.png",
            "Ice",
            Action::PourAction
        },
        // Non alcoholic liquids
        // Tonic Water
        {
            QColor(236, 236, 236),
            "oz",
            "TonicWater.png",
            "Tonic Water",
            Action::PourAction
        },
        // Sparkling Water
        {
            QColor(234, 239, 245),
            "oz",
            "SparklingWater.png",
            "Sparkling Water",
            Action::PourAction
        },
        // Club Soda
        {
            QColor(238, 238, 238),
            "oz",
            "ClubSoda.png",
            "Club Soda",
            Action::PourAction
        },
        // Cola
        {
            QColor(222, 58, 20),
            "oz",
            "Cola.png",
            "Cola",
            Action::PourAction
        },
        // Simple Syrup
        {
            QColor(231, 230, 225),
            "oz",
            "SimpleSyrup.png",
            "Simple Syrup",
            Action::PourAction
        },
        // Cream
        {
            QColor(249, 248, 244),
            "oz",
            "Cream.png",
            "Cream",
            Action::PourAction
        },
        // Angostura Bitters
        {
            QColor(174, 73, 1),
            "oz",
            "AngosturaBitters.png",
            "Angostura Bitters",
            Action::PourAction
        },
        // Worcestershire Sauce
        {
            QColor(21, 3, 3),
            "oz",
            "WorcestershireSauce.png",
            "Worcestershire Sauce",
            Action::PourAction
        },
        // Cream Of Coconut
        {
            QColor(243, 242, 240),
            "oz",
            "CreamOfCoconut.png",
            "Cream Of Coconut",
            Action::PourAction
        },
        // Ginger Beer
        {
            QColor(226, 152, 19),
            "oz",
            "GingerBeer.png",
            "Ginger Beer",
            Action::PourAction
        },

        // Fruit juices.
        // Orange Juice
        {
            QColor(249, 198, 57),
            "oz",
            "OrangeJuice.png",
            "Orange Juice",
            Action::PourAction
        },
        // Lime Juice
        {
            QColor(224, 213, 168),
            "oz",
            "LimeJuice.png",
            "Lime Juice",
            Action::PourAction
        },
        // Lemon Juice
        {
            QColor(250, 220, 106),
            "oz",
            "LemonJuice.png",
            "Lemon Juice",
            Action::PourAction
        },
        // Pineapple Juice
        {
            QColor(235, 192, 61),
            "oz",
            "PineappleJuice.png",
            "Pineapple Juice",
            Action::PourAction
        },
        // Tomato Juice
        {
            QColor(223, 69, 45),
            "oz",
            "TomatoJuice.png",
            "Tomato Juice",
            Action::PourAction
        },
        // Cranberry Juice
        {
            QColor(144, 25, 28),
            "oz",
            "CranberryJuice.png",
            "Cranberry Juice",
            Action::PourAction
        },

        // Fruits and Vegetables.
        // Orange Wedge
        {
            QColor(255, 164, 3),
            "",
            "OrangeWedge.png",
            "Orange Wedge",
            Action::AddAction
        },
        // Orange Twist
        {
            QColor(251, 141, 43),
            "",
            "OrangeTwist.png",
            "Orange Twist",
            Action::AddAction
        },
        // Lime Wedge
        {
            QColor(188, 209, 6),
            "",
            "LimeWedge.png",
            "Lime Wedge",
            Action::AddAction
        },
        // Lime Twist
        {
            QColor(28, 94, 4),
            "",
            "LimeTwist.png",
            "Lime Twist",
            Action::AddAction
        },
        // Lemon Twist
        {
            QColor(217, 200, 48),
            "",
            "LemonTwist.png",
            "Lemon Twist",
            Action::AddAction
        },
        // Pineapple Wedge
        {
            QColor(240, 155, 38),
            "",
            "PineappleWedge.png",
            "Pineapple Wedge",
            Action::AddAction
        },
        // Mint Leaf
        {
            QColor(76, 151, 32),
            "",
            "MintLeaf.png",
            "Mint Leaf",
            Action::AddAction
        },
        // Mint Sprig
        {
            QColor(137, 172, 44),
            "",
            "MintSprig.png",
            "Mint Sprig",
            Action::AddAction
        },
        // Cherry
        {
            QColor(171, 0, 5),
            "",
            "Cherry.png",
            "Cherry",
            Action::AddAction
        },
        // Green Olive
        {
            QColor(177, 166, 16),
            "",
            "GreenOlive.png",
            "Green Olive",
            Action::AddAction
        },
        // Celery
        {
            QColor(177, 207, 81),
            "stalk",
            "Celery.png",
            "Celery",
            Action::AddAction
        },

        // Actions
        // Shake
        {
            QColor(0, 0, 0),
            "",
            "Shake.png",
            "Shake",
            Action::ShakeAction
        },
        // Stir
        {
            QColor(0, 0, 0),
            "",
            "Stir.png",
            "Stir",
            Action::StirAction
        },
        // Muddle
        {
            QColor(0, 0, 0),
            "",
            "Muddle.png",
            "Muddle",
            Action::MuddleAction
        },
    };

}

#endif // INGREDIENTS_H
