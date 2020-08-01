#pragma once
#include <Windows.h>
#include <random>
#include <ctime>

static const double PI = 3.141592;
static const float SizeMultiple = 1.3;

// 부모클래스
/*
좌표 = 중심x,y
크기 = R값 (별일경우 뾰족한 부분 / 사각형일 경우 중심으로부터 큰 길이

타입 (원 / 사각형 / 별 )
벡터값 x,y

Update() - 현재 상태를 계속해서 확인하는 함수

콜리전

타이머가 돌때마다

좌표 + 벡터값

회전각 ++ (사각형, 별만)

Collison() - 충돌 판정 함수

벽과의 충돌이 최우선 

다른 오브젝트간 충돌





벽과의 충돌
판정 : 
변화 : x y 뒤집기


Show() - 자기 자신을 그려주는 함수


// 화면밖으로 나가면 소멸
// 커지면 소멸 등등
// 소멸하는 메소드를 하나 만들어서 불러오기


// 겹치게 생성되는 경우

*/

class cShape
{
	protected:
		POINT Center;
		double Vector = 3;
		double Angle, RotateAngel, SinRo, CosRo;
		int R = 40;
		int type = -1;
		bool ObjectCollided = false;
		bool WallCollided = false;

	public:
		cShape(LPARAM& lParam) // 클릭에 의한 생성자
		{
			Center.x = LOWORD(lParam);
			Center.y = HIWORD(lParam);
			Angle = 2 * PI * (rand()%10) * 0.1 ;
			RotateAngel = 0;
		}

		cShape(POINT NewCenter, double NewAngle, int NewR) // 분열에 의한 생성자
		{
			Angle = NewAngle + PI;
			RotateAngel = 0;
			R = NewR;
			Center.x = NewCenter.x + (int)(2*R*sin(Angle));
			Center.y = NewCenter.y + (int)(2*R*cos(Angle));
		}

		bool OutOfWindow(const RECT& rc)
		{
			if ((this->Center.x > rc.right) || (this->Center.x < rc.left) ||
				(this->Center.y < rc.top) || (this->Center.y > rc.bottom))
				return true;
			else
				return false;
		}

		int GetAngle() {
			return this->Angle;
		}

		int GetType() {
			return this->type;
		}

		POINT GetCenter() {
			return this->Center;
		}

		void setType(int i) {
			type = i;
		}
			
		int getR() {
			return this->R;
		}

		int Update()
		{
			Center.x += (int)(Vector*sin(Angle));
			Center.y += (int)(Vector*cos(Angle));
			RotateAngel += PI * 0.01;
			if (RotateAngel > 2 * PI)
				RotateAngel -= 2 + PI;
			SinRo = sin(RotateAngel);
			CosRo = cos(RotateAngel);
			return 0;
		}

		bool CollisonToMause(POINT& pt)
		{
			if ((pow(pow((this->Center.x - pt.x), 2) + pow((this->Center.y - pt.y), 2), 0.5)) <= (2 * this->R)) 
				return true;
			return false;
		}

		void CollisonToWall(const RECT& rc)
		{
			if (Center.x - R < 0 || Center.x + R > rc.right)
			{
				if (WallCollided)
					return;
				Angle = 2 * PI - Angle;
				Center.x += (int)(Vector*sin(Angle));

				Center.x += (int)(Vector*sin(Angle));
				Center.y += (int)(Vector*cos(Angle));
				WallCollided = true;
				return;
			}
			if (Center.y - R < 0 || Center.y + R > rc.bottom)
			{
				if (WallCollided)
					return;
				Angle = PI - Angle;
				Center.y += (int)(Vector*cos(Angle));

				Center.x += (int)(Vector*sin(Angle));
				Center.y += (int)(Vector*cos(Angle));
				WallCollided = true;
				return;
			}
			WallCollided = false;
		}

		void CollisonMode1(const std::vector<cShape*>& _mObject)
		{
			
			for (int i = 0; i < _mObject.size(); i++)
			{
				if ((_mObject[i] == this))
					break;
				else if ((pow(pow((this->Center.x - _mObject[i]->Center.x), 2) + pow((this->Center.y - _mObject[i]->Center.y), 2), 0.5))
					< (_mObject[i]->R + this->R))
					{

						if (ObjectCollided)
							return;

						double tempV, tempA;
						tempV = _mObject[i]->Vector;
						_mObject[i]->Vector = this->Vector;
						this->Vector = tempV;

						tempA = _mObject[i]->Angle;
						_mObject[i]->Angle = this->Angle;
						this->Angle = tempA;
					
						Center.x += (int)(Vector*sin(Angle));
						Center.y += (int)(Vector*cos(Angle));

						ObjectCollided = true;
						return;
					}
					ObjectCollided = false;
			}

			if (Angle > 2 * PI)
				Angle -= 2 * PI;
			if (Angle < 0)
				Angle += 2 * PI;
		}

		int CollisonMode2(const std::vector<cShape*>& _mObject)
		{
			for (int i = 0; i < _mObject.size(); i++)
			{
				if ((_mObject[i] == this))
					break;
				else if ((pow(pow((this->Center.x - _mObject[i]->Center.x), 2) + pow((this->Center.y - _mObject[i]->Center.y), 2), 0.5))
					< (_mObject[i]->R + this->R)) 
				{
					if (ObjectCollided)
						return -1;

					double tempV, tempA;
					tempV = _mObject[i]->Vector;
					_mObject[i]->Vector = this->Vector;
					this->Vector = tempV;

					tempA = _mObject[i]->Angle;
					_mObject[i]->Angle = this->Angle;
					this->Angle = tempA;

					Center.x += (int)(Vector*sin(Angle));
					Center.y += (int)(Vector*cos(Angle));

					if (
						((this->type == 0) && (_mObject[i]->type == 2)) || 
						((this->type == 1) && (_mObject[i]->type == 0)) ||
						((this->type == 2) && (_mObject[i]->type == 1))
						)
					{
						this->R *= SizeMultiple;

						ObjectCollided = true;
						return i;
					}
					else if (this->type == _mObject[i]->type)
						return -1;
					else
					{
						_mObject[i]->R *= SizeMultiple;
						ObjectCollided = true;
						return -2;
					}
					return -1;
				}
				ObjectCollided = false;
			}

			if (Angle > 2 * PI)
				Angle -= 2 * PI;
			if (Angle < 0)
				Angle += 2 * PI;

			return -1;
		}
		
		int CollisonMode3(const std::vector<cShape*>& _mObject)
		{
			for (int i = 0; i < _mObject.size(); i++)
			{
				if ((_mObject[i] == this))
					break;
				else if ((pow(pow((this->Center.x - _mObject[i]->Center.x), 2) + pow((this->Center.y - _mObject[i]->Center.y), 2), 0.5))
					<
					(_mObject[i]->R + this->R)) {

					if (ObjectCollided)
						return -1;

					double tempV, tempA;
					tempV = _mObject[i]->Vector;
					_mObject[i]->Vector = this->Vector;
					this->Vector = tempV;

					tempA = _mObject[i]->Angle;
					_mObject[i]->Angle = this->Angle;
					this->Angle = tempA;

					Center.x += (int)(Vector*sin(Angle));
					Center.y += (int)(Vector*cos(Angle));

					if (
						((this->type == 0) && (_mObject[i]->type == 2)) ||
						((this->type == 1) && (_mObject[i]->type == 0)) ||
						((this->type == 2) && (_mObject[i]->type == 1))
						)
					{
						_mObject[i]->R *= 0.5;
						ObjectCollided = true;
						return i;
					}
					else if (this->type == _mObject[i]->type)
						return -1;
					else
					{
						this->R *= 0.5;
						ObjectCollided = true;
						return -2;
					}
					return -1;
				}

				ObjectCollided = false;
			}

			if (Angle > 2 * PI)
				Angle -= 2 * PI;
			if (Angle < 0)
				Angle += 2 * PI;

			return -1;
		}

		virtual void Draw(HDC& hdc) = 0;

};

class cCircle : public cShape
{
	public:
	cCircle(LPARAM& lParam) : cShape(lParam)
	{
		this->setType(0);
	}

	cCircle(POINT NewCenter, double NewAngle, int NewR) : cShape(NewCenter, NewAngle, NewR)
	{
		this->setType(0);
	}

	void Draw(HDC& hdc)
	{
		DrawCircle(hdc, Center.x, Center.y, R);
	}
};

class cSquare : public cShape
{
	public:
	cSquare(LPARAM& lParam) : cShape(lParam)
	{
		this->setType(1);
	}

	cSquare(POINT NewCenter, double NewAngle, int NewR) : cShape(NewCenter, NewAngle, NewR)
	{
		this->setType(1);
	}

	// 미세 충돌 계산 - 추후 추가
	/*
	void CollisonSq(const RECT& rc, const std::vector<cShape*>& _mObject)
	{
		if (Center.x - R < 0 || Center.x + R > rc.right)
		{
			Angle = 2 * PI - Angle;
			while (Center.y - R < 0 || Center.y + R > rc.bottom)
				Center.x += abs((int)(Vector*cos(Angle)));
		}

		if (Center.y - R < 0 || Center.y + R > rc.bottom)
		{
			Angle = PI - Angle;

			while(Center.y - R < 0 || Center.y + R > rc.bottom)
				Center.y -= abs((int)(Vector*cos(Angle)));
		}

		if (Angle > 2 * PI)
			Angle -= 2 * PI;
		if (Angle < 0)
			Angle += 2 * PI;
	}

	void Draw(HDC& hdc)
	{
		DrawRoSquare(hdc, Center.x, Center.y, R, SinRo ,CosRo);
	}

	*/

};

class cStar : public cShape
{
public:

	cStar(LPARAM& lParam) : cShape(lParam)
	{
		this->setType(2);
	}
	cStar(POINT NewCenter, double NewAngle, int NewR) : cShape(NewCenter, NewAngle, NewR)
	{
		this->setType(2);
	}

	void Draw(HDC& hdc)
	{
		DrawRoStar(hdc, Center.x, Center.y, R, RotateAngel);
	}
};