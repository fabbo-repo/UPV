using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Entities;

namespace GestDepLogicDesignTest
{
    [TestClass]
    public class GymTest
    {
        [TestMethod]
        public void NoParametersConstructor()
        {
            Gym gym = new Gym();
            Assert.AreNotSame(null, gym, "There must be a constructor without parameters");
            Assert.IsNotNull(gym.Activities, "The collection of Activites was not intialized properly.\nPatch the problem by adding:  Activities = new List<Activity>();");
            Assert.IsNotNull(gym.Rooms, "The collection of Rooms was not intialized properly.\nPatch the problem by adding:  Rooms = new List<Room>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, gym.Activities.Count, "The collection of Activites was not intialized properly.\n You have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, gym.Rooms.Count, "The collection of Rooms was not intialized properly.\n You have added an extra element");
        }
        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Gym gym = new Gym(TestData.EXPECTED_GYM_CLOSING_HOUR, TestData.EXPECTED_GYM_DISCOUNT_LOCAL, TestData.EXPECTED_GYM_DISCOUNT_RETIRED,
                TestData.EXPECTED_GYM_FREE_USER_PRICE, TestData.EXPECTED_GYM_NAME, TestData.EXPECTED_GYM_OPENING_HOUR, 
                TestData.EXPECTED_GYM_ZIP_CODE);
            Assert.AreEqual(TestData.EXPECTED_GYM_CLOSING_HOUR, gym.ClosingHour, "ClosingHour was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_GYM_DISCOUNT_LOCAL, gym.DiscountLocal, "DiscountLocal was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_GYM_DISCOUNT_RETIRED, gym.DiscountRetired, "DiscountRetired was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_GYM_FREE_USER_PRICE, gym.FreeUserPrice, "FreeUserPrice was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_GYM_NAME, gym.Name, "Name was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_GYM_OPENING_HOUR, gym.OpeningHour, "OpeningHour was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.EXPECTED_GYM_ZIP_CODE, gym.ZipCode, "ZipCode was not intialized properly. Check the order of the parameters and the assignment.");

            Assert.IsNotNull(gym.Activities, "The collection of Activites was not intialized properly.\nPatch the problem by adding:  Activities = new List<Activity>();");
            Assert.IsNotNull(gym.Rooms, "The collection of Rooms was not intialized properly.\nPatch the problem by adding:  Rooms = new List<Room>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, gym.Activities.Count, "The collection of Activites was not intialized properly.\n You have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, gym.Rooms.Count, "The collection of Rooms was not intialized properly.\n You have added an extra element");


        }
    }
}
