#pragma once

#include "stdafx.h"
#include <cmath>
double getRadian(int in);
void MoveObjectRef(WPARAM& wParam, long& Pos, int accel);

void Drawline(HDC hdc, double startX, double startY, double angle, double lenght);
//hdc, 100, 100, 500, 500, 50
void DrawGrid(HDC hdc, int startX, int startY, int endX, int endY, int term)
{
	//가로 출력

	for (int i = startY; i <= endY; i += term)
	{
		MoveToEx(hdc, startX, i, NULL);
		LineTo(hdc, endX, i);
	}

	for (int i = startX; i <= endX; i += term)
	{
		MoveToEx(hdc, i, startY, NULL);
		LineTo(hdc, i, endY);
	}
}

void Drawline(HDC hdc, double startX, double startY, double angle, double lenght)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, startX + (lenght * cos(getRadian(angle))), startY - (lenght * sin(getRadian(angle))));
}

void DrawSnail(HDC hdc, int startX, int startY, int size, int term)
{
	startX -= term;
	int len = size + term;
	
	while (len > term)
	{
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, startX + len, startY);
		len -= 2 * term;
		startX += term;
		startY += term;
	}
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, startX + len, startY);
	startY += term;
	len += term;
	//startX -= term;
	
	

	while (len <= size)
	{
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, startX + len, startY);
		len += 2 * term;
		startX -= term;
		startY += term;
	}
}

void DrawCircle(HDC hdc, double centerX, double centerY, double r)
{
	Ellipse(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
}

void DrawSquare(HDC hdc, double centerX, double centerY, double r)
{
	Rectangle(hdc, centerX - r, centerY - r, centerX + r, centerY + r );
}

void DrawRoSquare(HDC hdc, double centerX, double centerY, double r, double& SinAngle, double& CosAngle)
{
	POINT pt[4] = { 
		{ centerX - (r * SinAngle), centerY - (r*CosAngle) },
		{ centerX + (r * CosAngle), centerY - (r*SinAngle) },
		{ centerX + (r * SinAngle), centerY + (r*CosAngle) },
		{ centerX - (r * CosAngle), centerY + (r*SinAngle) }
	};
	Polygon(hdc,pt, 4);
}

double getRadian(int in)
{
	return (3.1415926535 / 180 * in);
}

void DrawSunflower(HDC hdc, double centerPosX, double centerPosY, double centerR, int numOfSmallCircle)
{
	int halfOfRotation = 180 / numOfSmallCircle;
	double smallR = (sin(getRadian(halfOfRotation)) * centerR) / (1 - sin(getRadian(halfOfRotation)));
	double bigR = smallR + centerR;
	double leafPosX, leafPosY;
	Ellipse(hdc, centerPosX - centerR, centerPosY - centerR, centerPosX + centerR, centerPosY + centerR);

	for (int delta = 0; delta < 360; delta += (2 * halfOfRotation))
	{
		leafPosX = centerPosX + bigR * cos(getRadian(delta));
		leafPosY = centerPosY + bigR * sin(getRadian(delta));
		DrawCircle(hdc, leafPosX, leafPosY, smallR);
	}
}

void DrawSunflowerFractal(HDC hdc, double centerPosX, double centerPosY, double centerR, int numOfSmallCircle)
{
	if (centerR < 4)
		return;
	int halfOfRotation = 180 / numOfSmallCircle;
	double smallR = (sin(getRadian(halfOfRotation)) * centerR) / (1 - sin(getRadian(halfOfRotation)));
	double bigR = smallR + centerR;
	double leafPosX, leafPosY;
	Ellipse(hdc, centerPosX - centerR, centerPosY - centerR, centerPosX + centerR, centerPosY + centerR);

	for (int delta = 0; delta < 360; delta += (2 * halfOfRotation))
	{
		leafPosX = centerPosX + bigR * cos(getRadian(delta));
		leafPosY = centerPosY + bigR * sin(getRadian(delta));
		DrawCircle(hdc, leafPosX, leafPosY, smallR);
		DrawSunflowerFractal(hdc, leafPosX, leafPosY, smallR, numOfSmallCircle);
	}
}

void DrawStar(HDC hdc, double x ,double y,double r)
{
	POINT pt[10];
	POINT test[5];
	double angle = 360*0.2;
	/*
	for (int i = 0; i < 5; i++)
		test[i] = { (int)(x + (r*sin(getRadian(72 * i)))), (int)(y - (r*cos(getRadian(72 * i)))) };
	*/
	for (int i = 0; i < 5; i++) {
		pt[2 * i] = { (int)(x + (r*sin(getRadian(angle * i)))), (int)(y - (r*cos(getRadian(angle * i)))) };
	}
	int i = 0;
	double a, b, c, d, e, f;
	a = pt[0].y - pt[4].y;
	b = pt[4].x - pt[0].x;
	c = pt[2].y - pt[8].y;
	d =  pt[8].x - pt[2].x;
	e = a * pt[0].x - ((-1)*b) * pt[0].y;
	f = c * pt[2].x - ((-1)*d) * pt[2].y;
	double smallR = pow((pow(x - ((e*d - b*f) / (a*d - b*c)), 2) + pow(y - ((a*f - e*c) / (a*d - b*c)), 2)), 0.5);

	for (int i = 0; i < 5; i++) 
	{
		pt[(2 * i)+1] = { (int)(x + (smallR*sin(getRadian((angle * i)+ (angle*0.5))))), 
			(int)(y - (smallR*cos(getRadian((angle * i) + (angle*0.5))))) };
	}
	
	//Polygon(hdc, test, 5);
	Polygon(hdc, pt, 10);
}

void DrawRoStar(HDC hdc, double x, double y, double r, double rotate)
{
	POINT pt[10];
	POINT test[5];
	double angle = 72;
	/*
	for (int i = 0; i < 5; i++)
	test[i] = { (int)(x + (r*sin(getRadian(72 * i)))), (int)(y - (r*cos(getRadian(72 * i)))) };
	*/
	for (int i = 0; i < 5; i++) {
		pt[2 * i] = { (int)(x + (r*sin(getRadian(angle * i) + rotate))), (int)(y - (r*cos(getRadian(angle * i) + rotate))) };
	}
	int i = 0;
	double a, b, c, d, e, f;
	a = pt[0].y - pt[4].y;
	b = pt[4].x - pt[0].x;
	c = pt[2].y - pt[8].y;
	d = pt[8].x - pt[2].x;
	e = a * pt[0].x - ((-1)*b) * pt[0].y;
	f = c * pt[2].x - ((-1)*d) * pt[2].y;
	double smallR = pow((pow(x - ((e*d - b*f) / (a*d - b*c)), 2) + pow(y - ((a*f - e*c) / (a*d - b*c)), 2)), 0.5);

	for (int i = 0; i < 5; i++)
	{
		pt[(2 * i) + 1] = { (int)(x + (smallR*sin(getRadian((angle * i) + (angle*0.5)) + rotate))),
			(int)(y - (smallR*cos(getRadian((angle * i) + (angle*0.5)) + rotate))) };
	}

	//Polygon(hdc, test, 5);
	Polygon(hdc, pt, 10);
}


void MoveObjectByKeyboard(WPARAM wParam, POINT& centerPos, int accel)
{
	switch (wParam)
	{
	case VK_LEFT: //centerPos.x -= accel;
		MoveObjectRef(wParam, centerPos.x,  -accel);
		break;
	case VK_UP: centerPos.y -= accel;
		break;
	case VK_RIGHT: centerPos.x += accel;
		break;
	case VK_DOWN: centerPos.y += accel;
		break;
	}
}

void MoveObjectRef(WPARAM& wParam, long& Pos, int accel)
{
	Pos += accel;
}

void MoveObjectToPoint(int& x , int& y, POINT& pos, int accel)
{
	int disX = x - pos.x;
	int disY = y - pos.y;

	if (abs(disX) > accel && abs(disY) > accel)
	{
		pos.x += ((disX / abs(disX)) * accel);
		pos.y += ((disY / abs(disY)) * accel);
	}
	else if (abs(disX) > accel)
	{
		pos.x += ((disX / abs(disX)) * accel);
	}
	else if (abs(disY) > accel)
	{
		pos.y += ((disY / abs(disY)) * accel);
	}
}