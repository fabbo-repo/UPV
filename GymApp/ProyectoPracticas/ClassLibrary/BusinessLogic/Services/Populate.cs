using GestDep.Entities;
using GestDep.Persistence;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GestDep.Services
{
    class Populate
    {
        private int cityHallCount; //Number of CityHalls in the system. Used to create new CityHall names
        private int personCount; //Number of persons in the system. Used to create  new ids and names of new people
        private int gymCount; // Number of gyms in the system.Used to create new gym names
        private int roomCount; //number of rooms of the system. Used to creat new rooms
        private IDAL dal;

        //PERSON    
        private const string PERSON_ADDRESS = "Address";
        private const string PERSON_NAME = "Name";
        private const string PERSON_IBAN = "ES6621000418401234567891";
        private const int  PERSON_ZIP_CODE = 46021;

        //INSTRUCTOR
        private string INSTRUCTOR_SSN = "ES0000000";

        //CITY HALL
        private const string CITY_HALL_NAME = "CityHall";

        //GYM
        private  DateTime GYM_CLOSING_HOUR = DateTime.Parse("22:00:00");
        private const int GYM_DISCOUNT_LOCAL = 10;
        private const int GYM_DISCOUNT_RETIRED = 10;
        private const double GYM_FREE_USER_PRICE = 1.50;
        private const string GYM_NAME = "Gym";
        private DateTime GYM_OPENING_HOUR = DateTime.Parse("07:00:00");
        private const int GYM_ZIP_CODE = 46021;    

        //Assigment Table NIF
        private const string MATCHES = "TRWAGMYFPDXBNJZSQVHLCKE";

        /// <summary>
        /// Creates a PopulateObject initializes the counters getting the info from the DB
        /// </summary>        
        /// <param name="initDatabase">If true, firt clears the database</param>
        /// <param name="dal">Database conexion</param>
        public Populate(bool initDatabase, IDAL dal)
        {  //DB conexion
            this.dal = dal;
            if (initDatabase)
            {
                dal.RemoveAllData();
                this.cityHallCount =0;
                this.personCount = 0;
                this.gymCount = 0;
                this.roomCount = 0;
            } 
            else 
            { 
            //Initiate counters
                this.cityHallCount = dal.GetAll<CityHall>().Count();
                this.personCount= dal.GetAll<Person>().Count(); 
                this.gymCount= dal.GetAll<Gym>().Count();
                this.roomCount = dal.GetAll<Room>().Count();
            }

        }



        /// <summary>Calculates the letter which matches with a dni number. </summary>
        /// <param name="dni"> DNI number in string format </param>
        /// <returns>  DNI letter. </returns>
        private char NIFLetter(string dni)
        {
            Match match = new Regex(@"\b(\d{8})\b").Match(dni);
            if (match.Success)
                return MATCHES[int.Parse(dni) % 23];
            else
                throw new ArgumentException("8 digits required in DNI");
        }
        
        /// <summary>
        /// Inserts into the database a new CityHall with a default name
        /// </summary>
        /// <returns>The new CittyHall</returns>
        
        public CityHall InsertCityHall()
        {
            cityHallCount++;
            CityHall cityHall = new CityHall(CITY_HALL_NAME);
            dal.Insert(cityHall);
            dal.Commit();

            return cityHall;
        }
                /// <summary>
        /// Inserts into the database  new CityHalls with a default name
        /// </summary>
        /// <returns>A colection with new CittyHalls</returns>
        public ICollection<CityHall> InsertCityHalls(int numberNewCityHalls)
        {
             ICollection < CityHall > cityHalls = new List<CityHall>();

            for (int i = 0; i < numberNewCityHalls; i++)
                cityHalls.Add(InsertCityHall());

            return cityHalls;

        }

        /// <summary>
        /// Inserts into the database one instructor and returns it. The id is based in the counter of persons in the system
        /// </summary>
        /// <param name="cityHall">The citiHall which containg the gym. It must be previously inserted in the dal</param>
        /// <returns>The new instructor</returns>
        public Instructor InsertInstructor(CityHall cityHall)
        {
            personCount++;
            string personId = personCount.ToString("D8"); //eight digits
         

            if (personId.Length <= 8)
            {
                char letter = NIFLetter(personId);
                personId = personId + letter;//adds the corresponding letter
                Instructor instructor = new Instructor(PERSON_ADDRESS + personCount, PERSON_IBAN, personId, PERSON_NAME + personCount, PERSON_ZIP_CODE, INSTRUCTOR_SSN);
                dal.Insert(instructor);
                cityHall.People.Add(instructor);
                dal.Commit();

                return instructor;
            }
            else
                throw new ArgumentOutOfRangeException("only 8 digits required in DNI");
        }
        /// <summary>
        /// Inserts into the database new instructorors and returns them. The id is based in the counter of persons in the system
        /// </summary>
        /// <param name="cityHall">The citiHall which containg the gym. It must be previously inserted in the dal</param>
        /// <returns>A collection with new instructors</returns>
        public ICollection<Instructor> InsertInstructors(int numberNewInstructors, CityHall cityHall)
        {
            ICollection<Instructor> newInstructors = new List<Instructor>();

            for (int i = 0;i < numberNewInstructors; i++)            
                newInstructors.Add(InsertInstructor(cityHall));                   

            return newInstructors;

        }

        /// <summary>
        /// Inserts a new gym in the DB associated to cityHall
        /// </summary>
        /// <param name="cityHall">The citiHall which containg the gym. It must be previously inserted in the dal</param>
        /// <returns>Gym inserted</returns>

        public Gym InsertGym( CityHall cityHall)
        {
            gymCount++;
            Gym gym = new Gym(GYM_CLOSING_HOUR, GYM_DISCOUNT_LOCAL, GYM_DISCOUNT_RETIRED,
                GYM_FREE_USER_PRICE, GYM_NAME+gymCount, GYM_OPENING_HOUR, GYM_ZIP_CODE);
            dal.Insert(gym);
            cityHall.Gyms.Add(gym);
            dal.Commit();
            return gym;

        }
		/// <summary>
        /// Inserts gyms in the DB associated to cityHall
        /// </summary>
        /// <param name="numberNewGyms">Number of gyms to insert </param>
        /// <param name="cityHall">The citiHall which containg the gym. It must be previously inserted in the dal</param>
        /// <returns>A collection with the gyms inserted</returns>
        public ICollection<Gym> InsertGyms(int numberNewGyms, CityHall cityHall)
        {
            ICollection<Gym> newGyms = new List<Gym>();
            for (int i = 0; i < numberNewGyms; i++)
                newGyms.Add(InsertGym(cityHall));

            return newGyms;

        }
        
        /// <summary>
        /// Inserts a new room in the DB
        /// </summary>
        /// <param name="gym">Gym which sontains the room, previously inserted in the dal</param>
        /// <returns>Room inserted</returns>
        public Room InsertRoom(Gym gym)
        {
            roomCount++;
            Room room = new Room(roomCount);
            gym.Rooms.Add(room); 
            dal.Insert(room);
            dal.Commit();

            return room;
        }
		/// <summary>
        /// Inserts new rooma in the DB
        /// </summary>
        /// <param name="gym">Gym which contains the room, previously inserted in the dal</param>
        /// <returns>A collection with the rooms inserted</returns>
        public ICollection<Room> InsertRooms(int numberNewRooms, Gym gym)
        {
            ICollection<Room> newRooms = new List<Room>();
            for (int i = 0; i < numberNewRooms; i++)
                newRooms.Add(InsertRoom(gym));
            return newRooms;
        }


    }
    

    
}
