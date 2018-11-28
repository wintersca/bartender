#include "xmldrinkparser.h"
#include <iostream>
#include <QDir>

XMLDrinkParser::XMLDrinkParser()
{

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
        stringsToIngredients["Margarita Salt"]=Ingredients::MargaritaSalt;

}

QVector<Drink*> XMLDrinkParser::parseXMLDatabase()
{
    std::cout <<QDir::currentPath().toStdString()<<std::endl;
    //QVector<Drink> result;
    QFile file("../a8-an-educational-app-f18-kathrynriding-1/database/DrinkDatabase.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        std::cout << "Cannot read file: " << file.errorString().toStdString() <<std::endl;
        return drinkDatabase;
    }
    else
    {
        reader.setDevice(&file);
        read();
    }

return drinkDatabase;
}

void XMLDrinkParser::read(){
    if(reader.readNextStartElement()){
        if(reader.name()=="collection"){
            readDrinkDatabase();
        }
        else{
            std::cout<<"Not a drink database"<<std::endl;
        }
    }
}

void XMLDrinkParser::readDrinkDatabase(){
    while(reader.readNextStartElement()){
        if(reader.name()=="drink"){
            //std::cout<<"Drink found"<<std::endl;
            readDrink();
        }
        else{
            reader.skipCurrentElement();
        }
    }
}

void XMLDrinkParser::readDrink(){
    Drink* drink = new Drink();
    readName(drink);
    while(reader.readNextStartElement()){
        if(reader.name()=="ingredients"){
            readIngredients(drink);
        }
        else if(reader.name()=="actions"){
            readSteps(drink);
        }
        else if(reader.name()=="trivia_details"){
            readTrivia(drink);
        }
        else{
            reader.skipCurrentElement();
        }
    }
    addDrink(drink);
}

void XMLDrinkParser::readName(Drink* drink){
    reader.readNextStartElement();
    QString name = reader.readElementText();
    //std::cout<<"Name found "<<name.toStdString()<<std::endl;
    drink->setName(name);
}

void XMLDrinkParser::readIngredients(Drink* drink){
    bool test=reader.readNextStartElement();
    while(test){
        //std::cout<<"Top of while: "<< test <<std::endl;
        QString skip = reader.name().toString();
        //std::cout<<"Start Element Name "<<skip.toStdString()<<std::endl;
        if(reader.name()=="ingredient"){
            const QString name = reader.attributes().value("name").toString();
            //std::cout<<"Ingredient found "<<name.toStdString()<<std::endl;
            double amt = reader.attributes().value("amount").toDouble();
            //std::cout<<"Ingredient found "<<amt<<std::endl;
            drink->addIngredient(stringsToIngredients.value(name), amt);
        }
        reader.skipCurrentElement();
        test=reader.readNextStartElement();
        skip = reader.name().toString();
        //std::cout<<"Reader Name "<<skip.toStdString()<<std::endl;
        //std::cout<<"Bottom of while: "<< test <<std::endl;
    }
}

void XMLDrinkParser::readSteps(Drink* drink){
    while(reader.readNextStartElement()){
        if(reader.name()=="action"){
            QString inst = reader.attributes().value("instruction").toString();
            //std::cout<<"Step found "<<inst.toStdString()<<std::endl;
            const QString item = reader.attributes().value("item").toString();
            //std::cout<<"Step found "<<item.toStdString()<<std::endl;
            double amt = reader.attributes().value("amount").toDouble();
            //std::cout<<"Step found "<<amt<<std::endl;
            drink->addStep(inst, stringsToIngredients.value(item), amt);
        }
        reader.skipCurrentElement();
    }
}

void XMLDrinkParser::readTrivia(Drink* drink){
    while(reader.readNextStartElement()){
        if(reader.name()=="trivia"){
            QString triv = reader.attributes().value("description").toString();
            //std::cout<<"Trivia found "<<triv.toStdString()<<std::endl;
            drink->addTrivia(triv);
        }
        reader.skipCurrentElement();
    }
}

void XMLDrinkParser::addDrink(Drink* drink){
    drinkDatabase.push_back(drink);
    drink->print();
}

void XMLDrinkParser::updateXMLDatabase(Drink* newDrink)
{

}
