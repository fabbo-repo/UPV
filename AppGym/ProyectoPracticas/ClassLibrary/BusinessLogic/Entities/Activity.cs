using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class Activity
    {
        public Activity()
        {
            Enrollments = new List<Enrollment>();
            Rooms = new List<Room>();
        }
        public Activity(Days activityDays, string description,
            TimeSpan duration, DateTime finishDate, int maximumEnrollments,
            int minimumEnrollments, double price, DateTime startDate, DateTime startHour):this()
        {
            this.ActivityDays = activityDays;
            this.Cancelled = false; // las actividades al crearse no estarán canceladas
            this.Description = description;
            this.Duration = duration;
            this.FinishDate = finishDate;
            this.MaximumEnrollments = maximumEnrollments;
            //EF se encarga de los atributos ID de tipo int
            this.MinimumEnrollments = minimumEnrollments;
            this.Price = price;
            this.StartDate = startDate;
            this.StartHour = startHour;
        }

        public void AddRoom(Room r)
        {
            this.Rooms.Add(r);
        }
        public void AddInstructor(Instructor ins)
        {
            this.Instructor = ins;
        }
        public void AddRooms(ICollection<Room> rooms)
        {
            foreach (Room r in rooms)
            {
                this.Rooms.Add(r);
            }
        }
        public void AddEnrollment(Enrollment en)
        {
            this.Enrollments.Add(en);
        }

        public string GetInstructorId()
        {
            if (this.Instructor == null) return "-";
            else return Instructor.Id;
        }
        public Enrollment GetEnrollmentById(int enrollmentId)
        {
            foreach (Enrollment en in this.Enrollments)
            {
                if (enrollmentId == en.Id) { return en; }
            }
            return null;
        }
        public Payment GetPaymentById(int paymentId)
        {
            foreach (Enrollment e in this.Enrollments)
            {
                Payment p = e.GetPaymentById(paymentId);
                if (p != null) return p;
            }
            return null;
        }
        public ICollection<int> GetEnrollmentIds() {
            ICollection<int> i = new List<int>();
            foreach (Enrollment e in this.Enrollments) {
                i.Add(e.Id);
            }
            return i;
        }
        public ICollection<int> GetRoomIds()
        {
            ICollection<int> i = new List<int>();
            foreach (Room r in this.Rooms)
            {
                i.Add(r.Id);
            }
            return i;
        }

        public Boolean EqualsActivity(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour)
        {
            DateTime finishHour = startHour.Add(duration);
            Days aD = this.ActivityDays; TimeSpan d = this.Duration; DateTime fD = this.FinishDate;
            DateTime sD = this.StartDate; DateTime sH = this.StartHour; DateTime fH = sH.Add(d);

            if (finishDate.Date.CompareTo(sD.Date) >= 0
                && startDate.Date.CompareTo(fD.Date) <= 0)
            {
                if (activityDays.HasFlag(aD) || aD.HasFlag(activityDays))
                {
                    if (finishHour.TimeOfDay.CompareTo(sH.TimeOfDay) > 0
                        && startHour.TimeOfDay.CompareTo(fH.TimeOfDay) < 0)
                        return true;
                }
            }
            return false;
        }

        public void GetActivityData(out Days activityDays, out string description, out TimeSpan duration, out DateTime finishDate,
            out int maximumEnrollments, out int minimumEnrollments, out double price, out DateTime startDate, out DateTime startHour,
            out ICollection<int> enrollmentIds, out string instructorId, out ICollection<int> roomIds)
        {
            activityDays = this.ActivityDays; description = this.Description; duration = this.Duration;
            finishDate = this.FinishDate; maximumEnrollments = this.MaximumEnrollments;
            minimumEnrollments = this.MinimumEnrollments; price = this.Price; startDate = this.StartDate;
            startHour = this.StartHour; enrollmentIds = this.GetEnrollmentIds(); instructorId = this.GetInstructorId();
            roomIds = this.GetRoomIds();
        }
        public void GetEnrollmentDataFromId(int enrollmentId, out DateTime? cancellationDate, out DateTime enrollmentDate,
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds, out string userId)
        {
            Enrollment en = this.GetEnrollmentById(enrollmentId);
            if (en == null) { throw new ArgumentException("Error: No existe esta inscripción."); }
            en.GetEnrollmentData(out cancellationDate, out enrollmentDate, out returnedFirstCuotaIfCancelledActivity, out paymentIds, 
                out userId);
        }

        public Boolean IsRunningOrFuture()
        {
            DateTime fechaActual = DateTime.Today;
            if (fechaActual.CompareTo(this.FinishDate) > 0)
            {
                return false;
            }
            else if (fechaActual.CompareTo(this.FinishDate) == 0)
            {
                DateTime horaActual = DateTime.Now;
                DateTime FinishHour = this.StartHour.Add(this.Duration);
                if (horaActual.CompareTo(FinishHour) > 0)
                {
                    return false;
                }
            }
            return true;
        }
    }
}
