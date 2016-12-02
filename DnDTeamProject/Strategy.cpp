#include "Strategy.h"

#include "Map.h"
#include "Character.h"

#include <fstream>

//! do nothing
void DefaultStrategy::execute(Character* actor, Map* context)
{
	
}

//! move towards Player
void FriendlyStrategy::execute(Character* actor, Map* context)
{
	// get current cell
	Map::Cell* current = context->getCell(actor->getX(), actor->getY());
	// get player
	Character* player = context->getPlayerCharacter();
	// get player's cell
	Map::Cell* target = context->getCell(player->getX(), player->getY());
	
	
	
	// next cell to move to
	Map::Cell* nextCell = context->nextMove(current, target);

	//debugging
	
	
	
	if (nextCell->sameCell(current))
	{
		//no path, do nothing
		return;
	}
	
	if (context->isCellOccupied(nextCell->getX(), nextCell->getY()))
	{
		// cell is occupied
	}
	else
	{
		// cell is free
		
		if (current->getX() != nextCell->getX())
			actor->setX(nextCell->getX());

		if (current->getY() != nextCell->getY())
			actor->setY(nextCell->getY());
	}
	
}

void HostileStrategy::execute(Character* actor, Map* context)
{
	// get current cell
	Map::Cell* current = context->getCell(actor->getX(), actor->getY());
	// get player
	Character* player = context->getPlayerCharacter();
	// get player's cell
	Map::Cell* target = context->getCell(player->getX(), player->getY());



	// next cell to move to
	Map::Cell* nextCell = context->nextMove(current, target);

	//debugging



	if (nextCell->sameCell(current))
	{
		//no path, do nothing
		return;
	}

	if (context->isCellOccupied(nextCell->getX(), nextCell->getY()))
	{
		// cell is occupied
		if (nextCell->sameCell(target))
		{
			actor->attack(context->getPlayerCharacter(), context);
		}
	}
	else
	{
		// cell is free

		if (current->getX() != nextCell->getX())
			actor->setX(nextCell->getX());

		if (current->getY() != nextCell->getY())
			actor->setY(nextCell->getY());
	}
}