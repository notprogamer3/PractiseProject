//
// Created by rdast on 31.05.2024.
//'
#define BOOST_TEST_MODULE MyProjectTest
#include <boost/test/included/unit_test.hpp>
#include "../src/Deposit.h"


BOOST_AUTO_TEST_SUITE(SetupUiTestSuite)

BOOST_AUTO_TEST_CASE(test_deposit_getters_and_setters)
{
    std::string test_login = "test_login";
    std::string test_name_surname = "test_name_surname";
    std::string test_phone = "test_phone";
    std::string test_email = "test_email";
    std::string test_type = "test_type";
    int test_time_in_months = 12;
    int test_amount = 1000;
    int test_percent = 5;
    int test_income = 50;

    Deposit deposit(test_login, test_name_surname, test_phone, test_email, test_type, test_time_in_months, test_amount, test_percent);

    BOOST_CHECK_EQUAL(deposit.getLogin(), test_login);
    BOOST_CHECK_EQUAL(deposit.getName_Surname(), test_name_surname);
    BOOST_CHECK_EQUAL(deposit.getPhone(), test_phone);
    BOOST_CHECK_EQUAL(deposit.getEmail(), test_email);
    BOOST_CHECK_EQUAL(deposit.getType(), test_type);
    BOOST_CHECK_EQUAL(deposit.getTimeInMonths(), test_time_in_months);
    BOOST_CHECK_EQUAL(deposit.getAmount(), test_amount);
    BOOST_CHECK_EQUAL(deposit.getPercent(), test_percent);
    BOOST_CHECK_EQUAL(deposit.getIncome(), test_income);
}

BOOST_AUTO_TEST_SUITE_END()