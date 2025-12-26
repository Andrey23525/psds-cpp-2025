#include "phasor.hpp"

double Phasor::NormalizePhase(double phase) {
    // Используем std::remainder для нормализации в диапазон (-pi, pi]
    constexpr double TWO_PI = 2.0 * M_PI;
    double normalized = std::remainder(phase, TWO_PI);
    // std::remainder возвращает значение [-pi, pi]
    if (normalized <= -M_PI) {
        normalized += TWO_PI;
    }
    return normalized;
}

Phasor::Phasor() : real_(0.0), imag_(0.0) {}

Phasor::Phasor(double magnitude, double phase) {
    // Если амплитуда отрицательная, делаем её положительной и сдвигаем фазу на pi
    if (magnitude < 0) {
        magnitude = -magnitude;
        phase += M_PI;
    }
    phase = NormalizePhase(phase);
    real_ = magnitude * std::cos(phase);
    imag_ = magnitude * std::sin(phase);
}

Phasor::Phasor(double magnitude, double phase, ExpTag) : Phasor(magnitude, phase) {}

Phasor::Phasor(double magnitude, double phase_deg, DegTag)
    : Phasor(magnitude, phase_deg * M_PI / 180.0) {}

Phasor::Phasor(double real, double imag, AlgTag) : real_(real), imag_(imag) {}

void Phasor::SetPolar(double magnitude, double phase) {
    if (magnitude < 0) {
        magnitude = -magnitude;
        phase += M_PI;
    }
    phase = NormalizePhase(phase);
    real_ = magnitude * std::cos(phase);
    imag_ = magnitude * std::sin(phase);
}

void Phasor::SetCartesian(double real, double imag) {
    real_ = real;
    imag_ = imag;
}

double Phasor::Magnitude() const {
    return std::hypot(real_, imag_);
}

double Phasor::Phase() const {
    return std::atan2(imag_, real_);
}

double Phasor::PhaseDeg() const {
    return Phase() * 180.0 / M_PI;
}

double Phasor::Real() const {
    return real_;
}

double Phasor::Imag() const {
    return imag_;
}

double Phasor::Abs() const {
    return Magnitude();
}

double Phasor::Angle() const {
    return Phase();
}

double Phasor::AngleDeg() const {
    return PhaseDeg();
}

Phasor Phasor::Conj() const {
    return Phasor(real_, -imag_, AlgTag{});
}

Phasor Phasor::Inv() const {
    double mag_sq = real_ * real_ + imag_ * imag_;
    return Phasor(real_ / mag_sq, -imag_ / mag_sq, AlgTag{});
}

Phasor Phasor::operator-() const {
    return Phasor(-real_, -imag_, AlgTag{});
}

Phasor& Phasor::operator+=(const Phasor& other) {
    real_ += other.real_;
    imag_ += other.imag_;
    return *this;
}

Phasor& Phasor::operator-=(const Phasor& other) {
    real_ -= other.real_;
    imag_ -= other.imag_;
    return *this;
}

Phasor& Phasor::operator*=(const Phasor& other) {
    double new_real = real_ * other.real_ - imag_ * other.imag_;
    double new_imag = real_ * other.imag_ + imag_ * other.real_;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}

Phasor& Phasor::operator/=(const Phasor& other) {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    double new_real = (real_ * other.real_ + imag_ * other.imag_) / denom;
    double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denom;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}

bool Phasor::operator==(const Phasor& other) const {
    constexpr double EPSILON = 1e-9;
    return std::abs(real_ - other.real_) < EPSILON &&
           std::abs(imag_ - other.imag_) < EPSILON;
}

bool Phasor::operator!=(const Phasor& other) const {
    return !(*this == other);
}

Phasor operator+(const Phasor& lhs, const Phasor& rhs) {
    return Phasor(lhs.Real() + rhs.Real(), lhs.Imag() + rhs.Imag(), AlgTag{});
}

Phasor operator-(const Phasor& lhs, const Phasor& rhs) {
    return Phasor(lhs.Real() - rhs.Real(), lhs.Imag() - rhs.Imag(), AlgTag{});
}

Phasor operator*(const Phasor& lhs, const Phasor& rhs) {
    double real = lhs.Real() * rhs.Real() - lhs.Imag() * rhs.Imag();
    double imag = lhs.Real() * rhs.Imag() + lhs.Imag() * rhs.Real();
    return Phasor(real, imag, AlgTag{});
}

Phasor operator/(const Phasor& lhs, const Phasor& rhs) {
    double denom = rhs.Real() * rhs.Real() + rhs.Imag() * rhs.Imag();
    double real = (lhs.Real() * rhs.Real() + lhs.Imag() * rhs.Imag()) / denom;
    double imag = (lhs.Imag() * rhs.Real() - lhs.Real() * rhs.Imag()) / denom;
    return Phasor(real, imag, AlgTag{});
}

Phasor operator+(const Phasor& phasor, double scalar) {
    return Phasor(phasor.Real() + scalar, phasor.Imag(), AlgTag{});
}

Phasor operator+(double scalar, const Phasor& phasor) {
    return phasor + scalar;
}

Phasor operator-(const Phasor& phasor, double scalar) {
    return Phasor(phasor.Real() - scalar, phasor.Imag(), AlgTag{});
}

Phasor operator-(double scalar, const Phasor& phasor) {
    return Phasor(scalar - phasor.Real(), -phasor.Imag(), AlgTag{});
}

Phasor operator*(const Phasor& phasor, double scalar) {
    return Phasor(phasor.Real() * scalar, phasor.Imag() * scalar, AlgTag{});
}

Phasor operator*(double scalar, const Phasor& phasor) {
    return phasor * scalar;
}

Phasor operator/(const Phasor& phasor, double scalar) {
    return Phasor(phasor.Real() / scalar, phasor.Imag() / scalar, AlgTag{});
}

Phasor operator/(double scalar, const Phasor& phasor) {
    double denom = phasor.Real() * phasor.Real() + phasor.Imag() * phasor.Imag();
    double real = (scalar * phasor.Real()) / denom;
    double imag = (-scalar * phasor.Imag()) / denom;
    return Phasor(real, imag, AlgTag{});
}

Phasor MakePhasorCartesian(double real, double imag) {
    return Phasor(real, imag, AlgTag{});
}

Phasor MakePhasorPolar(double magnitude, double phase) {
    return Phasor(magnitude, phase);
}

Phasor MakePhasorPolarDeg(double magnitude, double phase_deg) {
    return Phasor(magnitude, phase_deg, DegTag{});
}

std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    os << std::fixed << std::setprecision(3);
    os << p.Magnitude() << "*e(j*" << p.PhaseDeg() << ") [";
    os << p.Real() << " + j*" << p.Imag() << "]";
    return os;
}