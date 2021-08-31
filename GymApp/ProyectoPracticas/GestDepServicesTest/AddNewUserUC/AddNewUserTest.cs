using System;
using System.Collections.Generic;
using System.Linq;
using GestDep.Entities;
using GestDep.Persistence;
using GestDep.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepServicesTest
{
    [TestClass]
    public class AddNewUserTest : BaseTest
    {
               

        [TestMethod]
        public void InvalidAddress()
        {
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser("", TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[0], TestData.EXPECTED_PERSON_NAME, 
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED), 
                "An exception was not thrown if the address was empty.");
        }
        [TestMethod]
        public void InvalidIban()
        {
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, "", TestData.DISTINCT_IDS[1], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the IBAN was empty.");
        }

        [TestMethod]
        public void InvalidIdEmpty()
        {
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, "", TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the Id was empty.");
        }

        [TestMethod]
        public void InvalidIdMoreDigits()
        {
            string invalidID = "111121111Y"; //10 digits
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, invalidID, TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the Id has more than 9 dgits.");
        }
        [TestMethod]
        public void InvalidIdLessDigits()
        {
            string invalidID = "1111211Y"; //8 digits
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, invalidID, TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the Id is less than 9 digits.");
        }
        [TestMethod]
        public void InvalidIdNoLetter()
        {
            string invalidID = "111121111"; //9 digits without letter
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, invalidID, TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the Id was empty.");
        }

        [TestMethod]
        public void InvalidName()
        {
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[2], "",
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the name was empty.");
        }

        [TestMethod]
        public void InvalidZipCode()
        {
            int invalidZipcode = 0;
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[3], TestData.EXPECTED_PERSON_NAME,
                invalidZipcode, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the Zip Code was equal to 0");
            
        }
        [TestMethod]
        public void NegativeZipCode()
        {
            int invalidZipcode = -1;
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[3], TestData.EXPECTED_PERSON_NAME,
                invalidZipcode, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the Zip Code is lower than 0");
           
        }
        [TestMethod]
        public void InvalidBirthDate()
        {
            int daysIncrement = 1;
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[3], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, DateTime.Now.AddDays(daysIncrement), TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown if the birthdate was in the future.");
        }
        [TestMethod]
        public void UserAlreadyExists()
        {
            User localUser = new User(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[3], TestData.EXPECTED_PERSON_NAME,
            TestData.EXPECTED_PERSON_ZIP_CODE, DateTime.Now.AddYears(-TestData.LEGAL_AGE), TestData.EXPECTED_USER_RETIRED);
            gestDepService.cityHall.People.Add(localUser);            
            dal.Commit();

           
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[3], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, DateTime.Now.AddYears(-TestData.LEGAL_AGE), TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown when a person with this Id already exists.");
        }
        [TestMethod]
        public void InstructorAlreadyExists()
        {
            Instructor localInstructor = new Instructor(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[5], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_SSN);
            gestDepService.cityHall.People.Add(localInstructor);
            dal.Commit();
           
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[5], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, DateTime.Now.AddYears(-TestData.LEGAL_AGE), TestData.EXPECTED_USER_RETIRED),
                "An exception was not thrown when a person with this Id already exists.");
        }
        [TestMethod]
        public void AddLegalAgeUser()
        {
            
            try
            {   DateTime birthdate = DateTime.Now.AddYears(-TestData.LEGAL_AGE);
                gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[6], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, birthdate, TestData.EXPECTED_USER_RETIRED);
                //Asserts
                User userdal = dal.GetById<User>(TestData.DISTINCT_IDS[6]);
                Assert.IsNotNull(userdal, "User not added to database");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ADDRESS, userdal.Address, "User is not well stored  in the database: wrong address");
                Assert.AreEqual(TestData.EXPECTED_PERSON_IBAN, userdal.IBAN, "User is not well stored  in the database: wrong Iban");
                Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, userdal.Name, "User is not well stored  in the database: wrong name");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ZIP_CODE, userdal.ZipCode, "User is not well stored  in the database: wrong zipcode");
                Assert.AreEqual(birthdate, userdal.BirthDate, "User is not well stored  in the database: wrong birthdate");
                Assert.AreEqual(TestData.EXPECTED_USER_RETIRED, userdal.Retired, "User is not well stored  in the database: wrong retired");
            }
            catch (ServiceException serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);
            }
        }

        [TestMethod]
        public void AddLegalAgeUserOnlyLogic()
        {
           try
            {
                DateTime birthdate = DateTime.Now.AddYears(-TestData.LEGAL_AGE);
                gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[6], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, birthdate, TestData.EXPECTED_USER_RETIRED);
                //Asserts
                User userLogic = gestDepService.cityHall.People.Where(person => person.Id == TestData.DISTINCT_IDS[6]).FirstOrDefault() as User;



                Assert.IsNotNull(userLogic, "User not added to the CityHall");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ADDRESS, userLogic.Address, "User is not well stored  in the CityHall: wrong address");
                Assert.AreEqual(TestData.EXPECTED_PERSON_IBAN, userLogic.IBAN, "User is not well stored  in the CityHall: wrong Iban");
                Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, userLogic.Name, "User is not well stored  in the CityHall: wrong name");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ZIP_CODE, userLogic.ZipCode, "User is not well stored  in the CityHall: wrong zipcode");
                Assert.AreEqual(birthdate, userLogic.BirthDate, "User is not well stored  in the CityHall: wrong birthdate");
                Assert.AreEqual(TestData.EXPECTED_USER_RETIRED, userLogic.Retired, "User is not well stored  in the CityHall: wrong retired");
            }
            catch (ServiceException serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);
            }
        }

        [TestMethod]
        public void AddBabyUser()
        {
            int daysIncrement = 1;
            DateTime birthdate = DateTime.Now.AddYears(-daysIncrement);
            try
            {
              
                gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[7], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, birthdate, TestData.EXPECTED_USER_RETIRED);
                //Asserts
                User userdal = dal.GetById<User>(TestData.DISTINCT_IDS[7]);
                Assert.IsNotNull(userdal, "User not added to database");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ADDRESS, userdal.Address, "User is not well stored  in the database: wrong address");
                Assert.AreEqual(TestData.EXPECTED_PERSON_IBAN, userdal.IBAN, "User is not well stored  in the database: wrong Iban");
                Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, userdal.Name, "User is not well stored  in the database: wrong name");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ZIP_CODE, userdal.ZipCode, "User is not well stored  in the database: wrong zipcode");
                Assert.AreEqual(birthdate, userdal.BirthDate, "User is not well stored  in the database: wrong birthdate");
                Assert.AreEqual(TestData.EXPECTED_USER_RETIRED, userdal.Retired, "User is not well stored  in the database: wrong retired");

            }
            catch (ServiceException serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);
            }
        }
        [TestMethod]
        public void AddRetiredUser()
        {
           
            try
            {
                DateTime birthdate = DateTime.Now.AddYears(-TestData.RETIRED_AGE);

                   gestDepService.AddNewUser(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.DISTINCT_IDS[8], TestData.EXPECTED_PERSON_NAME,
                TestData.EXPECTED_PERSON_ZIP_CODE, birthdate, TestData.EXPECTED_USER_IS_RETIRED);
                //Asserts
                User userdal = dal.GetById<User>(TestData.DISTINCT_IDS[8]);
                Assert.IsNotNull(userdal, "User not added to database");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ADDRESS, userdal.Address, "User is not well stored  in the database: wrong address");
                Assert.AreEqual(TestData.EXPECTED_PERSON_IBAN, userdal.IBAN, "User is not well stored  in the database: wrong Iban");
                Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, userdal.Name, "User is not well stored  in the database: wrong name");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ZIP_CODE, userdal.ZipCode, "User is not well stored  in the database: wrong zipcode");
                Assert.AreEqual(birthdate, userdal.BirthDate, "User is not well stored  in the database: wrong birthdate");
                Assert.AreEqual(TestData.EXPECTED_USER_IS_RETIRED, userdal.Retired, "User is not well stored  in the database: wrong retired");

            }
            catch (ServiceException serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);
            }
        }
    }
}
