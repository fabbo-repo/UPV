using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class User
    {
        public User()
        {
            Enrollments = new List<Enrollment>();
        }
        public User(string address, string iban, string id, string name, int zipCode, DateTime birthDate, bool retired) :
        base(address, iban, id, name, zipCode)
        {
            BirthDate = birthDate;
            Retired = retired;
            Enrollments = new List<Enrollment>();
        }

        public void AddEnrollment(Enrollment en)
        {
            this.Enrollments.Add(en);
        }

        public ICollection<int> GetEnrollmentIds()
        {
            ICollection<int> en = new List<int>();
            foreach (Enrollment e in this.Enrollments)
            {
                en.Add(e.Id);
            }
            return en;
        }

        public Enrollment GetEnrollmentById(int id)
        {
            foreach (Enrollment en in this.Enrollments)
            {
                if (en.Id == id) return en;
            }
            return null;
        }

        public void GetUserData(out string address, out string iban, out string name, out int zipCode, out DateTime birthDate, out bool retired, 
            out ICollection<int> enrollmentIds)
        {
            address = this.Address; iban = this.IBAN; name = this.Name; zipCode = this.ZipCode; birthDate = this.BirthDate;
            retired = this.Retired; enrollmentIds = this.GetEnrollmentIds();
        }

        public Boolean IsEnrolledInActivityId(int activityId) 
        {
            foreach (Enrollment e in this.Enrollments) 
            {
                if (e.Activity.Id == activityId) return true;
            }
            return false;
        }
        
    }
}
