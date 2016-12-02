#pragma once

class Map;
class Character;

class Strategy
{
public:
	virtual void execute(Character* actor, Map* context) = 0;
};

class DefaultStrategy : public Strategy
{
public:
	void execute(Character* actor, Map* context);
};

class FriendlyStrategy : public Strategy
{
public:
	void execute(Character* actor, Map* context);
};

class HostileStrategy : public Strategy
{
public:
	void execute(Character* actor, Map* context);
};