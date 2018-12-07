#include "drink.h"
#include <iostream>

Drink::Drink()
{
    IngredientsMap = QMap<Ingredients::Ingredients, double>();
    Trivia = QVector<QString>();
    Steps = QVector<Step>();
    userSelected=false;
}

Drink::Drink(QString name)
{

    Name = name;
    IngredientsMap = QMap<Ingredients::Ingredients, double>();
    Trivia = QVector<QString>();
    Steps = QVector<Step>();
    userSelected=false;
}

void Drink::setName(QString name){
    Name = name;
}

void Drink::setSteps(QVector<Step> steps){
    Steps= steps;
}

void Drink::addTrivia(QString triv){
    Trivia.push_back(triv);
}

void Drink::addIngredient(Ingredients::Ingredients ingredient, double amount){

    IngredientsMap[ingredient] = amount;

}

void Drink::addStep(QString instruction, Ingredients::Ingredients ingredient, double amount){
    Step step = Step(instruction, ingredient, amount);
    Steps.push_back(step);
}

void Drink::setSelected(bool select){
    userSelected=select;
}

QString Drink::getName(){
    return Name;
}

QVector<QString> Drink::getTrivia(){
    return Trivia;
}

QMap<Ingredients::Ingredients, double> Drink::getTngredients(){
    return IngredientsMap;
}

QVector<Step> Drink::getSteps(){
    return Steps;
}

bool Drink::getSelected(){
    return userSelected;
}

void Drink::print(){
    std::cout<<"-------------------Drink Name: "<<Name.toStdString()<<"-------------------"<<std::endl;
    QMap<Ingredients::Ingredients, double>::iterator it;
    QString output;
    output ="Ingredients:";
    std::cout<<output.toStdString()<<std::endl;
    for (it = IngredientsMap.begin(); it != IngredientsMap.end(); ++it) {
        // Format output here.
        output="";
        output+= Ingredients::ingredientData[it.key()].displayString;
        output+=" ";
        output+= QString::number(IngredientsMap.value(it.key()));
        output+=" ";
        std::cout<<output.toStdString()<<std::endl;
    }

    output ="Steps:\n";

    for (int i = 0; i < Steps.size(); ++i)
    {

        output += Steps.at(i).getInstruction();
        output +="\nItem: ";
        output += Ingredients::ingredientData[Steps.at(i).getItem()].displayString;
        output +="\nAmount: ";
        output += QString::number(Steps.at(i).getAmount());
        std::cout<<output.toStdString()<<std::endl;
        output="";
    }
    output="Trivia:";
    std::cout<<output.toStdString()<<std::endl;
    for(int j=0; j<Trivia.size(); ++j){
        output=Trivia.at(j);
        std::cout<<output.toStdString()<<std::endl;
    }

}

