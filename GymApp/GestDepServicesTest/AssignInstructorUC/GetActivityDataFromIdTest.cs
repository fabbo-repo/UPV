using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;
using GestDep.Entities;
using GestDep.Services;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetActivityDataFromIdTest : BaseTest
    {
        [TestMethod]
        public void NegativeActivityId()
        {
            int incorrectActivityId = -1;
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetActivityDataFromId(incorrectActivityId, out Days activityDays, out string description, out TimeSpan duration,
                    out DateTime finishDate, out int maximumEnrollments, out int minimumEnrollments, out double price, out DateTime startDate, out DateTime startHour, out ICollection<int> enrollmentIds,
                    out string instructorId, out ICollection<int> roomIds),
             "An exception is not thrown when wrong ActivityId value is provided");
        }
        [TestMethod]
        public void IncorrectActivityId()
        {
            int incorrectActivityId = 1; //There are not activities in the system.

            Assert.ThrowsException<ServiceException>(() => gestDepService.GetActivityDataFromId(incorrectActivityId, out Days activityDays, out string description, out TimeSpan duration,
                    out DateTime finishDate, out int maximumEnrollments, out int minimumEnrollments, out double price, out DateTime startDate, out DateTime startHour, out ICollection<int> enrollmentIds,
                    out string instructorId, out ICollection<int> roomIds),
             "An exception is not thrown when wrong ActivityId value is provided");
        }

        [TestMethod]
        public void GetActivityByIdTest()
        {
            try
            {
                
                Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
                //The activity uses one room
                Room defaultLocalRoom = dal.GetAll<Room>().First();              
               
                firstActivity.Rooms.Add(defaultLocalRoom);
                defaultLocalRoom.Activities.Add(firstActivity);
                //The actvity has one enrollment
                User user = new User(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_USER_BIRTHDATE, TestData.EXPECTED_USER_RETIRED);
                gestDepService.cityHall.People.Add(user);
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
              
                gestDepService.GetActivityDataFromId(firstActivity.Id, out Days activityDays, out string description, out TimeSpan duration,
                    out DateTime finishDate, out int maximumEnrollments, out int minimumEnrollments, out double price, out DateTime startDate, out DateTime startHour, out ICollection<int> enrollmentIds,
                    out string instructorId, out ICollection<int> roomIds);

                Assert.AreEqual(TestData.EXPECTED_ACTIVITY_DAYS, activityDays, "The days are not the expected values.");
                Assert.AreEqual(TestData.EXPECTED_ACTIVITY_DESCRIPTION, description, "The description is not the expected one.");
                Assert.AreEqual(TestData.EXPECTED_ACTIVITY_DURATION, duration, "The duration is not the expected one.");
                Assert.AreEqual(TestData.EXPECTED_ACTIVITY_FINISH_DATE, finishDate, "The finish date is not the expected one.");
                Assert.AreEqual(TestData.EXPECTED_MAX_ENROLLMENTS, maximumEnrollments, "The maximum enrollment number is not the expected one.");
                Assert.AreEqual(TestData.EXPECTED_MIN_ENROLLMENTS, minimumEnrollments, "The minimum enrollment number is not the expected one.");
                Assert.AreEqual(TestData.EXPECTED_ACTIVITY_PRICE, price, "The price is not the expected one.");
                Assert.AreEqual(TestData.EXPECTED_ACTIVITY_START_DATE, startDate, "The start date is not the expected one.");
                Assert.AreEqual(TestData.EXPECTED_ACTIVITY_START_HOUR, startHour, "The start hour is not the expected one.");
                Assert.IsNotNull(enrollmentIds, "The list of enrollment ids should not be null.");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT,enrollmentIds.Count, "The list of enrollment ids must contain one element");
                Assert.AreEqual(enrollment.Id, enrollmentIds.First(), "The list of enrollment ids must contain the id of the activity enrollment");
                Assert.AreEqual(instructor.Id, instructorId, "The instructor id is incorrect");
                 Assert.IsNotNull(roomIds, "The list of room ids should not be null.");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, roomIds.Count, "The list of rooms ids must contain one element");
                Assert.AreEqual(defaultLocalRoom.Id, roomIds.First(), "The list of rooms ids must contain the id of the room used by the activity");

            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }
    }
}
