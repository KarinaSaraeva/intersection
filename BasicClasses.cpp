#pragma once

#include <iostream>
#include <math.h>
#include "Header.h"


using namespace std;

void Vector3D::set(const double& x, const double& y, const double& z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

const double& Vector3D::get_x() const {
	return(x);
}

const double& Vector3D::get_y() const {
	return(y);
}

const double& Vector3D::get_z() const {
	return(z);
}

Vector3D Vector3D::operator+(const Vector3D& v2) const {
	Vector3D v(x + v2.get_x(), y + v2.get_y(), z + v2.get_z());
	return(v);
}

Vector3D Vector3D::operator-(const Vector3D& v2) const {
	Vector3D v(x - v2.get_x(), y - v2.get_y(), z - v2.get_z());
	return(v);
}

Vector3D Vector3D::operator*(const double& a) const {
	Vector3D v(x*a, y*a, z*a);
	return(v);
}

Vector3D operator* (const double& a, const Vector3D& v2) {
	Vector3D v(v2.x * a, v2.y * a, v2.z * a);
	return(v);
}


Vector3D::Vector3D() {
	double a = 0;
	set(a, a, a);
}

Vector3D::Vector3D(const double& x, const double& y, const double& z) {
	set(x, y, z);
}

void Segment3D::fill_start(const Vector3D& start) {
	this->start = start;
}

void Segment3D::fill_end(const Vector3D& end) {
	this->end = end;
}

const Vector3D& Segment3D::get_start() const {
	return(start);
}

const Vector3D& Segment3D::get_end() const {
	return(end);
}

const Vector3D& Segment3D::get_pr() const {
	return(projections);
}

void Segment3D::set_projections() {
	projections.set(end.get_x() - start.get_x(), end.get_y() - start.get_y(), end.get_z() - start.get_z());
}


Segment3D::Segment3D() {

	Vector3D v1;
	Vector3D v2(1,0,0);
	fill_start(v1);
	fill_end(v2);
	set_projections();
}

Segment3D::Segment3D(const Vector3D& v1, const Vector3D& v2){
	fill_start(v1);
	fill_end(v2);
	set_projections();	
}



double determinant2D(const double& A, const double& B, const double& C, const double& D) {
	return (A * D - B * C);
}

void Vector3D::operator+=(const Vector3D& v2) {
	set(x + v2.get_x(), y + v2.get_y(), z + v2.get_z());
}

void Vector3D::operator-=(const Vector3D& v2) {
	set(x - v2.get_x(), y - v2.get_y(), z - v2.get_z());
}

void Vector3D::operator*=(const double a) {
	set(x * a, y * a, z * a);
}

ostream& operator<<(ostream& os, const Vector3D& v) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return (os);
}

ostream& operator<<(ostream& os, const Segment3D& sg) {
	os << "[" << sg.start << ", " << sg.end << "]";
	return (os);
}


Vector3D Intersect(const Segment3D& sg1, const Segment3D& sg2) {
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
		//then solve system of two linear equations, cause the third one is redundant
		double a11, a12, a21, a22;
		double b1, b2;


		if ((sg1.get_pr().get_x() == 0) * (sg2.get_pr().get_x() == 0)) {
			a11 = sg2.get_pr().get_y();
			a12 = -sg1.get_pr().get_y();
			a21 = sg2.get_pr().get_z();
			a22 = -sg1.get_pr().get_z();

			b1 = sg3.get_pr().get_y();
			b2 = sg3.get_pr().get_z();

		}
		else if ((sg1.get_pr().get_y() == 0) * (sg2.get_pr().get_y() == 0)){
			a11 = sg2.get_pr().get_x();
			a12 = -sg1.get_pr().get_x();
			a21 = sg2.get_pr().get_z();
			a22 = -sg1.get_pr().get_z();

			b1 = sg3.get_pr().get_x();
			b2 = sg3.get_pr().get_z();

		}
		else {
			a11 = sg2.get_pr().get_x();
			a12 = -sg1.get_pr().get_x();
			a21 = sg2.get_pr().get_y();
			a22 = -sg1.get_pr().get_y();

			b1 = sg3.get_pr().get_x();
			b2 = sg3.get_pr().get_y();
		}


		double t2 =
			determinant2D(b1, a12, b2, a22)/
			determinant2D(a11, a12, a21, a22);
		double t1 =
			determinant2D(a11, b1, a21, b2) /
			determinant2D(a11, a12, a21, a22);


		if ((t2 >= 0)*(t2 <= 1)*(t1 >= 0)*(t1 <= 1)) {
			
			Vector3D point(sg1.get_start().get_x() + sg1.get_pr().get_x()*t1, sg1.get_start().get_y() + sg1.get_pr().get_y() * t1, sg1.get_start().get_z() + sg1.get_pr().get_z() * t1);
			return point;
		}
		else {
			cout << "t1 = "<< t1 << "t2 = " << t2 << "Segments do not intersect \n";
			Vector3D point;
			return point;
		}

	}
	else {
		cout << "lines do not intersect\n";
		Vector3D point;
		return point;
	}
}


