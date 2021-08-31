using System;
using GestDep.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepLogicDesignTest
{
    [TestClass]
    public class CityHallTest
    {
        public void NoParametersConstructor()
        {
            CityHall cityHall = new CityHall();
            Assert.AreNotSame(null, cityHall, "There must be a constructor without parameters");
            Assert.IsNotNull(cityHall.People, "The collection of People was not intialized properly.\nPatch the problem by adding:  People = new List<Person>();");
            Assert.IsNotNull(cityHall.Payments, "The collection of Payments was not intialized properly.\nPatch the problem by adding:  Payments = new List<Payment>();");
            Assert.IsNotNull(cityHall.Gyms, "The collection of Gyms was not intialized properly.\nPatch the problem by adding:  Gyms = new List<Gym>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, cityHall.People.Count, "The collection of People was not intialized properly.\nYou have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, cityHall.Payments.Count, "The collection of Payments was not intialized properly.\nYou have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, cityHall.Gyms.Count, "The collection of Gyms was not intialized properly.\nYou have added an extra element");

        }
        [TestMethod]
        public void ConstructorInitializesProps()
        {
            CityHall cityHall = new CityHall(TestData.EXPECTED_CITY_HALL_NAME);
            Assert.AreEqual(TestData.EXPECTED_CITY_HALL_NAME, cityHall.Name, "Name was not intialized properly. Check the order of the parameters and the assignment.");
            Assert.IsNotNull(cityHall.People, "The collection of People was not intialized properly.\nPatch the problem by adding:  People = new List<Person>();");
            Assert.IsNotNull(cityHall.Payments, "The collection of Payments was not intialized properly.\nPatch the problem by adding:  Payments = new List<Payment>();");
            Assert.IsNotNull(cityHall.Gyms, "The collection of Gyms was not intialized properly.\nPatch the problem by adding:  Gyms = new List<Gym>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, cityHall.People.Count, "The collection of People was not intialized properly.\nYou have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, cityHall.Payments.Count, "The collection of Payments was not intialized properly.\nYou have added an extra element");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, cityHall.Gyms.Count, "The collection of Gyms was not intialized properly.\nYou have added an extra element");

        }
    }
}
