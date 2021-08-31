using System;
using System.Collections;
using System.Collections.Generic;
using GestDep.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepServicesTest
{
    public class TestData
    {
        //GENERIC
        public const int EXPECTED_EMPTY_LIST_COUNT = 0;
        public const int EXPECTED_ONE_ELEMENT_LIST_COUNT = 1;

        //PERSON
        public const string EXPECTED_PERSON_ID = "94814560G";
        public const string EXPECTED_PERSON_ADDRESS = "Camí de Vera";
        public const string EXPECTED_PERSON_NAME = "Nom de prova";
        public const string EXPECTED_PERSON_IBAN = "ES6621000418401234567891";
        public const int EXPECTED_PERSON_ZIP_CODE = 46021;
        public static string[] DISTINCT_IDS = { "11112111Y", "11112112F", "11112113P", "11112114D", "11112115X", "11112116B", "11112117N", "11112118J", "11112119Z" };
        public const int LEGAL_AGE = 18;
        public const int RETIRED_AGE = 67;

        //USER
        public static DateTime EXPECTED_USER_BIRTHDATE = new Date​Time(2000, 07, 27);
        public const bool EXPECTED_USER_RETIRED = false;
        public const bool EXPECTED_USER_IS_RETIRED = true;

        //INSTRUCTOR
        public const string EXPECTED_SSN = "ES10292421";

        //ACTIVITY
        public const Days EXPECTED_ACTIVITY_DAYS = Days.Tue | Days.Thu;
        public const string EXPECTED_ACTIVITY_DESCRIPTION = "Spinning class";
        public static TimeSpan EXPECTED_ACTIVITY_DURATION = TimeSpan.FromMinutes(60);
        public static DateTime EXPECTED_ACTIVITY_START_DATE = DateTime.Now.AddDays(1); //tomorrow
        public static DateTime EXPECTED_ACTIVITY_FINISH_DATE = DateTime.Now.AddDays(90); //90 days from now
        public static DateTime EXPECTED_ACTIVITY_START_HOUR = DateTime.Parse("10:00:00");
        public const int EXPECTED_MAX_ENROLLMENTS = 15;
        public const int EXPECTED_MIN_ENROLLMENTS = 5;
        public const double EXPECTED_ACTIVITY_PRICE = 1.0;     


        //ENROLLMENT
        public static DateTime EXPECTED_ENROLLMENT_DATE = DateTime.Now; //now

        //PAYMENT
        public static DateTime EXPECTED_PAYMENT_DATE = DateTime.Now; //now
        public const string EXPECTED_PAYMENT_DESCRIPCION = "Spinning class enrollment payment";
        public const double EXPECTED_PAYMENT_QUANTITY = 1.0;
       
    }
}
