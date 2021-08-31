using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Services;
using GestDep.Entities;
using System.Linq;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetAllActivitiesIdsTest : BaseTest
    {
        [TestMethod]
        public void OneActivity()
        {
            try
            {
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
               
                gestDepService.gym.Activities.Add(activity);             

                //persist
                dal.Commit();
             
                ICollection<int> activitiesIds = gestDepService.GetAllActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should contain one element.");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, activitiesIds.Count, "The list of activities is empty and it should contain one element");
                Assert.AreEqual(activity.Id, activitiesIds.First(), "The list of activities doesn't contain the activity Id inserted");

            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }


        }
        [TestMethod]
        public void TwoActivities()
        {
            try
            {
                //First Activity
                Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
                //Second activity
                Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
                gestDepService.gym.Activities.Add(activity);
                gestDepService.gym.Activities.Add(activity2);

                //persist
                dal.Commit();

                ICollection<int> activitiesIds = gestDepService.GetAllActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should contain two elements.");
                Assert.AreEqual(gestDepService.gym.Activities.Count, activitiesIds.Count, "The list of activities should contain two elements");
                Assert.AreEqual(activity.Id, activitiesIds.First(), "The list of activities doesn't contain the activity Id inserted");

            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }


        }
        [TestMethod]
        public void NoActivities()
        {
            try
            {
                ICollection<int> activitiesIds = gestDepService.GetAllActivitiesIds();
                Assert.IsNotNull(activitiesIds, "The list of activities is null, and it should be empty");
                Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, activitiesIds.Count, "The list of activities should be empty");
            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }
    }
}
