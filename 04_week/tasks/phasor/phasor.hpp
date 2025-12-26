#pragma once

#include <cmath>
#include <iostream>
#include <iomanip>
#include <iosfwd>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
private:
    double real_ = 0.0;
    double imag_ = 0.0;

    // Нормализация фазы
    static double NormalizePhase(double phase);

public:
    Phasor();
    Phasor(double magnitude, double phase);
    Phasor(double magnitude, double phase, ExpTag);
    Phasor(double magnitude, double phase_deg, DegTag);
    Phasor(double real, double imag, AlgTag);

    void SetPolar(double magnitude, double phase);
    void SetCartesian(double real, double imag);

    double Magnitude() const;
    double Phase() const;
    double PhaseDeg() const;

    double Real() const;
    double Imag() const;

    double Abs() const;
    double Angle() const;
    double AngleDeg() const;

    Phasor Conj() const;
    Phasor Inv() const;

    Phasor operator-() const;
    Phasor& operator+=(const Phasor& other);
    Phasor& operator-=(const Phasor& other);
    Phasor& operator*=(const Phasor& other);
    Phasor& operator/=(const Phasor& other);

    bool operator==(const Phasor& other) const;
    bool operator!=(const Phasor& other) const;
};

Phasor operator+(const Phasor& lhs, const Phasor& rhs);
Phasor operator-(const Phasor& lhs, const Phasor& rhs);
Phasor operator*(const Phasor& lhs, const Phasor& rhs);
Phasor operator/(const Phasor& lhs, const Phasor& rhs);

Phasor operator+(const Phasor& phasor, double scalar);
Phasor operator+(double scalar, const Phasor& phasor);
Phasor operator-(const Phasor& phasor, double scalar);
Phasor operator-(double scalar, const Phasor& phasor);
Phasor operator*(const Phasor& phasor, double scalar);
Phasor operator*(double scalar, const Phasor& phasor);
Phasor operator/(const Phasor& phasor, double scalar);
Phasor operator/(double scalar, const Phasor& phasor);

Phasor MakePhasorCartesian(double real, double imag);
Phasor MakePhasorPolar(double magnitude, double phase);
Phasor MakePhasorPolarDeg(double magnitude, double phase_deg);

std::ostream& operator<<(std::ostream& os, const Phasor& p);
