using System;
using System.Collections.Generic;
using System.Linq;
using GestDep.Entities;
using GestDep.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepServicesTest
{
    [TestClass]
    public class AddActivityTest : BaseTest
    {


        [TestMethod]
        public void InvalidDateInterval()
        {  //finishDate is earlier than startDate
            int daysIncement = 1;
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                DateTime.Now, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                DateTime.Now.AddDays(daysIncement), TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for invalid date ranges.");
        }

        [TestMethod]
        public void InvalidStartDate()
        { //start date in the past
            Room  defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                DateTime.Now.AddDays(-1), TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for invalid start date.");
        }

        [TestMethod]
        public void NegativeDurationValue()
        { //start date in the past
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION.Negate(),
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for invalid duration value.");
        }

        [TestMethod]
        public void NoRommIds()
        { //No room ids provided
          

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, null),
                "An exception is not thrown for an empty list of room ids");
        }

        [TestMethod]
        public void RoomIdNoExists()
        { //room id is incorrect
            Room defaultLocalRoom = dal.GetAll<Room>().Last();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id+1);

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for invalid room ids: the room id provided doen't exist");
        }

        [TestMethod]
        public void PriceNegative()
        { 
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            double negativePrice = -1; //a negative quantity

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, negativePrice,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for negative price");
        }

        [TestMethod]
        public void MinEnrollmentNegative()
        { //room id is incorrect
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            int negativeMinEnroll = -1; //a negative quantity

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, negativeMinEnroll, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for negative minimumEnrollments");
        }


        [TestMethod]
        public void MaxEnrollmentNegative()
        {
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            int negativeMaxEnroll = -1; //a negative quantity

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, negativeMaxEnroll, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for negative minimumEnrollments");
        }
        [TestMethod]
        public void WrongEnrollmentInterval()
        { //min>max  --> values exchanged in the call
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);


            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown for a wrong enrollment interval: minimum > maximum");
        }

        [TestMethod]
        public void NoneActivityDays()
        { //We pass None as Days
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);


            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(Days.None, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                "An exception is not thrown when wrong Days value is provided: None");
        }
       
        [TestMethod]
        public void RoomAlreadyInUsePersisted()
        {  //We add an activity which uses defaultLocalRoom
            Room defaultLocalRoom = dal.GetAll<Room>().First();
           
            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();


            //We try to add other activity, for the same days and times, using the same room
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                     TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                    TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                    "An exception is not thrown when the room is not available.");
          
        }
        [TestMethod]
        public void RoomAlreadyInUse()
        {  //We add an activity which uses defaultLocalRoom
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);
            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
           
            //without persist in the database

            //We try to add other activity, for the same days and times, using the same room
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                     TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                    TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                    "An exception is not thrown when the room is not available. You retrieve the info only from the database, and not from the classes");

        }
        [TestMethod]
        public void RoomAlreadyInUseOneDayPersisted()
        {  //We add an activity which uses defaultLocalRoom on thursday
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(Days.Thu, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();


            //We try to add other activity, for the same days and times, using the same room on tuesdays and thursdays
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);
            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                     TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                    TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                    "An exception is not thrown when the room is not available.");

        }
        [TestMethod]
        public void OneRoomAlreadyInUse()
        {  //We add an activity which uses two rooms, and only one is used
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();


            //We try to add other activity, for the same days and times, using the same room 
            ICollection<int> defaultRoomIds = new List<int>();
            
            defaultRoomIds.Add(dal.GetAll<Room>().Last().Id); //uses one free room
            defaultRoomIds.Add(defaultLocalRoom.Id);//room  used

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                     TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                    TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                    "An exception is not thrown when one room is not available.");

        }

        [TestMethod]
        public void RoomAlreadyInUsePartial()
        { /**
                 [  previous ]
            [ new    ]
             ***/
            int daysDiference = -2;
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();

            //We try to add other activity, for the same days and times, using the same room on tuesdays and thursdays
            ICollection<int> defaultRoomIds = new List<int>();

            defaultRoomIds.Add(dal.GetAll<Room>().Last().Id); //uses one free room
            defaultRoomIds.Add(defaultLocalRoom.Id);//room  used

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                     TestData.EXPECTED_ACTIVITY_FINISH_DATE.AddDays(daysDiference), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                    TestData.EXPECTED_ACTIVITY_START_DATE.AddDays(daysDiference), TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                    "An exception is not thrown when one room is not available.");

        }
        [TestMethod]
        public void RoomAlreadyInUsePartial2()
        { /**
             [  previous ]
                    [ new    ]
             ***/
            int daysDiference = 2;
            Room defaultLocalRoom = dal.GetAll<Room>().First();

            Activity previous_activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR);

            previous_activity.Rooms.Add(defaultLocalRoom);
            defaultLocalRoom.Activities.Add(previous_activity);
            gestDepService.gym.Activities.Add(previous_activity);
            dal.Commit();

            //We try to add other activity, for the same days and times, using the same room on tuesdays and thursdays
            ICollection<int> defaultRoomIds = new List<int>();

            defaultRoomIds.Add(dal.GetAll<Room>().Last().Id); //uses one free room
            defaultRoomIds.Add(defaultLocalRoom.Id);//room  used

            Assert.ThrowsException<ServiceException>(() => gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                     TestData.EXPECTED_ACTIVITY_FINISH_DATE.AddDays(daysDiference), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                    TestData.EXPECTED_ACTIVITY_START_DATE.AddDays(daysDiference), TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds),
                    "An exception is not thrown when one room is not available.");

        }


        //Action of a duration==0 allowed
        

        [TestMethod]
        public void ValidData()
        {
            Room defaultLocalRoom = dal.GetAll<Room>().First();
            ICollection<int> defaultRoomIds = new List<int>();
            defaultRoomIds.Add(defaultLocalRoom.Id);

            try
            {
                gestDepService.AddNewActivity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                TestData.EXPECTED_ACTIVITY_FINISH_DATE, TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                TestData.EXPECTED_ACTIVITY_START_DATE, TestData.EXPECTED_ACTIVITY_START_HOUR, defaultRoomIds); //uses first and last 
                //Assert section
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT,gestDepService.gym.Activities.Count(),"The activity is not added to the collecion of activities of the gym  ");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, gestDepService.gym.Activities.First().Rooms.Count, "The room  is not added to the rooms collection of the activity");
                Assert.AreEqual(defaultLocalRoom.Id, gestDepService.gym.Activities.First().Rooms.First().Id, "The room  is not added to the rooms collection of the activity");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, gestDepService.gym.Activities.First().Rooms.First().Activities.Count, "The activity was not added to the activities collection of the room");
                Assert.AreEqual(gestDepService.gym.Activities.First().Id, gestDepService.gym.Activities.First().Rooms.First().Activities.Last().Id, "The activity was not added to the activities collection of the room");
                //Persists 
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, dal.GetAll<Activity>().Count(),  "The activity is not in the databasse");
                Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, dal.GetAll<Gym>().First().Activities.Count, "The activity is not associatedd to the gym in the databasse");

            }
            catch (Exception serv)
            {
                Assert.Fail("An exception was thrown when none was expected: " + serv.Message);
            }
        }

    }
}
