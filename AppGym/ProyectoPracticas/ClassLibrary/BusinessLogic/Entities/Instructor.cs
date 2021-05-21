using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class Instructor
    {
        public Instructor()
        {
            Activities = new List<Activity>();
        }
        public Instructor(string address, string iban, string id, string name, int zipCode,  string ssn) :
        base(address, iban, id, name, zipCode)
        {
            Ssn = ssn;
            Activities = new List<Activity>();
        }

        public void AddActivity(Activity a)
        {
            this.Activities.Add(a);
        }

        public ICollection<int> GetActivitiesIds()
        {
            ICollection<int> ac = new List<int>();
            foreach (Activity a in this.Activities) {
                ac.Add(a.Id);
            }
            return ac;
        }

        public void GetInstructorData(out string address, out string IBAN, out string name, out int zipCode, out string ssn,
            out ICollection<int> activitiesIds)
        {
            address = this.Address; IBAN = this.IBAN; name = this.Name; zipCode = this.ZipCode;
            ssn = this.Ssn; activitiesIds = this.GetActivitiesIds();
        }

        public Boolean IsAvailable (Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour)
        {
            foreach (Activity a in this.Activities)
            {
                if (a.EqualsActivity(activityDays, duration, finishDate, startDate, startHour))
                    return false;
            }

            return true;
        }
    }
}
