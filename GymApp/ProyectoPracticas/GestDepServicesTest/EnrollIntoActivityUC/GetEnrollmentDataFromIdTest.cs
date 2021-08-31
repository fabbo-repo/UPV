using GestDep.Entities;
using GestDep.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetEnrollmentDataFromIdTest : BaseTest
    {
        [TestMethod]
        public void NegativeActivityId()
        {
            int incorrectActivityId = -1;
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
               TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
               TestData.EXPECTED_ACTIVITY_START_HOUR);

            //The activity uses one room
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            firstActivity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(firstActivity);

            //The actvity has one enrollment
            User user = new User(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED);
            Payment payment = new Payment(TestData.EXPECTED_PAYMENT_DATE, TestData.EXPECTED_PAYMENT_DESCRIPCION, TestData.EXPECTED_PAYMENT_QUANTITY);
            Enrollment enrollment = new Enrollment(TestData.EXPECTED_ENROLLMENT_DATE, firstActivity, payment, user);
            user.Enrollments.Add(enrollment);
            firstActivity.Enrollments.Add(enrollment);
            gestDepService.gym.Activities.Add(firstActivity);

            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);

            //persists
            dal.Commit(); //new object have ids

            Assert.ThrowsException<ServiceException>(() => gestDepService.GetEnrollmentDataFromIds(incorrectActivityId, enrollment.Id, out DateTime? cancellationDate, out DateTime enrollmentDate,
                out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds,
                out string userId), "An exception is not thrown when wrong ActivityId value is provided");

        }
        [TestMethod]
        public void ActivityDoesntExist()
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
            user.Enrollments.Add(enrollment);
            firstActivity.Enrollments.Add(enrollment);

            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);

            //persists
            dal.Commit();

            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetEnrollmentDataFromIds(firstActivity.Id+1, enrollment.Id, out DateTime? cancellationDate, out DateTime enrollmentDate,
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds,
            out string userId),
            "An exception is not thrown when the activity doesn't exist.");
        }

        [TestMethod]
        public void EnrollmentDoesntExist()
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
            user.Enrollments.Add(enrollment);
            firstActivity.Enrollments.Add(enrollment);

            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);

            //persists
            dal.Commit();

            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetEnrollmentDataFromIds(firstActivity.Id, enrollment.Id+1, out DateTime? cancellationDate, out DateTime enrollmentDate,
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds,
            out string userId),
            "An exception is not thrown when the enrollment doesn't exist.");
        }
        [TestMethod]
        public void NegativeEnrollmenActivityId()
        {
            int negativeEnrollmentId = -1;
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

            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetEnrollmentDataFromIds(firstActivity.Id, negativeEnrollmentId, out DateTime? cancellationDate, out DateTime enrollmentDate,
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds,
            out string userId),
            "An exception is not thrown when the enrollmentid isnegative");
        }

        [TestMethod]
        public void ValidData()
        {
            int EXPECTED_PAYMENTS_COUNT = 1;
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

            //Asserts
            gestDepService.GetEnrollmentDataFromIds(firstActivity.Id, enrollment.Id, out DateTime? cancellationDate, out DateTime enrollmentDate,
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds,
            out string userId);

            Assert.AreEqual(enrollment.CancellationDate, cancellationDate, "Enrollment data has not been properly retrieved: the cancellation date is wrong");
            Assert.AreEqual(enrollment.EnrollmentDate, enrollmentDate, "Enrollment data has not been properly retrieved: enrollment date is wrong");
            Assert.AreEqual(enrollment.ReturnedFirstCuotaIfCancelledActivity, returnedFirstCuotaIfCancelledActivity, "Enrollment data has not been properly retrieved: ReturnedFirstCuotaIfCancelledActivity is wrong");
            Assert.IsNotNull(enrollment.User, "Enrollment data has not been properly retrieved: the user should not be null.");
            Assert.AreEqual(enrollment.User.Id, userId, "Enrollment data has not been properly retrieved: the user id is wrong");
            Assert.IsNotNull(paymentIds, "Enrollment data has not been properly retrieved: enrollmentIds must be an empty list");
            Assert.AreEqual(EXPECTED_PAYMENTS_COUNT, paymentIds.Count, "Enrollment data has not been properly retrieved: paymentIds doesn't have the expected number of elements.");
            Assert.AreEqual(payment.Id, paymentIds.First(), "The payment id doesn't match the expected one.");
        }
    }
}
