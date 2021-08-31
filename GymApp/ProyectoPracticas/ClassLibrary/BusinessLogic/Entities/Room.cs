using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class Room
    {
        public Room() {
            Activities = new List<Activity>();
        }
        public Room(int num)
        {
            //EF se encarga de los atributos ID de tipo int
            Number = num;
            Activities = new List<Activity>();
        }

        public void AddActivity(Activity a) 
        {
            this.Activities.Add(a);
        }

        public ICollection<int> GetActivityIds() 
        {
            ICollection<int> res = new List<int>();
            foreach (Activity a in this.Activities) res.Add(a.Id);
            return res;
        }

        public void GetRoomData(out int number, out ICollection<int> activityIds)
        {
            number = this.Number; activityIds = this.GetActivityIds();
        }

        public Boolean IsAvailable(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour) 
        {

            DateTime finishHour = startHour.Add(duration);
            if (startHour.CompareTo(finishHour) > 0)
                throw new ArgumentException("Error: duracion incorrecta.");
            else if (startDate.CompareTo(finishDate) > 0)
                throw new ArgumentException("Error: Fecha inicio debe ir antes que la fecha fin.");
            else if (startDate.CompareTo(DateTime.Now) < 0)
                throw new ArgumentException("Error: Fecha inicio debe ser posterior a la fecha actual.");
            else if (activityDays == Days.None)
                throw new ArgumentException("Error: Día incorrecto.");

            foreach (Activity a in this.Activities) 
            {
                if(a.EqualsActivity(activityDays, duration, finishDate, startDate, startHour))
                {
                    return false;
                }
            }
            
            return true;
        }

        
    }
}
