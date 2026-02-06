#include <vex.h>

void menu();
void preAuton();

#pragma once

#include <iostream>

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Variables for ACCESS_OS > Constant vars that won't change during program run
------------------------------------------------------------------------------------------------------*/
#include <string>

//Define buttons for easy coding
#define btnNONE				0
#define btnUP				  1
#define btnDOWN				2
#define btnLEFT				3
#define btnRIGHT			4
#define btnA				  5
#define btnB				  6
#define btnX				  7
#define btnY				  8
#define btnR1				  9
#define btnR2				  10
#define btnL1				  11
#define btnL2				  12

//Define delays
#define bounceDelay			20		//Time to wait between reads to check for key bounce
#define refreshDelay		150		//Time to wait between refreshing screens

//Define usable screen space for easy coding
#define screenTextWidth		16		//Max characters you can print on one line
#define screenTextHeight	3		//Max lines of text that can show on the controller

//Define max entries in 2d array for easy coding
#define maxMenus			3		//Make this the same # as items in maxMenusIndex
#define maxOptions			10		//Make this the same # as items in 2D of menuDisplayIndex

//Define robot status for easy coding
#define modeDisabled		0
#define modeDriver			1
#define modeAuton			2
#define modeError			3

//Define more robot info for easy coding
#define LEFT						0
#define RIGHT						1
#define SKILLS		  		        2

#define LG6_3                       0
#define LG9                         1
#define LG7                         2   

#define RED							0
#define BLUE						1

#define COLOR						0
#define POSITION				    1
#define POINTS					    2

/*------------------------------------------------------------------------------------------------------
[CLASS] ACCESS_OS > Defines class functions
------------------------------------------------------------------------------------------------------*/
class ACCESS_OS 
{
private:
	int keyPressedRaw();		//Raw button inputs
	bool isCursorOn = false;	//Flag for if cursor is showing or not

	/*------------------------------------------------------------------------------------------------------
	[GLOBAL] Arrays for ACCESS_OS > ACCESS_OS needed stuff
	------------------------------------------------------------------------------------------------------*/
	//1D array for displaying robot status
	std::string robotStatus[4] =
	{
		"!Robot Disabled!",
		"Driver Control",
		"Auton Control",
		"!! MODE ERROR !!"
	};

	//1D Array for max options in menu
	int maxMenusIndex[maxMenus] =
	{
		2,
		4,
		9
	};

	//1D Array for default selected options.
	//NOTE: Changing the values here will change the default options
	int configuration[maxMenus] =
	{
		0,
		0,
		1
	};

	//1D array for displaying the menu types
	std::string menuTypes[maxMenus] =
	{
		" Pos: ",
		" Pnts: ",
		" Team: "
	};

	//2D array for displaying the menu options
	std::string menuOptions[maxMenus][maxOptions] =
	{
		{ "Left", "Right", "Skills" }, //If "" doesn't work, try "NULL"
		{ "6+3", "LG9",	"LG7" },
		{ "Red", "Blue" }
	};
public:
	ACCESS_OS();											//???
	int keyPressed();										//Filtered button inputs
	int currStatus();										//Gets current robot status
	void clearLine(int l_row);								//Smart row clearer
	void clearScreen();										//Smart screen clearer
	void print(std::string text, int row, int col);			//Prints without overwriting selector
	void selector(int row);									//Prints selector
	void displayMenu(int currRow, int configuration[]);		//Prints config menu
	int getValues(int wantConfig);							//Returns current values of configuration[]

	//Pre-built programs
	void notificationHUD(std::string str);					//Prints a message on first line
	void statusHUD();										//Prints current robot status on two lines
	void menuCONFIG();										//Runs complete config menu
};