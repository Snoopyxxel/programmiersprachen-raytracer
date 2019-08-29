// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color {

  friend std::ostream& operator<<(std::ostream& os, Color const& c) {
    os << "(" << c.r << "," << c.g << "," << c.b << ")";
    return os;
  }

  Color& operator+=(Color const& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b) {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b) {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(float a, Color const& b) {
      auto tmp(b);
      tmp.r *= a;
      tmp.g *= a;
      tmp.b *= a;
      return tmp;
  }

    friend Color operator*(Color const& b, float a) {
        auto tmp(b);
        tmp.r *= a;
        tmp.g *= a;
        tmp.b *= a;
        return tmp;
    }

    friend Color operator*(Color const& a, Color const& b) {
        auto tmp(b);
        tmp.r *= a.r;
        tmp.g *= a.g;
        tmp.b *= a.b;
        return tmp;
    }

    bool operator>(float in) const {
        if (r > in)
            return true;
        if (in > r)
            return false;
        if (g > in)
            return true;
        if (in > g)
            return false;
        return b > in;
    }

    float r;
  float g;
  float b;
};

#endif //#define BUW_COLOR_HPP
