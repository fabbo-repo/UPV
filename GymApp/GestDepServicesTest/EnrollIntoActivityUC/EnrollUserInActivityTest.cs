using GestDep.Entities;
using GestDep.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Linq;

namespace GestDepServicesTest
{
    [TestClass]
    public class EnrollUserInActivityTest : BaseTest
    {
        [TestMethod]
        public void NegativeActivityId()
        {
            User user = new User(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_ZIP_CODE,
                TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED);
            gestDepService.cityHall.People.Add(user);
            dal.Commit();
            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.EnrollUserInActivity(-1, user.Id),
                "An exception was not thrown when the activity id has a negative value.");
        }
        [TestMethod]
        public void InvalidUserId()
        {
            string INVALID_USER_ID = "ERROR";
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //The activity uses one room
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            firstActivity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(firstActivity);

            //the activity has one instructor

            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit();
            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.EnrollUserInActivity(firstActivity.Id, INVALID_USER_ID),
                "An exception was not thrown when the user id has an invalid value.");
        }
        [TestMethod]
        public void EmptyUsedId()
        {
            string INVALID_USER_ID = "";
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //The activity uses one room
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            firstActivity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(firstActivity);

            //the activity has one instructor

            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit();
            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.EnrollUserInActivity(firstActivity.Id, INVALID_USER_ID),
                "An exception was not thrown when the user id has an invalid value.");
        }
        [TestMethod]
        public void ActivityDoesntExist()
        {
            User user = new User(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_ZIP_CODE,
                TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED);
            gestDepService.cityHall.People.Add(user);
            dal.Commit();
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //The activity uses one room
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            firstActivity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(firstActivity);

            //the activity has one instructor

            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit();
            Assert.ThrowsException<ServiceException>(() => gestDepService.EnrollUserInActivity(firstActivity.Id+1, user.Id),
                "An exception was not thrown when the user doesn't exist.");
        }
        [TestMethod]
        public void UserDoesntExist()
        {
            string INCORRECT_DNI = "11112111Y";
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //The activity uses one room
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            firstActivity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(firstActivity);

            //the activity has one instructor

            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit();
            Assert.ThrowsException<ServiceException>(() => gestDepService.EnrollUserInActivity(firstActivity.Id, INCORRECT_DNI), 
                "An exception was not thrown when the user doesn't exist.");               
        }
        [TestMethod]
        public void UserAlreadyInActivity()
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


            Assert.ThrowsException<ServiceException>(() => gestDepService.EnrollUserInActivity(firstActivity.Id, user.Id),
            "An exception is not thrown when the user is already enrolled in the activity.");
        }
        [TestMethod]
        public void ValidData()
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
            
            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);

            //persists
            dal.Commit();

            try
            {
                int enrollmentId = gestDepService.EnrollUserInActivity(firstActivity.Id, user.Id);
                Enrollment enrommentDal = dal.GetAll<Enrollment>().First();
                Assert.AreEqual(enrommentDal.Id, enrollmentId, "The enrollmentId is not returned or not properly stored in the DB.");
                Assert.AreEqual(firstActivity.Enrollments.Last().Id, enrollmentId, "The enrollment is not added to the list of the activity.");
                Assert.AreEqual(user.Enrollments.Last().Id, enrollmentId, "The enrollment is not added to the list of the activity.");
                Enrollment enrollment = user.Enrollments.Last();
                Assert.AreEqual(enrollment.Payments.First().Id, gestDepService.cityHall.Payments.Last().Id, "The payment is not added to the necessary collections.");
              

            } catch(Exception e)
            {
                Assert.Fail("An exception was thrown when none was expected. Message: " + e.Message);
            }
        }
    }
}
