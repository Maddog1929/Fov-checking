#include <algorithm>
#include <math.h>
#include "Vector.h"

inline float GetFov(Vector3 angle, Vector3 src, Vector3 dst)//pass your current viewangle, current 3d eye position, and 3d entity position (the cube)  <<this is what you call after confirming LOS. Everything else is called by this
{
	Vector3 ang, aim;
	ang = CalcAngle(src, dst);

	MakeVector(angle, aim);
	MakeVector(ang, ang);

	float mag = sqrtf(pow(aim.x, 2) + pow(aim.y, 2) + pow(aim.z, 2));
	float u_dot_v = aim.Dot(ang);

	return RAD2DEG(acos(u_dot_v / (pow(mag, 2))));  // will return an exact float for fov. 
}

/*if (this->GetFov(currentView, pLocal->GetEyePosition(), target) <= 80.0f) {
					cmd->viewangles = oldViewangle;
				}Heres an example for checking if a projectile is in our 80 fov
				*/

inline Vector3 CalcAngle(Vector3 PlayerPos, Vector3 EnemyPos)//returns an angle in a vector mesureing difference between you and entity
{
	Vector3 AimAngles;
	Vector3 delta = PlayerPos - EnemyPos;
	float hyp = sqrtf((delta.x * delta.x) + (delta.y * delta.y)); //SUPER SECRET IMPROVEMENT CODE NAME DONUT STEEL
	AimAngles.x = atanf(delta.z / hyp) * RADPI;
	AimAngles.y = atanf(delta.y / delta.x) * RADPI;
	AimAngles.z = 0.0f;
	if (delta.x >= 0.0)
		AimAngles.y += 180.0f;

	return AimAngles;
}

inline void MakeVector(Vector3 angle, Vector3& vector) //idk what this does *make a vector i quess*, but it uses passing by refrence so your gona have to figure that out in c# which dosent do that i think.
{
	float pitch = float(angle[0] * PI / 180);
	float yaw = float(angle[1] * PI / 180);
	float tmp = float(cos(pitch));
	vector[0] = float(-tmp * -cos(yaw));
	vector[1] = float(sin(yaw)*tmp);
	vector[2] = float(-sin(pitch));
}
