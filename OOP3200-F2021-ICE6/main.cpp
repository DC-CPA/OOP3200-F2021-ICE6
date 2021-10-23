#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>

#include "GameObject.h"
#include "Vector3D.h"


void PrintGameObjects(const std::map<std::string, GameObject*>& game_objects)
{
	std::cout << "=================================" << std::endl;
	std::cout << " Output map of Game Objects	   " << std::endl;
	std::cout << "=================================" << std::endl;

	//for every game_object in gameObjects

	for (const auto& game_object : game_objects)
	{
		std::cout << "Key	: " << game_object.first << std::endl;
		std::cout << "=================================" << std::endl;
		std::cout << game_object.second->ToString();
		std::cout << "=================================" << std::endl;
	}
}

int main()
{


	//map made up of key value pairs, the key here is a string
	//									and the value is a GameObject
	std::map<std::string, GameObject*> gameObjects;

	auto* ship = new GameObject("Ship", 0, 3.0f, 4.0f);
	auto* enemy = new GameObject("Enemy", 1, 10.0f, 20.0f);

	gameObjects[ship->GetName()] = ship;
	gameObjects[enemy->GetName()] = enemy;

	PrintGameObjects(gameObjects);

	const auto distance = Vector2D<float>::Distance(gameObjects["ship"]->GetPosition(), gameObjects["enemy"]->GetPosition());

	std::cout << "Distance between " << gameObjects["ship"]->GetName() << " and " << gameObjects["enemy"]->GetName() << " is: " << std::to_string(distance) << std::endl;


//begining of output
	std::ofstream outfile("GameObjects.txt", std::ios::out);
	outfile << gameObjects["ship"]->ToFile() << std::endl;
	outfile << gameObjects["enemy"]->ToFile() << std::endl;
	outfile.close();

	std::cout << "-------------------------------------------------------\n" << std::endl;
	std::cout << "	END OF OUTPUT \n" << std::endl;
	std::cout << "-------------------------------------------------------\n\n" << std::endl;

	std::cout << "-------------------------------------------------------\n" << std::endl;
	std::cout << "	STARTING INPUT \n" << std::endl;
	std::cout << "-------------------------------------------------------\n\n\n" << std::endl;
	
	std::ifstream infile;
	std::string fileName = "GameObject.txt";

	infile.open(fileName.c_str());

	if(infile.is_open())
	{
		int id;
		float x, y = 0;
		std::string name;

		while(!infile.fail())
		{
			
			infile >> id >> name;
			infile.ignore(1, ' ');
			infile.ignore(1, '(');
			infile >> x;
			infile.ignore(1, ',');
			infile.ignore(1, ' ');
			infile >> y;
			infile.ignore(1, ')');

			auto* tempObject = new GameObject(name, id, x, y);

			gameObjects[name + " 1"] = tempObject;
		}
		infile.close();
	}

	PrintGameObjects(gameObjects);

	std::cout << "-------------------------------------------------------\n" << std::endl;
	std::cout << "	END OF INPUT \n" << std::endl;
	std::cout << "-------------------------------------------------------\n\n\n" << std::endl;


}

