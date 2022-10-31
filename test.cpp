#include "Integer.hpp"

using namespace std;
using namespace arbitrary_precision_arithmetic;

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE("Number initialization") {
  Integer a1(CHAR_MIN), a2(CHAR_MAX), a3(UCHAR_MAX), a4, &a5(a1);
  REQUIRE(a1 == CHAR_MIN);
  REQUIRE(a2 == CHAR_MAX);
  REQUIRE(a3 == UCHAR_MAX);
  REQUIRE(a4 == 0);
  REQUIRE(a5 == CHAR_MIN);

  Integer b1(SHRT_MAX), b2(SHRT_MIN), b3(USHRT_MAX);
  REQUIRE(b1 == SHRT_MAX);
  REQUIRE(b2 == SHRT_MIN);
  REQUIRE(b3 == USHRT_MAX);

  Integer c1(INT_MIN), c2(INT_MAX), c3(UINT_MAX);
  REQUIRE(c1 == INT_MIN);
  REQUIRE(c2 == INT_MAX);
  REQUIRE(c3 == UINT_MAX);

  Integer d1(LONG_MIN), d2(LONG_MAX), d3(ULONG_MAX);
  REQUIRE(d1 == LONG_MIN);
  REQUIRE(d2 == LONG_MAX);
  REQUIRE(d3 == ULONG_MAX);

  Integer e1(LLONG_MIN), e2(LLONG_MAX), e3(ULLONG_MAX);
  REQUIRE(e1 == LLONG_MIN);
  REQUIRE(e2 == LLONG_MAX);
  REQUIRE(e3 == ULLONG_MAX);
}

TEST_CASE("String initialization") {
  Integer a1("0"), a2("0000000000"), a3("-0"), a4("-0000000000");
  REQUIRE(a1 == a2);
  REQUIRE(a3 == a4);
  REQUIRE(a1 == a3);

  Integer b1("Foo"), b2("Boo"), b3("Bar"), b4("Baz");
  REQUIRE(b1 == 0);
  REQUIRE(b1 == b2);
  REQUIRE(b3 == b4);
  REQUIRE(b1 == b3);

  Integer c1(to_string(CHAR_MIN)), c2(to_string(CHAR_MAX)),
      c3(to_string(UCHAR_MAX));
  REQUIRE(c1 == CHAR_MIN);
  REQUIRE(c2 == CHAR_MAX);
  REQUIRE(c3 == UCHAR_MAX);

  Integer d1(to_string(SHRT_MIN)), d2(to_string(SHRT_MAX)),
      d3(to_string(USHRT_MAX));
  REQUIRE(d1 == SHRT_MIN);
  REQUIRE(d2 == SHRT_MAX);
  REQUIRE(d3 == USHRT_MAX);

  Integer e1(to_string(INT_MIN)), e2(to_string(INT_MAX)),
      e3(to_string(UINT_MAX));
  REQUIRE(std::string(e1) == to_string(INT_MIN));
  REQUIRE(e2 == INT_MAX);
  REQUIRE(e3 == UINT_MAX);

  Integer f1(to_string(LONG_MIN)), f2(to_string(LONG_MAX)),
      f3(to_string(ULONG_MAX));
  REQUIRE(f1 == LONG_MIN);
  REQUIRE(f2 == LONG_MAX);
  REQUIRE(f3 == ULONG_MAX);

  Integer g1(to_string(LLONG_MIN)), g2(to_string(LLONG_MAX)),
      g3(to_string(ULLONG_MAX));
  REQUIRE(g1 == LLONG_MIN);
  REQUIRE(g2 == LLONG_MAX);
  REQUIRE(g3 == ULLONG_MAX);

  Integer h1("12345678900987654321123456789009876543211123456789000987654321");
  REQUIRE(std::string(h1) ==
          "12345678900987654321123456789009876543211123456789000987654321");
  Integer h2("0000000000125");
  REQUIRE(h2 == 125);
  Integer h3("000000000-41242");
  REQUIRE(h3 == 0);
  Integer h4("-12345678900987654321123456789009876543211123456789000987654321");
  REQUIRE(std::string(h4) ==
          "-12345678900987654321123456789009876543211123456789000987654321");
  Integer h5("1000000000100000000010000000001");
  REQUIRE(std::string(h5) == "1000000000100000000010000000001");
}

TEST_CASE("Operator=") {
  Integer a1;
  Integer &a2 = a1;
  REQUIRE(a2 == 0);

  Integer b1(LLONG_MAX);
  Integer &b2 = b1;
  REQUIRE(b2 == LLONG_MAX);

  Integer c1("12");
  Integer c2 = c1;
  c2 *= 2;
  REQUIRE(c2 == 24);
}

TEST_CASE("Cast to uchar") {
  Integer a1(UCHAR_MAX), a2(UCHAR_MAX + 1), a3(LLONG_MAX), a4(0), a5(-1),
      a6(LLONG_MIN), a7(UCHAR_MAX / 2);
  auto s1 = static_cast<unsigned char>(a1);
  auto s2 = static_cast<unsigned char>(a2);
  auto s3 = static_cast<unsigned char>(a3);
  auto s4 = static_cast<unsigned char>(a4);
  auto s5 = static_cast<unsigned char>(a5);
  auto s6 = static_cast<unsigned char>(a6);
  auto s7 = static_cast<unsigned char>(a7);
  REQUIRE(s1 == UCHAR_MAX);
  REQUIRE(s2 == UCHAR_MAX);
  REQUIRE(s3 == UCHAR_MAX);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == 0);
  REQUIRE(s6 == 0);
  REQUIRE(s7 == UCHAR_MAX / 2);
}

TEST_CASE("Cast to char") {
  Integer a1(CHAR_MAX), a2(CHAR_MAX + 1), a3(ULLONG_MAX), a4(0), a5(CHAR_MIN),
      a6(CHAR_MIN - 1), a7(LLONG_MIN), a8(CHAR_MAX / 2), a9(CHAR_MIN / 2);
  char s1 = static_cast<char>(a1);
  char s2 = static_cast<char>(a2);
  char s3 = static_cast<char>(a3);
  char s4 = static_cast<char>(a4);
  char s5 = static_cast<char>(a5);
  char s6 = static_cast<char>(a6);
  char s7 = static_cast<char>(a7);
  char s8 = static_cast<char>(a8);
  char s9 = static_cast<char>(a9);
  REQUIRE(s1 == CHAR_MAX);
  REQUIRE(s2 == CHAR_MAX);
  REQUIRE(s3 == CHAR_MAX);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == CHAR_MIN);
  REQUIRE(s6 == CHAR_MIN);
  REQUIRE(s7 == CHAR_MIN);
  REQUIRE(s8 == CHAR_MAX / 2);
  REQUIRE(s9 == CHAR_MIN / 2);
}

TEST_CASE("Cast to ushort") {
  Integer a1(USHRT_MAX), a2(USHRT_MAX + 1), a3(LLONG_MAX), a4(0), a5(-1),
      a6(LLONG_MIN), a7(USHRT_MAX / 2);
  auto s1 = static_cast<unsigned short>(a1);
  auto s2 = static_cast<unsigned short>(a2);
  auto s3 = static_cast<unsigned short>(a3);
  auto s4 = static_cast<unsigned short>(a4);
  auto s5 = static_cast<unsigned short>(a5);
  auto s6 = static_cast<unsigned short>(a6);
  auto s7 = static_cast<unsigned short>(a7);
  REQUIRE(s1 == USHRT_MAX);
  REQUIRE(s2 == USHRT_MAX);
  REQUIRE(s3 == USHRT_MAX);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == 0);
  REQUIRE(s6 == 0);
  REQUIRE(s7 == USHRT_MAX / 2);
}

TEST_CASE("Cast to short") {
  Integer a1(SHRT_MAX), a2(SHRT_MAX + 1), a3(LLONG_MAX), a4(0), a5(SHRT_MIN),
      a6(SHRT_MIN - 1), a7(LLONG_MIN), a8(SHRT_MAX / 2), a9(SHRT_MIN / 2);
  auto s1 = static_cast<short>(a1);
  auto s2 = static_cast<short>(a2);
  auto s3 = static_cast<short>(a3);
  auto s4 = static_cast<short>(a4);
  auto s5 = static_cast<short>(a5);
  auto s6 = static_cast<short>(a6);
  auto s7 = static_cast<short>(a7);
  auto s8 = static_cast<short>(a8);
  auto s9 = static_cast<short>(a9);
  REQUIRE(s1 == SHRT_MAX);
  REQUIRE(s2 == SHRT_MAX);
  REQUIRE(s3 == SHRT_MAX);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == SHRT_MIN);
  REQUIRE(s6 == SHRT_MIN);
  REQUIRE(s7 == SHRT_MIN);
  REQUIRE(s8 == SHRT_MAX / 2);
  REQUIRE(s9 == SHRT_MIN / 2);
}

TEST_CASE("Cast to uint") {
  long long max = UINT_MAX;
  Integer a1(max), a2(max + 1), a3(LLONG_MAX), a4(0), a5(-1), a6(LLONG_MIN),
      a7(UINT_MAX / 2);
  auto s1 = static_cast<unsigned int>(a1);
  auto s2 = static_cast<unsigned int>(a2);
  auto s3 = static_cast<unsigned int>(a3);
  auto s4 = static_cast<unsigned int>(a4);
  auto s5 = static_cast<unsigned int>(a5);
  auto s6 = static_cast<unsigned int>(a6);
  auto s7 = static_cast<unsigned int>(a7);
  REQUIRE(s1 == max);
  REQUIRE(s2 == max);
  REQUIRE(s3 == UINT_MAX);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == 0);
  REQUIRE(s6 == 0);
  REQUIRE(s7 == UINT_MAX / 2);
}

TEST_CASE("Cast to int") {
  long long max = INT_MAX;
  long long min = INT_MIN;
  Integer a1(max), a2(max + 1), a3(LLONG_MAX), a4(0), a5(min), a6(min - 1),
      a7(LLONG_MIN), a8(max / 2), a9(min / 2);
  int s1 = static_cast<int>(a1);
  int s2 = static_cast<int>(a2);
  int s3 = static_cast<int>(a3);
  int s4 = static_cast<int>(a4);
  int s5 = static_cast<int>(a5);
  int s6 = static_cast<int>(a6);
  int s7 = static_cast<int>(a7);
  int s8 = static_cast<int>(a8);
  int s9 = static_cast<int>(a9);
  REQUIRE(s1 == max);
  REQUIRE(s2 == max);
  REQUIRE(s3 == max);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == min);
  REQUIRE(s6 == min);
  REQUIRE(s7 == min);
  REQUIRE(s8 == max / 2);
  REQUIRE(s9 == min / 2);
}

TEST_CASE("Cast unsigned long") {
  Integer a1(ULONG_MAX), a2("18446744073709551616"), a3(0), a4(-1),
      a5(LLONG_MIN), a6(ULONG_MAX / 2);
  auto s1 = static_cast<unsigned long int>(a1);
  auto s2 = static_cast<unsigned long int>(a2);
  auto s3 = static_cast<unsigned long int>(a3);
  auto s4 = static_cast<unsigned long int>(a4);
  auto s5 = static_cast<unsigned long int>(a5);
  auto s6 = static_cast<unsigned long int>(a6);
  REQUIRE(s1 == ULONG_MAX);
  REQUIRE(s2 == ULONG_MAX);
  REQUIRE(s3 == 0);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == 0);
  REQUIRE(s6 == ULONG_MAX / 2);
}

TEST_CASE("Cast long") {
  Integer a1(LONG_MAX), a2("1123456789123456789123456789"), a3(0), a4(LONG_MIN),
      a5("-1123456789123456789123456789"), a6(LONG_MAX / 2), a7(LONG_MIN / 2);
  auto s1 = static_cast<long int>(a1);
  auto s2 = static_cast<long int>(a2);
  auto s3 = static_cast<long int>(a3);
  auto s4 = static_cast<long int>(a4);
  auto s5 = static_cast<long int>(a5);
  auto s6 = static_cast<long int>(a6);
  auto s7 = static_cast<long int>(a7);
  REQUIRE(s1 == LONG_MAX);
  REQUIRE(s2 == LONG_MAX);
  REQUIRE(s3 == 0);
  REQUIRE(s4 == LONG_MIN);
  REQUIRE(s5 == LONG_MIN);
  REQUIRE(s6 == LONG_MAX / 2);
  REQUIRE(s7 == LONG_MIN / 2);
}

TEST_CASE("Cast unsigned long long") {
  Integer a1(ULLONG_MAX), a2("1123456789123456789123456789"), a3(0),
      a4(LLONG_MIN), a5("-1123456789123456789123456789"), a6(ULLONG_MAX / 2);
  auto s1 = static_cast<unsigned long long int>(a1);
  auto s2 = static_cast<unsigned long long int>(a2);
  auto s3 = static_cast<unsigned long long int>(a3);
  auto s4 = static_cast<unsigned long long int>(a4);
  auto s5 = static_cast<unsigned long long int>(a5);
  auto s6 = static_cast<unsigned long long int>(a6);
  REQUIRE(s1 == ULLONG_MAX);
  REQUIRE(s2 == ULLONG_MAX);
  REQUIRE(s3 == 0);
  REQUIRE(s4 == 0);
  REQUIRE(s5 == 0);
  REQUIRE(s6 == ULLONG_MAX / 2);
}

TEST_CASE("Cast long long") {
  Integer a1(LLONG_MAX), a2("1123456789123456789123456789"), a3(0),
      a4(LLONG_MIN), a5("-1123456789123456789123456789"), a6(LLONG_MAX / 2),
      a7(LLONG_MIN / 2);
  auto s1 = static_cast<long long int>(a1);
  auto s2 = static_cast<long long int>(a2);
  auto s3 = static_cast<long long int>(a3);
  auto s4 = static_cast<long long int>(a4);
  auto s5 = static_cast<long long int>(a5);
  auto s6 = static_cast<long long int>(a6);
  auto s7 = static_cast<long long int>(a7);
  REQUIRE(s1 == LLONG_MAX);
  REQUIRE(s2 == LLONG_MAX);
  REQUIRE(s3 == 0);
  REQUIRE(s4 == LLONG_MIN);
  REQUIRE(s5 == LLONG_MIN);
  REQUIRE(s6 == LLONG_MAX / 2);
  REQUIRE(s7 == LLONG_MIN / 2);
}

TEST_CASE("Unary operators") {
  Integer a1(5), a2(-5), a3(0), a4(ULLONG_MAX), a5("5"), a6("-5"), a7("0"),
      a8(to_string(ULLONG_MAX));
  REQUIRE(-a1 == -5);
  REQUIRE(-a2 == 5);
  REQUIRE(-a3 == a3);
  REQUIRE(std::string(-a4) == "-18446744073709551615");
  REQUIRE(-a5 == -5);
  REQUIRE(-a6 == 5);
  REQUIRE(-a7 == 0);
  REQUIRE(std::string(-a8) == "-18446744073709551615");

  REQUIRE(--a1 == 4);
  REQUIRE(--a2 == -6);
  REQUIRE(--a3 == -1);
  REQUIRE(--a4 == ULLONG_MAX - 1);
  REQUIRE(--a5 == 4);
  REQUIRE(--a6 == -6);
  REQUIRE(--a7 == -1);
  REQUIRE(--a8 == ULLONG_MAX - 1);

  REQUIRE(a1-- == 4);
  REQUIRE(a2-- == -6);
  REQUIRE(a3-- == -1);
  REQUIRE(a4-- == ULLONG_MAX - 1);
  REQUIRE(a5-- == 4);
  REQUIRE(a6-- == -6);
  REQUIRE(a7-- == -1);
  REQUIRE(a8-- == ULLONG_MAX - 1);

  REQUIRE(a1 == 3);
  REQUIRE(a2 == -7);
  REQUIRE(a3 == -2);
  REQUIRE(a4 == ULLONG_MAX - 2);
  REQUIRE(a5 == 3);
  REQUIRE(a6 == -7);
  REQUIRE(a7 == -2);
  REQUIRE(a8 == ULLONG_MAX - 2);

  REQUIRE(+a1 == 3);
  REQUIRE(+a2 == -7);
  REQUIRE(+a3 == -2);
  REQUIRE(+a4 == ULLONG_MAX - 2);
  REQUIRE(+a5 == 3);
  REQUIRE(+a6 == -7);
  REQUIRE(+a7 == -2);
  REQUIRE(+a8 == ULLONG_MAX - 2);

  REQUIRE(++a1 == 4);
  REQUIRE(++a2 == -6);
  REQUIRE(++a3 == -1);
  REQUIRE(++a4 == ULLONG_MAX - 1);
  REQUIRE(++a5 == 4);
  REQUIRE(++a6 == -6);
  REQUIRE(++a7 == -1);
  REQUIRE(++a8 == ULLONG_MAX - 1);

  REQUIRE(a1++ == 4);
  REQUIRE(a2++ == -6);
  REQUIRE(a3++ == -1);
  REQUIRE(a4++ == ULLONG_MAX - 1);
  REQUIRE(a5++ == 4);
  REQUIRE(a6++ == -6);
  REQUIRE(a7++ == -1);
  REQUIRE(a8++ == ULLONG_MAX - 1);

  REQUIRE(a1 == 5);
  REQUIRE(a2 == -5);
  REQUIRE(a3 == 0);
  REQUIRE(a4 == ULLONG_MAX);
  REQUIRE(a5 == 5);
  REQUIRE(a6 == -5);
  REQUIRE(a7 == 0);
  REQUIRE(a8 == ULLONG_MAX);
}

TEST_CASE("Binary operators") {
  {
    Integer a1(5), a2(-5);
    REQUIRE(a1 - a2 == 10);

    Integer b1(-5), b2(5);
    REQUIRE(b1 - b2 == -10);

    Integer c1(-5), c2(-5);
    REQUIRE(c1 - c2 == 0);

    Integer d1("5"), d2("-5");
    REQUIRE(d1 - d2 == 10);

    Integer e1("-5"), e2("5");
    REQUIRE(e1 - e2 == -10);

    Integer f1("-5"), f2("-5");
    REQUIRE(f1 - f2 == 0);

    Integer g1(10), g2(-5), g3(1000);
    g3 -= g1 - g2;
    REQUIRE(g3 == 985);

    Integer h1("10"), h2("-5"), h3(1000);
    h3 -= h1 - h2;
    REQUIRE(h3 == 985);
  }

  {
    Integer a1(5), a2(-5);
    REQUIRE(a1 + a2 == 0);

    Integer b1(-5), b2(5);
    REQUIRE(b1 + b2 == 0);

    Integer c1(-5), c2(-5);
    REQUIRE(c1 + c2 == -10);

    Integer d1("5"), d2("-5");
    REQUIRE(d1 + d2 == 0);

    Integer e1("-5"), e2("5");
    REQUIRE(e1 + e2 == 0);

    Integer f1("-5"), f2("-5");
    REQUIRE(f1 + f2 == -10);

    Integer g1(10), g2(-5), g3(1000);
    g3 += g1 + g2;
    REQUIRE(g3 == 1005);

    Integer h1("10"), h2("-5"), h3(1000);
    h3 += h1 + h2;
    REQUIRE(h3 == 1005);
  }

  {
    Integer a1(1), b1(59);
    for (int i = 0; i < 10; ++i) {
      a1 *= b1;
    }
    REQUIRE(a1 == 511116753300641401);
    Integer a2(a1);
    a2 *= a1;
    REQUIRE(std::string(a2) == "261240335504588722483367157995242801");
    REQUIRE(std::string(a2 * a1) ==
            "133524312114275664899926313757566191470823300027804201");

    Integer a3(-2), a4(2);
    for (int i = 0; i < 11; ++i) {
      a3 *= a4;
    }
    REQUIRE(a3 == -4096);
    Integer b2(-1);
    REQUIRE(a3 * b2 == 4096);
  }

  {
    Integer a1("1"), b1("59");
    for (int i = 0; i < 10; ++i) {
      a1 *= b1;
    }
    REQUIRE(a1 == 511116753300641401);
    Integer a2(a1);
    a2 *= a1;
    REQUIRE(std::string(a2) == "261240335504588722483367157995242801");
    REQUIRE(std::string(a2 * a1) ==
            "133524312114275664899926313757566191470823300027804201");

    Integer a3("-2"), a4("2");
    for (int i = 0; i < 11; ++i) {
      a3 *= a4;
    }
    REQUIRE(a3 == -4096);
    Integer b2(-1);
    REQUIRE(a3 * b2 == 4096);
  }

  {
    Integer a1("44444444444444444444"), a2("2");
    REQUIRE(std::string(a1 / a2) == "22222222222222222222");
    Integer b1("1000000000000000000000000000000"), b2("2");
    REQUIRE(std::string(b1 / b2) == "500000000000000000000000000000");

    Integer c1("9223372036854775809"), c2(-2);
    REQUIRE(c1 / c2 == -4611686018427387904);

    Integer d1(200000000000000), d2(123456789);
    for (int i = 0; i < 10; ++i) {
      d1 *= d2;
    }
    Integer d3(
        "2002020202003290329930290392039209093029032930920392842022222222222222"
        "22222222222222222222222");
    Integer res(d1 / d3);

    REQUIRE(res == 821);

    Integer e1(123456789), e2(1234567899876765);
    for (int i = 0; i < 3; ++i) {
      e1 *= e2;
    }
    Integer e3(2282828282828282);
    Integer res2 = e1 / e3;
    REQUIRE(std::string(res2) == "101762243845125996630920367070138659751");

    Integer f1("-284783274979342409832480932840932"),
        f2("-42749837568324800112222222222"), res3(f1 / f2);
    REQUIRE(res3 == 6661);

    Integer g1(
        "1234567899876543223456665432345678987654321234567890987654321345678998"
        "76545454543255222");
    Integer g2(
        "-222222222222222222222222222222222222222222222222222222222222222222222"
        "2222222222222");
    Integer res4(g1 / g2);
    REQUIRE(res4 == -55555);

    Integer h1(
        "-498884848498298492847875967632597302583284073265326471082148021746976"
        "219571048009820184");
    Integer h2("1222887");
    h1 /= h2;
    REQUIRE(std::string(h1) ==
            "-40795662109278984309087917986911080302863966438871823077859853097"
            "3815421679229568");
  }

  {
    Integer a1(234422), b1(2);
    REQUIRE(a1 % b1 == 0);

    Integer a2(2324241), b2(2);
    REQUIRE(a2 % b2 == 1);

    Integer a3("123456"), b3("12345");
    REQUIRE(a3 % b3 == 6);

    Integer a4("12345"), b4("123456");
    REQUIRE(a4 % b4 == 12345);

    Integer a5("123456789123456789123456789"),
        b5("123456789123456789123467891234789");
    REQUIRE(std::string(a5 % b5) == "123456789123456789123456789");

    Integer a6("2312421421432131"), b6("4213213");
    REQUIRE(a6 % b6 == 1460182);

    Integer a7("1232422422"), b7(2);
    a7 %= b7;
    REQUIRE(a7 == 0);
  }
}

TEST_CASE("Comparators") {
  {
    Integer a1(1), b1(2);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == false);
    REQUIRE((a1 > b1) == false);
    REQUIRE((a1 <= b1) == true);
    REQUIRE((a1 < b1) == true);
  }

  {
    Integer a1(2), b1(1);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == true);
    REQUIRE((a1 > b1) == true);
    REQUIRE((a1 <= b1) == false);
    REQUIRE((a1 < b1) == false);
  }

  {
    Integer a1(-1), b1(2);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == false);
    REQUIRE((a1 > b1) == false);
    REQUIRE((a1 <= b1) == true);
    REQUIRE((a1 < b1) == true);
  }

  {
    Integer a1(2), b1(-1);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == true);
    REQUIRE((a1 > b1) == true);
    REQUIRE((a1 <= b1) == false);
    REQUIRE((a1 < b1) == false);
  }

  {
    Integer a1(-1), b1(-2);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == true);
    REQUIRE((a1 > b1) == true);
    REQUIRE((a1 <= b1) == false);
    REQUIRE((a1 < b1) == false);
  }

  {
    Integer a1(LLONG_MIN), b1(LLONG_MIN + 1);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == false);
    REQUIRE((a1 > b1) == false);
    REQUIRE((a1 <= b1) == true);
    REQUIRE((a1 < b1) == true);
  }

  {
    Integer a1(-234567892345678), b1(-234567892345678);
    REQUIRE((a1 == b1) == true);
    REQUIRE((a1 != b1) == false);
    REQUIRE((a1 >= b1) == true);
    REQUIRE((a1 > b1) == false);
    REQUIRE((a1 <= b1) == true);
    REQUIRE((a1 < b1) == false);
  }

  {
    Integer a1(0), b1(1000);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == false);
    REQUIRE((a1 > b1) == false);
    REQUIRE((a1 <= b1) == true);
    REQUIRE((a1 < b1) == true);
  }

  {
    Integer a1(0), b1(-1000);
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == true);
    REQUIRE((a1 > b1) == true);
    REQUIRE((a1 <= b1) == false);
    REQUIRE((a1 < b1) == false);
  }

  {
    Integer a1("123456789123456789123456789123456789");
    Integer b1("123456789123456789123456789");
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == true);
    REQUIRE((a1 > b1) == true);
    REQUIRE((a1 <= b1) == false);
    REQUIRE((a1 < b1) == false);
  }

  {
    Integer a1("-1"), b1("-2");
    REQUIRE((a1 == b1) == false);
    REQUIRE((a1 != b1) == true);
    REQUIRE((a1 >= b1) == true);
    REQUIRE((a1 > b1) == true);
    REQUIRE((a1 <= b1) == false);
    REQUIRE((a1 < b1) == false);
  }
}

TEST_CASE("Conversion to string") {
  Integer a1(12345), a2("12345"), a3(-0), a4(0), a5("0"), a6(-12345),
      a7("-12345"), a8(12345678912345678), a9("123456789123456789123456789"),
      a10("-1234567891234567891234567"), a11("-0");
  REQUIRE(std::string(a1) == "12345");
  REQUIRE(std::string(a2) == "12345");
  REQUIRE(std::string(a3) == "0");
  REQUIRE(std::string(a4) == "0");
  REQUIRE(std::string(a5) == "0");
  REQUIRE(std::string(a6) == "-12345");
  REQUIRE(std::string(a7) == "-12345");
  REQUIRE(std::string(a8) == "12345678912345678");
  REQUIRE(std::string(a9) == "123456789123456789123456789");
  REQUIRE(std::string(a10) == "-1234567891234567891234567");
  REQUIRE(std::string(a11) == "0");
}
