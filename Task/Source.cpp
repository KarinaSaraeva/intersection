#include <iostream>
#include <math.h>
#include "Header.h"
using namespace std;

void Vector3D::fill_x(const double& x) {
	this->x = x;
}

void Vector3D::fill_y(const double& y) {
	this->y = y;
}

void Vector3D::fill_z(const double& z) {
	this->z = z;
}

double Vector3D::get_x() const {
	return(x);
}

double Vector3D::get_y() const {
	return(y);
}

double Vector3D::get_z() const {
	return(z);
}

Vector3D::Vector3D() {
	double a = 0;
	fill_x(a);
	fill_y(a);
	fill_z(a);
}

Vector3D::Vector3D(const double& x, const double& y, const double& z) {
	fill_x(x);
	fill_y(y);
	fill_z(z);
}

void Segment3D::fill_start(const Vector3D& start) {
	this->start = start;
}

void Segment3D::fill_end(const Vector3D& end) {
	this->end = end;
}


Vector3D Segment3D::get_start() const {
	return(start);
}

Vector3D Segment3D::get_end() const {
	return(end);
}

Vector3D Segment3D::get_pr() const {
	return(projections);
}

Segment3D::Segment3D(const Vector3D& v1, const Vector3D& v2){
	fill_start(v1);
	fill_end(v2);
	Vector3D temp(end.get_x() - start.get_x(), end.get_y() - start.get_y(), end.get_z() - start.get_z());
	projections = temp;
}

double determinant2D(double A, double B, double C, double D) {
	return (A * D - B * C);
}


Vector3D& Intersect(const Segment3D& sg1, const Segment3D& sg2) {
	int i = 0;
	Segment3D sg3(sg2.get_start(), sg1.get_start());

	//check if the Triple product is zero
	double determinant =
		sg1.get_pr().get_x() * determinant2D(sg2.get_pr().get_y(), sg3.get_pr().get_y(), sg2.get_pr().get_z(), sg3.get_pr().get_z()) -
		sg2.get_pr().get_x() * determinant2D(sg1.get_pr().get_y(), sg3.get_pr().get_y(), sg1.get_pr().get_z(), sg3.get_pr().get_z()) +
		sg3.get_pr().get_x() * determinant2D(sg1.get_pr().get_y(), sg2.get_pr().get_y(), sg1.get_pr().get_z(), sg2.get_pr().get_z());
	
	

	//check if the vector sg1 sg2 product is zero
	double cross_mul =
		abs(determinant2D(sg1.get_pr().get_y(), sg1.get_pr().get_z(), sg2.get_pr().get_y(), sg2.get_pr().get_z())) +
		abs(determinant2D(sg1.get_pr().get_x(), sg1.get_pr().get_z(), sg2.get_pr().get_x(), sg2.get_pr().get_z())) +
		abs(determinant2D(sg1.get_pr().get_x(), sg1.get_pr().get_y(), sg2.get_pr().get_x(), sg2.get_pr().get_y()));


	if ((cross_mul != 0)*(determinant == 0)) {
		cout << "lines intersect\n";
		//then solve cictem of two linear equations, cause the third one is redundant
		double t2 =
			determinant2D(sg3.get_pr().get_x(), -sg1.get_pr().get_x(), sg3.get_pr().get_y(), -sg1.get_pr().get_y()) /
			determinant2D(sg2.get_pr().get_x(), -sg1.get_pr().get_x(), sg2.get_pr().get_y(), -sg1.get_pr().get_y());
		double t1 =
			determinant2D(sg2.get_pr().get_x(), sg3.get_pr().get_x(), sg2.get_pr().get_y(), sg3.get_pr().get_y()) /
			determinant2D(sg2.get_pr().get_x(), -sg1.get_pr().get_x(), sg2.get_pr().get_y(), -sg1.get_pr().get_y());


		if ((t2 >= 0)*(t2 <= 1)*(t1 >= 0)*(t1 <= 1)) {
			Vector3D point(sg1.get_start().get_x() + sg1.get_pr().get_x()*t1, sg1.get_start().get_y() + sg1.get_pr().get_y() * t1, sg1.get_start().get_z() + sg1.get_pr().get_z() * t1);
			return point;
		}
		else {
			cout << "Segments do not intersect \n";
		}

	}
	else {
		cout << "lines do not intersect\n";
		Vector3D point;
		return point;
	}
}


void main(){
	Vector3D point1(-1, -1, 1);
	Vector3D point2(2, 2, 1);
	Vector3D point3(-2, -6, 1);
	Vector3D point4(2, 6, 1);

	Segment3D segment1(point1, point2);
	Segment3D segment2(point3, point4);


	Vector3D point = Intersect(segment1, segment2);
	cout << "intersection point:" << point.get_x() << "," << point.get_y() << "," << point.get_z();

};