using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Services;
using GestDep.Entities;
using System.Linq;
using System.Collections.Generic;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetAvailableInstructorsIdsTest : BaseTest
    {
        [TestMethod]
        public void InvalidDaysValue()
        {
            //all Istructors are free
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetAvailableInstructorsIds(Days.None, TestData.EXPECTED_ACTIVITY_DURATION,
                  TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR),
                  "An exception is not thrown for invalid days value");
        }

        [TestMethod]
        public void NegativeDurationValue()
        {
            //all Istructors are free
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetAvailableInstructorsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION.Negate(),
                  TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR),
                  "An exception is not thrown for invalid duration value");
        }

        [TestMethod]
        public void InvalidDateInterval()
        {  //all Istructors are free
            //finishDate is earlier than startDate
            int daysIncrement = 1;
            //all Istructors are free
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetAvailableInstructorsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                  DateTime.Today, DateTime.Today.AddDays(daysIncrement), TestData.EXPECTED_ACTIVITY_START_HOUR),
                  "An exception is not thrown for invalid date ranges");
        }
        [TestMethod]
        public void DateIntervalInPast()
        {  //finishDate  and  startDate are in the past
            int daysInPast = -10;
            int daysDuration = 2;
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetAvailableInstructorsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                  DateTime.Today.AddDays(daysInPast + daysDuration), DateTime.Today.AddDays(daysInPast), TestData.EXPECTED_ACTIVITY_START_HOUR)
                 , "An exception is not thrown for invalid date ranges: it is in the past.");

        }

        [TestMethod]
        public void OneInstructorNotAvailablePersisted()
        {
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //the activity has one instructor

            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit();

            try
            {
                ICollection<string> instructorIds = gestDepService.GetAvailableInstructorsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
                int freeInstructorsCount = dal.GetAll<Instructor>().Count() - 1;
                //Assert section
                Assert.IsNotNull(instructorIds, "List of available instructors incorrect");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Count, "List of available instructors incorrect");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Where(instructorId => instructorId != instructor.Id).Count(), "List of available instructors incorrect");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }

        }

        [TestMethod]
        public void OneInstructorNotAvailable()
        {
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //the activity has one instructor

            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);
           

            try
            {
                ICollection<string> instructorIds = gestDepService.GetAvailableInstructorsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
                int freeInstructorsCount = dal.GetAll<Instructor>().Count() - 1;
                //Assert section
                Assert.IsNotNull(instructorIds, "List of available instructors incorrect. Do you get the info from dal?");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Count, "List of available instructors incorrect. Do you get the info from dal?");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Where(instructorId => instructorId != instructor.Id).Count(), "List of available instructors incorrect. Do you get the info from dal?");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }

        }

        [TestMethod]
        public void TwoInstructorsNotAvailablePersisted()
        {
           
            int daysIncrement = 2;
            int instructorsNotAvailable = 2;

            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                 TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                 TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);


            Activity secondActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE.AddDays(-daysIncrement), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE.AddDays(daysIncrement), TestData.EXPECTED_ACTIVITY_START_HOUR);
            //the activity has one instructor
            Instructor instructor2 = dal.GetAll<Instructor>().Last();
            secondActivity.Instructor = instructor2;
            instructor2.Activities.Add(secondActivity);
            gestDepService.gym.Activities.Add(secondActivity);

            //persists
            dal.Commit();
            try
            {
                ICollection<string> instructorIds = gestDepService.GetAvailableInstructorsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
                int freeInstructorsCount = dal.GetAll<Instructor>().Count() - instructorsNotAvailable;
                //Assert section
                Assert.IsNotNull(instructorIds, "List of available instructors incorrect");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Count, "List of available instructors incorrect");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Where(instructorId => (instructorId != instructor.Id) && (instructorId != instructor2.Id)).Count(), "List of available instructors incorrect");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }
        }
        [TestMethod]
        public void TwoInstructorsNotAvailable()
        {

            int daysIncrement = 2;
            int instructorsNotAvailable = 2;

            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                 TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                 TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            //the activity has one instructor
            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
            gestDepService.gym.Activities.Add(firstActivity);


            Activity secondActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE.AddDays(-daysIncrement), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE.AddDays(daysIncrement), TestData.EXPECTED_ACTIVITY_START_HOUR);
            //the activity has one instructor
            Instructor instructor2 = dal.GetAll<Instructor>().Last();
            secondActivity.Instructor = instructor2;
            instructor2.Activities.Add(secondActivity);
            gestDepService.gym.Activities.Add(secondActivity);

         
            try
            {
                ICollection<string> instructorIds = gestDepService.GetAvailableInstructorsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
                int freeInstructorsCount = dal.GetAll<Instructor>().Count() - instructorsNotAvailable;
                //Assert section
                Assert.IsNotNull(instructorIds, "List of available instructors incorrect. Do you get the info from dal?");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Count, "List of available instructors incorrect. Do you get the info from dal?");
                Assert.AreEqual(freeInstructorsCount, instructorIds.Where(instructorId => (instructorId != instructor.Id) && (instructorId != instructor2.Id)).Count(), "List of available instructors incorrect. Do you get the info from dal?");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }
        }
    }
}
