using System;
using System.Collections.Generic;
using GestDep.Entities;
using GestDep.Services;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepServicesTest
{
    [TestClass]
    public class AssignInstructorToActivityTest : BaseTest
    {
        [TestMethod]
        public void NegativeActivityId()
        {
            int incorrectActivityId = -1;
            Instructor instructor = dal.GetAll<Instructor>().First();

            Assert.ThrowsException<ServiceException>(() => gestDepService.AssignInstructorToActivity(incorrectActivityId, instructor.Id),
                 "An exception is not thrown when wrong ActivityId value is provided");
        }
        [TestMethod]
        public void IncorrectActivityId()
        {
            int incorrectActivityId = 1; //There are not avtivities in the system.
            Instructor instructor = dal.GetAll<Instructor>().First();
            Assert.ThrowsException<ServiceException>(() => gestDepService.AssignInstructorToActivity(incorrectActivityId, instructor.Id),
                          "An exception is not thrown when wrong ActivityId value is provided");
        }
        [TestMethod]
        public void IncorrectID()
        {
            string incorrectInstructorId = "incorrect";
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit(); //assigns the id to the activity

            Assert.ThrowsException<ServiceException>(() => gestDepService.AssignInstructorToActivity(firstActivity.Id, incorrectInstructorId),
              "An exception is not thrown when wrong InstructorId value is provided");
        }
        [TestMethod]
        public void InstructorNotExists()
        {
            string incorrectInstructorId = "11112111Y";
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
              TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
              TestData.EXPECTED_ACTIVITY_START_HOUR);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit(); //assigns the id to the activity

            Assert.ThrowsException<ServiceException>(() => gestDepService.AssignInstructorToActivity(firstActivity.Id, incorrectInstructorId),
              "An exception is not thrown when wrong InstructorId value is provided");
        }
        [TestMethod]
        public void InstructorNotAvailable()
        {
            int daysIncement = 2;
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
                TestData.EXPECTED_ACTIVITY_START_HOUR);
            //the activity has one instructor

            Instructor instructor = dal.GetAll<Instructor>().First();
            firstActivity.Instructor = instructor;
            instructor.Activities.Add(firstActivity);
          
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
           
            Activity secondActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
               TestData.EXPECTED_ACTIVITY_FINISH_DATE.AddDays(-daysIncement), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
               TestData.EXPECTED_ACTIVITY_START_DATE.AddDays(daysIncement), TestData.EXPECTED_ACTIVITY_START_HOUR);
            gestDepService.gym.Activities.Add(secondActivity);

            dal.Commit();

            Assert.ThrowsException<ServiceException>(() => gestDepService.AssignInstructorToActivity(secondActivity.Id, instructor.Id),
            "An exception is not thrown when a not available instructor is provided");
        }

        [TestMethod]
        public void ValidData()
        {
            Instructor instructor = dal.GetAll<Instructor>().First();
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
            TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
            TestData.EXPECTED_ACTIVITY_START_HOUR);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit(); //Assigns the id to the activity
            try
            { 
                gestDepService.AssignInstructorToActivity(firstActivity.Id, instructor.Id);
                //asserts
                Instructor instructorDal = dal.GetById<Instructor>(instructor.Id);
                Activity activityDal = dal.GetById<Activity>(firstActivity.Id);
                Assert.AreEqual(instructor.Id, activityDal.Instructor.Id, "The instructor is not assigned to the activity");
                Assert.AreEqual(firstActivity.Id, instructorDal.Activities.First().Id,"The activity is not assigned to the instructor");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }


        }
        [TestMethod]
        public void ValidDataLogic()
        {
            Instructor instructor = dal.GetAll<Instructor>().First();
            Activity firstActivity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
            TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE, TestData.EXPECTED_ACTIVITY_START_DATE,
            TestData.EXPECTED_ACTIVITY_START_HOUR);
            gestDepService.gym.Activities.Add(firstActivity);
            //persists
            dal.Commit(); //Assigns the id to the activity
            try
            {
                gestDepService.AssignInstructorToActivity(firstActivity.Id, instructor.Id);
                //asserts: checks if model is consistent
                Instructor instructorLogic= gestDepService.cityHall.People.Where(person => person.Id==instructor.Id).FirstOrDefault() as Instructor;
                Assert.IsNotNull(instructorLogic, "Instructor deleted from the system");

                Activity activityLogic = gestDepService.gym.Activities.Where(activity => activity.Id == firstActivity.Id).FirstOrDefault();
                Assert.AreEqual(instructor.Id, activityLogic.Instructor.Id, "The instructor is not assigned to the activity of the gym");
                Assert.AreEqual(firstActivity.Id, instructorLogic.Activities.First().Id, "The activity is not assigned to the instructo of the gymr");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }


        }
    }
}
