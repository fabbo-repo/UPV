using GestDep.Entities;
using GestDep.Persistence;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Services
{
    public class GestDepService : IGestDepService
    {
        private readonly IDAL dal; //Persistence Layer Interface
        public CityHall cityHall;  //Services only work on a City Hall
        public Gym gym;			   // Gym of the City Hall. Also available from cityHall.Gyms.First();
        
        /// </summary>
        /// Returns a service Layer connected with the persistence Layer. Retrieves the CitiHall and Gym from the database if they exist. If not, it creates new ones
        /// </summary>
        /// <param name="dal"> Persistence Layer Interface</param>
        
        public GestDepService(IDAL dal)
        {
            this.dal = dal;
            try
            {
                    
                if (dal.GetAll<CityHall>().Count() == 0) //No cityHall in the system. Data initilization. 
                {
                    bool CLEAR_DATABASE = true;
                    int ROOMS_NUMBER = 9;
                    int INSTRUCTORS_NUMBER = 5;
                    Populate populateDB = new Populate(CLEAR_DATABASE,dal);
                    cityHall = populateDB.InsertCityHall();
                    gym = populateDB.InsertGym(cityHall);     //Also in cityHall.First();                
                    populateDB.InsertRooms(ROOMS_NUMBER, gym);  //Now available from gym.rooms;
                    populateDB.InsertInstructors(INSTRUCTORS_NUMBER, cityHall); //Now available from cityHall.People;

                }
                else
                {   //Retrieve the CityHall stored
                    cityHall = dal.GetAll<CityHall>().First();

                    if (cityHall.Gyms.Count > 0)
                    { //Retrieve the Gym stored
                        gym = cityHall.Gyms.First();                       

                    }
                    else
                    { //Adding Rooms and Gym
                        bool MANTAIN_DATABASE = false;
                        int ROOMS_NUMBER = 9;
                        Populate populateDB = new Populate(MANTAIN_DATABASE, dal);
                        gym = populateDB.InsertGym(cityHall);
                        populateDB.InsertRooms(ROOMS_NUMBER, gym);
                    }
                    int INSTRUCTORS_NUMBER = 5;
                    if (dal.GetAll<Instructor>().Count() == 0)//No instructors
                    { 
                        bool MANTAIN_DATABASE = false;
                        Populate populateDB = new Populate(MANTAIN_DATABASE, dal);
                        populateDB.InsertInstructors(INSTRUCTORS_NUMBER, cityHall); //Now available from cityHall.People;
                    }

                }
            } catch(Exception e)
            {
                throw new ServiceException("Error in the service init process", e);
                
            }
        }

        public int AddNewActivity(Days activityDays, string description, TimeSpan duration, DateTime finishDate, int maximumEnrollments,
            int minimumEnrollments, double price, DateTime startDate, DateTime startHour, ICollection<int> roomsIds)
        {
            try
            {
                int id = gym.AddNewActivity(activityDays, description, duration, finishDate, maximumEnrollments,
                    minimumEnrollments, price, startDate, startHour, roomsIds);
                this.SaveChanges();
                return id;
            }
            catch(ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public void AddNewUser(string address, string iban, string id, string name, int zipCode, DateTime birthDate, bool retired)
        {
            try
            {
                this.cityHall.AddNewUser(address, iban, id, name, zipCode, birthDate, retired);
                this.SaveChanges();
            }
            catch (ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public void AssignInstructorToActivity(int activityId, string instructorId)
        {
            try
            {
                Instructor ins = this.cityHall.GetInstructorById(instructorId);
                this.gym.AssignInstructorToActivity(activityId, ins);
                SaveChanges();
            }
            catch(ArgumentException e) { throw new ServiceException(e.Message); }
        }

        public int EnrollUserInActivity(int activityId, string userId)
        {
            try
            {
                User u = this.cityHall.GetUserById(userId);
                Enrollment en; Payment p; 
                gym.EnrollUserInActivity(activityId, u, out en, out p);
                this.cityHall.AddPayment(p);

                SaveChanges();
                return en.Id;
            }
            catch (ArgumentException e) { throw new ServiceException(e.Message); }
        }

        public void GetActivityDataFromId(int activityId, out Days activityDays, out string description, out TimeSpan duration, out DateTime finishDate, 
            out int maximumEnrollments, out int minimumEnrollments, out double price, out DateTime startDate, out DateTime startHour, 
            out ICollection<int> enrollmentIds, out string instructorId, out ICollection<int> roomIds)
        {
            try
            {
                gym.GetActivityDataFromId(activityId, out activityDays, out description, out duration, out finishDate, out maximumEnrollments,
                    out minimumEnrollments, out price, out startDate, out startHour, out enrollmentIds, out instructorId, out roomIds);
            }
            catch (ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public ICollection<int> GetAllActivitiesIds()
        { 
            return gym.GetAllActivitiesIds();
        }

        public ICollection<int> GetAllRunningOrFutureActivitiesIds()
        {
            return gym.GetAllRunningOrFutureActivitiesIds();
            //if (act.Count() == 0) throw new ServiceException("No hay actividades en curso o planificadas para el futuro.");
        }

        public ICollection<string> GetAvailableInstructorsIds(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour)
        {
            try
            {
                return this.cityHall.GetAvailableInstructorsIds(activityDays, duration, finishDate, startDate, startHour);
            }
            catch (ArgumentException e) { throw new ServiceException(e.Message); }
        }

        public void GetEnrollmentDataFromIds(int activityId, int enrollmentId, out DateTime? cancellationDate, out DateTime enrollmentDate, 
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds, out string userId)
        {
            try
            {
                gym.GetEnrollmentDataFromIds(activityId, enrollmentId, out cancellationDate, out enrollmentDate, out returnedFirstCuotaIfCancelledActivity,
                    out paymentIds, out userId);
            }
            catch (ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public void GetGymData(out int gymId, out DateTime closingHour, out int discountLocal, out int discountRetired, out double freeUserPrice, out string name, 
            out DateTime openingHour, out int zipCode, out ICollection<int> activityIds, out ICollection<int> roomIds)
        {
            if (this.cityHall.Gyms.Count() == 0) { throw new ServiceException("No existen gyms."); }
            gym.GetGymData(out gymId, out closingHour, out discountLocal, out discountRetired, out freeUserPrice, out name, out openingHour, out zipCode,
                out activityIds, out roomIds);
        }

        public void GetInstructorDataFromId(string instructorId, out string address, out string IBAN, out string name, out int zipCode, out string ssn, 
            out ICollection<int> activitiesIds)
        {
            try
            {
                this.cityHall.GetInstructorDataFromId(instructorId, out address, out IBAN, out name, out zipCode, out ssn, out activitiesIds);
            }
            catch (ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public ICollection<int> GetListAvailableRoomsIds(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour)
        {
            try
            {
                ICollection<int> rooms = this.gym.GetListAvailableRoomsIds(activityDays, duration, finishDate, startDate, startHour);
                if (rooms.Count() == 0) { throw new ServiceException("Error: No hay salas disponibles."); }
                return rooms;
            }
            catch (ArgumentException e){ throw new ServiceException(e.Message); }
        }

        public Dictionary<DateTime, int> GetListAvailableRoomsPerWeek(DateTime initialMonday)
        {
            if (DayOfWeek.Monday != initialMonday.DayOfWeek) { throw new ServiceException("Error: el dia inicial debe ser un lunes"); }
            try
            {
                return this.gym.GetListAvailableRoomsPerWeek(initialMonday);
            }
            catch (ArgumentException e) { throw new ServiceException(e.Message); }
        }

        public void GetPaymentDataFromId(int paymentId, out DateTime date, out string description, out double quantity)
        {
            try
            {
                this.gym.GetPaymentDataFromId(paymentId, out date, out description, out quantity);
            }
            catch (ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public void GetRoomDataFromId(int roomId, out int number, out ICollection<int> activityIds)
        {
            try
            {
                this.gym.GetRoomDataFromId(roomId, out number, out activityIds);
            }
            catch (ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public void GetUserDataFromId(string userId, out string address, out string iban, out string name, out int zipCode, out DateTime birthDate, 
            out bool retired, out ICollection<int> enrollmentIds)
        {
            try
            {
                this.cityHall.GetUserDataFromId(userId, out address, out iban, out name, out zipCode, out birthDate, out retired, out enrollmentIds);
            }
            catch (ArgumentException e)
            {
                throw new ServiceException(e.Message);
            }
        }

        public double GetUserDataNotInActivityAndFirstQuota(int activityId, string userId, out string address, out string iban, out string name, 
            out int zipCode, out DateTime birthDate, out bool retired, out ICollection<int> enrollmentIds)
        {
            User u = this.cityHall.GetUserById(userId);
            if (u == null) throw new ServiceException("Error: No existe este usuario en la BD.");
            if (!u.IsEnrolledInActivityId(activityId)) 
            {
                this.cityHall.GetUserDataFromId(userId, out address, out iban, out name, out zipCode, out birthDate, out retired, out enrollmentIds);
                try
                {
                    return gym.GetFirstQuotaByActivityId(activityId, retired, zipCode);
                }
                catch(ArgumentException e) { throw new ServiceException(e.Message); }
            }
            else throw new ServiceException("Error: Usuario ya se ha inscrito en dicha actividad");
        }

        #region Connection with the Persistence Layer
        public void RemoveAllData()
        {
            dal.RemoveAllData();
        }

     
        public void SaveChanges()
        {
            dal.Commit();
        }
        #endregion
    }
}
