using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class CityHall
    {
        public CityHall()
        {
            People = new List<Person>();
            Payments = new List<Payment>();
            Gyms = new List<Gym>();
        }
        public CityHall(string name)
        {
            //EF se encarga de los atributos ID de tipo int
            Name = name;
            People = new List<Person>();
            Payments = new List<Payment>();
            Gyms = new List<Gym>();
        }

        public void AddUser(User u) 
        {
            this.People.Add(u);
        }
        public void AddPayment(Payment p)
        {
            this.Payments.Add(p);
        }

        public Person GetPersonById(string id) 
        {
            foreach (Person p in this.People)
            {
                if (p.Id == id) return p;
            }
            return null;
        }

        public Instructor GetInstructorById(string id)
        {
            foreach (Person p in this.People)
            {
                if (p.Id == id) return (Instructor) p;
            }
            return null;
        }

        public User GetUserById(string id)
        {
            foreach (Person p in this.People)
            {
                if (p.Id == id) return (User) p;
            }
            return null;
        }

        public ICollection<Instructor> GetAllInstructors()
        {
            ICollection<Instructor> ins = new List<Instructor>();
            foreach (Person p in this.People)
            {
                try
                {
                    ins.Add((Instructor) p);
                }
                catch(Exception) { }
            }
            return ins;
        }

        public ICollection<string> GetAvailableInstructorsIds(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour)
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

            ICollection<Instructor> instructors = this.GetAllInstructors();
            if (instructors.Count() == 0)
                throw new ArgumentException("Error: No hay instructores.");
            ICollection<string> iIds = new List<string>();
            foreach (Instructor i in instructors)
            {
                if (i.IsAvailable(activityDays, duration, finishDate, startDate, startHour))
                {
                    iIds.Add(i.Id);
                }
            }
            if (iIds.Count() == 0) 
                throw new ArgumentException("Error: No hay instructores disponibles en este periodo de tiempo.");
            return iIds;
        }

        public void GetUserDataFromId(string userId, out string address, out string iban, out string name, out int zipCode, out DateTime birthDate, 
            out bool retired, out ICollection<int> enrollmentIds)
        {
            User u = this.GetUserById(userId);
            if (u == null) throw new ArgumentException("Error: No existe este usuario.");
            u.GetUserData(out address, out iban, out name, out zipCode, out birthDate, out retired, out enrollmentIds);
        }

        public void GetInstructorDataFromId(string instructorId, out string address, out string IBAN, out string name, out int zipCode, out string ssn, 
            out ICollection<int> activitiesIds)
        {
            Instructor i = this.GetInstructorById(instructorId);
            if (i == null) { throw new ArgumentException("Error: No existe este instructor en la."); }
            i.GetInstructorData(out address, out IBAN, out name, out zipCode, out ssn,out activitiesIds);
        }

        public void AddNewUser(string address, string iban, string id, string name, int zipCode, DateTime birthDate, bool retired)
        {
            if (address == "")
                throw new ArgumentException("Error: Direccion incorrecta.");
            if (iban == "")
                throw new ArgumentException("Error: IBAN incorrecto.");
            if (name == "")
                throw new ArgumentException("Error: Nombre incorrecto.");
            if (int.TryParse(id, out _) || id.Length != 9) // TryParse devuelve true si id contiene solo numeros
                throw new ArgumentException("Error: ID incorrecto.");
            if (zipCode <= 0)
                throw new ArgumentException("Error: Codigo Postal incorrecto.");
            if (birthDate.CompareTo(DateTime.Today) >= 0) 
                    throw new ArgumentException("Error: la fecha de nacimiento incorrecta.");
            Person p = this.GetPersonById(id);
            if (p == null)
            {
                User u = new User(address, iban, id, name, zipCode, birthDate, retired);
                this.AddUser(u);
            }
            else throw new ArgumentException("Error: Usuario ya existe.");

        }
    }
}
