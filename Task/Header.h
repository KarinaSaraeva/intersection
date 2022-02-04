#pragma once
class Vector3D {
private:
    double x;
    double y;
    double z;  

public:
    double get_x() const; //read-only function
    double get_y() const;
    double get_z() const;
    
    void fill_x(const double& x); //write function
    void fill_y(const double& y);
    void fill_z(const double& z);

    Vector3D(); //default constructor
    Vector3D(const double&, const double&, const double&); //constructor
    
};

class Segment3D {
private:
    Vector3D start;
    Vector3D end;
    Vector3D projections;
    

public:
    Vector3D get_start() const; //read-only function
    Vector3D get_end() const;
    Vector3D get_pr() const;

    void fill_start(const Vector3D& start); //write function
    void fill_end(const Vector3D& end);
       

    Segment3D(const Vector3D& , const Vector3D& ); //constructor via two points 
};


Vector3D& Intersect(const Segment3D& segment1, const Segment3D& segment2);