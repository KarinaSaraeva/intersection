#pragma once
class Vector3D {
private:
    double x;
    double y;
    double z;  

public:
    const double& get_x() const; //read-only function
    const double& get_y() const;
    const double& get_z() const;
    
    void fill_x(const double& x); //write function
    void fill_y(const double& y);
    void fill_z(const double& z);

    Vector3D summ(const Vector3D& v2) const;

    void info() const; //output of coordinates 

    Vector3D(); //default constructor
    Vector3D(const double&, const double&, const double&); //constructor
    ~Vector3D() {}
};

class Segment3D {
private:
    Vector3D start;
    Vector3D end;
    Vector3D projections;
    void set_projections();
    void fill_start(const Vector3D& start); //write function
    void fill_end(const Vector3D& end);

public:
    const Vector3D& get_start() const; //read-only function
    const Vector3D& get_end() const;
    const Vector3D& get_pr() const;

    
    void info() const; //output of start and end coordinates 
    void inverse(); //swap start and end points of the segment
       
    Segment3D(); //default constructor
    Segment3D(const Vector3D& , const Vector3D& ); //constructor via two points 
    ~Segment3D(){};
};


Vector3D Intersect(const Segment3D& segment1, const Segment3D& segment2);