#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;
using namespace sf;

int board[8][8] =
{ -1, -2, -3, -4, -5, -3, -2, -1,
-6, -6, -6, -6, -6, -6, -6, -6,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
6, 6, 6, 6, 6, 6, 6, 6,
1, 2, 3, 4, 5, 3, 2, 1 };

class figura
{
protected:
	int a;
public:
	Sprite figure;
	void seta(int b)
	{
		a = b;
	}
	int geta()
	{
		return a;
	}
};

int max1(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int min1(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int chesspoint(int a, int b)
{
	if (a < 0) {
		return -100; cout << "dfdf" << endl;
	}
	int p[64];
	for (int i = 1; i <= 64; i++)
		p[i - 1] = i;
	int t = 0;
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
		{
			if (a >= 56 * i && a < 56 * (i + 1) && b >= 56 * j && b < 56 * (j + 1))
				return p[t];
			t++;
		}
}

int osi(int a)
{
	int d = 1;
	while ((a - 8) > 0)
	{
		d++;
		a -= 8;
	}
	return d;
}

figura f[32];

class rock
{
public:
	int pos[4] = { 1, 8, 57, 64 };
	void newpos1(int b, int c)
	{
		for (int i = 0; i < 4; i++)
			if (pos[i] == b)
			{
				pos[i] = c;
				break;
			}
	}
	int move(int a, int b)
	{
		int* sp = new int[2];
		sp[0] = 8 - (osi(a)*8 - a); // Начальный x
		sp[1] = osi(a); // начальный y
		int* fp = new int[2];
		fp[0] = 8 - (osi(b) * 8 - b); //конечный x
		fp[1] = osi(b); // конечный y
		if (((sp[0] != fp[0]) && sp[1] == fp[1]) || (sp[1] != fp[1]) && sp[0] == fp[0])
			return 1;
		else
			return 0;
	}
};

class horse
{
public:
	int pos[4] = { 2, 7, 63, 58 };
	void newpos1(int b, int c)
	{
		for (int i = 0; i < 4; i++)
			if (pos[i] == b)
			{
				pos[i] = c;
				break;
			}
	}
	int move(int a, int b)
	{
		int* sp = new int[2];
		sp[0] = 8 - (osi(a) * 8 - a);
		sp[1] = osi(a);
		int* fp = new int[2];
		fp[0] = 8 - (osi(b) * 8 - b);
		fp[1] = osi(b);
		if ((abs(sp[1] - fp[1]) == 2 && abs(sp[0] - fp[0]) == 1) || abs(sp[1] - fp[1]) == 1 && abs(sp[0] - fp[0]) == 2)
			return 1;
		else
			return 0;
	}
};

class elephant
{
public:
	int pos[4] = { 3, 6, 62, 59 };
	void newpos1(int b, int c)
	{
		for (int i = 0; i < 4; i++)
			if (pos[i] == b)
			{
				pos[i] = c;
				break;
			}
	}
	int move(int a, int b)
	{
		int* sp = new int[2];
		sp[0] = 8 - (osi(a) * 8 - a);
		sp[1] = osi(a);
		int* fp = new int[2];
		fp[0] = 8 - (osi(b) * 8 - b);
		fp[1] = osi(b);
		if (abs(sp[0] - fp[0]) == abs(sp[1] - fp[1]))
			return 1;
		else
			return 0;
	}
};

class queen
{
public:
	int pos[2] = { 4, 60 };
	void newpos1(int b, int c)
	{
		for (int i = 0; i < 2; i++)
			if (pos[i] == b)
			{
				pos[i] = c;
				break;
			}
	}
};

class king
{
public:
	int pos[2] = { 5, 61 };
	void newpos1(int b, int c)
	{
		for (int i = 0; i < 2; i++)
			if (pos[i] == b)
			{
				pos[i] = c;
				break;
			}
	}
	int move(int a, int b)
	{
		int* sp = new int[2];
		sp[0] = 8 - (osi(a) * 8 - a);
		sp[1] = osi(a);
		int* fp = new int[2];
		fp[0] = 8 - (osi(b) * 8 - b);
		fp[1] = osi(b);
		if (abs(sp[1] - fp[1]) == 0 && abs(sp[0] - fp[0]) == 0)
			return 1;
		if (abs(sp[1] - fp[1]) == 0 && abs(sp[0] - fp[0]) == 1)
			return 1;
		else
			if (abs(sp[1] - fp[1]) == 1 && abs(sp[0] - fp[0]) == 0)
				return 1;
			else
				if (abs(sp[1] - fp[1]) == 1 && abs(sp[0] - fp[0]) == 1)
					return 1;
				else
					return 0;
	}
	int gameover()
	{
		if (pos[0] < 0) {
			cout << "White won!" << endl; return 1;
		}
		if (pos[1] < 0) {
			cout << "Black won!" << endl; return 1;
		}
	}
};

class pawn
{
public:
	int pos[16] = { 9, 10, 11, 12, 13, 14, 15, 16, 56, 55, 54, 53, 52, 51, 50, 49 };
	int moving[16] = { 9, 10, 11, 12, 13, 14, 15, 16, 56, 55, 54, 53, 52, 51, 50, 49 };
	void newpos1(int b, int c)
	{
		for (int i = 0; i < 16; i++)
			if (pos[i] == b)
			{
				pos[i] = c;
				break;
			}
	}
	int move(int a, int b, rock c, horse c1, elephant c2, queen c3, king c4)
	{
		int* sp = new int[2];
		sp[0] = 8 - (osi(a) * 8 - a); // x
		sp[1] = osi(a); // y
		int* fp = new int[2];
		fp[0] = 8 - (osi(b) * 8 - b); // x
		fp[1] = osi(b); // y
		bool first = true;
		bool eat = false;
		bool anothereat = true;
		int allpos[32];
		for (int i = 0; i < 4; i++)
			allpos[i] = c.pos[i];
		for (int i = 0; i < 4; i++)
			allpos[i + 4] = c1.pos[i];
		for (int i = 0; i < 4; i++)
			allpos[i + 8] = c2.pos[i];
		for (int i = 0; i < 2; i++)
			allpos[i + 12] = c3.pos[i];
		for (int i = 0; i < 2; i++)
			allpos[i + 14] = c4.pos[i];
		for (int i = 0; i < 16; i++)
			allpos[i + 16] = pos[i];
		for (int i = 0; i < 16; i++)
			if (a == pos[i])
				if (i < 8) {
					if (a > b)
						return 0;
					else
						break;
				}
				else
					if (a < b)
						return 0;
					else
						break;
		for (int i = 0; i < 32; i++)
			if (abs(allpos[i] - a) == 7 || abs(allpos[i] - a) == 9) {
				for (int j = 0; j<32; j++)
				if (b == allpos[j] && (abs(b-a) == 7 || abs(b-a) == 9))
					return 1;
			}
		for (int i = 0; i < 16; i++)
			if (a == moving[i])
			{
				eat = true;
				break;
			}
		int e = 0;
		int i1 = 0;
		while (i1 + 1 + min1(sp[0], fp[0]) < max1(sp[0], fp[0])) {
			e = 8 * (min1(sp[0], fp[0]) + i1) + sp[1]; i1++;
		}
		for (int i = 0; i < 32; i++)
			if (e == allpos[i] || b == allpos[i])
				return 0;
		if (eat)
			{
				if ((fp[0] == sp[0] && abs(fp[1] - sp[1]) == 1 || abs(fp[1] - sp[1]) == 2))
					return 1;
			}
			else
			if (fp[0] == sp[0] && abs(fp[1] - sp[1]) == 1)
				return 1;
			else 
				return 0;
	}
};

int check(int a, rock c, pawn c1, horse c2, elephant c3, queen c4, king c5)
{
	for (int i = 0; i < 4; i++)
		if (a == c.pos[i])
			return 1;
	for (int i = 0; i < 16; i++)
		if (a == c1.pos[i])
			return 2;
	for (int i = 0; i < 4; i++)
		if (a == c2.pos[i])
			return 3;
	for (int i = 0; i < 4; i++)
		if (a == c3.pos[i])
			return 4;
	for (int i = 0; i < 2; i++)
		if (a == c4.pos[i])
			return 5;
	for (int i = 0; i < 2; i++)
		if (a == c5.pos[i])
			return 6;
}

int check2(Vector2f a1, Vector2f b1, rock c, pawn c1, horse c2, elephant c3, queen c4, king c5)
{
	bool checkbool = true;
	int a = chesspoint(a1.x, a1.y);
	int b = chesspoint(b1.x, b1.y);
	int a21 = osi(a); // y
	int a22 = 8 - (osi(a) * 8 - a); // x
	int b21 = osi(b); // y
	int b22 = 8 - (osi(b) * 8 - b); // x
	int nowpos[6];
	nowpos[0] = -1;
	int posfig[32];
	int i1 = 0;
	int t = 0;
	for (int i = 0; i < 16; i++)
		posfig[i] = c1.pos[i];
	for (int i = 0; i < 4; i++)
		posfig[i + 16] = c.pos[i];
	for (int i = 0; i < 4; i++)
		posfig[i + 20] = c2.pos[i];
	for (int i = 0; i < 4; i++)
		posfig[i + 24] = c3.pos[i];
	for (int i = 0; i < 2; i++)
		posfig[i + 28] = c4.pos[i];
	for (int i = 0; i < 2; i++)
		posfig[i + 30] = c5.pos[i];
	bool damka = false;
	if (check(a, c, c1, c2, c3, c4, c5) == 5)
		if (c.move(a, b) == 1)
			damka = true;
	if (check(a, c, c1, c2, c3, c4, c5) == 1 || damka) {
		if ((a21 == b21) && (b22 == a22))
			return 1;
		if (a22 == b22)
			while (i1 + 1 + min1(a21, b21) < max1(a21, b21)) {
				nowpos[i1] = 8 * (min1(a21, b21) + i1) + a22; t++; i1++;
			}
		else
			if (a21 == b21)
				while ((min1(a22, b22) + i1 + 1) < max1(a22, b22)) {
					nowpos[i1] = 8 * (a21 - 1) + min1(a22, b22) + i1 + 1; t++; i1++;
				}
		if (nowpos[0] == 0)
			return 1;
		for (int i = 0; i < t; i++)
			for (int j = 0; j < 32; j++)
				if (nowpos[i] == posfig[j]) {
					checkbool = false; break;
				}
			if (checkbool)
				return 1;
			else
				return 0;
	}
	int i2 = 0; // клеточек между слонами
	int t2 = 0;
	bool eleph = true;
	if (check(a, c, c1, c2, c3, c4, c5) == 4 || damka == false)
	{
		if (abs(a21 - b21) == 1)
			return 1;
		while (min1(a21, b21) + i1 + 1 <= max1(a21, b21))
		{
			i2++; i1++;
		}
		i1 = 0;
		while (min1(a21, b21) + i1 + 1 < max1(a21, b21))
		{
			nowpos[i1] = min1(a, b) + abs(b - a) / i2 * (i1 + 1); i1++; t2++;
		}
		for (int i = 0; i < t2; i++)
			for (int j = 0; j < 32; j++)
				if (nowpos[i] == posfig[j])
				{
					eleph = false;
					break;
				}
		if (eleph)
			return 1;
		else
			return 0;
	}
}

void position()
{
	int a = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int b = board[i][j];
			if (b != 0)
				if (b < 0)
				{
					int x = abs(b) - 1;
					f[a].figure.setTextureRect(IntRect(56 * x, 0, 56, 56));
					f[a].figure.setPosition(j * 56, i * 56);
					a++;
					f[a].seta(0);//черный
				}
				else
				{
					int x = b - 1;
					f[a].figure.setTextureRect(IntRect(56 * x, 56, 56, 56));
					f[a].figure.setPosition(j * 56, i * 56);
					a++;
					f[a].seta(1);//белый
				}
		}
}

int main()
{
	RenderWindow window(sf::VideoMode(454, 455), "Chess");

	Texture d1;
	d1.loadFromFile("images/figures.png");

	Texture texture;
	texture.loadFromFile("images/board0.png");
	Sprite dress(texture);
	bool moving = false; // переменная для движения
	float dx = 0; // две переменные для движение фигур с помощью зажатия мыши
	float dy = 0;
	int n = 0; // переменная, отвечающая за выделенную фигуру
	int moveab; // переменная для проверки правильности хода
	bool eat; // переменная, отвечающая за возможность есть
	bool point = false; // переменная для проверки хода фигуры на одном месте
	int aga = 0; // переменная для проверки фантомного нажатия по доске
	bool color, anothercheck; // переменные для поочередных ходов (белый - черный)
	int checkcolor = 1; // еще одна переменная для поочередных ходов

	for (int i = 0; i < 32; i++)
		f[i].figure.setTexture(d1);
	position();

	rock rock;
	pawn pawn;
	horse horse;
	elephant elephant;
	queen queen;
	king king;

	Vector2f prevpos, newpos;
	int figuretype;

	while (window.isOpen())
	{
		Vector2i pixelpos = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					for (int i = 0; i < 32; i++)
						if (f[i].figure.getGlobalBounds().contains(pixelpos.x, pixelpos.y))
						{
							eat = true;
							dx = pixelpos.x - f[i].figure.getPosition().x;
							dy = pixelpos.y - f[i].figure.getPosition().y;
							moving = true;
							n = i;
							prevpos = f[i].figure.getPosition();
						}
						else {
							aga++;
							if (aga == 32) // Если не попали ни в одну из фигур
								point = true;
						}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					moving = false;
					Vector2f a = f[n].figure.getPosition() + Vector2f(56 / 2, 56 / 2);
					Vector2f newPos = Vector2f(56 * int(a.x / 56), 56 * int(a.y / 56));
					f[n].figure.setPosition(newPos);
					newpos = f[n].figure.getPosition();
					figura bag = f[n];
					moveab = 0;
					if (checkcolor % 2 != 0 && f[n].geta() == 1) {
						color = true; anothercheck = true;
					}
					else
						if (checkcolor % 2 == 0 && f[n].geta() == 0) {
							color = true; anothercheck = true;
						}
						else {
							color = false; anothercheck = false;
						}
					if (color) {
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 1)
							moveab = rock.move(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (moveab == 1)
							if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 1)
								moveab = check2(prevpos, newpos, rock, pawn, horse, elephant, queen, king);
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 3)
							moveab = horse.move(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 2)
							moveab = pawn.move(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y), rock, horse, elephant, queen, king);
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 4)
							moveab = elephant.move(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (moveab == 1)
							if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 4)
								moveab = check2(prevpos, newpos, rock, pawn, horse, elephant, queen, king);
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 5)
							if (rock.move(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y)) == 1 || elephant.move(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y)) == 1)
								moveab = 1;
						if (moveab == 1)
							if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 5)
								moveab = check2(prevpos, newpos, rock, pawn, horse, elephant, queen, king);
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 6)
							moveab = king.move(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
					}
					if (moveab == 0)
					{
						if (point);
						else {
							f[n].figure.setPosition(prevpos);
							eat = false;
						}
					}
					for (int j = 0; j < 32; j++)
						if (f[n].figure.getPosition() == f[j].figure.getPosition() && n != j)
							if ((f[n].geta() != f[j].geta()) && eat)
							{
								Vector2f eaten = f[j].figure.getPosition();
								if (check(chesspoint(eaten.x, eaten.y), rock, pawn, horse, elephant, queen, king) == 1)
									rock.newpos1(chesspoint(eaten.x, eaten.y), -100);
								if (check(chesspoint(eaten.x, eaten.y), rock, pawn, horse, elephant, queen, king) == 2)
									pawn.newpos1(chesspoint(eaten.x, eaten.y), -100);
								if (check(chesspoint(eaten.x, eaten.y), rock, pawn, horse, elephant, queen, king) == 3)
									horse.newpos1(chesspoint(eaten.x, eaten.y), -100);
								if (check(chesspoint(eaten.x, eaten.y), rock, pawn, horse, elephant, queen, king) == 4)
									elephant.newpos1(chesspoint(eaten.x, eaten.y), -100);
								if (check(chesspoint(eaten.x, eaten.y), rock, pawn, horse, elephant, queen, king) == 5)
									queen.newpos1(chesspoint(eaten.x, eaten.y), -100);
								if (check(chesspoint(eaten.x, eaten.y), rock, pawn, horse, elephant, queen, king) == 6)
									king.newpos1(chesspoint(eaten.x, eaten.y), -100);
								f[j].figure.setPosition(-100, -100);
							}
							else
							{
								f[n].figure.setPosition(prevpos);
								cout << "Don't eat your figures" << endl;
							}
					if (moveab == 1) {
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 1)
							rock.newpos1(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 2)
							pawn.newpos1(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 3)
							horse.newpos1(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 4)
							elephant.newpos1(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 5)
							queen.newpos1(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
						if (check(chesspoint(prevpos.x, prevpos.y), rock, pawn, horse, elephant, queen, king) == 6)
							king.newpos1(chesspoint(prevpos.x, prevpos.y), chesspoint(newpos.x, newpos.y));
					}
					if (point == false && anothercheck && prevpos != newpos && moveab == 1)
						checkcolor++;
					point = false;
					aga = 0;
				}
			f[n].figure.setColor(Color::White);
		}
		if (moving)
		{
			f[n].figure.setPosition(pixelpos.x - dx, pixelpos.y - dy);
			f[n].figure.setColor(Color::Green);
		}
		if (king.gameover() == 1)
			return 0;
		window.clear();
		window.draw(dress);
		for (int i = 0; i < 32; i++)
			window.draw(f[i].figure);
		window.display();
	}
	return 0;
}