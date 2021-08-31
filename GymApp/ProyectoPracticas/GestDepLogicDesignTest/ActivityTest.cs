using System;
using GestDep.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepLogicDesignTest
{
    [TestClass]
    public class ActivityTest
    {
        [TestMethod]
        public void NoParametersConstructor()
        {
            Activity activity = new Activity();
            Assert.AreNotSame(null, activity, "There must be a constructor without parameters");
            Assert.IsNotNull(activity.Enrollments, "The collection of Enrollments was not intialized properly.\nPatch the problem by adding:  Enrollments = new List<Enrollment>();");
            Assert.IsNotNull(activity.Rooms, "The collection of Rooms was not intialized properly.\nPatch the problem by adding:  Rooms = new List<Room>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, activity.Rooms.Count, "The collection of Rooms was not intialized properly.\n You have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, activity.Enrollments.Count, "The collection of Enrollments was not intialized properly.\nYou have added an extra element");
        }
        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            Assert.AreEqual(TestData.EXPECTED_ACTIVITY_DAYS, activity.ActivityDays, "ActivityDays was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_ACTIVITY_DESCRIPTION, activity.Description, "Description was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_ACTIVITY_DURATION, activity.Duration, "Duration was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_ACTIVITY_FINISH_DATE, activity.FinishDate, "FinishDate was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_MAX_ENROLLMENTS, activity.MaximumEnrollments, "MaximumEnrollments was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_MIN_ENROLLMENTS, activity.MinimumEnrollments, "MinimumEnrollments was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_ACTIVITY_PRICE, activity.Price, "Price was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_ACTIVITY_START_DATE, activity.StartDate, "StartDate was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_ACTIVITY_START_HOUR, activity.StartHour, "StartHour was not initialized properly. Check the order of the parameters and the assignment.");
            Assert.IsNotNull(activity.Cancelled, "Cancelled was not intialized properly. Check the order of the parameters and the assignment.");

            Assert.IsNotNull(activity.Enrollments, "The collection of Enrollments was not intialized properly.\nPatch the problem by adding:  Enrollments = new List<Enrollment>();");
            Assert.IsNotNull(activity.Rooms, "The collection of Rooms was not intialized properly.\nPatch the problem by adding:  Rooms = new List<Room>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, activity.Rooms.Count, "The collection of Rooms was not intialized properly.\n You have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, activity.Enrollments.Count, "The collection of Enrollments was not intialized properly.\nYou have added an extra element");


        }
    }
}
