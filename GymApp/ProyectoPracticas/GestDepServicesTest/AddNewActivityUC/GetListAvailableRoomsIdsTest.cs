using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Services;
using GestDep.Entities;
using System.Linq;
using System.Collections.Generic;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetListAvailableRoomsIdsTest : BaseTest
    {
        [TestMethod]
        public void InvalideDaysValue()
        {
            //All  rooms are free ->9
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetListAvailableRoomsIds(GestDep.Entities.Days.None, TestData.EXPECTED_ACTIVITY_DURATION,
                  TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR)
                 , "An exception is not thrown for invalid days value");
        }
        [TestMethod]
        public void NegativeDurationValue()
        {
            //All  rooms are free ->9
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetListAvailableRoomsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION.Negate(),
                  TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR)
                 , "An exception is not thrown for invalid duration value");
        }
        //Action of a duration==0 allowed
        [TestMethod]
        public void InvalidDateInterval()
        {  //finishDate is earlier than startDate
            int daysIncement = 1;
            //All  rooms are free ->9
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetListAvailableRoomsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                  DateTime.Today, DateTime.Today.AddDays(daysIncement), TestData.EXPECTED_ACTIVITY_START_HOUR)
                 , "An exception is not thrown for invalid date ranges.");
        }
        [TestMethod]
        public void DateIntervalInPast()
        {  //finishDate  and  startDate are in the past
            int daysInPast = -10;
            int daysDuration = 2;
            //All  rooms are free ->9
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetListAvailableRoomsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                  DateTime.Today.AddDays(daysInPast+ daysDuration), DateTime.Today.AddDays(daysInPast), TestData.EXPECTED_ACTIVITY_START_HOUR)
                 , "An exception is not thrown for invalid date ranges: it is in the past.");
        }
        [TestMethod]
        public void RoomInUsePersisted()
        {  //We add an activity which uses defaultLocalRoom
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();
            try
            {
                ICollection<int> roomdIds = gestDepService.GetListAvailableRoomsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

                int freeRoomsCount = dal.GetAll<Room>().Count() - 1;
                //Assert section
                Assert.IsNotNull(roomdIds, "List of available rooms incorrect.");
                Assert.AreEqual(freeRoomsCount, roomdIds.Count, "List of available rooms incorrect.");
                //the used rrom is not in the list
                Assert.AreEqual(freeRoomsCount,roomdIds.Where(roomId => roomId != defaultLocalRoom.Id).Count(), "List of available rooms incorrect.") ;
            }catch(Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }


        }
        [TestMethod]
        public void RoomInUse()
        {  //We add an activity which uses defaultLocalRoom.
           //no persists in the database: if students get the info from the dal, this test will fail
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
                      
            
            try
            {
                ICollection<int> roomdIds = gestDepService.GetListAvailableRoomsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

                int freeRoomsCount = dal.GetAll<Room>().Count() - 1;
                //Assert section
                Assert.IsNotNull(roomdIds, "List of available rooms incorrect. Do you get the info from dal?");
                Assert.AreEqual(freeRoomsCount, roomdIds.Count, "List of available rooms incorrect. Do you get the info from dal?");
                //the used rrom is not in the list
                Assert.AreEqual(freeRoomsCount, roomdIds.Where(roomId => roomId != defaultLocalRoom.Id).Count(), "List of available rooms incorrect. Do you get the info from dal?");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }

        }
        [TestMethod]
        public void RoomsInUsePersisted()
        {  //We add two activity which uses two different rooms. On activity is done in an interval included in the other
            Room firstLocalRoom = dal.GetAll<Room>().First();
            Room secondLocalRoom = dal.GetAll<Room>().Last();
            int daysIncement = 2;
            int roomsInUse = 2;

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity.Rooms.Add(firstLocalRoom);
            firstLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);

            Activity previous_activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE.AddDays(-daysIncement), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE.AddDays(daysIncement), TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity2.Rooms.Add(secondLocalRoom);
            secondLocalRoom.Activities.Add(previous_activity2);
            gestDepService.gym.Activities.Add(previous_activity2);

            //persist
            dal.Commit();

            try
            {
                ICollection<int> roomdIds = gestDepService.GetListAvailableRoomsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

                int freeRoomsCount = dal.GetAll<Room>().Count() - roomsInUse;
                //Assert section
                Assert.AreEqual(freeRoomsCount, roomdIds.Count, "List of available rooms incorrect.");
                //the used rooms are not in the list
                Assert.AreEqual(freeRoomsCount, roomdIds.Where(roomId => (roomId != firstLocalRoom.Id) && (roomId != secondLocalRoom.Id)).Count(), "List of available rooms incorrect.");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }


        }
        [TestMethod]
        public void RoomsInUse()
        {  //We add two activity which uses two different rooms. On activity is done in an interval included in the other
           //no persists in the database: if students get the info from the dal, this test will fail
            Room firstLocalRoom = dal.GetAll<Room>().First();
            Room secondLocalRoom = dal.GetAll<Room>().Last();
            int daysIncement = 2;
            int roomsInUse = 2;

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity.Rooms.Add(firstLocalRoom);
            firstLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);

            Activity previous_activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE.AddDays(-daysIncement), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE.AddDays(daysIncement), TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity2.Rooms.Add(secondLocalRoom);
            secondLocalRoom.Activities.Add(previous_activity2);
            gestDepService.gym.Activities.Add(previous_activity2);


            try
            {
                ICollection<int> roomdIds = gestDepService.GetListAvailableRoomsIds(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

                int freeRoomsCount = dal.GetAll<Room>().Count() - roomsInUse;
                //Assert section
                Assert.AreEqual(freeRoomsCount, roomdIds.Count, "List of available rooms incorrect. Do you get the info from dal?");
                //the used rooms are not in the list
                Assert.AreEqual(freeRoomsCount, roomdIds.Where(roomId => (roomId != firstLocalRoom.Id) && (roomId != secondLocalRoom.Id)).Count(), "List of available rooms incorrect. Do you get the info from dal?");
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }


        }
        [TestMethod]
        public void RoomInUseDifferentDay()
        {  //We add an activity which uses defaultLocalRoom
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();
            try
            {   //In a different Day
                ICollection<int> roomdIds = gestDepService.GetListAvailableRoomsIds(Days.Fri, TestData.EXPECTED_ACTIVITY_DURATION,
                    TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

                int freeRoomsCount = dal.GetAll<Room>().Count();
                //Assert section
                //all rooms are free for Friday
                Assert.AreEqual(freeRoomsCount, roomdIds.Count, "List of available rooms incorrect.");
              
            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);

            }


        }

    }
}
