using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Services;
using System.Collections.Generic;
using GestDep.Entities;
using System.Linq;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetRoomDataFromIdTest: BaseTest
    {
        [TestMethod]
        public void NegativeRoomId()
        {
            int incorrectRoomId = -1;
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetRoomDataFromId(incorrectRoomId,out int roomNumber, out ICollection<int> roomActivityIds),
                "An exception is not thrown when wrong roomId value is provided");
        }

        [TestMethod]
        public void IncorrectRoomId()
        {
            int incorrectRoomId = dal.GetAll<Room>().Last().Id + 1;
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetRoomDataFromId(incorrectRoomId, out int roomNumber, out ICollection<int> roomActivityIds),
                "An exception is not thrown when wrong roomId value is provided");
        }
        [TestMethod]
        public void ExistingRoomIdPersisted() 
        {
            //We add an activity which uses defaultLocalRoom
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();

            gestDepService.GetRoomDataFromId(defaultLocalRoom.Id, out int roomNumber, out ICollection<int> roomActivityIds);

            //Assert
            Assert.AreEqual(defaultLocalRoom.Number, roomNumber, "The room values are not well recovered. Room number incorrect. ");
            Assert.AreEqual(defaultLocalRoom.Activities.Count, roomActivityIds.Count, "The room values are not well recovered.ActivityIds incorrect. ");

        }
        [TestMethod]
        public void ExistingRoomId()
        {
            //We add an activity which uses defaultLocalRoom
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            
            //No persisted
            gestDepService.GetRoomDataFromId(defaultLocalRoom.Id, out int roomNumber, out ICollection<int> roomActivityIds);

            //Assert
            Assert.AreEqual(defaultLocalRoom.Number, roomNumber, "The room values are not well recovered. Room number incorrect. Do you recover the data from the DAL? ");
            Assert.AreEqual(defaultLocalRoom.Activities.Count, roomActivityIds.Count, "The room values are not well recovered.ActivityIds incorrect. Do you recover the data from the DAL? ");

        }

    }
}
