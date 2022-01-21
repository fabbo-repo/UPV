using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Services;
using System.Collections.Generic;
using GestDep.Entities;
using System.Linq;


namespace GestDepServicesTest
{
    [TestClass]
    public class GetUserDataFromIdTest: BaseTest
    {
        [TestMethod]
        public void IncorrectID()
        {
            string incorrectUserId = "incorrect";
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetUserDataFromId(incorrectUserId, out string userAddress,out string userIBAN,
                out string userName, out int userZipcode, out DateTime userBirthDate, out bool retired, out ICollection<int> enrollmentIds),               
                "An exception is not thrown when wrong user Id value is provided");
        }

        [TestMethod]
        public void UserDoesntExist()
        {
            string incorrectUserId = "11112111Y";
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetUserDataFromId(incorrectUserId, out string userAddress, out string userIBAN,
                out string userName, out int userZipcode, out DateTime userBirthDate, out bool retired, out ICollection<int> enrollmentIds),
                "An exception is not thrown when the user doesn't exist");
        }
        [TestMethod]
        public void UserWithoutEnrollments()
        {
            User user = new User(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_ZIP_CODE,
                TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED);
            gestDepService.cityHall.People.Add(user);
            dal.Commit();
            //No activities
            try
            {
                gestDepService.GetUserDataFromId(TestData.EXPECTED_PERSON_ID, out string userAddress, out string userIBAN,
                     out string userName, out int userZipcode, out DateTime userBirthDate, out bool retired, out ICollection<int> enrollmentIds);
                //Asserts
                Assert.AreEqual(TestData.EXPECTED_PERSON_ADDRESS, userAddress, "User data has not been properly retrieved: Address is wrong");
                Assert.AreEqual(TestData.EXPECTED_PERSON_IBAN, userIBAN, "User data has not been properly retrieved: IBAN is wrong");
                Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, userName, "User data has not been properly retrieved: Name is wrong");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ZIP_CODE, userZipcode, "User data has not been properly retrieved: ZipCode is wrong");
                Assert.AreEqual(TestData.EXPECTED_USER_BIRTHDATE, userBirthDate, "User data has not been properly retrieved: the birthdate is wrong");
                Assert.AreEqual(TestData.EXPECTED_USER_RETIRED, retired, "User data has not been properly retrieved: the retired attribute is wrong");
                Assert.IsNotNull(enrollmentIds, "User data has not been properly retrieved: enrollmentIds must be an empty list");
                Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, enrollmentIds.Count, "User data has not been properly retrieved: enrollmentIds is not empty");


            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

        [TestMethod]
        public void UserWithEnrollments()
        {
            
            User user = new User(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_ZIP_CODE,
                TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED);
            gestDepService.cityHall.People.Add(user);
            
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //The activity uses one room
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            firstActivity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(firstActivity);
            //The actvity has one enrollment
            Payment payment = new Payment(TestData.EXPECTED_PAYMENT_DATE, TestData.EXPECTED_PAYMENT_DESCRIPCION, TestData.EXPECTED_PAYMENT_QUANTITY);
            Enrollment enrollment = new Enrollment(TestData.EXPECTED_ENROLLMENT_DATE, firstActivity, payment, user);
            firstActivity.Enrollments.Add(enrollment);
            user.Enrollments.Add(enrollment);
            gestDepService.cityHall.Payments.Add(payment);
            
            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit();
           
            try
            {
                gestDepService.GetUserDataFromId(TestData.EXPECTED_PERSON_ID, out string userAddress, out string userIBAN,
                     out string userName, out int userZipcode, out DateTime userBirthDate, out bool retired, out ICollection<int> enrollmentIds);
                //Asserts
                Assert.AreEqual(TestData.EXPECTED_PERSON_ADDRESS, userAddress, "User data has not been properly retrieved: Address is wrong");
                Assert.AreEqual(TestData.EXPECTED_PERSON_IBAN, userIBAN, "User data has not been properly retrieved: IBAN is wrong");
                Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, userName, "User data has not been properly retrieved: Name is wrong");
                Assert.AreEqual(TestData.EXPECTED_PERSON_ZIP_CODE, userZipcode, "User data has not been properly retrieved: ZipCode is wrong");
                Assert.AreEqual(TestData.EXPECTED_USER_BIRTHDATE, userBirthDate, "User data has not been properly retrieved: the birthdate is wrong");
                Assert.AreEqual(TestData.EXPECTED_USER_RETIRED, retired, "User data has not been properly retrieved: the retired attribute is wrong");
                Assert.IsNotNull(enrollmentIds, "User data has not been properly retrieved: enrollmentIds must be an empty list");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, enrollmentIds.Count, "User data has not been properly retrieved: enrollmentIds doesn't have the expected number of elements.");
            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }
    }
}
