#pragma once

#include "Constants.h"

template<typename FinalT>
struct GeneralUnit
{
	friend bool operator< (FinalT const& l, FinalT const& r) { return l.value <  r.value; }
	friend bool operator> (FinalT const& l, FinalT const& r) { return l.value >  r.value; }
	friend bool operator<=(FinalT const& l, FinalT const& r) { return l.value <= r.value; }
	friend bool operator>=(FinalT const& l, FinalT const& r) { return l.value >= r.value; }
	friend bool operator==(FinalT const& l, FinalT const& r) { return l.value == r.value; }
	friend bool operator!=(FinalT const& l, FinalT const& r) { return l.value != r.value; }
	friend FinalT operator+(FinalT l, FinalT r) { return FinalT(l.value + r.value); }
	friend FinalT operator-(FinalT l, FinalT r) { return FinalT(l.value - r.value); }
	friend constexpr FinalT operator-(FinalT val) { return FinalT(-val.value); }
};

template<typename FinalT, template<typename> class GroupT>
struct UnitGroup : GeneralUnit<FinalT> {};

template<typename FinalT>
struct Distance : UnitGroup<FinalT, Distance> {};

template<typename FinalT>
struct Mass : UnitGroup<FinalT, Mass> {};

struct Scalar : GeneralUnit<Scalar>
{
	Scalar() : value(0) {}
	constexpr Scalar(double val) : value(val) {}
	double value;
};
// multiplication is commutative, but division is not. Cannot divide scalar by unit
template<typename FinalT> FinalT operator*(FinalT const& l, Scalar r) { return FinalT(l.value * r.value); }
template<typename FinalT> FinalT operator*(Scalar l, FinalT const& r) { return FinalT(l.value * r.value); }
template<typename FinalT> FinalT operator/(FinalT const& l, Scalar r) { return FinalT(l.value / r.value); }
template<typename FinalT> Scalar operator/(FinalT const& l, FinalT const& r) { return l.value / r.value; }

struct Gram;
struct Kilogram;
struct SolarMass;

struct Gram : Mass<Gram>
{
	Gram() : value(0) {}
	constexpr Gram(double val) : value(val) {}
	explicit Gram(Kilogram kg);
	explicit Gram(SolarMass sm);
	double value;
};

struct Kilogram : Mass<Kilogram>
{
	Kilogram() : value(0) {}
	constexpr Kilogram(double val) : value(val) {}
	explicit Kilogram(Gram g);
	explicit Kilogram(SolarMass sm);
	double value;
};

struct SolarMass : Mass<SolarMass>
{
	SolarMass() : value(0) {}
	constexpr SolarMass(double val) : value(val) {}
	explicit SolarMass(Gram g);
	explicit SolarMass(Kilogram kg);
	double value;
};

struct AstronomicalUnit;
struct SolarRadius;
struct Kilometer;

struct Meter : Distance<Meter>
{
	Meter() : value(0) {}
	constexpr Meter(double val) : value(val) {}
	explicit Meter(Kilometer km);
	explicit Meter(AstronomicalUnit au);
	explicit Meter(SolarRadius sr);
	double value;
};

struct Kilometer : Distance<Kilometer>
{
	Kilometer() : value(0) {}
	constexpr Kilometer(double val) : value(val) {}
	explicit Kilometer(AstronomicalUnit au);
	explicit Kilometer(SolarRadius sr);
	double value;
};

struct AstronomicalUnit : Distance<AstronomicalUnit>
{
	AstronomicalUnit() : value(0) {}
	constexpr AstronomicalUnit(double val) : value(val) {}
	explicit AstronomicalUnit(Meter m);
	explicit AstronomicalUnit(Kilometer sm);
	explicit AstronomicalUnit(SolarRadius sr);
	double value;
};

struct SolarRadius : Distance<SolarRadius>
{
	SolarRadius() : value(0) {}
	constexpr SolarRadius(double val) : value(val) {}
	explicit SolarRadius(Meter m);
	explicit SolarRadius(Kilometer km);
	explicit SolarRadius(AstronomicalUnit sm);
	double value;
};


inline Gram::Gram(Kilogram kg) : value(kg.value * 1000.) {}
inline Gram::Gram(SolarMass sm) : value(sm.value * kgPerSolarMass() * 1000.) {}
inline Kilogram::Kilogram(SolarMass sm) : value(sm.value * kgPerSolarMass()) {}
inline Kilogram::Kilogram(Gram g) : value(g.value / 1000.) {}
inline SolarMass::SolarMass(Kilogram kg) : value(kg.value / kgPerSolarMass()) {}
inline SolarMass::SolarMass(Gram g) : value((g.value / 1000.) / kgPerSolarMass()) {}
inline Meter::Meter(Kilometer km) : value(km.value * 1000.) {}
inline Meter::Meter(AstronomicalUnit au) : value(au.value * kilometersPerAU() * 1000.) {}
inline Meter::Meter(SolarRadius sr) : value(sr.value * kilometersPerSolarRadius() * 1000.) {}
inline AstronomicalUnit::AstronomicalUnit(Meter m) : value(m.value / 1000. / kilometersPerAU()) {}
inline AstronomicalUnit::AstronomicalUnit(Kilometer km) : value(km.value / kilometersPerAU()) {}
inline AstronomicalUnit::AstronomicalUnit(SolarRadius sr) : value(sr.value * kilometersPerSolarRadius() / kilometersPerAU()) {}
inline Kilometer::Kilometer(AstronomicalUnit au) : value(au.value * kilometersPerAU()) {}
inline Kilometer::Kilometer(SolarRadius sr) : value(sr.value * kilometersPerSolarRadius()) {}
inline SolarRadius::SolarRadius(AstronomicalUnit au) : value(au.value / kilometersPerSolarRadius() * kilometersPerAU()) {}
inline SolarRadius::SolarRadius(Kilometer km) : value(km.value / kilometersPerSolarRadius()) {}
inline SolarRadius::SolarRadius(Meter m) : value(m.value / 1000. / kilometersPerSolarRadius()) {}


struct SolarLuminosity : GeneralUnit<SolarLuminosity>
{
	SolarLuminosity() : value(0) {}
	constexpr SolarLuminosity(double val) : value(val) {}
	double value;
};

template<typename LeftT, typename RightT, template<typename> class GroupT> bool   operator< (UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) <  LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> bool   operator> (UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) >  LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> bool   operator<=(UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) <= LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> bool   operator>=(UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) >= LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> bool   operator==(UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) == LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> bool   operator!=(UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) != LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> LeftT  operator+ (UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) +  LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> LeftT  operator- (UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) -  LeftT(static_cast<RightT const&>(r)); }
template<typename LeftT, typename RightT, template<typename> class GroupT> Scalar operator/ (UnitGroup<LeftT, GroupT> const& l, UnitGroup<RightT, GroupT> const& r) { return static_cast<LeftT const&>(l) /  LeftT(static_cast<RightT const&>(r)); }

inline constexpr Gram operator"" _g(long double val) { return Gram(val); }
inline constexpr Kilogram operator"" _kg(long double val) { return Kilogram(val); }
inline constexpr SolarMass operator"" _M(long double val) { return SolarMass(val); }
inline constexpr Meter operator"" _m(long double val) { return Meter(val); }
inline constexpr Kilometer operator"" _km(long double val) { return Kilometer(val); }
inline constexpr SolarRadius operator"" _R(long double val) { return SolarRadius(val); }
inline constexpr AstronomicalUnit operator"" _au(long double val) { return AstronomicalUnit(val); }
inline constexpr SolarLuminosity operator"" _L(long double val) { return SolarLuminosity(val); }
inline constexpr Gram operator"" _g(unsigned long long val) { return Gram(val); }
inline constexpr Kilogram operator"" _kg(unsigned long long val) { return Kilogram(val); }
inline constexpr SolarMass operator"" _M(unsigned long long val) { return SolarMass(val); }
inline constexpr Meter operator"" _m(unsigned long long val) { return Meter(val); }
inline constexpr Kilometer operator"" _km(unsigned long long val) { return Kilometer(val); }
inline constexpr SolarRadius operator"" _R(unsigned long long val) { return SolarRadius(val); }
inline constexpr AstronomicalUnit operator"" _au(unsigned long long val) { return AstronomicalUnit(val); }
inline constexpr SolarLuminosity operator"" _L(unsigned long long val) { return SolarLuminosity(val); }

template<typename OStreamT> OStreamT& operator<<(OStreamT& os, Gram val) { return os << val.value << "g"; }
template<typename OStreamT> OStreamT& operator<<(OStreamT& os, Kilogram val) { return os << val.value << "kg"; }
template<typename OStreamT> OStreamT& operator<<(OStreamT& os, SolarMass val) { return os << val.value << "M"; }
template<typename OStreamT> OStreamT& operator<<(OStreamT& os, Meter val) { return os << val.value << "m"; }
template<typename OStreamT> OStreamT& operator<<(OStreamT& os, Kilometer val) { return os << val.value << "km"; }
template<typename OStreamT> OStreamT& operator<<(OStreamT& os, SolarRadius val) { return os << val.value << "R"; }
template<typename OStreamT> OStreamT& operator<<(OStreamT& os, AstronomicalUnit val) { return os << val.value << "au"; }
template<typename OStreamT> OStreamT& operator<<(OStreamT& os, SolarLuminosity val) { return os << val.value << "L"; }

