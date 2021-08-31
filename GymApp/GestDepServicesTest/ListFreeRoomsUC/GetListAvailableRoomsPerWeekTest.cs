using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GestDep.Entities;
using GestDep.Services;
using System.Linq;
using System.Collections.Generic;

namespace GestDepServicesTest
{
    [TestClass]
    public class GetListAvailableRoomsPerWeekTest : BaseTest
    {
        private static int daysOfWeek = 7; //Open from Monday to  Sunday
        private int minutesPerSlot = 45; // As UC indicates
        private int minutesHour = 60; //minutes in 1 hour

        [TestMethod]
        public void DayIsNotMonday()
        {
            DateTime notMonday = DateTime.Today;
            if (notMonday.DayOfWeek == DayOfWeek.Monday)
                notMonday = notMonday.AddDays(1); //Tuesday
            Assert.ThrowsException<ServiceException>(() => gestDepService.GetListAvailableRoomsPerWeek(notMonday),
                " An exception is not thrown when the selected Day isn't Monday");

        }
        [TestMethod]
        public void AllAvailable()
        {
            DateTime nextWeekMonday = DateTime.Now.AddDays(7);
            while (nextWeekMonday.DayOfWeek != DayOfWeek.Monday) nextWeekMonday = nextWeekMonday.AddDays(-1);          
            
            int expectedSlots = ((gestDepService.gym.ClosingHour.Hour - gestDepService.gym.OpeningHour.Hour)* minutesHour / minutesPerSlot)*daysOfWeek;
            int roomsCount = gestDepService.gym.Rooms.Count;
            
            try
            {
                Dictionary<DateTime, int> availableRooms = gestDepService.GetListAvailableRoomsPerWeek(nextWeekMonday);
                DateTime firstSlot = new DateTime(nextWeekMonday.Year, nextWeekMonday.Month, nextWeekMonday.Day, gestDepService.gym.OpeningHour.Hour, 0, 0);
                
                Assert.AreEqual(expectedSlots, availableRooms.Count,"The number of the slots of the dictionary is not the expected one. " +
                    "The dictionary must contain the info about the free rooms from Monday to Sunday, from the opening to the cosing time in intervals of 45 minutes");
                while (firstSlot.Hour < (gestDepService.gym.ClosingHour.Hour))
                {
                    DateTime rowSlot = firstSlot;
                    for (int i = 1; i < daysOfWeek; i++)
                    { 
                        Assert.AreEqual(roomsCount, availableRooms[firstSlot], "Icorrect number of free rooms in the slot " + rowSlot);
                        rowSlot.AddDays(i);
                    }
         
                    firstSlot = firstSlot.AddMinutes(45);
                }


            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }

       
        [TestMethod]
        public void TwoActivities()
        {

            Room firstLocalRoom = dal.GetAll<Room>().First();
            Room secondLocalRoom = dal.GetAll<Room>().Last();
            int daysIncrement = 3;
            int daysDuration = 90;
            int roomsCount = dal.GetAll<Room>().Count();
            int roomsUsedTuesday = 1;
            int roomUsedThursday = 2;

            DateTime nextWeekMonday = DateTime.Now.AddDays(7);
            while (nextWeekMonday.DayOfWeek != DayOfWeek.Monday) nextWeekMonday = nextWeekMonday.AddDays(-1);

            

            //45bminutes after opening
            DateTime startHour = new DateTime(nextWeekMonday.AddDays(daysIncrement).Year, nextWeekMonday.AddDays(daysIncrement).Month, nextWeekMonday.AddDays(daysIncrement).Day,
                gestDepService.gym.OpeningHour.Hour, gestDepService.gym.OpeningHour.Minute, gestDepService.gym.OpeningHour.Second);
            startHour = startHour.AddMinutes(minutesPerSlot);

            //Uses tuesdays and thursday, but begins next wednesday..so tuesday is free. 60 minutes (2 slots)
            Activity activity = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                nextWeekMonday.AddDays(daysDuration), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
                nextWeekMonday.AddDays(daysIncrement), startHour);
            activity.Rooms.Add(firstLocalRoom);
            firstLocalRoom.Activities.Add(activity);
            gestDepService.gym.Activities.Add(activity);

            DateTime startHour2 = new DateTime(nextWeekMonday.Year, nextWeekMonday.Month, nextWeekMonday.Day, gestDepService.gym.OpeningHour.Hour, 
                gestDepService.gym.OpeningHour.Minute, gestDepService.gym.OpeningHour.Second);
            startHour2 = startHour2.AddMinutes(minutesPerSlot); 

            //Uses tuesdays and thursday, begins next monday. 60 minutes (2 slots)
            Activity activity2 = new Activity(TestData.EXPECTED_ACTIVITY_DAYS, TestData.EXPECTED_ACTIVITY_DESCRIPTION, TestData.EXPECTED_ACTIVITY_DURATION,
                nextWeekMonday.AddDays(daysDuration), TestData.EXPECTED_MAX_ENROLLMENTS, TestData.EXPECTED_MIN_ENROLLMENTS, TestData.EXPECTED_ACTIVITY_PRICE,
               nextWeekMonday, startHour2);
            activity2.Rooms.Add(secondLocalRoom);
            secondLocalRoom.Activities.Add(activity2);
            gestDepService.gym.Activities.Add(activity2);

            //persist
            dal.Commit();

            try
            {
                Dictionary<DateTime, int> availableRooms = gestDepService.GetListAvailableRoomsPerWeek(nextWeekMonday);

                //asserts
                DateTime firstSlot = new DateTime(nextWeekMonday.Year, nextWeekMonday.Month, nextWeekMonday.Day, gestDepService.gym.OpeningHour.Hour, 0, 0);
                Assert.AreEqual(roomsCount - roomsUsedTuesday, availableRooms[firstSlot.AddDays(1).AddMinutes(minutesPerSlot)], "Wrong table. There is one room used on Tuesday at "+ startHour2.Hour +":" + startHour2.Minute);
                Assert.AreEqual(roomsCount - roomsUsedTuesday, availableRooms[firstSlot.AddDays(1).AddMinutes(minutesPerSlot*2)], "Wrong table. There is one room used on Tuesday at " + startHour2.AddMinutes(minutesPerSlot).Hour + ":" + startHour2.AddMinutes(minutesPerSlot).Minute);
                Assert.AreEqual(roomsCount - roomUsedThursday, availableRooms[firstSlot.AddDays(daysIncrement).AddMinutes(minutesPerSlot)], "Wrong table. There is one room used on Tuesday at " + startHour.Hour + ":" + startHour.Minute);
                Assert.AreEqual(roomsCount - roomUsedThursday, availableRooms[firstSlot.AddDays(daysIncrement).AddMinutes(minutesPerSlot*2)], "Wrong table. There are two rooms used on Thursday at " + startHour.AddMinutes(minutesPerSlot).Hour + ":" + startHour.AddMinutes(minutesPerSlot).Minute);



            }
            catch (Exception exc)
            {
                Assert.Fail("An exception was shown when none was expected. Message: " + exc.Message);
            }
        }
     }
    
}
