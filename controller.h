#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QtMath>
#include <QDebug>
#include "drink.h"
#include "ingredients.h"
#include "ingredientsprite.h"
#include "qsfmlcanvas.h"
#include "xmldrinkparser.h"
#include "recordtracker.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @brief The Controller class: in charge of game data
 * and communications with tools outside of game mechanics.
 * Author: Cody Winters
 */
class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(XMLDrinkParser *parser, QObject *parent = nullptr);

public slots:

    /**
     * @brief timerUpdate: updates the in-game timer and mood sprite every second If the time has exceed the
     * time alloted to make the drink, decreases the customers current mood every starting mood seconds.
     * If the customers mood drops to 0 the mood is no longer decreased, but the timer continues to run until the
     * user ends the roudn by serving the drink.
     */
    void timerUpdate();

    /**
     * @brief startRound: Calls newCustomer and sets up values for the round:
     * drinkComplexity: the number of steps in the selected recipe, it is used to calculate the time allowed to complete
     * the drink as well as the tip earned at the end of a round Sends the selected drink and mood to the game and allows
     * the user to serve a drink. If the user has selected the easy difficulty, they are given unlimited time.
     */
    void startRound();

    /**
     * @brief updateRecipes: Receives a drink object created by the user and calls the xml parser to add the drink to the database.
     * Also, appends the new drink to the main and user specified menus
     * @param newRecipe: recipe to update
     */
    void updateRecipes(Drink* newRecipe);

    /**
     * @brief checkIngredient: Checks the user added ingredient and amount against the recipe for the currently
     * selected drink and assigns points/penalties. Actions (eg stir) are handled separately as they have no amount
     * value. Points are assigned according to the following rules:
     *
     * If the ingredient has not been added to the drink:
     * correct ingredient, step, and amount = 3 points
     * correct ingredient and step, but wrong amount = 2 points
     * correct ingredient, but wrong step and amount = 1 point
     * ingredient that the drink does not contain = -3 points
     *
     * If the added ingredient has already been added to the drink:
     * ingredient in the recipe and this addition corrects the amount = 1 point
     * otherwise adding a previously added ingredient = -3 points
     *
     * @param ingredient: ingredient to check
     */
    void checkIngredient(Ingredients::Ingredients ingredient);

    /**
     * @brief menuRequestByGameArea: send the entire menu (not only userspecified) to gameArea
     */
    void menuRequestByGameArea();

    /**
     * @brief menuRequestedByMainWindow: send the entire menu (not only userspecified) to mainWindow in the receiveMenu slot
     */
    void menuRequestedByMainWindow();

    /**
     * @brief menuInfoRequestedByMainWindow: send the entire menu (not only userspecified) to mainWindow in the receiveMenuInfo slot
     */
    void menuInfoRequestedByMainWindow();

    /**
     * @brief receiveUserSpecifiedMenu: after the user has selected/deselected drinks in the UI, receive the vector containing all
     * drinks and remove/add drinks to the user specified menu for use in selecting drinks in future rounds
     *
     * @param newMenu: new custom drinks
     */
    void receiveUserSpecifiedMenu(QVector<Drink*> newMenu);

    /**
     * @brief startGame: intializes the difficutly variable, clears any ingredients added to the glass before the game started, and calls the startRound function
     * @param difficulty
     */
    void startGame(unsigned int difficulty);

    /**
     * @brief receiveAmountToAdd: intializes the ingredient amount variable with the user specifed amount
     * @param amount: inputted amount
     */\
    void receiveAmountToAdd(double amount);

    /**
     * @brief drinkServed: calls the endRound for the current round, clears the contents of the current drink from the glass and starts a new round after 1 second
     */
    void drinkServed();

    /**
     * @brief recordsRequestedByMainWindow: sends the historical score data to mainWindow as a QMap<QString, int>
     */
    void recordsRequestedByMainWindow();

signals:

    /**
     * @brief moodToGameArea: sends the currentHappiness variable to the receiveMood slot in gameArea for sprite selection
     * @param happinessLevel: current customer happiness level
     */
    void moodToGameArea(int happinessLevel);

    /**
     * @brief clearDrink: informs gameArea to remove ingredients from the glass via the drinkServed slot
     */
    void clearDrink();

    /**
     * @brief menuToMainWindow: sends the menu to the receiveMenu slot in mainWindow
     * @param menu: menu to send
     */
    void menuToMainWindow(QVector<Drink*> menu);

    /**
     * @brief menuInfoToMainWindow: sends the menu to the receiveMenuInfo slot in mainWindow
     * @param menu: menu to send
     */
    void menuInfoToMainWindow(QVector<Drink*> menu);

    /**
     * @brief recordsToMainWindow: sends historical score data to the receiveRecords slot in MainWindow
     */
    void recordsToMainWindow(QMap<QString, int>);

    /**
     * @brief sendDrink: sends a reference to the round selected drink object to the receiveDrink slot in mainWindow
     * @param drink: drink to send
     */
    void sendDrink(Drink* drink);

    /**
     * @brief sendTime: sends the updated timer to the receiveTime slot in mainWindow
     * @param currentTime
     */
    void sendTime(int currentTime);

    /**
     * @brief tipAmountToGame: sends total dollars and cents for this game session as ints to the receiveTips slot in mainWindow
     * @param tipDollars: dollars to add
     * @param tipCents: cents to add
     */
    void tipAmountToGame(int tipDollars, int tipCents);

    /**
     * @brief requestAmountToAdd: sends a request for the amount of an ingredient that has been added to the drink glass in gameArea to the
     * requestAmountToAdd slot in mainWindow
     */
    void requestAmountToAdd();

    /**
     * @brief enableServe: sends a request to the enableServe slot of mainWindow to set the status of the serve drink button to enabled(true)
     */
    void enableServe();

private:

    /**
     * @brief calculateTip: Receives references to the totalTip dollars and cents variables that are appropriate to the user selected
     * difficulty as parameters. The tip for the round is calculated by the following equation (drinkPoints * 10 * moodValueModifier)
     * where drink points are the points earned by adding correct ingredients and the moodValueModifier
     * is currentHappiness/5 where 5 is the maximum displayed customer mood.
     * currentHappines can exceed 5 due to excellent service time and drink correctness or drop belowzero due to served drink incorrectness
     * Tips are not calculated for customers whose currentHappiness is <= 0
     * @param dollars: dollar amount to calculate
     * @param cents: cent amount to calculate
     */
    void calculateTip(int dollars, int cents); //when drink is served

    /**
     * @brief endRound: stops the round timer and calls endOfRoundHappinessBonus to determine the currentHappiness score
     * for the customer based on quality and timeliness of drink service.
     *
     * It calculates the tip and stores the following information in the historical score document:
     * total tip dollars and cents
     * number of satisfied customers
     * number of dissatisfied customers
     * number of drinks served
     *
     * After the score information has been stored, standardizes the happiness of the customer
     * to be between 0 and 5 so that mood can be displayed by the UI
     */
    void endRound();

    /**
     * @brief getAllRecipes: calls the XML database parser for a vector of Drink pointers to be used as the menu for the game.
     * @return
     */
    QVector<Drink*> getAllRecipes();

    /**
     * @brief newCustomer: Randomizes the starting currentHappiness value based on difficulty level as per below:
     * easy: 3, 4, 5
     * medium: 2, 3, 4
     * hard: 2, 3
     *
     * calls selectRandomDrink to get a recipe from the user specified menu generates the moodValuModifier as
     * currentHappiness/5 where 5 is the maximum starting happiness sets up the added ingredients vector and step count for a new round
     *
     * @param difficulty: level of difficulty
     */
    void newCustomer(unsigned int difficulty);

    /**
     * @brief selectNewRandomDrink: Randomly selects a recipe from the user specified menu and returns a pointer to the drink object.
     * @return
     */
    Drink* selectNewRandomDrink();

    /**
     * @brief handleActionIngredients: because action ingredients do not have an amount, they are handled by this helper method instead of in
     * checkAddedIngredients Actions are granted points based on the following rules:
     *
     * action taken on the correct step = 3 points action in recipe,
     * but wrong order = 1 point action not in recipe or
     * action has already been taken = -3 points
     *
     * @param steps: steps to check
     * @param current: current step
     * @param ingredient: ingredient to check
     */
    void handleActionIngredients(QVector<Step> steps, Step current, Ingredients::Ingredients ingredient);

    /**
     * @brief endOfRoundHappinessBonus: Allows the user to gain extra tips through timely and accurate drink service according to the following rules:
     * when drinkPoints <= 0: happiness = 0 otherwise happiness =  (5 * drinkPoints) / (drinkComplexity * 3)) - 2
     *
     * This equation is derived from the following:
     * max drinkPoints = 3 times drinkComplexity (3 for each step in the recipe)
     * percent correct = 100 x drinkPoints / max drink points
     * divide by 20 to get a number from 0 to 5 (100 becomes 5)subtract 2 so that tips dont get higher than the price of a drink
     * apply the new mood to moodValueModifier
     */
    void endOfRoundHappinessBonus();

    /**
     * @brief standardizeHappiness: The moods that can be displayed by the UI canonly be in the range of 0 to 5
     * while the moods of customers in the controller can be higher or lower for score calculation after score has
     * been tabluated, return currentHappiness to the displayable range.
     */
    void standardizeHappiness();

    /**
     * @brief containsIngredient: Helper method for checkIngredient which scans a recipe to determine if
     * an ingredient is contained therein.
     *
     * @param ingredient: ingredient to check
     * @param steps: steps to check
     * @return
     */
    bool containsIngredient(Ingredients::Ingredients ingredient, QVector<Step> steps);

    /**
     * @brief outOfOrderAmount: Helper method for checkIngredient which checks if the amount of ingredient
     * added to the glass when the ingredients are not added in order, matches the amount of the ingredient
     * that is supposed to be added according to the recipe.
     *
     * @param ingredient: ingredient to check
     * @param steps: steps to check
     * @param amount: amount to check
     * @return
     */
    bool outOfOrderAmount(Ingredients::Ingredients ingredient, QVector<Step> steps, double amount);

    // class variables
    Drink* currentDrink;
    int currentHappiness;
    int standardizedHappiness;
    int stepCount;
    int easyTotalTipDollars;
    int medTotalTipDollars;
    int hardTotalTipDollars;
    int easyTotalTipCents;
    int medTotalTipCents;
    int hardTotalTipCents;
    int easyTotalCustomersSatisfied;
    int medTotalCustomersSatisfied;
    int hardTotalCustomersSatisfied;
    int easyTotalCustomersDissatisfied;
    int medTotalCustomersDissatisfied;
    int hardTotalCustomersDissatisfied;
    int easyTotalDrinksServed;
    int medTotalDrinksServed;
    int hardTotalDrinksServed;
    int timeToCompleteDrink;
    int drinkComplexity;
    int drinkPoints;
    unsigned int difficulty;
    double moodValueModifier;
    double ingredientAmount;
    QVector<Drink*> menu;
    QVector<Drink*> userSpecifiedMenu;
    QMap<Ingredients::Ingredients,double> addedIngredients;
    XMLDrinkParser *parser;
    QTimer *timer;
};

#endif // CONTROLLER_H
