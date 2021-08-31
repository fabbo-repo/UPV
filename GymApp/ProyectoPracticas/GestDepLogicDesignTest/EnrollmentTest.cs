using System;
using System.Linq;
using GestDep.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepLogicDesignTest
{
    [TestClass]
    public class EnrollmentTest
    {
        [TestMethod]
        public void NoParamsConstructorInitializesMaintenances()
        {
            Enrollment enrollment = new Enrollment();
            Assert.AreNotSame(null, enrollment, "There must be a constructor without parameters.");
            Assert.IsNotNull(enrollment.Payments, "Collection of Payments not properly initialized. \n Patch the problem adding:  Payments = new List<Payment>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, enrollment.Payments.Count, "Collection of Payments not properly initialized. \nYou have added an extra element");
        }
        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Enrollment enrollment = new Enrollment(TestData.EXPECTED_ENROLLMENT_DATE, TestData.DEFAULT_ACTIVITY, TestData.DEFAULT_PAYMENT, TestData.DEFAULT_USER);
            Assert.AreEqual(TestData.EXPECTED_ENROLLMENT_DATE, enrollment.EnrollmentDate, "EnrollmentDate not properly initialized. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.DEFAULT_ACTIVITY, enrollment.Activity, "Activity not properly initialized. Check the order of the parameters and the assignment.");
            Assert.AreEqual(TestData.DEFAULT_USER, enrollment.User, "User not properly initialized. Check the order of the parameters and the assignment.");

            Assert.IsNull(enrollment.CancellationDate, "CancellationDate not properly initialized. It should be null.  Check the order of the parameters and the assignment.");
            Assert.IsNull(enrollment.ReturnedFirstCuotaIfCancelledActivity, "ReturnedFirstCuotaIfCancelledActivity not properly initialized. It should be null.  Check the order of the parameters and the assignment.");

            Assert.IsNotNull(enrollment.Payments, "Collection of Payments not properly initialized. \n Patch the problem adding:  Payments = new List<Payment>();");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, enrollment.Payments.Count, "Payment not added to the list of Payments.");
            Assert.AreEqual(TestData.DEFAULT_PAYMENT, enrollment.Payments.First(), "Payment not added to the list of Payments.");
        }
    }
}
