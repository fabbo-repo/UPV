using System;
using GestDep.Persistence;
using GestDep.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GestDepServicesTest
{
    [TestClass]
    public class BaseTest
    {
        protected EntityFrameworkDAL dal;
        protected GestDepService gestDepService;        
     
        [TestInitialize]
        public void IniTests()
        {
            // Runs before each test.
            dal = new EntityFrameworkDAL(new GestDepDbContext());
            dal.RemoveAllData();
            gestDepService = new GestDepService(dal);

        }
        [TestCleanup]
        public void CleanTests()
        {
            // Runs after each test
            dal.RemoveAllData();
        }
    }
}
