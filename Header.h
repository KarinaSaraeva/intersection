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
    
    void set(const double& x, const double& y, const double& z); //write function

    Vector3D operator+(const Vector3D& v2) const;
    Vector3D operator-(const Vector3D& v2) const;
    Vector3D operator*(const double& a) const;

    void operator+=(const Vector3D& v2);
    void operator-=(const Vector3D& v2);
    void operator*=(const double a);


    Vector3D(); //default constructor
    Vector3D(const double&, const double&, const double&); //constructor
    ~Vector3D() {}

    friend Vector3D operator* (const double& a, const Vector3D& v2);
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    
};

class Segment3D {
private:
    Vector3D start;
    Vector3D end;
    Vector3D projections;
    
    void fill_start(const Vector3D& start); //write function
    void fill_end(const Vector3D& end);
    void set_projections();

public:

    const Vector3D& get_start() const; //read-only function
    const Vector3D& get_end() const;
    const Vector3D& get_pr() const;
       
    Segment3D(); //default constructor
    Segment3D(const Vector3D& , const Vector3D& ); //constructor via two points 
    ~Segment3D(){};

    friend std::ostream& operator<<(std::ostream& os, const Segment3D& sg);
};


Vector3D Intersect(const Segment3D& segment1, const Segment3D& segment2);