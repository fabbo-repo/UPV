using System;
using GestDep.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepLogicDesignTest
{
    [TestClass]
    public class InstructorTest
    {
        [TestMethod]
        public void NoParametersConstructor()
        {
            Instructor instructor = new Instructor();
            Assert.AreNotSame(null, instructor, "There must be a constructor without parameters");
            Assert.IsNotNull(instructor.Activities, "The collection of Activities was not intialized properly.\nPatch the problem by adding:  Activities = new List<Activity>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, instructor.Activities.Count, "The collection of Activities was not intialized properly.\nYou have added an extra element");
        }
        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Instructor instructor = new Instructor(TestData.EXPECTED_PERSON_ADDRESS, TestData.EXPECTED_PERSON_IBAN, TestData.EXPECTED_PERSON_ID,
                TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_ZIP_CODE, TestData.EXPECTED_SSN);
            Assert.AreEqual(TestData.EXPECTED_PERSON_ADDRESS, instructor.Address, "Address doesn't have the expected value. Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_ID, instructor.Id, "Id  was not intialized properly. Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_IBAN, instructor.IBAN, "IBAN was not intialized properly.Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, instructor.Name, "Name was not intialized properly.Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_ZIP_CODE, instructor.ZipCode, "Zip code was not intialized properly. Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_SSN, instructor.Ssn, "SSN was not initialized properly. Check the order of the parameters and the assignment.");

            Assert.IsNotNull(instructor.Activities, "The collection of Activities was not intialized properly.\nPatch the problem by adding:  Activities = new List<Activity>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, instructor.Activities.Count, "The collection of Activities was not intialized properly.\nYou have added an extra element");
        }
    }
}
