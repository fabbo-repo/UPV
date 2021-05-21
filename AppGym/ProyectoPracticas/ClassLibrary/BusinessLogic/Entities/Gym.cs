using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class Gym
    {
        //Constructor
        public Gym () {
            this.Activities = new List<Activity>();
            this.Rooms = new List<Room>();
        }

        public Gym (DateTime closingHour, int discountLocal, int discountRetired, 
            double freeUserPrice, string name, DateTime openingHour, int zipCode):this() {
            this.ClosingHour = closingHour;
            this.DiscountLocal = discountLocal;
            this.DiscountRetired = discountRetired;
            this.FreeUserPrice = freeUserPrice;
            //EF se encarga de los atributos ID de tipo int
            this.Name = name;
            this.OpeningHour = openingHour;
            this.ZipCode = zipCode;
        }

        public void AddActivity(Activity a)
        {
            this.Activities.Add(a);
        }
        public void AddRoom(Room r)
        {
            this.Rooms.Add(r);
        }

        public Activity GetActivityById(int ActivityId)
        {
            foreach (Activity ac in this.Activities)
            {
                if (ActivityId == ac.Id) { return ac; }
            }
            return null;
        }
        public Room GetRoomById(int roomId) 
        {
            foreach (Room r in this.Rooms)
                if (r.Id == roomId) { return r; }
            return null;
        }
        public Payment GetPaymentById(int paymentId)
        {
            foreach (Activity ac in this.Activities)
            {
                Payment p = ac.GetPaymentById(paymentId);
                if (p != null) return p;
            }
            return null;
        }

        public ICollection<int> GetAllActivitiesIds()
        { 
            ICollection<int> ac = new List<int>();
            foreach (Activity a in this.Activities) { ac.Add(a.Id); }
            return ac;
        }
        public ICollection<int> GetAllRoomsIds()
        {
            ICollection<int> room = new List<int>();
            foreach (Room rm in this.Rooms)
            {
                room.Add(rm.Id);
            }
            return room;
        }

        public ICollection<Room> GetAllRoomsFromIds(ICollection<int> ids)
        {
            ICollection<Room> room = new List<Room>();
            foreach (int id in ids)
            {
                Room r = this.GetRoomById(id);
                if(r!=null) room.Add(r);
            }
            return room;
        }

        public ICollection<int> GetAllRunningOrFutureActivitiesIds()
        {
            ICollection<int> act = new List<int>();
            foreach (Activity a in this.Activities) { 
                if(a.IsRunningOrFuture())act.Add(a.Id); }
            return act;
        }

        public ICollection<int> GetListAvailableRoomsIds(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour)
        {
            ICollection<int> rooms = new List<int>();
            foreach (Room r in this.Rooms)
                if (r.IsAvailable(activityDays, duration, finishDate, startDate, startHour))
                    rooms.Add(r.Id);

            return rooms;
        }

        public double GetFirstQuotaByActivityId(int activityId, Boolean retired, int zipCode)
        {
            Activity ac = GetActivityById(activityId);
            if (ac == null) throw new ArgumentException("Error: No existe esta actividad.");
            double cuota = ac.Price;
            if (retired && zipCode == this.ZipCode)
            {
                cuota = (100 - this.DiscountLocal - this.DiscountRetired) * cuota / 100;
            }
            else if (zipCode == this.ZipCode) { cuota = (100 - this.DiscountLocal) * cuota / 100; }
            else if (retired) { cuota = (100 - this.DiscountRetired) * cuota / 100; }
            return cuota;
        }

        public void GetActivityDataFromId(int ActivityId, out Days activityDays, out string description, out TimeSpan duration, out DateTime finishDate, 
            out int maximumEnrollments, out int minimumEnrollments, out double price, out DateTime startDate, out DateTime startHour, 
            out ICollection<int> enrollmentIds, out string instructorId, out ICollection<int> roomIds)
        {
            Activity a = this.GetActivityById(ActivityId);
            if (a == null) throw new ArgumentException("Error: No existe esta actividad.");
            a.GetActivityData(out activityDays, out description, out duration, out finishDate, out maximumEnrollments, out minimumEnrollments, out price,
                out startDate, out startHour, out enrollmentIds, out instructorId, out roomIds);
        }

        public void GetRoomDataFromId(int roomId, out int number, out ICollection<int> activityIds)
        {
            Room room = this.GetRoomById(roomId);
            if (room == null) throw new ArgumentException("Error: No existe la sala.");
            room.GetRoomData(out number, out activityIds);
        }

        public void GetPaymentDataFromId(int paymentId, out DateTime date, out string description, out double quantity)
        {
            Payment p = this.GetPaymentById(paymentId); //Esta función se encuentra en Gym, Activity y Enrollment.
            if (p == null) throw new ArgumentException("Error: No existe este pago.");
            p.GetPaymentData(out date, out description, out quantity);
        }

        public void GetEnrollmentDataFromIds(int activityId, int enrollmentId, out DateTime? cancellationDate, out DateTime enrollmentDate, 
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds, out string userId)
        {
            Activity ac = this.GetActivityById(activityId);
            if (ac == null) { throw new ArgumentException("Error: No existe esta actividad."); }
            ac.GetEnrollmentDataFromId(enrollmentId, out cancellationDate, out enrollmentDate, out returnedFirstCuotaIfCancelledActivity, 
                out paymentIds, out userId);
        }

        public void GetGymData(out int gymId, out DateTime closingHour, out int discountLocal, out int discountRetired, out double freeUserPrice, out string name, out DateTime openingHour, out int zipCode, out ICollection<int> activityIds, out ICollection<int> roomIds)
        {
            gymId = this.Id; closingHour = this.ClosingHour; discountLocal = this.DiscountLocal; discountRetired = this.DiscountRetired;
            freeUserPrice = this.FreeUserPrice; name = this.Name; openingHour = this.OpeningHour;
            zipCode = this.ZipCode; activityIds = this.GetAllActivitiesIds(); roomIds = this.GetAllRoomsIds();
        }

        public int AddNewActivity(Days activityDays, string description, TimeSpan duration, DateTime finishDate, int maximumEnrollments,
            int minimumEnrollments, double price, DateTime startDate, DateTime startHour, ICollection<int> roomsIds)
        {
            if (maximumEnrollments < 0)
                throw new ArgumentException("Error: Máximo de inscripciones no debe ser menor a 0.");
            if (minimumEnrollments < 0)
                throw new ArgumentException("Error: Mínimo de inscripciones no debe ser menor a 0.");
            if (minimumEnrollments > maximumEnrollments)
                throw new ArgumentException("Error: Máximo o mínimo inscripciones invalidas.");
            if (price < 0)
                throw new ArgumentException("Error: Precio no debe ser menor a 0.");
            if(roomsIds==null)
                throw new ArgumentException("Error: Precio no debe ser menor a 0.");
            
           ICollection<Room> rooms = this.GetAllRoomsFromIds(roomsIds);
            if(rooms.Count() == 0)
                throw new ArgumentException("Error: No hay salas seleccionadas existentes.");

            foreach (Room r in rooms)
            {
                if (!r.IsAvailable(activityDays, duration, finishDate, startDate, startHour))
                    throw new ArgumentException("Error: No estan disponibles las salas.");
            }
            
            Activity a = new Activity(activityDays, description, duration, finishDate, maximumEnrollments, minimumEnrollments, price,
               startDate, startHour);

            a.AddRooms(rooms);
            foreach (Room r in rooms)
            {
                r.AddActivity(a);
            }
            this.AddActivity(a);
            
            return a.Id;
        }

        public void AssignInstructorToActivity(int activityId, Instructor instructor)
        {
            Activity a = this.GetActivityById(activityId);
            if (a == null) throw new ArgumentException("Error: Esta actividad no existe en la BD.");
            if (instructor == null) throw new ArgumentException("Error: Instructor no existe.");
            if (!instructor.IsAvailable(a.ActivityDays, a.Duration, a.FinishDate, a.StartDate, a.StartHour)) 
                throw new ArgumentException("Error: Este instructor no está disponible.");
            
            a.AddInstructor(instructor);
            instructor.AddActivity(a);
        }

        public void EnrollUserInActivity(int activityId, User user, out Enrollment enrolm, out Payment paym)
        {
            if (user == null) throw new ArgumentException("Error: Usuario no existe.");
            Activity a = this.GetActivityById(activityId);
            if (a == null) throw new ArgumentException("Error: Actividad no existe.");
            if(user.IsEnrolledInActivityId(activityId)) throw new ArgumentException("Error: Usuario ya está inscrito en la actividad.");

            double pago = this.GetFirstQuotaByActivityId(activityId, user.Retired, user.ZipCode);
            Payment p = new Payment(DateTime.Today,"Usuario "+user.Name+", ha pagado "+pago, pago);
            Enrollment en = new Enrollment(DateTime.Today,a,p,user);
            a.AddEnrollment(en); user.AddEnrollment(en);
            enrolm = en;
            paym = p;
        }

        public Days ToDays(DayOfWeek DayOfWeek)
        {
            Days dia;
            switch (DayOfWeek)
            {
                case DayOfWeek.Monday: dia = Days.Mon; break;
                case DayOfWeek.Tuesday: dia = Days.Tue; break;
                case DayOfWeek.Wednesday: dia = Days.Wed; break;
                case DayOfWeek.Thursday: dia = Days.Thu; break;
                case DayOfWeek.Friday: dia = Days.Fri; break;
                case DayOfWeek.Saturday: dia = Days.Sat; break;
                case DayOfWeek.Sunday: dia = Days.Sun; break;
                default: dia = Days.None; break;
            }
            return dia;
        }

        public int NumAvailableRooms(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour) 
        {
            int cont = GetListAvailableRoomsIds(activityDays, new TimeSpan(0,45,0), finishDate, startDate, startHour).Count();
            return cont;
        }

        public Dictionary<DateTime, int> GetListAvailableRoomsPerWeek(DateTime initialMonday)
        {
            // Devuelve pares dia y numero de habitaciones disponibles, de todos los dias de la semana desde la fecha del initialMonday 
            Dictionary<DateTime, int> roomsPerTime = new Dictionary<DateTime, int>();
            DateTime endSunday = initialMonday.AddDays(6);
            for (DateTime fecha = initialMonday; fecha.CompareTo(endSunday) <= 0; fecha=fecha.AddDays(1))
            {
                for (DateTime hora = this.OpeningHour; hora.CompareTo(this.ClosingHour) < 0; hora=hora.AddMinutes(45))
                {
                    int cont = this.NumAvailableRooms(this.ToDays(fecha.DayOfWeek), new TimeSpan(0, 45, 0), fecha, fecha, hora);
                    DateTime fechaD = new DateTime(fecha.Year, fecha.Month, fecha.Day, hora.Hour, hora.Minute, hora.Second); 
                    roomsPerTime.Add(fechaD, cont);
                }
            }
            return roomsPerTime;
        }
    }
}
