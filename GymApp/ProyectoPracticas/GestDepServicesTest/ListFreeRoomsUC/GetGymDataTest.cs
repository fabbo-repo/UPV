using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Entities;
using GestDep.Services;
using System.Linq;
using System.Collections.Generic;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetGymDataTest : BaseTest
    {
        [TestMethod]
        public void NoGym()
        {
            gestDepService.cityHall.Gyms.Clear();
            gestDepService.gym = null;
            dal.Clear<Gym>();
            dal.Commit();
            //No gym available
            
             Assert.ThrowsException<ServiceException>(() => gestDepService.GetGymData(out int gymId, out DateTime closingHour, out int discountLocal, out int discountRetired, out double freeUserPrice,
                out String name, out DateTime openingHour, out int zipCode, out ICollection<int> activityIds, out ICollection<int> roomIds),
            "An exception is not thrown when the cityHall doesn't have gyms.");

        }
        [TestMethod]
        public void DefaultGym()
        {
            try {
                gestDepService.GetGymData(out int gymId, out DateTime closingHour, out int discountLocal, out int discountRetired, out double freeUserPrice,
                out String name, out DateTime openingHour, out int zipCode, out ICollection<int> activityIds, out ICollection<int> roomIds);

                //Assert
                Assert.AreEqual(gestDepService.gym.Id, gymId, "Gym data is not well retrieved: Id incorrect");
                Assert.AreEqual(gestDepService.gym.ClosingHour, closingHour, "Gym data is not well retrieved: closingHour incorrect");
                Assert.AreEqual(gestDepService.gym.DiscountLocal, discountLocal, "Gym data is not well retrieved: discountLocal incorrect");
                Assert.AreEqual(gestDepService.gym.DiscountRetired, discountRetired, "Gym data is not well retrieved: discountRetired incorrect");
                Assert.AreEqual(gestDepService.gym.FreeUserPrice, freeUserPrice, "Gym data is not well retrieved: freeUserPrice incorrect");
                Assert.AreEqual(gestDepService.gym.Name, name, "Gym data is not well retrieved: name incorrect");
                Assert.AreEqual(gestDepService.gym.OpeningHour, openingHour, "Gym data is not well retrieved: openingHour incorrect");
                Assert.AreEqual(gestDepService.gym.ZipCode, zipCode, "Gym data is not well retrieved: zipCode incorrect");
                Assert.AreEqual(gestDepService.gym.Activities.Count, activityIds.Count, "Gym data is not well retrieved: activityIds incorrect");
                Assert.AreEqual(gestDepService.gym.Rooms.Count, roomIds.Count, "Gym data is not well retrieved: roomIds incorrect");
            }

            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

        [TestMethod]
        public void HasActivitiesGym()
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

                //the activity has one instructor
                Instructor instructor = dal.GetAll<Instructor>().First();
                firstActivity.Instructor = instructor;
                instructor.Activities.Add(firstActivity);
                gestDepService.gym.Activities.Add(firstActivity);
                //persists
                dal.Commit();


                gestDepService.GetGymData(out int gymId, out DateTime closingHour, out int discountLocal, out int discountRetired, out double freeUserPrice,
                out String name, out DateTime openingHour, out int zipCode, out ICollection<int> activityIds, out ICollection<int> roomIds);

                //Assert
                Assert.AreEqual(gestDepService.gym.Id, gymId, "Gym data is not well retrieved: Id incorrect");
                Assert.AreEqual(gestDepService.gym.ClosingHour, closingHour, "Gym data is not well retrieved: closingHour incorrect");
                Assert.AreEqual(gestDepService.gym.DiscountLocal, discountLocal, "Gym data is not well retrieved: discountLocal incorrect");
                Assert.AreEqual(gestDepService.gym.DiscountRetired, discountRetired, "Gym data is not well retrieved: discountRetired incorrect");
                Assert.AreEqual(gestDepService.gym.FreeUserPrice, freeUserPrice, "Gym data is not well retrieved: freeUserPrice incorrect");
                Assert.AreEqual(gestDepService.gym.Name, name, "Gym data is not well retrieved: name incorrect");
                Assert.AreEqual(gestDepService.gym.OpeningHour, openingHour, "Gym data is not well retrieved: openingHour incorrect");
                Assert.AreEqual(gestDepService.gym.ZipCode, zipCode, "Gym data is not well retrieved: zipCode incorrect");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, activityIds.Count, "Gym data is not well retrieved: activityIds incorrect");
                Assert.AreEqual(gestDepService.gym.Rooms.Count, roomIds.Count, "Gym data is not well retrieved: roomIds incorrect");
            }

            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

    }
}
