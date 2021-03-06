//compile with BasicClasses.cpp 

#include <iostream>
#include <math.h>
#include "Header.h"

using namespace std;


int main() {
	Vector3D point1(-3, 0, -2);
	Vector3D point2(-1, 6, -8);
	Vector3D point3(0, 3, 0);
	Vector3D point4(-4, 3, -10);



	Segment3D segment1(point1, point2);
	Segment3D segment2(point3, point4);
	cout << "segment 1:" << segment1 << "\n";
	
	cout << "segment 2:" << segment2 << "\n";
	


	Vector3D point = Intersect(segment1, segment2);
	cout << "intersection point:" << point << "\n";
	

	return 0;
};