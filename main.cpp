#include <iostream>
#include <vector>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

class BaseGameElement;
class Map;
class Item;
class Weapon;
class Character;
class Renderer;
class Wall;
class Bullet;

enum moveEnum
{
	left,
	right,
	up,
	down
};

class BaseGameElement {
private:
	int x, y;
public:
	
	BaseGameElement() : x(0), y(0) {};
	
	void setX(int arg)
	{
		this->x = arg;
	}
	
	void setY(int arg)
	{
		this->y = arg;
	}
	
	void addX(int arg)
	{
		this->x += arg;
	}
	
	void addY(int arg)
	{
		this->y += arg;
	}
	
	int getX()
	{
		return this->x;
	}
	
	int getY()
	{
		return this->y;
	}
};

class Wall : public BaseGameElement
{
private:
	int direction, lenght;
public:
	
	bool operator!=(Wall &arg)
	{
		return getX() == arg.getX() ? getY() == arg.getY() ? direction == arg.direction ? lenght == arg.lenght ? true : false : false : false : false;
	}
	
	Wall()
	{
		setX(0);
		setY(0);
		this->direction = 1;
		this->lenght = 1;
	}
	
	Wall(int posX, int posY, int dir, int len)
	{
		setX(posX);
		setY(posY);
		this->direction = dir;
		this->lenght = len;
	}
	
	~Wall(){};
	
	int getDirection()
	{
		return this->direction;
	}
	
	void setDirection(int arg)
	{
		this->direction = arg;
	}
	
	int getLenght()
	{
		return this->lenght;
	}
	
	void setLenght(int arg)
	{
		this->lenght = arg;
	}
	
};

class Character : public BaseGameElement {
private:
	
	float hp; // character hp
	
	int score;
	
	
	bool isAlive;
	
	moveEnum moveV;
	
	moveEnum lastMove;
	
	static int ID;
	
	const int characterID;
	
	//Weapon currSelectedWeapon;
	
	//vector <Weapon> allHavedWeapons;
	
public:
	
	Character() : hp(100), score(0), isAlive(true), characterID(++ID)
	{
		setX(0);
		setY(0);
	}
	
	Character(int posX, int posY) : hp(100), score(0), isAlive(true), moveV(moveEnum::left), lastMove(moveEnum::left), characterID(++ID)
	{
		setX(posX);
		setY(posY);
	}
	
	int getHP()
	{
		return this->hp;
	}
	
	void setHP(int arg)
	{
		this->hp = arg;
	}
	
	void addHP(int arg)
	{
		this->hp += arg;
	}
	
	int getScore()
	{
		return this->score;
	}
	
	void setScore(int arg)
	{
		this->score = arg;
	}
	
	void addScore()
	{
		this->score++;
	}
	
	void setIsAlive(bool arg)
	{
		this->isAlive = arg;
	}
	
	bool getIsAlive()
	{
		return this->isAlive;
	}
	
	void setMove(moveEnum arg)
	{
		moveV = arg;
	}
	
	void setLastMove(moveEnum arg)
	{
		lastMove = arg;
	}
	
	moveEnum getMove()
	{
		return this->moveV;
	}
	
	moveEnum getLastMove()
	{
		return this->lastMove;
	}
	
	void setPlayer(int posX, int posY)
	{
		setX(posX);
		setY(posY);
	}
	
	int move() // return is character can move
	{
		lastMove = moveV;
		int ch;
		ch = getch();
		if(ch == 'd')
		{
			this->moveV = moveEnum::left;
			return 1;
		}
		else if(ch == 'a')
		{
			this->moveV = moveEnum::right;
			return 1;
		}
		else if(ch == 's')
		{
			this->moveV = moveEnum::down;
			return 1;
		}
		else if(ch == 'w')
		{
			this->moveV = moveEnum::up;
			return 1;
		}
		else if(ch == 'q')
		{
			return 0;
		}
		else if(ch == ' ')
		{
			return 2;
		}
		return 0;
	}
	
	void randomMove()
	{
		this->lastMove = moveV;
		
		int random = (rand() % 100);
		
		int lastMoveInt = static_cast<int>(this->lastMove);
		
		this->moveV = (random < 70) ? this->lastMove : (random < 80) ? static_cast<moveEnum>((lastMoveInt + 1) % 4) : (random < 90) ? static_cast<moveEnum>((lastMoveInt + 2) % 4) : (random < 100) ? static_cast<moveEnum>((lastMoveInt + 3) % 4) : this->lastMove;
		
		//this->moveV = static_cast<moveEnum>((rand() % 4));
	}
	
	int getCharacterID()
	{
		return this->characterID;
	}
};


class Item : public BaseGameElement {
private:
	int extraHP;
	int extraArmor;
	int extraAmmo;
	int rarity;
	
	bool isOnMap;
	
public:
	
	Item() : extraHP(0), extraArmor(0), extraAmmo(0), rarity(0), isOnMap(false)
	{
		setX(0);
		setY(0);
	}
	
	Item(int x, int y, int hp, int ar, int am, int rar) : extraHP(hp), extraArmor(ar), extraAmmo(am), rarity(rar), isOnMap(false)
	{
		setX(x);
		setY(y);
	}
	
	void setExtraHP(int hp)
	{
		this->extraHP = hp;
	}
	
	void setExtraArmor(int ar)
	{
		this->extraArmor = ar;
	}
	
	void setExtraAmmo(int am)
	{
		this->extraAmmo = am;
	}
	
	void setRarity(int rar)
	{
		this->rarity = rar;
	}
	
	int getExtraHP()
	{
		return this->extraHP;
	}
	
	int getExtraArmor()
	{
		return this->extraArmor;
	}
	
	int getExtraAmmo()
	{
		return this->extraAmmo;
	}
	
	int getRarity()
	{
		return this->rarity;
	}
	
	void setIsOnMap(bool arg)
	{
		this->isOnMap = arg;
	}
	
	bool getIsOnMap()
	{
		return this->isOnMap;
	}
	
};



class Map { // change to conteiners of elements, add function rendering map
private:
	
	vector<Item*> items;
	
	vector<Wall> walls;
	
	vector<Character*> players;
	
	int variable = 3;
	
	
public:
	bool canIMove(Character &c)
	{	
		if(c.getMove() == c.getLastMove())
		{
			int x = c.getX();
			int y = c.getY();
			switch(c.getMove())
			{
				case moveEnum::left:
					x++;
					break;
				case moveEnum::right:
					x--;
					break;
				case moveEnum::down:
					y++;
					break;
				case moveEnum::up:
					y--;
					break;
				default:
					break;
			}
			
			for(unsigned int i = 0; i < walls.size(); i++)
			{
				if((y == walls.at(i).getY() && x < walls.at(i).getX() + walls.at(i).getLenght()) || (x == walls.at(i).getX() && y < walls.at(i).getY() + walls.at(i).getLenght()))
				{
					c.setPlayer((rand() % walls.at(0).getLenght() - 2) + walls.at(0).getX(), (rand() % walls.at(1).getLenght() - 2) + walls.at(0).getY());
					return false;
				}
				
				if((x - 1) == walls.at(i).getX() || (x + 1) == walls.at(i).getX())
				{
					if(y < walls.at(i).getY() + walls.at(i).getLenght())
					{
						return false;
						
					}
				}
				else if( (y - 1) == walls.at(i).getY() || (y + 1) == walls.at(i).getY())
				{
					if(x < walls.at(i).getX() + walls.at(i).getLenght())
					{
						return false;
					}
				}
			}
			
			for(unsigned int i = 0; i < players.size(); i++)
			{
				if(c.getCharacterID() == players.at(i)->getCharacterID())
				{
					continue;
				}
				else
				{
					if(c.getCharacterID() == 1)
					{
						mvprintw(25, 10, "                                 ");
						mvprintw(25, 10, "Player X %d Y %d Bot X %d Y %d getMove %d", x, y, players.at(i)->getX(), players.at(i)->getY(), static_cast<int>(players.at(i)->getMove()));
					}
					switch(players.at(i)->getMove())
					{
						case moveEnum::left:
							if(y == players.at(i)->getY())
							{
								if(((x + 1) == players.at(i)->getX()) || ((x - 2) == players.at(i)->getX()))
								{
									if((c.getMove() == moveEnum::left) || (c.getMove() == moveEnum::right))
										return false;
								}
							}
							else if(((x - 1) == players.at(i)->getX() && (y - 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y - 1) == players.at(i)->getY()) || ((x - 1) == players.at(i)->getX() && (y + 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y + 1) == players.at(i)->getY()))
							{
								if(c.getMove() == moveEnum::up || c.getMove() == moveEnum::down)
									return false;
							}
							break;
							
						case moveEnum::right:
							if(y == players.at(i)->getY())
							{
								if(((x - 1) == players.at(i)->getX()) || ((x + 2) == players.at(i)->getX()))
								{
									if((c.getMove() == moveEnum::left) || (c.getMove() == moveEnum::right))
										return false;
								}
							}
							else if(((x + 1) == players.at(i)->getX() && (y - 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y - 1) == players.at(i)->getY()) || ((x + 1) == players.at(i)->getX() && (y + 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y + 1) == players.at(i)->getY()))
							{
								if(c.getMove() == moveEnum::up || c.getMove() == moveEnum::down)
									return false;
							}
							break;
						case moveEnum::down:
							if(y == players.at(i)->getY())
							{
								if(((x + 1) == players.at(i)->getX()) || ((x - 2) == players.at(i)->getX()))
								{
									if((c.getMove() == moveEnum::left) || (c.getMove() == moveEnum::right))
										return false;
								}
							}
							else if(((x + 1) == players.at(i)->getX() && (y - 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y + 1) == players.at(i)->getY()) || ((x - 2)  == players.at(i)->getX() && (y - 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y - 2) == players.at(i)->getY()))
							{
									return false;
							}
							break;
						case moveEnum::up:
							if(y == players.at(i)->getY())
							{
								if(((x + 1) == players.at(i)->getX()) || ((x - 2) == players.at(i)->getX()))
								{
									if((c.getMove() == moveEnum::left) || (c.getMove() == moveEnum::right))
										return false;
								}
							}
							else if(((x - 1) == players.at(i)->getX() && (y + 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y - 1) == players.at(i)->getY()) || ((x + 2)  == players.at(i)->getX() && (y + 1) == players.at(i)->getY()) || (x == players.at(i)->getX() && (y + 2) == players.at(i)->getY()))
							{
								return false;
							}
							break;
					}
					
					if(x == players.at(i)->getX() && y == players.at(i)->getY())
					{
						
						return false;
					}
				}
			}
		}
		else
		{
			for(unsigned int i = 0; i < players.size(); i++) // TODO repair arrow collision check
			{
				if(c.getCharacterID() == players.at(i)->getCharacterID())
				{
					continue;
				}
				else
				{
					
					int playerArrowX = players.at(i)->getX();
					int playerArrowY = players.at(i)->getY();
					
					switch(players.at(i)->getMove())
					{
						case moveEnum::left:
							playerArrowX++;
							break;
						case moveEnum::right:
							playerArrowX--;
							break;
						case moveEnum::down:
							playerArrowY++;
							break;
						case moveEnum::up:
							playerArrowY--;
							break;
						default:
							break;
					}
					
					switch(c.getMove())
					{
						case moveEnum::left:
							if(c.getX() + 1 == playerArrowX && c.getY() == playerArrowY)
								return false;
							break;
						case moveEnum::right:
							if(c.getX() - 1 == playerArrowX && c.getY() == playerArrowY)
								return false;
							break;
						case moveEnum::down:
							if(c.getX() == playerArrowX && c.getY() + 1 == playerArrowY)
								return false;
							break;
						case moveEnum::up:
							if(c.getX() == playerArrowX && c.getY() - 1 == playerArrowY)
								return false;
							break;
						default:
							break;
					}
				
					if(c.getX() + 1 == players.at(i)->getX() && c.getY() == players.at(i)->getY())
						return false;
				}
			}
		}
		
		
		return true;
	}
	
	bool didIHit(int x, int y)
	{
		::this_thread::sleep_for(::chrono::milliseconds(5));
		for(unsigned int i = 0; i < walls.size(); i++)
		{
			if((x) == walls.at(i).getX() || (x) == walls.at(i).getX())
			{
				if(y < walls.at(i).getY() + walls.at(i).getLenght())
				{
					return false;
					
				}
			}
			else if( (y) == walls.at(i).getY() || (y) == walls.at(i).getY())
			{
				if(x < walls.at(i).getX() + walls.at(i).getLenght())
				{
					return false;
				}
			}
		}
		for(unsigned int i = 0; i < players.size(); i++)
		{
			if(players.at(i)->getIsAlive() == false)
			{
				continue;
			}
			
			switch(players.at(i)->getMove())
			{
				
				case moveEnum::left:
					if(x == players.at(i)->getX() + 1 && y == players.at(i)->getY())
					{
						players.at(i)->addHP(-20);
						if(players.at(i)->getHP() <= 0)
							players.at(i)->setIsAlive(false);
						return false;
					}
					break;
				case moveEnum::right:
					if(x == players.at(i)->getX() - 1 && y == players.at(i)->getY())
					{
						players.at(i)->addHP(-20);
						if(players.at(i)->getHP() <= 0)
							players.at(i)->setIsAlive(false);
						return false;
					}
					break;
				case moveEnum::down:
					if(x == players.at(i)->getX() && y == players.at(i)->getY() + 1)
					{
						players.at(i)->addHP(-20);
						if(players.at(i)->getHP() <= 0)
							players.at(i)->setIsAlive(false);
						return false;
					}
					break;
				case moveEnum::up:
					if(x == players.at(i)->getX() && y == players.at(i)->getY() - 1)
					{
						players.at(i)->addHP(-20);
						if(players.at(i)->getHP() <= 0)
							players.at(i)->setIsAlive(false);
						return false;
					};
					break;
				default:
					break;
			}
			
			if(x == players.at(i)->getX() && y == players.at(i)->getY())
			{
				players.at(i)->addHP(-20);
				if(players.at(i)->getHP() <= 0)
					players.at(i)->setIsAlive(false);
				return false;
			}
			
			mvprintw(27, 10, "in at hit, %d %d %d %d", players.at(i)->getX(), x, players.at(i)->getY(), y);
		}
		return true;
	}
	
	bool checkItems(int x, int y, moveEnum arg, int playerID, int startPosX, int startPosY, int mapLenght, int mapHeight)
	{
		for(unsigned int i = 0; i < items.size(); i++)
		{
			switch(arg)
			{
				case moveEnum::left:
					if((x == items.at(i)->getX() + 1) && (y == items.at(i)->getY()) && items.at(i)->getIsOnMap())
					{
						for(unsigned int j = 0; j < players.size(); j ++ )
						{
							if(playerID == players.at(j)->getCharacterID())
							{
								players.at(j)->addHP(items.at(i)->getExtraHP());
							}
						}
						
						items.at(i)->setIsOnMap(false);
						items.at(i)->setX((rand() % mapLenght) + startPosX);
						items.at(i)->setY((rand() % mapHeight) + startPosY);
						
						return true;
					}
					break;
				case moveEnum::right:
					if(x == items.at(i)->getX() - 1 && y == items.at(i)->getY() && items.at(i)->getIsOnMap())
					{
						for(unsigned int j = 0; j < players.size(); j ++ )
						{
							if(playerID == players.at(j)->getCharacterID())
							{
								players.at(j)->addHP(items.at(i)->getExtraHP());
							}
						}
						
						items.at(i)->setIsOnMap(false);
						items.at(i)->setX((rand() % mapLenght) + startPosX);
						items.at(i)->setY((rand() % mapHeight) + startPosY);
						
						return true;
					}
					break;
				case moveEnum::down:
					if(x == items.at(i)->getX() && y == items.at(i)->getY() + 1 && items.at(i)->getIsOnMap())
					{
						for(unsigned int j = 0; j < players.size(); j ++ )
						{
							if(playerID == players.at(j)->getCharacterID())
							{
								players.at(j)->addHP(items.at(i)->getExtraHP());
							}
						}
						
						items.at(i)->setIsOnMap(false);
						items.at(i)->setX((rand() % mapLenght) + startPosX);
						items.at(i)->setY((rand() % mapHeight) + startPosY);
						
						return true;
					}
					break;
				case moveEnum::up:
					if(x == items.at(i)->getX() && y == items.at(i)->getY() - 1 && items.at(i)->getIsOnMap())
					{
						for(unsigned int j = 0; j < players.size(); j ++ )
						{
							if(playerID == players.at(j)->getCharacterID())
							{
								players.at(j)->addHP(items.at(i)->getExtraHP());
							}
						}
						
						items.at(i)->setIsOnMap(false);
						items.at(i)->setX((rand() % mapLenght) + startPosX);
						items.at(i)->setY((rand() % mapHeight) + startPosY);
						
						return true;
					};
					break;
				default:
					break;
			}
			
			if(x == items.at(i)->getX() && y == items.at(i)->getY() && items.at(i)->getIsOnMap())
			{
				for(unsigned int j = 0; j < players.size(); j ++ )
				{
					if(playerID == players.at(j)->getCharacterID())
					{
						players.at(j)->addHP(items.at(i)->getExtraHP());
					}
				}
				
				items.at(i)->setIsOnMap(false);
				items.at(i)->setX((rand() % mapLenght) + startPosX);
				items.at(i)->setY((rand() % mapHeight) + startPosY);
				
				return true;
			}
		}
		return false;
	}
	
	void pushCharacter(Character *arg)
	{
		players.push_back(arg);
	}
	
	int getPlayersSize()
	{
		return players.size();
	}
	
	bool getPlayerAliveAt(int arg)
	{
		return players.at(arg)->getIsAlive();
	}
	
	void setPlayerAliveAt(int arg, bool arg2)
	{
		players.at(arg)->setIsAlive(arg2);
	}
	
	int getPlayerXAt(int arg)
	{
		return players.at(arg)->getX();
	}
	
	int getPlayerYAt(int arg)
	{
		return players.at(arg)->getY();
	}
	
	void setPlayerXAt(int arg, int arg2)
	{
		players.at(arg)->setX(arg2);
	}
	
	void setPlayerYAt(int arg, int arg2)
	{
		players.at(arg)->setY(arg2);
	}
	
	void addPlayerScoreAt(int arg)
	{
		players.at(arg)->addScore();
	}
	
	int getPlayerScoreAt(int arg)
	{
		return players.at(arg)->getScore();
	}
	
	void setPlayerHPAt(int arg, int arg2)
	{
		players.at(arg)->setHP(arg2);
	}
	
	moveEnum getPlayerMoveAt(int arg)
	{
		return players.at(arg)->getMove();
	}
	
	void pushItem(Item *arg)
	{
		items.push_back(arg);
	}
	
	int getItemsSize()
	{
		return items.size();
	}
	
	int getItemXAt(int arg)
	{
		return items.at(arg)->getX();
	}
	
	int getItemYAt(int arg)
	{
		return items.at(arg)->getY();
	}
	
	int getItemRarityAt(int arg)
	{
		return items.at(arg)->getRarity();
	}
	
	bool getItemIsOnMapAt(int arg)
	{
		return items.at(arg)->getIsOnMap();
	}
	
	void setItemIsOnMapAt(int arg, bool arg2)
	{
		return items.at(arg)->setIsOnMap(arg2);
	}
	
	void pushWall(const Wall &arg)
	{
		walls.push_back(arg);
	}
	
	int getWallsSize()
	{
		return walls.size();
	}
	
	Wall getWallsAt(int arg)
	{
		return walls.at(arg);
	}
};


//class Weapon : Item
//{
	
	
//};



class Renderer : Map
{
private:
	
public:
	
	void renderUI(Map &m, Character &c)
	{
		
		int cols = 0, rows = 0;
		getmaxyx(stdscr, rows, cols);
		char tekst[]= "HP: %d Armor: %d, Weapon: %s Score: %d";
		
		move(3, 0);
		clrtoeol(); // clear line
		
		mvprintw(3, (cols / 2) - ((sizeof(tekst)) / 2), tekst, c.getHP(), 100, "rocket luncher", c.getScore());

	}
	
	void drawWalls(Wall arg)
	{
		int cols = 0, rows = 0;
		getmaxyx(stdscr, rows, cols);
		
		int startX = arg.getX();
		int startY = arg.getY();
		int len = arg.getLenght();
		int dir = arg.getDirection();
		if(dir == 1)
		{
			for(int i = 0; i < len; i ++)
			{
				mvprintw(startY, startX + i, "#");
			}
		}
		else
		{
			for(int i = 0; i < len; i ++)
			{
				mvprintw(startY + i, startX, "#");
			}
		}
	}
	
	void putCharacterOnMap(Character c)
	{
		switch(c.getMove())
		{
			case moveEnum::left:
				mvprintw(c.getY(), c.getX(), "X");
				mvprintw(c.getY(), c.getX() + 1, "");
				addch(ACS_RARROW);
				break;
			case moveEnum::right:
				mvprintw(c.getY(), c.getX(), "X");
				mvprintw(c.getY(), c.getX() - 1, "");
				addch(ACS_LARROW);
				break;
			case moveEnum::down:
				mvprintw(c.getY(), c.getX(), "X");
				mvprintw(c.getY() + 1, c.getX(), "");
				addch(ACS_DARROW);
				break;
			case moveEnum::up:
				mvprintw(c.getY(), c.getX(), "X");
				mvprintw(c.getY() - 1, c.getX(), "");
				addch(ACS_UARROW);
				break;
			default:
				break;
		}
	}
	
	void update(Character &c, Map &m, int startPosX, int startPosY, int mapLenght, int mapHeight)
	{
		if(c.getIsAlive() == false)
			return;
		
		if(c.getLastMove() != c.getMove())
		{
			switch(c.getLastMove())
			{
				case moveEnum::left:
					mvprintw(c.getY(), c.getX() + 1, " ");
					break;
				case moveEnum::right:
					mvprintw(c.getY(), c.getX() - 1, " ");
					break;
				case moveEnum::down:
					mvprintw(c.getY() + 1, c.getX(), " ");
					break;
				case moveEnum::up:
					mvprintw(c.getY() - 1, c.getX(), " ");
					break;
				default:
					break;
			}
			
			switch(c.getMove())
			{
				case moveEnum::left:
					mvprintw(c.getY(), c.getX() + 1, "");
					addch(ACS_RARROW);
					break;
				case moveEnum::right:
					mvprintw(c.getY(), c.getX() - 1, "");
					addch(ACS_LARROW);
					break;
				case moveEnum::down:
					mvprintw(c.getY() + 1, c.getX(), "");
					addch(ACS_DARROW);
					break;
				case moveEnum::up:
					mvprintw(c.getY() - 1, c.getX(), "");
					addch(ACS_UARROW);
					break;
				default:
					break;
			}
		}
		else
		{
			mvprintw(c.getY(), c.getX(), " ");
			
			switch(c.getMove())
			{
				case moveEnum::left:
					c.addX(1);
					break;
				case moveEnum::right:
					c.addX(-1);
					break;
				case moveEnum::down:
					c.addY(1);
					break;
				case moveEnum::up:
					c.addY(-1);
					break;
				default:
					break;
			}
			
			switch(c.getMove())
			{
				case moveEnum::left:
					mvprintw(c.getY(), c.getX() + 1, "");
					addch(ACS_RARROW);
					break;
				case moveEnum::right:
					mvprintw(c.getY(), c.getX() - 1, "");
					addch(ACS_LARROW);
					break;
				case moveEnum::down:
					mvprintw(c.getY() + 1, c.getX(), "");
					addch(ACS_DARROW);
					break;
				case moveEnum::up:
					mvprintw(c.getY() - 1, c.getX(), "");
					addch(ACS_UARROW);
					break;
				default:
					break;
			}
		}
		mvprintw(c.getY(), c.getX(), "X");
		
		
		if(m.checkItems(c.getX(), c.getY(), c.getMove(), c.getCharacterID(), startPosX, startPosY, mapLenght, mapHeight))
		{
			if(c.getCharacterID() == 0)
				renderUI(m, c);
		}
	}
	
	
	void drawShoot(Character &c, Map &m, int startPosX, int startPosY, int mapLenght, int mapHeight)
	{
		//Bullet b;
		int bulletPosX = 0, bulletPosY = 0;
		switch(c.getMove())
		{
			case moveEnum::left:
				bulletPosX = c.getX() + 2;
				bulletPosY = c.getY();
				break;
			case moveEnum::right:
				bulletPosX = c.getX() - 2;
				bulletPosY = c.getY();
				break;
			case moveEnum::down:
				bulletPosX = c.getX();
				bulletPosY = c.getY() + 2;
				break;
			case moveEnum::up:
				bulletPosX = c.getX();
				bulletPosY = c.getY() - 2;
				break;
			default:
				break;
		}
		//mvprintw(25, 10, "b4 while");
		
		int firedBullets = 0;
		
		while(m.didIHit(bulletPosX, bulletPosY))
		{
			mvprintw(bulletPosY, bulletPosX, "");
			addch(ACS_BULLET);
			switch(c.getMove())
			{
				case moveEnum::left:
					bulletPosX++;
					break;
				case moveEnum::right:
					bulletPosX--;
					break;
				case moveEnum::down:
					bulletPosY++;
					break;
				case moveEnum::up:
					bulletPosY--;
					break;
				default:
					break;
			}
			firedBullets ++;
			if(firedBullets > 1)
			{
				switch(c.getMove())
				{
					case moveEnum::left:
						mvprintw(bulletPosY, bulletPosX - 2, " ");
						break;
					case moveEnum::right:
						mvprintw(bulletPosY, bulletPosX + 2, " ");
						break;
					case moveEnum::down:
						mvprintw(bulletPosY - 2, bulletPosX, " ");
						break;
					case moveEnum::up:
						mvprintw(bulletPosY + 2, bulletPosX, " ");
						break;
					default:
						break;
				}
			}
			refresh();
		}
		if(firedBullets > 0)
		{
			switch(c.getMove())
			{
				case moveEnum::left:
					mvprintw(bulletPosY, bulletPosX - 1, " ");
					break;
				case moveEnum::right:
					mvprintw(bulletPosY, bulletPosX + 1, " ");
					break;
				case moveEnum::down:
					mvprintw(bulletPosY - 1, bulletPosX, " ");
					break;
				case moveEnum::up:
					mvprintw(bulletPosY + 1, bulletPosX, " ");
						break;
				default:
					break;
			}
		}
		
		for(int i = 0; i < m.getPlayersSize(); i ++)
		{
			if(m.getPlayerAliveAt(i) == false)
			{
				mvprintw(m.getPlayerYAt(i), m.getPlayerXAt(i), " ");
				switch(m.getPlayerMoveAt(i))
				{
					case moveEnum::left:
						mvprintw(m.getPlayerYAt(i), m.getPlayerXAt(i) + 1, " ");
						break;
					case moveEnum::right:
						mvprintw(m.getPlayerYAt(i), m.getPlayerXAt(i) - 1, " ");
						break;
					case moveEnum::down:
						mvprintw(m.getPlayerYAt(i) + 1, m.getPlayerXAt(i), " ");
						break;
					case moveEnum::up:
						mvprintw(m.getPlayerYAt(i) - 1, m.getPlayerXAt(i), " ");
						break;
					default:
						break;
				}
				
				c.addScore();
				
				m.setPlayerHPAt(i, 100);
				
				m.setPlayerXAt(i, (rand() % mapLenght) + startPosX);
				m.setPlayerYAt(i, (rand() % mapHeight) + startPosY);
				m.setPlayerAliveAt(i, true);
				return;
			
			}
		}
		
	}
	
	void drawItems(int x, int y)
	{
		
		mvprintw(y, x, "");
		addch(ACS_DIAMOND);
	}
};
/*
class Bullet : BaseGameElement
{
private:
	
	int bulletType;
	
public:
	
	Bullet() : bulletType(ACS_BULLET) {};
	
	void setBulletType(int arg)
	{
		this->bulletType = arg;
	}
	
	int getBulletType()
	{
		return this->bulletType;
	}
	
	
};
*/

int Character::ID = 0;


int main()
{
	srand(time(NULL));
	
	initscr();
	
	raw(); // control special characters line ctrl + c
	
	noecho(); // switch off display characters in terminal
	
	keypad(stdscr, TRUE); // allow to use special keys
	
	curs_set(0); // hide cursor
	
	Map mapVariable;
	
	int mapVerticalLenght = 60;
	int mapHorisontalLenght = 20;
	
	int cols = 0, rows = 0;
	getmaxyx(stdscr, rows, cols);
	
	int startPointX = (cols / 2) - (mapVerticalLenght / 2);
	int startPointY = 4;
	
	Wall wallVariable(startPointX, startPointY, 1, mapVerticalLenght);
	mapVariable.pushWall(wallVariable);
	
	Wall wallVariable2(startPointX, startPointY, 2, mapHorisontalLenght);
	mapVariable.pushWall(wallVariable2);
	
	Wall wallVariable3(startPointX, startPointY + mapHorisontalLenght, 1, mapVerticalLenght);
	mapVariable.pushWall(wallVariable3);
	
	Wall wallVariable4(startPointX + mapVerticalLenght, startPointY, 2, mapHorisontalLenght);
	mapVariable.pushWall(wallVariable4);
	
	startPointX += 2;
	startPointY += 2;
	mapVerticalLenght -= 2;
	mapHorisontalLenght -= 2;
	
	Renderer r;
	
	int wallsSize = mapVariable.getWallsSize();
	for(int i = 0; i < wallsSize; i++)
	{
		r.drawWalls(mapVariable.getWallsAt(i));
	}
	
	Character *chPtr;
	Character *chPtr2;
	
	Character player( cols / 2, rows / 2 );
	r.putCharacterOnMap(player);
	
	chPtr = &player;
	mapVariable.pushCharacter(chPtr);
	
	Character bot((rand() % mapVerticalLenght) + startPointX, (rand() % mapHorisontalLenght) + startPointY);
	r.putCharacterOnMap(bot);
	
	chPtr2 = &bot;
	mapVariable.pushCharacter(chPtr2);
	
	
	Item *itemPtr;
	
	
	Item hpPack((rand() % mapVerticalLenght) + startPointX, (rand() % mapHorisontalLenght) + startPointY, 20, 0, 0, 2);
	itemPtr = &hpPack;
	mapVariable.pushItem(itemPtr);
	
	r.renderUI(mapVariable, player);
	
	
	
	int loop = 1;
	while(loop)
	{
		for(int i = 0; i < mapVariable.getItemsSize(); i++)
		{
			int itemRandom = rand() % 100;
			if((itemRandom < mapVariable.getItemRarityAt(i)) && !mapVariable.getItemIsOnMapAt(i))
			{
				r.drawItems(mapVariable.getItemXAt(i), mapVariable.getItemYAt(i));
				mapVariable.setItemIsOnMapAt(i, true);
			}
		}
		int shootRandom = 0;
		switch(player.move())
		{
			case 1: 
				if(mapVariable.canIMove(player))
				{
					r.update(player, mapVariable, startPointX, startPointY, mapVerticalLenght, mapHorisontalLenght);
					bot.randomMove();
					while(!mapVariable.canIMove(bot))
						bot.randomMove();
					r.update(bot, mapVariable, startPointX, startPointY, mapVerticalLenght, mapHorisontalLenght);
					shootRandom = rand() % 100;
					if(shootRandom < 20)
						r.drawShoot(bot, mapVariable, startPointX, startPointY, mapVerticalLenght, mapHorisontalLenght);
					r.renderUI(mapVariable, player);
				}
				break;
			case 2:
				r.drawShoot(player, mapVariable, startPointX, startPointY, mapVerticalLenght, mapHorisontalLenght);
				bot.randomMove();
				while(!mapVariable.canIMove(bot))
					bot.randomMove();
				r.update(bot, mapVariable, startPointX, startPointY, mapVerticalLenght, mapHorisontalLenght);
				shootRandom = rand() % 100;
				if(shootRandom < 20)
					r.drawShoot(bot, mapVariable, startPointX, startPointY, mapVerticalLenght, mapHorisontalLenght);
				r.renderUI(mapVariable, player);
				break;
			case 0:
				loop = 0;
				break;
		}
	}
	
	getch();
	endwin();
	
	return 0;
}