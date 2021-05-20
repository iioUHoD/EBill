#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include "Background.h"
#include <stdio.h>
#include <iostream>

typedef struct
{
	// em = electricity meter
	// wm = water meter
	int room_no;
	int pre_em_value;
	int now_em_value;
	int pre_wm_value;
	int now_wm_value;
	float cal_e_bill;
	float cal_w_bill;
}data;

// funtion prototype
void Input_rooms(int n, data* room);
void cal_bill(int n, data* room);
void SortbyID(int n, data* room);
void Print_bill(int n, data* room);
void initialNumberOfRoomInput();
void initialFont();
void initialRoomNumberInput();
void update();
void initialValuesInput();
void initialUnitInput();

Background* background;
sf::Texture* appBackground;

sf::Text* showInputNumOfRoom;
sf::Text* numOfRoomInput;
sf::RectangleShape textBox1;

sf::Font* font;

sf::Text* showInputRoomNum;
sf::Text* roomNumberInput;
sf::RectangleShape textBox2;

sf::Text* showInputElecValuePre;
sf::Text* showInputElecValueCur;
sf::Text* ElecValuePreInput;
sf::Text* ElecValueCurInput;
sf::Text* showInputWateValuePre;
sf::Text* showInputWateValueCur;
sf::Text* WateValuePreInput;
sf::Text* WateValueCurInput;
sf::RectangleShape textBox3;
sf::RectangleShape textBox4;
sf::RectangleShape textBox5;
sf::RectangleShape textBox6;

sf::Text* showUnitElecValue;
sf::Text* showUnitWaterValue;
sf::Text* ElecUnitInput;
sf::Text* WaterUnitInput;
sf::RectangleShape textBox7;
sf::RectangleShape textBox8;

sf::Text* resultStr;

bool isFinishNumOfRoomInput = false;
bool isStartRoomNumberInput = false;
bool isFinishRoomNumberInput = false;
bool isStartValuesInput = false;
bool isFinishValuesInput = false;
bool isStartUnitInput = false;
bool isFinishUnitInput = false;

int n_room;
int roomCount = 0;

float elecUnit;
float waterUnit;

data room[5];

int main(){
    // init Screen and Background
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Cal Bill");
	appBackground = new sf::Texture;
	appBackground->loadFromFile("Textures/bg.png");
	background = new Background(appBackground);

    
    std::string numOfRoom = "";
    std::string roomNumber = "";
    std::string valueIn = "";
    // std::string ElecValueCur = "";
    // std::string WateValuePre = "";
    // std::string WateValueCur = "";
    int inputCount = 0;
    int stateCount = 0;

    initialFont();
    initialNumberOfRoomInput();
    initialRoomNumberInput();
    initialValuesInput();
    initialUnitInput();

	
	//Input_rooms(n_room, room);
	//cal_bill(n_room, room);
	//SortbyID(n_room, room);
	//Print_bill(n_room, room);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
                window.close();
            }

            else if (event.type == sf::Event::TextEntered && !isFinishNumOfRoomInput ) {
			    switch (event.key.code) {
			        case 8:
				        if (numOfRoom.size() == 0) {
					        break;
				        }
				        numOfRoom.pop_back();
				        numOfRoomInput->setString(numOfRoom);
				        break;
			        case 13:
				        isFinishNumOfRoomInput = true;
                        break;
			        default:
				        numOfRoom += event.text.unicode;
				        numOfRoomInput->setString(numOfRoom);
                        n_room = std::stoi(numOfRoom);
			    }
		    }

            else if (event.type == sf::Event::TextEntered && isStartRoomNumberInput && !isFinishRoomNumberInput ) {
			    switch (event.key.code) {
			        case 8:
				        if (roomNumber.size() == 0) {
					        break;
				        }
				        roomNumber.pop_back();
				        roomNumberInput->setString(roomNumber);
				        break;
			        case 13:
                        room[roomCount].room_no = std::stoi(roomNumber);
				        roomCount++;
                        roomNumber = "";
                        roomNumberInput->setString(roomNumber);
                        break;
			        default:
				        roomNumber += event.text.unicode;
                        roomNumberInput->setString(roomNumber);
				        
			    }
		    }

            else if (event.type == sf::Event::TextEntered && isStartValuesInput && !isFinishValuesInput ) {
			    switch (event.key.code) {
			        case 8:
				        if (valueIn.size() == 0) {
					        break;
				        }
				        valueIn.pop_back();
				        if(stateCount == 0){
                            ElecValuePreInput->setString(valueIn);
                        }
                        else if(stateCount == 1){
                            ElecValueCurInput->setString(valueIn);
                        }
                        else if(stateCount == 2){
                            WateValuePreInput->setString(valueIn);
                        }
                        else if(stateCount == 3){
                            WateValueCurInput->setString(valueIn);
                        }
				        break;
			        case 13:
                        if(stateCount == 0){
                            room[roomCount].pre_em_value = std::stoi(valueIn);
                            ElecValuePreInput->setString(valueIn);
                            stateCount++;
                            valueIn = "";
                            break;
                        }
                        else if(stateCount == 1){
                            room[roomCount].now_em_value = std::stoi(valueIn);
                            ElecValueCurInput->setString(valueIn);
                            stateCount++;
                            valueIn = "";
                            break;
                        }
                        else if(stateCount == 2){
                            room[roomCount].pre_wm_value = std::stoi(valueIn);
                            WateValuePreInput->setString(valueIn);
                            stateCount++;
                            valueIn = "";
                            break;
                        }
                        else if(stateCount == 3){
                            room[roomCount].now_wm_value = std::stoi(valueIn);
                            WateValueCurInput->setString(valueIn);
                            stateCount++;
                            valueIn = "";
                            roomCount++;
                            stateCount = 0;
                            ElecValuePreInput->setString(valueIn);
                            ElecValueCurInput->setString(valueIn);
                            WateValuePreInput->setString(valueIn);
                            WateValueCurInput->setString(valueIn);
                            break;
                        }

			        default:
				        valueIn += event.text.unicode;
                        if(stateCount == 0){
                            ElecValuePreInput->setString(valueIn);
                        }
                        else if(stateCount == 1){
                            ElecValueCurInput->setString(valueIn);
                        }
                        else if(stateCount == 2){
                            WateValuePreInput->setString(valueIn);
                        }
                        else if(stateCount == 3){
                            WateValueCurInput->setString(valueIn);
                        }
			    }
		    }

            else if (event.type == sf::Event::TextEntered && isStartUnitInput && !isFinishUnitInput ) {
			    switch (event.key.code) {
			        case 8:
				        if (valueIn.size() == 0) {
					        break;
				        }
				        valueIn.pop_back();
                        if(stateCount == 0){
                            ElecUnitInput->setString(valueIn);
                        }
                        else if(stateCount == 1){
                            WaterUnitInput->setString(valueIn);
                        }
				        break;
			        case 13:
                        if(stateCount == 0){
                            elecUnit = std::stof(valueIn);
                            ElecUnitInput->setString(valueIn);
                            stateCount++;
                            valueIn = "";
                            break;
                        }
                        else if(stateCount == 1){
                            waterUnit = std::stof(valueIn);
                            WaterUnitInput->setString(valueIn);
                            stateCount++;
                            valueIn = "";
                            isFinishUnitInput = true;
                            break;
                        }

			        default:
				        valueIn += event.text.unicode;
                        if(stateCount == 0){
                            ElecUnitInput->setString(valueIn);
                        }
                        else if(stateCount == 1){
                            WaterUnitInput->setString(valueIn);
                        }
			    }
		    }
				
		}

        update();

		window.clear();
		background->render(window);

        window.draw(*showInputNumOfRoom);
        window.draw(textBox1);
        window.draw(*numOfRoomInput);

        window.draw(*showInputRoomNum);
        window.draw(textBox2);
        window.draw(*roomNumberInput);

        window.draw(*showInputElecValuePre);
        window.draw(*showInputElecValueCur);
        window.draw(textBox3);
        window.draw(textBox4);
        window.draw(*showInputWateValuePre);
        window.draw(*showInputWateValueCur);
        window.draw(textBox5);
        window.draw(textBox6);
        window.draw(*ElecValuePreInput);
        window.draw(*ElecValueCurInput);
        window.draw(*WateValuePreInput);
        window.draw(*WateValueCurInput);

        window.draw(*showUnitElecValue);
        window.draw(*showUnitWaterValue);
        window.draw(textBox7);
        window.draw(textBox8);
        window.draw(*ElecUnitInput);
        window.draw(*WaterUnitInput);
        if(isFinishUnitInput){
            window.draw(*resultStr);
        }
		window.display();
	}
	return 0;
}

void Input_rooms(int n, data* room){
    for (int i = 0; i < n; i++)
    {
        printf("Input room no: ");
        scanf("%d", &room[i].room_no);

        printf("Input Previous electricity meter values room %d: ", room[i].room_no);
        scanf("%d", &room[i].pre_em_value);
        printf("Input Current electricity meter values room %d: ", room[i].room_no);
        scanf("%d", &room[i].now_em_value);

        printf("Input Previous water meter values room %d: ", room[i].room_no);
        scanf("%d", &room[i].pre_wm_value);
        printf("Input Current water meter values room %d: ", room[i].room_no);
        scanf("%d", &room[i].now_wm_value);
        printf("\n");
    }
}

void cal_bill(int n, data* room){
    
    for (int i = 0; i < n; i++)
    {
        if (room[i].pre_em_value <= room[i].now_em_value)
        {
            room[i].cal_e_bill = (room[i].now_em_value - room[i].pre_em_value) * elecUnit;
        }
        else
        {
            room[i].cal_e_bill = ((100000 - room[i].pre_em_value) + room[i].now_em_value) * elecUnit;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (room[i].pre_wm_value <= room[i].now_wm_value)
        {
            room[i].cal_w_bill = (room[i].now_wm_value - room[i].pre_wm_value) * waterUnit;
        }
        else
        {
            room[i].cal_w_bill = ((100000 - room[i].pre_wm_value) + room[i].now_wm_value) * waterUnit;
        }
    }
}

void SortbyID(int n, data* room){
    data temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (room[i].room_no > room[j].room_no)
            {
                temp = room[i];
                room[i] = room[j];
                room[j] = temp;
            }
        }
    }
}

void Print_bill(int n, data* room){

    resultStr = new sf::Text();
	resultStr->setPosition(sf::Vector2f(50.0f, 260.0f));
	resultStr->setCharacterSize(40);
    resultStr->setFont(*font);
    std::string buff;
	resultStr->setString("");

    for (int i = 0; i < n; i++)
    {
        buff += "room : " + std::to_string(room[i].room_no) + "\n";
        buff += "Electricity bill : " + std::to_string(room[i].cal_e_bill) + "\n";
        buff += "Water billl : " + std::to_string(room[i].cal_w_bill) + "\n";
        buff += "\n";
    }
    resultStr->setString(buff);
}

void initialNumberOfRoomInput(){
	showInputNumOfRoom = new sf::Text();
	showInputNumOfRoom->setPosition(sf::Vector2f(50.0f, 50.0f));
	showInputNumOfRoom->setCharacterSize(40);
    showInputNumOfRoom->setFont(*font);
	showInputNumOfRoom->setString("Input number of room :");

	numOfRoomInput = new sf::Text();
	numOfRoomInput->setPosition(sf::Vector2f(380.0f, 52.0f));
    numOfRoomInput->setFont(*font);
    numOfRoomInput->setFillColor(sf::Color::Black);
	numOfRoomInput->setCharacterSize(40);

	textBox1.setPosition(sf::Vector2f(370.0f, 60.0f));
	textBox1.setSize(sf::Vector2f(100.0f,35.0f));
	textBox1.setFillColor(sf::Color::White);
}

void initialRoomNumberInput(){
	showInputRoomNum = new sf::Text();
	showInputRoomNum->setPosition(sf::Vector2f(50.0f, 90.0f));
	showInputRoomNum->setCharacterSize(40);
    showInputRoomNum->setFont(*font);
	showInputRoomNum->setString("Input room number :");

	roomNumberInput = new sf::Text();
	roomNumberInput->setPosition(sf::Vector2f(350.0f, 92.0f));
    roomNumberInput->setFont(*font);
    roomNumberInput->setFillColor(sf::Color::Black);
	roomNumberInput->setCharacterSize(40);

	textBox2.setPosition(sf::Vector2f(345.0f, 100.0f));
	textBox2.setSize(sf::Vector2f(100.0f,35.0f));
	textBox2.setFillColor(sf::Color::White);
}

void initialValuesInput(){
	showInputElecValuePre = new sf::Text();
	showInputElecValuePre->setPosition(sf::Vector2f(50.0f, 130.0f));
	showInputElecValuePre->setCharacterSize(40);
    showInputElecValuePre->setFont(*font);
	showInputElecValuePre->setString("Room 000 previous electricity : ");

    showInputElecValueCur = new sf::Text();
	showInputElecValueCur->setPosition(sf::Vector2f(550.0f, 130.0f));
	showInputElecValueCur->setCharacterSize(40);
    showInputElecValueCur->setFont(*font);
	showInputElecValueCur->setString("current : ");

    textBox3.setPosition(sf::Vector2f(450.0f, 140.0f));
	textBox3.setSize(sf::Vector2f(80.0f,35.0f));
	textBox3.setFillColor(sf::Color::White);

    textBox4.setPosition(sf::Vector2f(670.0f, 140.0f));
	textBox4.setSize(sf::Vector2f(80.0f,35.0f));
	textBox4.setFillColor(sf::Color::White);

    showInputWateValuePre = new sf::Text();
	showInputWateValuePre->setPosition(sf::Vector2f(50.0f, 170.0f));
	showInputWateValuePre->setCharacterSize(40);
    showInputWateValuePre->setFont(*font);
	showInputWateValuePre->setString("Room 000 previous water : ");

    showInputWateValueCur = new sf::Text();
	showInputWateValueCur->setPosition(sf::Vector2f(550.0f, 170.0f));
	showInputWateValueCur->setCharacterSize(40);
    showInputWateValueCur->setFont(*font);
	showInputWateValueCur->setString("current : ");

    textBox5.setPosition(sf::Vector2f(450.0f, 180.0f));
	textBox5.setSize(sf::Vector2f(80.0f,35.0f));
	textBox5.setFillColor(sf::Color::White);

    textBox6.setPosition(sf::Vector2f(670.0f, 180.0f));
	textBox6.setSize(sf::Vector2f(80.0f,35.0f));
	textBox6.setFillColor(sf::Color::White);

	ElecValuePreInput = new sf::Text();
	ElecValuePreInput->setPosition(sf::Vector2f(455.0f, 130.0f));
    ElecValuePreInput->setFont(*font);
    ElecValuePreInput->setFillColor(sf::Color::Black);
	ElecValuePreInput->setCharacterSize(40);

    ElecValueCurInput = new sf::Text();
	ElecValueCurInput->setPosition(sf::Vector2f(675.0f, 130.0f));
    ElecValueCurInput->setFont(*font);
    ElecValueCurInput->setFillColor(sf::Color::Black);
	ElecValueCurInput->setCharacterSize(40);

    WateValuePreInput = new sf::Text();
	WateValuePreInput->setPosition(sf::Vector2f(455.0f, 170.0f));
    WateValuePreInput->setFont(*font);
    WateValuePreInput->setFillColor(sf::Color::Black);
	WateValuePreInput->setCharacterSize(40);

    WateValueCurInput = new sf::Text();
	WateValueCurInput->setPosition(sf::Vector2f(675.0f, 170.0f));
    WateValueCurInput->setFont(*font);
    WateValueCurInput->setFillColor(sf::Color::Black);
	WateValueCurInput->setCharacterSize(40);

}

void initialUnitInput(){
    showUnitElecValue = new sf::Text();
	showUnitElecValue->setPosition(sf::Vector2f(50.0f, 210.0f));
	showUnitElecValue->setCharacterSize(40);
    showUnitElecValue->setFont(*font);
	showUnitElecValue->setString("Price per Unit Electricity : ");

    showUnitWaterValue = new sf::Text();
	showUnitWaterValue->setPosition(sf::Vector2f(550.0f, 210.0f));
	showUnitWaterValue->setCharacterSize(40);
    showUnitWaterValue->setFont(*font);
	showUnitWaterValue->setString("Water : ");

    textBox7.setPosition(sf::Vector2f(450.0f, 220.0f));
	textBox7.setSize(sf::Vector2f(80.0f,35.0f));
	textBox7.setFillColor(sf::Color::White);

    textBox8.setPosition(sf::Vector2f(670.0f, 220.0f));
	textBox8.setSize(sf::Vector2f(80.0f,35.0f));
	textBox8.setFillColor(sf::Color::White);

    ElecUnitInput = new sf::Text();
	ElecUnitInput->setPosition(sf::Vector2f(455.0f, 210.0f));
    ElecUnitInput->setFont(*font);
    ElecUnitInput->setFillColor(sf::Color::Black);
	ElecUnitInput->setCharacterSize(40);

    WaterUnitInput = new sf::Text();
	WaterUnitInput->setPosition(sf::Vector2f(675.0f, 210.0f));
    WaterUnitInput->setFont(*font);
    WaterUnitInput->setFillColor(sf::Color::Black);
	WaterUnitInput->setCharacterSize(40);

}

void initialFont(){
    font = new sf::Font;
	if (!font->loadFromFile("THSarabun.ttf")) {
		printf("Load font fail\n");
	}
}

void update(){
    if(isFinishNumOfRoomInput && !isStartRoomNumberInput && !isFinishRoomNumberInput){
        //printf("number of room finish \n");
        isStartRoomNumberInput = true;
    }
    
    if(isStartRoomNumberInput && !isFinishRoomNumberInput){
        
        if(roomCount < n_room){
            printf("not finish %d / %d\n",roomCount,n_room);
            showInputRoomNum->setString("Input " + std::to_string(roomCount + 1) + " room number :");
            isFinishRoomNumberInput = false;
        }
        else{
            printf("finish Input \n");
            isStartRoomNumberInput = false;
            isFinishRoomNumberInput = true;
            isStartValuesInput = true;
            roomCount = 0;
        }
    }

    if(isStartValuesInput){
        showInputElecValuePre->setString("Room "+ std::to_string(room[roomCount].now_wm_value) + " previous electricity : ");
        showInputWateValuePre->setString("Room "+ std::to_string(room[roomCount].now_wm_value) + " previous water : ");

        if(roomCount < n_room){
            printf("not finish input value %d / %d\n",roomCount,n_room);
            showInputRoomNum->setString("Input " + std::to_string(roomCount + 1) + " room number :");
            isFinishValuesInput = false;
        }
        else{
            isStartValuesInput = false;
            isFinishValuesInput = true;
            isStartUnitInput = true;
            roomCount = 0;
        }
    }

    if(isStartUnitInput){
        if(isFinishUnitInput){
            printf("finish unit input");
            isStartUnitInput = false;
            cal_bill(n_room, room);
            SortbyID(n_room, room);
            Print_bill(n_room, room);
            
        }
    }
}