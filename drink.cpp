#include "drink.h"

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

void Drink::setName(QString name)
{
    Name = name;
}

void Drink::setSteps(QVector<Step> steps)
{
    Steps= steps;
}

void Drink::addTrivia(QString triv)
{
    Trivia.push_back(triv);
}

void Drink::addIngredient(Ingredients::Ingredients ingredient, double amount)
{
    IngredientsMap[ingredient] = amount;

}

void Drink::addStep(QString instruction, Ingredients::Ingredients ingredient, double amount)
{
    Step step = Step(instruction, ingredient, amount);
    Steps.push_back(step);
}

void Drink::setSelected(bool select)
{
    userSelected=select;
}

QString Drink::getName()
{
    return Name;
}

QVector<QString> Drink::getTrivia()
{
    return Trivia;
}

QMap<Ingredients::Ingredients, double> Drink::getTngredients()
{
    return IngredientsMap;
}

QVector<Step> Drink::getSteps()
{
    return Steps;
}

bool Drink::getSelected()
{
    return userSelected;
}

