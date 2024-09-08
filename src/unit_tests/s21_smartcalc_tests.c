#include "s21_smartcalc_test.h"
#define EPS 1e-6

START_TEST(test_1) {
  char src[100] = "2^acos(1.2/2)/tan(3*1)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = -13.340957;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_2) {
  char src[100] = "4+4";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 8;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_3) {
  char src[100] = "111+0.555";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 111.555;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_4) {
  char src[100] = "log(-5)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = NAN;
  ck_assert_msg(isnan(res) && isnan(real_result), "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_5) {
  char src[100] = "-(-2)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 2;
  ck_assert_msg(res == real_result, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_6) {
  char src[100] = "cos(15mod3)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 1;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_7) {
  char src[100] = "sqrt(ln(10))";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 1.517427;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_8) {
  char src[100] = "atan(10)+sin(15)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 2.121416;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_9) {
  char src[100] = "asin(0.4)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 0.4115170;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_10) {
  char src[100] = "5-30*(-10)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 305;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_11) {
  char src[100] = "-(o(i(a(10.01)asdd*n(2))/10m2))^q(5)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  ck_assert_double_eq(res, 0.0);
  ck_assert_int_eq(result, INVALID_MATH_E);
}
END_TEST

START_TEST(test_12) {
  char src[100] = ")(sss(2)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  ck_assert_double_eq(res, 0.0);
  ck_assert_int_eq(result, INVALID_MATH_E);
}
END_TEST

START_TEST(test_13) {
  char src[100] = ".+ttt)";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  ck_assert_double_eq(res, 0.0);
  ck_assert_int_eq(result, INVALID_MATH_E);
}
END_TEST

START_TEST(test_14) {
  char src[100] = "2^2^2";
  double res = 0.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 16.0;
  ck_assert_double_eq(res, real_result);
  ck_assert_int_eq(result, OK);
}

START_TEST(test_15) {
  char src[100] = "+4";
  double res = 4.0;
  int result = s21_from_qt_calculator(src, 0, &res);
  double real_result = 4;
  ck_assert_msg(fabs(res - real_result) <= EPS, "fail");
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_16) {
  int res = OK;
  char *str = "4.0/2";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_17) {
  int res = OK;
  char *str = "*";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_18) {
  int res = OK;
  char *str =
      "3535353153113333333399000000000000000000000033333333333333333322"
      "2222222222222222222222222222222221111111999999313513131313131999"
      "93434343434343434399999999999999999993333333333333333333333333*"
      "3422222222222222222222222222222222222222222222222222222222222222"
      "22222222222222222222222222222222222222222222222222222";
  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, MORE_THAN_255);
}
END_TEST

START_TEST(test_19) {
  int res = OK;
  char *str = "7/0";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(test_20) {
  int res = OK;
  char *str = "7/2^";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_21) {
  int res = OK;
  char *str = "()";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_22) {
  int res = OK;
  char *str = "(3-)";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_23) {
  int res = OK;
  char *str = "3)+(-2";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_24) {
  int res = OK;
  char *str = "cos(cos(cos(cos(1))))";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_25) {
  int res = OK;
  char *str = "ln((sin(81^2))^2+(cos(3^8))^2)";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_26) {
  int res = OK;
  char *str = ")(";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_27) {
  int res = OK;
  char *str = "mog(342)";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_28) {
  int res = OK;
  char *str = "log(342)";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_29) {
  int res = OK;
  char *str = "log(342";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_30) {
  int res = OK;
  char *str = "3/atan342)";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_31) {
  int res = OK;
  char *str = "3/sin(342";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_32) {
  int res = OK;
  char *str = "cos(sin(tan(acos(asin(sqrt(atan(ln(log(1)))))))))";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_33) {
  int res = OK;
  char *str = "cos(sin(matan(acos(asin(sqrt(atan(ln(log(1)))))))))";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_34) {
  int res = OK;
  char *str = "+6";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_35) {
  int res = OK;
  char *str = "+-1";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

START_TEST(test_36) {
  int res = OK;
  char *str = "";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, EMPTY_MATH_E);
}
END_TEST

START_TEST(test_37) {
  int res = OK;
  char *str = "5+mod36565";

  res = s21_str_is_valid(str);
  ck_assert_int_eq(res, INVALID_MATH_E);
}
END_TEST

Suite *suite_calc_test() {
  Suite *s = suite_create("s21_str_parser");
  TCase *tc = tcase_create("s21_str_parser_test");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);
  tcase_add_test(tc, test_22);
  tcase_add_test(tc, test_23);
  tcase_add_test(tc, test_24);
  tcase_add_test(tc, test_25);
  tcase_add_test(tc, test_26);
  tcase_add_test(tc, test_27);
  tcase_add_test(tc, test_28);
  tcase_add_test(tc, test_29);
  tcase_add_test(tc, test_30);
  tcase_add_test(tc, test_31);
  tcase_add_test(tc, test_32);
  tcase_add_test(tc, test_33);
  tcase_add_test(tc, test_34);
  tcase_add_test(tc, test_35);
  tcase_add_test(tc, test_36);
  tcase_add_test(tc, test_37);
  suite_add_tcase(s, tc);
  return s;
}
