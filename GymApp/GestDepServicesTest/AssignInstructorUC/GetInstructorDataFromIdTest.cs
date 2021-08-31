using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Services;
using System.Collections.Generic;
using GestDep.Entities;
using System.Linq;


namespace GestDepServicesTest
{
    [TestClass]
    public class GetInstructorDataFromIdTest: BaseTest
    {
        [TestMethod]
        public void IncorrectID()
        {
            string incorrectInstructorId = "incorrect";
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetInstructorDataFromId(incorrectInstructorId, out string instructorAddress,out string instructorIBAN,
                out string instructorName, out int instructorZipcode,out string instructorSsn, out ICollection<int> instructorActivitiesIds),               
                "An exception is not thrown when wrong instructor Id value is provided");
        }

        [TestMethod]
        public void InstructorNoExist()
        {
            string incorrectInstructorId = "11112111Y";
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetInstructorDataFromId(incorrectInstructorId, out string instructorAddress, out string instructorIBAN,
                out string instructorName, out int instructorZipcode, out string instructorSsn, out ICollection<int> instructorActivitiesIds),
                "An exception is not thrown when the instructor doesn't exist");
        }
        [TestMethod]
        public void InstructorWithoutActivities()
        {
            //No activities
            Instructor instructor = dal.GetAll<Instructor>().First();
            try
            {
                gestDepService.GetInstructorDataFromId(instructor.Id, out string instructorAddress, out string instructorIBAN,
                     out string instructorName, out int instructorZipcode, out string instructorSsn, out ICollection<int> instructorActivitiesIds);
                //Asserts
                Assert.AreEqual(instructor.Address, instructorAddress, "Instructor data has not been properly retrieved: wrong Address ");
                Assert.AreEqual(instructor.IBAN, instructorIBAN, "Instructor data has not been properly retrieved: wrong IBAN ");
                Assert.AreEqual(instructor.Name, instructorName, "Instructor data has not been properly retrieved: wrong Name ");
                Assert.AreEqual(instructor.ZipCode, instructorZipcode, "Instructor data has not been properly retrieved: wrong ZipCode ");
                Assert.AreEqual(instructor.Ssn, instructorSsn, "Instructor data has not been properly retrieved: wrong Snn ");
                Assert.IsNotNull(instructorActivitiesIds, "Instructor data has not been properly retrieved: activitiesIds must be an empty list");
                Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, instructorActivitiesIds.Count, "Instructor data has not been properly retrieved: activitiesIds is not empty");


            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }


        }
        [TestMethod]
        public void InstructorHasActitvies()
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
                gestDepService.GetInstructorDataFromId(instructor.Id, out string instructorAddress, out string instructorIBAN,
                     out string instructorName, out int instructorZipcode, out string instructorSsn, out ICollection<int> instructorActivitiesIds);
                //Asserts
                Assert.AreEqual(instructor.Address, instructorAddress, "Instructor data has not been properly retrieved: wrong Address ");
                Assert.AreEqual(instructor.IBAN, instructorIBAN, "Instructor data has not been properly retrieved: wrong IBAN ");
                Assert.AreEqual(instructor.Name, instructorName, "Instructor data has not been properly retrieved: wrong Name ");
                Assert.AreEqual(instructor.ZipCode, instructorZipcode, "Instructor data has not been properly retrieved: wrong ZipCode ");
                Assert.AreEqual(instructor.Ssn, instructorSsn, "Instructor data has not been properly retrieved: wrong Snn ");
                Assert.IsNotNull(instructorActivitiesIds, "Instructor data has not been properly retrieved: activitiesIds must contain one element");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, instructorActivitiesIds.Count, "Intructor data has not been properly retrieved: activitiesIds must contain one element");
                Assert.AreEqual(firstActivity.Id, instructorActivitiesIds.First(), "Instructor data has not been properly retrieved: wrong activitiesIds");
            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

    }
}
