#include "ingredientsmap.h"

IngredientsMap::IngredientsMap()
{
    // Create a dictionary to map strings to enums.
    stringsToIngredients = QMap<QString, Ingredients::Ingredients>();
    stringsToIngredients["Vodka"] = Ingredients::Vodka;
    stringsToIngredients["Tequila"] = Ingredients::Tequila;
    stringsToIngredients["Bourbon"] = Ingredients::Bourbon;
    stringsToIngredients["Gin"] = Ingredients::Gin;
    stringsToIngredients["Dark Rum"] = Ingredients::DarkRum;
    stringsToIngredients["White Rum"] = Ingredients::WhiteRum;
    stringsToIngredients["Light Rum"] = Ingredients::LightRum;
    stringsToIngredients["Grand Marnier"] = Ingredients::GrandMarnier;
    stringsToIngredients["Sweet Vermouth"] = Ingredients::SweetVermouth;
    stringsToIngredients["Dry Vermouth"] = Ingredients::DryVermouth;
    stringsToIngredients["Tripple Sec"] = Ingredients::TrippleSec;
    stringsToIngredients["Kahlua"] = Ingredients::Kahlua;
    stringsToIngredients["Jagermeister"] = Ingredients::Jagermeister;
    stringsToIngredients["Campari"] = Ingredients::Campari;
    stringsToIngredients["Green Creme de Menthe"] = Ingredients::GreenCremeDeMenthe;
    stringsToIngredients["Creme de Cacao"] = Ingredients::CremeDeCacao;
    stringsToIngredients["Peach Schnapps"] = Ingredients::PeachSchnapps;
    stringsToIngredients["Salt"] = Ingredients::Salt;
    stringsToIngredients["Margarita Salt"] = Ingredients::MargaritaSalt;
    stringsToIngredients["Pepper"] = Ingredients::Pepper;
    stringsToIngredients["Ice"] = Ingredients::Ice;
    stringsToIngredients["Simple Syrup"] = Ingredients::SimpleSyrup;
    stringsToIngredients["Tonic Water"] = Ingredients::TonicWater;
    stringsToIngredients["Sparkling Water"] = Ingredients::SparklingWater;
    stringsToIngredients["Angostura Bitters"] = Ingredients::AngosturaBitters;
    stringsToIngredients["Cola"] = Ingredients::Cola;
    stringsToIngredients["Club Soda"] = Ingredients::ClubSoda;
    stringsToIngredients["Cream"] = Ingredients::Cream;
    stringsToIngredients["Worcestershire Sauce"] = Ingredients::WorcestershireSauce;
    stringsToIngredients["Orange Juice"] = Ingredients::OrangeJuice;
    stringsToIngredients["Lime Juice"] = Ingredients::LimeJuice;
    stringsToIngredients["Lemon Juice"] = Ingredients::LemonJuice;
    stringsToIngredients["Pineapple Juice"] = Ingredients::PineappleJuice;
    stringsToIngredients["Tomato Juice"] = Ingredients::TomatoJuice;
    stringsToIngredients["Cranberry Juice"] = Ingredients::CranberryJuice;
    stringsToIngredients["Orange Wedge"] = Ingredients::OrangeWedge;
    stringsToIngredients["Orange Twist"] = Ingredients::OrangeTwist;
    stringsToIngredients["Lime Wedge"] = Ingredients::LimeWedge;
    stringsToIngredients["Lime Twist"] = Ingredients::LimeTwist;
    stringsToIngredients["Lemon Twist"] = Ingredients::LemonTwist;
    stringsToIngredients["Pineapple Wedge"] = Ingredients::PineappleWedge;
    stringsToIngredients["Cream Of Coconut"] = Ingredients::CreamOfCoconut;
    stringsToIngredients["Ginger Beer"] = Ingredients::GingerBeer;
    stringsToIngredients["Mint Leaf"] = Ingredients::MintLeaf;
    stringsToIngredients["Mint Sprig"] = Ingredients::MintSprig;
    stringsToIngredients["Cherry"] = Ingredients::Cherry;
    stringsToIngredients["Green Olive"] = Ingredients::GreenOlive;
    stringsToIngredients["Celery"] = Ingredients::Celery;
    stringsToIngredients["Nutmeg"] = Ingredients::Nutmeg;
    stringsToIngredients["Shake"] = Ingredients::Shake;
    stringsToIngredients["Stir"] = Ingredients::Stir;
    stringsToIngredients["Muddle"] = Ingredients::Muddle;
}
