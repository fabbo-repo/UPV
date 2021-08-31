using GestDep.Entities;
using GestDep.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Linq;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetPaymentDataFromIdTest : BaseTest
    {

        [TestMethod]
        public void NegativePayment()
        {
            int incorrectId = -1;
            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetPaymentDataFromId(incorrectId, out DateTime date, out string description,
            out double quantity),
            "An exception is not thrown when the payment id is not valid.");
        }
        [TestMethod]
        public void PaymentDoesntExist()
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
            gestDepService.cityHall.Payments.Add(payment);

            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit();

            //Asserts
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetPaymentDataFromId(payment.Id+1, out DateTime date, out string description,
            out double quantity),
            "An exception is not thrown when the payment doesn't exist.");
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
            try { 
            //Asserts
             gestDepService.GetPaymentDataFromId(payment.Id, out DateTime date, out string description,
            out double quantity);

                Assert.AreEqual(payment.Date, date, "Payment data has not been properly retrieved: the date is wrong");
                Assert.AreEqual(payment.Description, description, "Payment data has not been properly retrieved: description is wrong");
                Assert.AreEqual(payment.Quantity, quantity, "Payment data has not been properly retrieved: the quantity is wrong");
           }
             catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }
    }
}
