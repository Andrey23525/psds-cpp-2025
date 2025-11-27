constexpr long double FT_TO_M = 0.3048L;
constexpr long double M_TO_FT = 1.0L / FT_TO_M;
constexpr long double FT_TO_IN = 12.0L;
constexpr long double IN_TO_FT = 1.0L / FT_TO_IN;
constexpr long double FT_TO_CM = FT_TO_M * 100.0L;
constexpr long double CM_TO_FT = 1.0L / FT_TO_CM;

constexpr long double IN_TO_M = 0.0254L;
constexpr long double M_TO_IN = 1.0L / IN_TO_M;
constexpr long double IN_TO_CM = IN_TO_M * 100.0L;
constexpr long double CM_TO_IN = 1.0L / IN_TO_CM;


constexpr long double  CM_TO_M = 0.01L;
constexpr long double M_TO_CM = 1.0L / CM_TO_M;


// ft ->
constexpr double operator"" _ft_to_m(long double value) {
    return static_cast<double>(value * FT_TO_M);
}

constexpr double operator"" _ft_to_in(long double value) {
    return static_cast<double>(value * FT_TO_IN);
}

constexpr double operator"" _ft_to_cm(long double value) {
    return static_cast<double>(value * FT_TO_CM);
}

// in ->
constexpr double operator"" _in_to_m(long double value) {
    return static_cast<double>(value * IN_TO_M);
}

constexpr double operator"" _in_to_ft(long double value) {
    return static_cast<double>(value * IN_TO_FT);
}

constexpr double operator"" _in_to_cm(long double value) {
    return static_cast<double>(value * IN_TO_CM);
}

// cm ->
constexpr double operator"" _cm_to_m(long double value) {
    return static_cast<double>(value * CM_TO_M);
}

constexpr double operator"" _cm_to_ft(long double value) {
    return static_cast<double>(value * CM_TO_FT);
}

constexpr double operator"" _cm_to_in(long double value) {
    return static_cast<double>(value * CM_TO_IN);
}

// m ->
constexpr double operator"" _m_to_ft(long double value) {
    return static_cast<double>(value * M_TO_FT);
}

constexpr double operator"" _m_to_in(long double value) {
    return static_cast<double>(value * M_TO_IN);
}

constexpr double operator"" _m_to_cm(long double value) {
    return static_cast<double>(value * M_TO_CM);
}
