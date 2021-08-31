using GestDep.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetAllRunningOrFutureActivitiesIds : BaseTest
    {
        private DateTime ONE_YEAR_AGO = DateTime.Now.AddYears(-1);
        private DateTime SIX_MONTHS_AGO = DateTime.Now.AddMonths(-6);
        private DateTime IN_SIX_MONTHS = DateTime.Now.AddMonths(6);
        private DateTime IN_ONE_YEAR = DateTime.Now.AddYears(1);
        [TestMethod]
        public void AllPastActivities()
        {
            try
            {
               
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                SIX_MONTHS_AGO, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                //Second activity
                Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                SIX_MONTHS_AGO, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                gestDepService.gym.Activities.Add(activity);
                gestDepService.gym.Activities.Add(activity2);
                
                //persist
                dal.Commit();

                ICollection<int> activitiesIds = gestDepService.GetAllRunningOrFutureActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should just be empty.");
                Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, activitiesIds.Count, "The list of activities should be empty.");

            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

        [TestMethod]
        public void OnePastOneCurrent()
        {
            try
            {
                
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_SIX_MONTHS, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                //Second activity
                Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                SIX_MONTHS_AGO, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                gestDepService.gym.Activities.Add(activity);
                gestDepService.gym.Activities.Add(activity2);

                //persist
                dal.Commit();

                ICollection<int> activitiesIds = gestDepService.GetAllRunningOrFutureActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should have one element.");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, activitiesIds.Count, "The list of activities should have one element, "+activitiesIds.Count+" found.");
                Assert.AreEqual(activity.Id, activitiesIds.First(), "The ids don't match.");
            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

        [TestMethod]
        public void AllCurrent()
        {
            try
            {
                int EXPECTED_ACTIVITIES = 2;
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_SIX_MONTHS, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                //Second activity
                Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_SIX_MONTHS, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                gestDepService.gym.Activities.Add(activity);
                gestDepService.gym.Activities.Add(activity2);

                //persist
                dal.Commit();

                ICollection<int> activitiesIds = gestDepService.GetAllRunningOrFutureActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should have two elements.");
                Assert.AreEqual(EXPECTED_ACTIVITIES, activitiesIds.Count, "The list of activities should have two elements, " + activitiesIds.Count + " found.");
                Assert.IsTrue(activity.Id == activitiesIds.First() || activity.Id == activitiesIds.Last(), "The ids don't match.");
                Assert.IsTrue(activity2.Id == activitiesIds.First() || activity2.Id == activitiesIds.Last(), "The ids don't match.");
            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

        [TestMethod]
        public void OneCurrentOneFuture()
        {
            try
            {
                int EXPECTED_ACTIVITIES = 2;
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_SIX_MONTHS, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                //Second activity
                Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_ONE_YEAR, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                IN_SIX_MONTHS, TestData.EXPECTED_ACTIVITY_START_HOUR);
                gestDepService.gym.Activities.Add(activity);
                gestDepService.gym.Activities.Add(activity2);

                //persist
                dal.Commit();

                ICollection<int> activitiesIds = gestDepService.GetAllRunningOrFutureActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should have two elements.");
                Assert.AreEqual(EXPECTED_ACTIVITIES, activitiesIds.Count, "The list of activities should have two elements, " + activitiesIds.Count + " found.");
                Assert.IsTrue(activity.Id == activitiesIds.First() || activity.Id == activitiesIds.Last(), "The ids don't match.");
                Assert.IsTrue(activity2.Id == activitiesIds.First() || activity2.Id == activitiesIds.Last(), "The ids don't match.");

            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

        [TestMethod]
        public void AllFuture()
        {
            try
            {
                int EXPECTED_ACTIVITIES = 2;
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_ONE_YEAR, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                IN_SIX_MONTHS, TestData.EXPECTED_ACTIVITY_START_HOUR);
                //Second activity
                Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_ONE_YEAR, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                IN_SIX_MONTHS, TestData.EXPECTED_ACTIVITY_START_HOUR);
                gestDepService.gym.Activities.Add(activity);
                gestDepService.gym.Activities.Add(activity2);

                //persist
                dal.Commit();

                ICollection<int> activitiesIds = gestDepService.GetAllRunningOrFutureActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should have two elements.");
                Assert.AreEqual(EXPECTED_ACTIVITIES, activitiesIds.Count, "The list of activities should have two elements, " + activitiesIds.Count + " found.");
                Assert.IsTrue(activity.Id == activitiesIds.First() || activity.Id == activitiesIds.Last(), "The ids don't match.");
                Assert.IsTrue(activity2.Id == activitiesIds.First() || activity2.Id == activitiesIds.Last(), "The ids don't match.");
            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

        [TestMethod]
        public void OnePastOneFuture()
        {
            try
            {
                
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                SIX_MONTHS_AGO, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                ONE_YEAR_AGO, TestData.EXPECTED_ACTIVITY_START_HOUR);
                //Second activity
                Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                IN_ONE_YEAR, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                IN_SIX_MONTHS, TestData.EXPECTED_ACTIVITY_START_HOUR);
                gestDepService.gym.Activities.Add(activity);
                gestDepService.gym.Activities.Add(activity2);

                //persist
                dal.Commit();

                ICollection<int> activitiesIds = gestDepService.GetAllRunningOrFutureActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should have one element.");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, activitiesIds.Count, "The list of activities should have one element, " + activitiesIds.Count + " found.");
                Assert.AreEqual(activity2.Id, activitiesIds.First(), "The ids don't match.");
            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }
    }
}
